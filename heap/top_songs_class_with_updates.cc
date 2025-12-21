/**
 * @file top_songs_class_with_updates.cc
 * @brief Top K Songs Class with Cumulative Play Count Updates
 * 
 * This file implements a class that tracks the top k most played songs,
 * supporting cumulative updates to play counts. Unlike top_songs_class.cc,
 * the same song can be registered multiple times with plays being ADDED.
 * 
 * Key Concepts:
 * - Cumulative updates: Multiple registrations add to total play count
 * - Lazy deletion: Old entries remain in heap but are invalidated
 * - Hash map validation: Check if heap entry matches current play count
 * 
 * Challenge with Updates:
 * - Standard heap doesn't support efficient decrease/increase key
 * - Solution: Push new entry with updated count, validate during extraction
 * 
 * Algorithm (Lazy Deletion):
 * 1. On register_plays: Update map with new total, push new heap entry
 * 2. On top_k: Pop entries, skip stale ones (map value != heap value)
 * 3. Re-push valid entries to maintain heap state
 * 
 * Time Complexities:
 * - register_plays(): O(log n) - single heap push
 * - top_k():          O(m log n) where m is stale entries encountered
 *                     Amortized O(k log n) over many calls
 * 
 * Space Complexity: O(n) - map + heap (heap may have stale entries)
 */

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

/**
 * @class TopSongs
 * @brief Tracks top k songs with support for cumulative play updates
 * 
 * Features:
 * - Same song can be registered multiple times (plays accumulate)
 * - Uses max-heap with lazy deletion for efficient updates
 * - Hash map stores authoritative play counts
 */
class TopSongs {
  int k_;                            // Number of top songs to track
  priority_queue<pair<int,string>> pq;  // Max-heap: (plays, title)
  unordered_map<string,int> umap;    // Authoritative play counts
  
  public:
  /**
   * @brief Constructor - initializes with k value
   * @param k Number of top songs to return
   */
  TopSongs(int k);
  
  /**
   * @brief Registers play count for a song (cumulative)
   * @param title Song title
   * @param count Number of new plays to add
   * 
   * If song was previously registered, count is ADDED to existing total.
   * Pushes new entry to heap (old entries become stale but remain).
   * 
   * Time Complexity: O(log n)
   */
  void register_plays(const string&,int);
  
  /**
   * @brief Returns titles of the k most played songs
   * @return Vector of up to k song titles with highest play counts
   * 
   * Uses lazy deletion: validates heap entries against map.
   * Re-pushes valid entries to maintain heap state for future calls.
   * 
   * Time Complexity: O(m log n) where m is stale entries + k
   */
  vector<string> top_k();
};

/*============================================================================
 * IMPLEMENTATION SECTION
 *============================================================================*/

/**
 * Constructor: Initialize k and empty containers
 */
TopSongs::TopSongs(int k): k_{k},pq{} {}

/**
 * register_plays() - Add plays to a song's total
 * 
 * Algorithm:
 * 1. Calculate new total (existing + new count)
 * 2. Update map with new total
 * 3. Push new entry to max-heap
 * 
 * Note: Old heap entries for this song are NOT removed.
 * They become "stale" and are filtered out in top_k().
 * 
 * Why not remove old entries?
 * - Heap doesn't support efficient arbitrary removal
 * - Lazy deletion is simpler and amortizes well
 */
void TopSongs::register_plays(const string& title,int count) {
  int newTotalPlays = count;
  if (umap.count(title)) {
    newTotalPlays += umap[title];  // Add to existing total
  }
  umap[title] = newTotalPlays;
  pq.push({newTotalPlays, title});  // Push updated entry
}

