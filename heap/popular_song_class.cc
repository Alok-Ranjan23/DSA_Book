/**
 * @file popular_song_class.cc
 * @brief Determine if a Song is Popular using Two-Heap Median Tracking
 * 
 * This file implements a class that tracks song popularity by comparing
 * play counts against the running median. Uses the classic two-heap
 * approach to maintain median in O(1) time.
 * 
 * Key Concepts:
 * - Running Median: The middle value of all registered play counts
 * - Two-Heap Approach: Max-heap for lower half, min-heap for upper half
 * - Popular: A song is popular if its plays exceed the median
 * 
 * Two-Heap Median Algorithm:
 * - max_pq: stores the smaller half (max at top = median candidate)
 * - min_pq: stores the larger half (min at top = median candidate)
 * - Invariant: |max_pq| == |min_pq| or |max_pq| == |min_pq| + 1
 * - Median = max_pq.top() if odd count, else average of both tops
 * 
 * Time Complexities:
 * - register_plays(): O(log n) - heap insertions and rebalancing
 * - is_popular():     O(1) - just compare against stored median
 * 
 * Space Complexity: O(n) - storing all play counts in heaps + map
 */

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <vector>
using namespace std;

/**
 * @class PopularSongs
 * @brief Tracks songs and determines popularity based on median play count
 * 
 * A song is "popular" if its play count is strictly greater than the
 * median of all registered play counts.
 * 
 * Uses the two-heap technique for efficient median maintenance:
 * - Left heap (max-heap): stores smaller half of values
 * - Right heap (min-heap): stores larger half of values
 */
class PopularSongs {
  unordered_map<string,int> umap;   // Maps song title -> play count
  priority_queue<int> max_pq;        // Max-heap: smaller half (left side)
  priority_queue<int,vector<int>,greater<int>> min_pq;  // Min-heap: larger half (right side)
  
  public:
  /**
   * @brief Registers a song with its play count
   * @param title Song title (unique)
   * @param plays Number of times the song was played
   * 
   * Algorithm:
   * 1. Store (title, plays) in hash map for O(1) lookup
   * 2. Add plays to max_pq (left heap)
   * 3. Balance: move max_pq's top to min_pq
   * 4. Rebalance if min_pq grows too large
   * 
   * Invariant maintained: |max_pq| >= |min_pq|
   * This ensures median is always max_pq.top() for odd count.
   * 
   * Time Complexity: O(log n)
   */
  void register_plays(const string& title, int plays);
  
  /**
   * @brief Checks if a song is popular (plays > median)
   * @param title Song title to check
   * @return true if song's plays exceed the median, false otherwise
   * 
   * Median calculation:
   * - Odd count: median = max_pq.top()
   * - Even count: median = (max_pq.top() + min_pq.top()) / 2
   * 
   * Time Complexity: O(1)
   */
  bool is_popular(const string& title);
};

/*============================================================================
 * IMPLEMENTATION SECTION
 *============================================================================*/

/**
 * register_plays() - Add song to tracking system
 * 
 * The balancing logic ensures the two heaps stay balanced:
 * 1. Always add to max_pq first
 * 2. Move the max to min_pq (ensures max_pq has smaller values)
 * 3. If min_pq got too big, move one back to max_pq
 * 
 * This guarantees max_pq.top() is the lower median.
 */
//O(logn)
void PopularSongs::register_plays(const string& title, int plays) {
  umap[title] = plays;
  max_pq.push(plays);
  min_pq.push(max_pq.top());max_pq.pop();
  if(max_pq.size()<min_pq.size()) {
    max_pq.push(min_pq.top());min_pq.pop();
  }
}

/**
 * is_popular() - Check if song exceeds median plays
 * 
 * A song is popular if playCount > median.
 * Note: The comparison is STRICTLY greater than, not >=.
 * 
 * Median logic:
 * - If sizes differ (odd total): median = max_pq.top()
 * - If sizes equal (even total): median = average of both tops
 *   (integer division is used)
 */
//O(1)
bool PopularSongs::is_popular(const string& title) {
  if(!umap.count(title)) return false;
  int playCount = umap[title];
  int median = (max_pq.size()>min_pq.size())?max_pq.top():(max_pq.top() + min_pq.top())/2;
  return median<playCount;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  PopularSongs p = PopularSongs();
  cout<<boolalpha;
  
  // Register first song: median = 193
  p.register_plays("Boolean Rhapsody", 193);
  cout<<p.is_popular("Boolean Rhapsody")<<"\n"; // Returns False (193 not > 193)
  
  // Register more songs: sorted = [132, 140, 193], median = 140
  p.register_plays("Coding In The Deep", 140);
  p.register_plays("All the Single Brackets", 132);
  cout<<p.is_popular("Boolean Rhapsody")<<"\n"; // Returns True (193 > 140)
  cout<<p.is_popular("Coding In The Deep")<<"\n"; // Returns False (140 not > 140)
  cout<<p.is_popular("All the Single Brackets")<<"\n"; // Returns False (132 not > 140)
  
  // Register more songs: sorted = [132, 140, 193, 223, 274, 291]
  // Median = (193 + 223) / 2 = 208
  p.register_plays("All About That Base Case", 291);
  p.register_plays("Oops! I Broke Prod Again", 274);
  p.register_plays("Here Comes The Bug", 223);
  cout<<p.is_popular("Boolean Rhapsody")<<"\n"; // Returns False (193 not > 208)
  cout<<p.is_popular("Here Comes The Bug")<<"\n"; // Returns True (223 > 208)
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Popular Songs Class
 * 
 * Implement a `PopularSongs` class that has two methods:
 * 
 * - `register_plays(title, plays)` indicates that a song was played a 
 *   given number of times. It returns nothing. The method is never called 
 *   with the same title twice.
 * - `is_popular(title)` returns whether the given song is popular. A song 
 *   is _popular_ if its play count is strictly higher than the median 
 *   play count.
 * 
 * The median of a collection of integers with odd size is the middle 
 * element in sorted order; if the size is even, the median is the average 
 * of the two middle elements.
 * 
 * Example:
 * p = PopularSongs()
 * p.register_plays("Boolean Rhapsody", 193)
 * p.is_popular("Boolean Rhapsody")                   # Returns False
 * p.register_plays("Coding In The Deep", 140)
 * p.register_plays("All the Single Brackets", 132)
 * p.is_popular("Boolean Rhapsody")                   # Returns True
 * p.is_popular("Coding In The Deep")                 # Returns False
 * p.is_popular("All the Single Brackets")            # Returns False
 * p.register_plays("All About That Base Case", 291)
 * p.register_plays("Oops! I Broke Prod Again", 274)
 * p.register_plays("Here Comes The Bug", 223)
 * p.is_popular("Boolean Rhapsody")                   # Returns False
 * p.is_popular("Here Comes The Bug")                 # Returns True
 * 
 * Analyze the space and runtime of each operation in terms of the number 
 * of songs registered so far. The goal is to minimize the total runtime 
 * assuming we will make the same number of operations of each type.
 * 
 * Constraints:
 * - Song titles are unique and have at most `50` characters.
 * - The number of plays is at least `1` and at most `10^9`.
 * - The number of registered songs is at most `10^5`.
 * 
 *============================================================================*/
