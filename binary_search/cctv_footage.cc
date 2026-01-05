/**
 * @file cctv_footage.cc
 * @brief Binary Search to find transition point using an API
 * 
 * This file implements binary search to find the first timestamp when
 * a condition becomes true (bike gets stolen), given only an API to
 * query the state at any timestamp.
 * 
 * Key Concepts:
 * - Binary search on answer space (not array indices)
 * - Finding transition point (first True in [False, False, ..., True, True])
 * - Minimizing API calls using binary search
 * - Using std::function for callback/predicate
 * 
 * Time Complexity: O(log(t2 - t1)) API calls
 * Space Complexity: O(1)
 * 
 * Algorithm Pattern: Binary Search for First True (Lower Bound)
 * 
 * Real-world analogy: Like finding the exact frame in video footage
 * where an event occurs, without watching the entire video.
 */

#include <iostream>
#include <functional>
#include <type_traits>
using namespace std;

/*============================================================================
 * BINARY SEARCH FOR TRANSITION POINT
 *============================================================================*/

/**
 * @brief Finds the first timestamp when the bike was stolen
 * @param t1 Start timestamp (bike was present here, is_stolen(t1) = false)
 * @param t2 End timestamp (bike was missing here, is_stolen(t2) = true)
 * @param is_stolen Function that returns true if bike is missing at time t
 * @return First timestamp where is_stolen returns true
 * 
 * Algorithm (Binary Search for First True):
 * 1. Initialize search range [l=t1, h=t2]
 * 2. While l <= h:
 *    a. Calculate mid = (l + h) / 2
 *    b. If is_stolen(mid) is true AND mid is the leftmost possible:
 *       - Return mid (found the transition point)
 *    c. If is_stolen(mid) is true:
 *       - Record mid as potential answer, search left (h = mid - 1)
 *    d. If is_stolen(mid) is false:
 *       - Search right (l = mid + 1)
 * 3. Return the recorded answer
 * 
 * Invariant: 
 * - Everything to the left of answer is False
 * - Everything at answer and to the right is True
 * 
 * Visual (t1=1, t2=5, stolen at t>=3):
 *   t:        1    2    3    4    5
 *   stolen:   F    F    T    T    T
 *                       ^-- Find this transition point
 */
int cctv_footage(int t1, int t2, function<bool(int)> is_stolen) {
  int l = t1;
  int h = t2;
  int ans = -1;
  
  while(l <= h) {
    int mid = (l + h) >> 1;                   // Midpoint of search range
    bool is_bike_stolen = is_stolen(mid);     // Query the API
    
    // Early return if we found it and can't go any further left
    if(is_bike_stolen && mid == l) return mid;
    
    else if(is_bike_stolen) {
      ans = mid;                              // Record potential answer
      h = mid - 1;                            // Search for earlier timestamp
    }
    else {
      l = mid + 1;                            // Bike still there, search later
    }
  }
  
  return ans;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Example 1: Stolen at timestamp 3
  int t1 = 1, t2 = 5;
  auto is_stolen1 = [](int t) { return t >= 3; };
  cout << cctv_footage(t1, t2, is_stolen1) << "\n";  // Output: 3
  
  // Example 2: Stolen at timestamp 7
  t1 = 1; t2 = 10;
  auto is_stolen2 = [](int t) { return t >= 7; };
  cout << cctv_footage(t1, t2, is_stolen2) << "\n";  // Output: 7
  
  // Example 3: Stolen at timestamp 8
  t1 = 5; t2 = 10;
  auto is_stolen3 = [](int t) { return t >= 8; };
  cout << cctv_footage(t1, t2, is_stolen3) << "\n";  // Output: 8
  
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT
 *============================================================================
 * 
 * # CCTV Footage
 * 
 * You are given an API called `is_stolen(t)` which takes a timestamp as 
 * input and returns `True` if the bike is missing at that timestamp and 
 * `False` if it is still there. You're also given two timestamps, `t1` 
 * and `t2`, representing when you parked the bike and when you found it 
 * missing. Return the timestamp when the bike was first missing, 
 * minimizing the number of API calls. Assume that `0 < t1 < t2`, 
 * `is_stolen(t1)` is `False`, and `is_stolen(t2)` is `True`.
 * 
 * Example 1: t1 = 1, t2 = 5, is_stolen = lambda t: t >= 3
 * Output: 3. The bike was stolen at timestamp 3.
 * 
 * Example 2: t1 = 1, t2 = 10, is_stolen = lambda t: t >= 7
 * Output: 7. The bike was stolen at timestamp 7.
 * 
 * Example 3: t1 = 5, t2 = 10, is_stolen = lambda t: t >= 8
 * Output: 8. The bike was stolen at timestamp 8.
 * 
 * Constraints:
 * - 0 < t1 < t2 <= 10^6
 * - The API call is_stolen(t) takes O(1) time
 * 
 *============================================================================*/