/**
 * top_k() - Extract top k songs, handling stale entries
 * 
 * Algorithm:
 * 1. Pop entries from max-heap
 * 2. For each entry, check if it's "fresh" (heap count == map count)
 * 3. If stale (counts don't match), skip it
 * 4. If fresh, add to result
 * 5. After collecting k songs, re-push them to maintain heap
 * 
 * Why re-push?
 * - We want subsequent top_k() calls to work correctly
 * - Re-pushing maintains the valid entries in the heap
 * 
 * Example of staleness:
 * - Register "Song A" with 100 plays -> heap has (100, "Song A")
 * - Register "Song A" with 50 plays -> heap has (150, "Song A") AND (100, "Song A")
 * - The (100, "Song A") entry is stale because map["Song A"] = 150
 */
vector<string> TopSongs::top_k() {
  vector<string> res;
  
  while (res.size() < static_cast<size_t>(k_) && !pq.empty()) {
    auto [count, title] = pq.top();  // Structured binding (C++17)
    pq.pop();
    
    // Validate: is this entry current?
    if (umap[title] == count) {
      res.push_back(title);  // Fresh entry - include in result
    }
    // Stale entry - skip (implicitly deleted)
  }
  
  // Re-push valid entries to maintain heap for future calls
  for (const auto& title : res) {
    pq.push({umap[title], title});
  }
  
  return res;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  TopSongs s = TopSongs(3);
  
  // Multiple registrations for same song - plays accumulate
  s.register_plays("Boolean Rhapsody", 100);
  s.register_plays("Boolean Rhapsody", 193);  // Total: 293
  s.register_plays("Coding In The Deep", 75);
  s.register_plays("Coding In The Deep", 75);  // Total: 150
  s.register_plays("All About That Base Case", 200);
  s.register_plays("All About That Base Case", 90);  // Total: 290
  s.register_plays("All About That Base Case", 1);   // Total: 291
  s.register_plays("Here Comes The Bug", 223);
  s.register_plays("Oops! I Broke Prod Again", 274);
  s.register_plays("All the Single Brackets", 132);
  
  // Top 3: Boolean Rhapsody (293), All About That Base Case (291), 
  //        Oops! I Broke Prod Again (274)
  for(auto& title : s.top_k()) cout<<title<<"\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Top Songs Class With Updates
 * 
 * Implement a `TopSongs` class that receives an integer `k > 0` during 
 * initialization and has two methods:
 * 
 * - `register_plays(title, plays)` indicates that a song was played a 
 *   given number of times. It returns nothing. If the song was already 
 *   registered, the new plays should be **added** to the total number 
 *   of plays for that song.
 * - `top_k()` returns the (up to) `k` registered song titles with the 
 *   most plays, in any order, and breaking ties arbitrarily.
 * 
 * Example:
 * s = TopSongs(3)
 * s.register_plays("Boolean Rhapsody", 100)
 * s.register_plays("Boolean Rhapsody", 193)  # Total 293
 * s.register_plays("Coding In The Deep", 75)
 * s.register_plays("Coding In The Deep", 75)  # Total 150
 * s.register_plays("All About That Base Case", 200)
 * s.register_plays("All About That Base Case", 90)  # Total 290
 * s.register_plays("All About That Base Case", 1)   # Total 291
 * s.register_plays("Here Comes The Bug", 223)
 * s.register_plays("Oops! I Broke Prod Again", 274)
 * s.register_plays("All the Single Brackets", 132)
 * s.top_k()  # Returns ["All About That Base Case", "Boolean Rhapsody", 
 *            #          "Oops! I Broke Prod Again"]
 * 
 * Analyze the space and runtime of each operation in terms of the number 
 * of songs registered so far. The goal is to minimize the total runtime 
 * assuming we will make the same number of operations of each type and 
 * that `k` will be relatively small compared to the number of songs.
 * 
 * Constraints:
 * - `0 < k < 1000`
 * - Song titles are unique and have at most `50` characters.
 * - Each time a song is registered, the number of plays is at least `1`.
 * - The total number of plays for a song never exceeds `10^9`.
 * 
 *============================================================================*/
