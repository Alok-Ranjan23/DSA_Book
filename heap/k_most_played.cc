/**
 * @file k_most_played.cc
 * @brief Find K Most Played Songs using a Min-Heap
 * 
 * This file solves the "Top K Elements" problem for song play counts.
 * Uses a min-heap of size k to efficiently track the k most played songs.
 * 
 * Key Concepts:
 * - Min-heap of size k: keeps the k largest elements seen so far
 * - When a new element is larger than heap's min, replace the min
 * - This is more efficient than sorting when k << n
 * 
 * Algorithm:
 * 1. Iterate through all songs
 * 2. Push each song (plays, title) into min-heap
 * 3. If heap size exceeds k, pop the minimum (least played)
 * 4. After processing all songs, heap contains k most played
 * 
 * Why Min-Heap for finding maximums?
 * - We want to keep track of the k LARGEST elements
 * - Min-heap allows quick removal of the SMALLEST in our k candidates
 * - When we find a larger element, we can efficiently replace the smallest
 * 
 * Time Complexity: O(n log k)
 * - Each of n songs: push O(log k) + potential pop O(log k)
 * - Better than O(n log n) when k << n
 * 
 * Space Complexity: O(k) - only store k elements in heap
 */

#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

/**
 * @brief Finds the k most played songs from a list
 * @param songs Vector of (title, plays) pairs
 * @param k Number of top songs to return
 * @return Vector of song titles (k most played, in any order)
 * 
 * Implementation Details:
 * - Uses priority_queue with greater<> comparator for min-heap
 * - Stores pairs as (plays, title) for proper comparison by plays
 * - Returns titles in reverse order of extraction (min to max)
 * 
 * Time Complexity: O(n log k)
 * Space Complexity: O(k)
 */
/*
Time  Complexity: O(nlogk)
Space Complexity: O(k)
*/
vector<string> k_most_played(vector<pair<string,int>>& songs, int k) {
  vector<string> res;
  
  // Min-heap: smallest play count at top
  // Pair: (plays, title) - plays first for proper ordering
  priority_queue<pair<int,string>,vector<pair<int,string>>,greater<pair<int,string>>> pq;
  
  for(auto& p : songs) {
    pq.push({p.second,p.first});  // Push (plays, title)
    
    // Maintain heap size at k by removing minimum when exceeded
    if(pq.size()>static_cast<size_t>(k)) pq.pop();
  }
  
  // Extract remaining k songs from heap
  while(!pq.empty()) {
    res.push_back(pq.top().second);
    pq.pop();
  }
  return res;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  // Sample songs with play counts
  vector<pair<string,int>> songs {
    {"All the Single Brackets", 132},
    {"Oops! I Broke Prod Again", 274},
    {"Coding In The Deep", 146},
    {"Boolean Rhapsody", 193},
    {"Here Comes The Bug", 291},
    {"All About That Base Case", 291}};
  
  int k = 3;
  
  // Expected: The three songs with highest plays (291, 291, 274)
  // Output order may vary
  for(auto& song: k_most_played(songs,k)) cout<<song<<"\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # K Most Played
 * 
 * You are given a list of `(title, plays)` tuples where the first element 
 * is the name of a song, and the second is the number of times the song 
 * has been played. You are also given a positive integer `k`. Return the 
 * `k` most played songs from the list, in any order.
 * 
 * - If the list has fewer than `k` songs, return all of them.
 * - Break ties in any way you want.
 * - You can assume that song titles have a length of at most `50`.
 * 
 * Example:
 * songs = [["All the Single Brackets", 132],
 *          ["Oops! I Broke Prod Again", 274],
 *          ["Coding In The Deep", 146],
 *          ["Boolean Rhapsody", 193],
 *          ["Here Comes The Bug", 291],
 *          ["All About That Base Case", 291]]
 * k = 3
 * Output: ["All About That Base Case", "Here Comes The Bug", 
 *          "Oops! I Broke Prod Again"] (any order valid)
 * 
 * Follow-up: Can you solve it using only `O(k)` space?
 * Answer: Yes! This solution uses O(k) space with a min-heap.
 * 
 * Constraints:
 * - The length of `songs` is at most `10^5`
 * - Each element in `songs` is a tuple with a string and an integer
 * - All song titles are unique
 * - The length of the string in each song is at most `50`
 * - `1 <= k <= 10^5`
 * 
 *============================================================================*/
