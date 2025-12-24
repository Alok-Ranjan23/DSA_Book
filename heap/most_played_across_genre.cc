/**
 * @file most_played_across_genre.cc
 * @brief Top K Songs Across Multiple Genres using K-Way Merge with Max-Heap
 * 
 * This file implements a function that finds the top k most-listened songs
 * across multiple genre lists, where each genre list is already sorted
 * by play count in descending order.
 * 
 * Key Concepts:
 * - K-Way Merge: Classic technique for merging m sorted lists
 * - Max-Heap: Efficiently extracts the global maximum from m candidates
 * - Lazy Loading: Only one song per genre in the heap at any time
 * 
 * Algorithm:
 * 1. Initialize heap with first (most-played) song from each genre
 * 2. Pop the maximum (globally most-played song)
 * 3. Push the next song from that same genre (if any remain)
 * 4. Repeat until we have k songs
 * 
 * Why this works:
 * - Since each genre list is pre-sorted, the next candidate from any genre
 *   is always the front element of that genre's remaining list
 * - The heap always contains at most m elements (one per genre)
 * - We always extract the global maximum efficiently
 * 
 * Time Complexities:
 * - Initialization:  O(m log m) - push m elements to heap
 * - Main Loop:       O(k log m) - k iterations, each with pop/push O(log m)
 * - Total:           O(m log m + k log m) = O((m + k) log m)
 * 
 * Space Complexity: O(m) - heap stores at most one song per genre
 */

#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

/*============================================================================
 * FUNCTION IMPLEMENTATION
 *============================================================================*/

/**
 * @brief Finds the top k most-listened songs across all genres
 * @param genres Vector of genre lists, each containing (title, plays) pairs
 *               Each genre list is pre-sorted by plays (descending)
 * @param k Number of top songs to return
 * @return Vector of k song titles with highest play counts
 * 
 * Heap Structure: {{plays, title}, genre_index}
 * - plays is first for max-heap ordering by play count
 * - genre_index tracks which list the song came from
 * 
 * Time Complexity: O((m + k) log m) where m = number of genres
 */
vector<string> most_listened_across_genres(vector<vector<pair<string,int>>>& genres, int k) {
  vector<string> res;
  
  // Max-heap: {{plays, title}, genre_index}
  // Default priority_queue is max-heap, orders by plays (first element)
  priority_queue<pair<pair<int,string>,int>> pq;
  
  int n = genres.size();  // m = number of genres
  
  // Step 1: Initialize heap with first song from each genre
  // Each genre's first song is its most-played (pre-sorted)
  for(int i=0;i<n;++i) {
    pq.push({{genres[i][0].second,genres[i][0].first},i});
  }
  
  // Track current index in each genre's song list
  vector<int> index_vec(n,0);
  
  // Step 2-4: Extract max, push next from same genre, repeat
  while(!pq.empty()) {
    // Pop globally most-played song
    auto p = pq.top(); pq.pop();
    res.push_back(p.first.second);
    
    // Done if we have k songs
    if(res.size()==static_cast<size_t>(k)) break;
    
    // Push next song from the same genre (if available)
    int index = p.second;
    int j = ++index_vec[index];
    if(static_cast<size_t>(j)==genres[index].size()) continue;
    pq.push({{genres[index][j].second,genres[index][j].first},index});
  }
  
  return res;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  // Test data: 3 genres with songs sorted by plays (descending)
  vector<vector<pair<string,int>>> genres {
    {  // Pop
      {"Coding In The Deep", 123},
      {"Someone Like GNU", 99},
      {"Hello World", 98}
    },
    {  // Country
      {"Ring Of Firewalls", 217}
    },
    {  // Rock
      {"Boolean Rhapsody", 184},
      {"Merge Together", 119},
      {"Hey Queue", 102}
    }
  };
  
  int k = 5;
  
  // Expected output (top 5 by plays):
  // 1. Ring Of Firewalls  (217)
  // 2. Boolean Rhapsody   (184)
  // 3. Coding In The Deep (123)
  // 4. Merge Together     (119)
  // 5. Hey Queue          (102)
  for(auto& x : most_listened_across_genres(genres, k)) {
    cout << x << "\n";
  }
  
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
 * - Each list is non-empty and **already sorted** from most to least played.
 * - There are `n > 0` songs in total, and each song appears in at most one list.
 * 
 * You are also given a positive integer `k` satisfying `1 <= k <= n`. 
 * Return the titles of the top `k` most-listened songs across all genres, 
 * in order from most to least listened. Ties can be broken arbitrarily.
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
 *   "Ring Of Firewalls",
 *   "Boolean Rhapsody",
 *   "Coding In The Deep",
 *   "Merge Together",
 *   "Hey Queue"
 * ]
 * 
 * Constraints:
 * - The length of `genres`, `m`, is at least `1` and at most `10^5`.
 * - The total number of songs, `n`, is at least `1` and at most `10^5`.
 * - Song titles are unique and have at most `50` characters.
 * - Each genre list is already sorted from most to least played (ties allowed).
 * - `1 <= k <= n`.
 * 
 *============================================================================*/