/**
 * @file most_played_across_genre.cc
 * @brief Find Top K Songs Across Multiple Genres using Min-Heap
 * 
 * This file solves the problem of finding the k most played songs when
 * songs are organized into multiple genre lists. Uses the same min-heap
 * approach as k_most_played.cc but handles nested data structures.
 * 
 * Key Concepts:
 * - Min-heap of size k: efficient tracking of k largest elements
 * - Flattening nested structures: process all songs from all genres
 * - Same "Top K" pattern applied to multi-dimensional input
 * 
 * Algorithm:
 * 1. Iterate through all genres
 * 2. For each genre, iterate through all songs
 * 3. Push each song (plays, title) into min-heap
 * 4. If heap size exceeds k, pop the minimum (least played)
 * 5. After processing all songs, heap contains k most played
 * 
 * Note: Although input lists are pre-sorted within each genre, we don't
 * leverage this property. An optimized version could use a k-way merge.
 * 
 * Time Complexity: O(n log k) where n is total songs across all genres
 * Space Complexity: O(k) - only store k elements in heap
 */

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/**
 * @brief Finds the k most played songs across all genre lists
 * @param inputs Vector of genre lists, each containing (title, plays) pairs
 * @param k Number of top songs to return
 * @return Vector of song titles (k most played, in any order)
 * 
 * Implementation Details:
 * - Flattens the nested structure with two loops
 * - Uses min-heap to track k largest play counts
 * - Returns titles extracted from heap
 * 
 * Time Complexity: O(n log k) where n = total songs
 * Space Complexity: O(k)
 */
vector<string> top_k(vector<vector<pair<string, int>>>& inputs, int k) {
  vector<string> title;
  
  // Min-heap: smallest play count at top
  // Pair: (plays, title) - plays first for proper ordering
  priority_queue<pair<int,string>,vector<pair<int,string>>,greater<pair<int,string>>> pq;
  
  // Process all songs from all genres
  for(auto& vec: inputs) {
    for(auto& p: vec) {
      pq.push({p.second,p.first});  // Push (plays, title)
      
      // Maintain heap size at k
      if(pq.size()>static_cast<size_t>(k)) pq.pop();
    }
  }
  
  // Extract remaining k songs from heap
  while(!pq.empty()) {
    title.push_back(pq.top().second);
    pq.pop();
  }
  return title;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  // Songs organized by genre: Pop, Country, Rock
  // Each genre list is sorted by plays (descending)
  vector<vector<pair<string, int>>> inputs {
    {
      {"Coding In The Deep", 123},      // Pop - most played in genre
      {"Someone Like GNU",99},
      {"Hello World", 98}
    },
    {
      {"Ring Of Firewalls",  217}        // Country - only one song
    },
    {
      {"Boolean Rhapsody", 184},         // Rock - most played in genre
      {"Merge Together", 119},
      {"Hey Queue", 102}
    }
  };
  
  int k=5;
  
  // Expected output: Top 5 across all genres by play count
  // 217, 184, 123, 119, 102 -> corresponding titles
  for(auto& title: top_k(inputs,k)) cout<<title<<"\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Most Listened Across Genres
 * 
 * You are given an array, `genres`, of length `m`, where each element is 
 * an array of songs from a given genre. Each song consists of a 
 * `[title, plays]` pair.
 * 
 * - Each list is non-empty and **already sorted** from most to least 
 *   played songs.
 * - There are `n > 0` songs in total, and each song appears in at most 
 *   one list.
 * 
 * You are also given a positive integer `k` satisfying `1 <= k <= n`. 
 * Return the titles of the top `k` most-listened songs across all genres, 
 * in order from most to least listened. It doesn't matter how you break ties.
 * 
 * Example:
 * genres = [
 *   [ # Pop
 *     ["Coding In The Deep", 123],
 *     ["Someone Like GNU",    99],
 *     ["Hello World",         98]
 *   ],
 *   [ # Country
 *     ["Ring Of Firewalls",  217]
 *   ],
 *   [ # Rock
 *     ["Boolean Rhapsody",   184],
 *     ["Merge Together",     119],
 *     ["Hey Queue",          102]
 *   ]
 * ]
 * k = 5
 * Output: [
 *   "Ring Of Firewalls",      (217 plays)
 *   "Boolean Rhapsody",       (184 plays)
 *   "Coding In The Deep",     (123 plays)
 *   "Merge Together",         (119 plays)
 *   "Hey Queue"               (102 plays)
 * ]
 * 
 * Constraints:
 * - The length of `genres`, `m`, is at least `1` and at most `10^5`.
 * - The total number of songs, `n`, is at least `1` and at most `10^5`.
 * - Song titles are unique and have at most `50` characters.
 * - Each genre list is already sorted from most to least played songs.
 * - `1 <= k <= n`.
 * 
 *============================================================================*/
