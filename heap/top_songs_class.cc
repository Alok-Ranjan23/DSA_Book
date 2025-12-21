/**
 * @file top_songs_class.cc
 * @brief Top K Songs Class using Min-Heap (No Updates)
 * 
 * This file implements a class that tracks the top k most played songs.
 * Each song is registered exactly once (no cumulative updates).
 * Uses a min-heap of size k for efficient tracking.
 * 
 * Key Concepts:
 * - Min-heap of size k: always contains the k highest values seen
 * - When new song exceeds heap's minimum, replace the minimum
 * - More memory efficient than storing all songs
 * 
 * Algorithm:
 * 1. Push new song (plays, title) into min-heap
 * 2. If heap size exceeds k, pop the minimum
 * 3. For top_k(), extract all elements from heap copy
 * 
 * This is simpler than top_songs_class_with_updates.cc because:
 * - Each song is registered only once
 * - No need for hash map validation
 * - No stale entries to handle
 * 
 * Time Complexities:
 * - Constructor:       O(1)
 * - register_plays():  O(log k) - single heap operation
 * - top_k():           O(k log k) - extract k elements
 * 
 * Space Complexity: O(k) - only store k elements in heap
 */

#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

/**
 * @class TopSongs
 * @brief Tracks top k songs using a fixed-size min-heap
 * 
 * Uses a min-heap to efficiently maintain only the k highest
 * play counts. Songs are registered exactly once (no updates).
 * 
 * Why min-heap for finding maximums?
 * - Heap keeps the k largest elements
 * - Min-heap lets us quickly identify and remove the smallest
 *   among our k candidates when a larger element arrives
 */
class TopSongs {
  int k_;    // Number of top songs to track
  
  // Min-heap: (plays, title) - smallest plays at top
  priority_queue<pair<int,string>,vector<pair<int,string>>, greater<pair<int,string>>> pq;
  
  public:
  /**
   * @brief Constructor - initializes with k value
   * @param k Number of top songs to return
   * 
   * Time Complexity: O(1)
   */
  TopSongs(int k); // O(1)
  
  /**
   * @brief Registers a song with its play count (one-time only)
   * @param title Song title (must be unique, never called twice)
   * @param count Number of plays
   * 
   * Maintains heap size at k by removing minimum when exceeded.
   * 
   * Time Complexity: O(log k)
   */
  void register_plays(const string&,int); // O(logk)
  
  /**
   * @brief Returns titles of the k most played songs
   * @return Vector of up to k song titles with highest play counts
   * 
   * Creates a copy of heap to preserve original for future calls.
   * Elements are returned in ascending order of plays (min first).
   * 
   * Time Complexity: O(k + k log k) = O(k log k)
   */
  vector<string> top_k(); // O(k+klogk)
};

/*============================================================================
 * IMPLEMENTATION SECTION
 *============================================================================*/

/**
 * Constructor: Initialize k and empty heap
 */
TopSongs::TopSongs(int k): k_{k},pq{} {}

/**
 * register_plays() - Add a new song to tracking
 * 
 * Algorithm:
 * 1. Push new song to min-heap
 * 2. If heap now has more than k elements, pop the minimum
 * 
 * The minimum is always the song with fewest plays among
 * the current top candidates. By removing it when a new
 * song arrives, we maintain exactly the k highest.
 * 
 * Example with k=3:
 * - Push 100 -> heap: [100]
 * - Push 50  -> heap: [50, 100]
 * - Push 200 -> heap: [50, 100, 200]
 * - Push 150 -> heap: [50, 100, 150, 200] -> pop 50 -> [100, 150, 200]
 */
void TopSongs::register_plays(const string& title,int count) {
  pq.push({count,title});
  if(pq.size()>static_cast<size_t>(k_)) pq.pop();  // Remove smallest
}

/**
 * top_k() - Extract top k songs
 * 
 * Creates a temporary copy of the heap to preserve state.
 * Extracts elements in order (smallest first due to min-heap).
 * 
 * Note: Elements are returned in ascending order of plays,
 * but the problem allows any order.
 */
vector<string> TopSongs::top_k() {
  int temp = k_;
  
  // Copy heap to preserve original for future top_k() calls
  priority_queue<pair<int,string>,vector<pair<int,string>>, greater<pair<int,string>>> pq_temp = pq;
  
  vector<string> res;
  while(!pq_temp.empty() && temp--) {
    res.push_back(pq_temp.top().second);
    pq_temp.pop();
  }
  return res;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  TopSongs s = TopSongs(3);
  
  // Register songs (each title only once)
  s.register_plays("Boolean Rhapsody", 193);
  s.register_plays("Coding In The Deep", 146);
  
  // With only 2 songs, returns both
  for(auto&title: s.top_k()) cout<<title<<"\n";  // Returns ["Coding In The Deep", "Boolean Rhapsody"]
  cout<<"----------------\n";
  
  // Register more songs
  s.register_plays("All About That Base Case", 291);
  s.register_plays("Here Comes The Bug", 223);
  s.register_plays("Oops! I Broke Prod Again", 274);
  s.register_plays("All the Single Brackets", 132);
  
  // Top 3: 291, 274, 223 plays
  for(auto& title: s.top_k()) cout<<title<<"\n"; 
  cout<<"----------------\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Top Songs Class
 * 
 * Implement a `TopSongs` class that receives an integer `k > 0` during 
 * initialization and has two methods:
 * 
 * - `register_plays(title, plays)` indicates that a song was played a 
 *   given number of times. It returns nothing. The method is never called 
 *   with the same title twice.
 * - `top_k()` returns the (up to) `k` registered song titles with the 
 *   most plays, in any order, and breaking ties arbitrarily.
 * 
 * Example:
 * s = TopSongs(3)
 * s.register_plays("Boolean Rhapsody", 193)
 * s.register_plays("Coding In The Deep", 146)
 * s.top_k()  # Returns ["Coding In The Deep", "Boolean Rhapsody"]
 * s.register_plays("All About That Base Case", 291)
 * s.register_plays("Here Comes The Bug", 223)
 * s.register_plays("Oops! I Broke Prod Again", 274)
 * s.register_plays("All the Single Brackets", 132)
 * s.top_k()  # Returns ["All About That Base Case", "Here Comes The Bug", 
 *            #          "Oops! I Broke Prod Again"]
 * 
 * Analyze the space and runtime of each operation in terms of the number 
 * of songs registered so far. The goal is to minimize the total runtime 
 * assuming we will make the same number of operations of each type and 
 * that `k` will be relatively small compared to the number of songs.
 * 
 * Constraints:
 * - `0 < k < 1000`.
 * - Song titles are unique and have at most `50` characters.
 * - The number of plays is at least `1` and at most `10^9`.
 * - Song titles are unique and have at most `50` characters.
 * 
 *============================================================================*/
