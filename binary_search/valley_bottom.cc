/**
 * @file valley_bottom.cc
 * @brief Binary Search to find minimum in a valley-shaped (bitonic) array
 * 
 * This file implements binary search to find the minimum element in a
 * valley-shaped array - one that first decreases then increases.
 * Similar to finding a peak in a mountain array, but inverted.
 * 
 * Key Concepts:
 * - Valley-shaped array: decreasing prefix + increasing suffix
 * - Binary search on the property of "being in decreasing part"
 * - The minimum is at the transition point
 * - Using comparison with neighbors to determine which half we're in
 * 
 * Time Complexity: O(log n) - binary search
 * Space Complexity: O(1) - constant extra space
 * 
 * Algorithm Pattern: Binary Search on Answer (Finding Local Minimum)
 * 
 * Visual:
 *   Value: 6   5   4   7   9
 *   Index: 0   1   2   3   4
 *              \  /
 *               \/  <- Valley bottom (minimum) at index 2
 */

#include <iostream>
#include <vector>
using namespace std;

/*============================================================================
 * VALLEY BOTTOM SEARCH IMPLEMENTATION
 *============================================================================*/

/**
 * @brief Finds the minimum value in a valley-shaped array
 * @param arr Valley-shaped array (decreasing then increasing)
 * @return The minimum value in the array
 * 
 * Algorithm:
 * 1. Handle edge cases:
 *    - Empty array: return -1
 *    - Single element: return that element
 *    - Increasing array (prefix has 1 element): return first element
 *    - Decreasing array (suffix has 1 element): return last element
 * 
 * 2. Binary search for transition point:
 *    - Define "is_before(mid)" = true if we're still in decreasing part
 *    - This is true when arr[mid] < arr[mid-1] (still going down)
 *    - Find the last position in the decreasing part
 * 
 * Property of valley at index i:
 *   - arr[i-1] > arr[i] (coming from decreasing part)
 *   - arr[i] < arr[i+1] (leading to increasing part)
 * 
 * Visual trace for [6, 5, 4, 7, 9]:
 *   l=0, r=4
 *   arr[0]=6 > arr[1]=5 -> not purely increasing
 *   arr[4]=9 > arr[3]=7 -> not purely decreasing
 *   Binary search:
 *     mid=2: arr[2]=4 < arr[1]=5 -> in decreasing part, l=2
 *     mid=3: arr[3]=7 > arr[2]=4 -> in increasing part, r=3
 *     r-l=1, return arr[2]=4
 */
int valley_bottom(vector<int>& arr) {
  int n = arr.size();
  if(n == 0) return -1;                     // Empty array
  
  int l = 0;
  int r = n - 1;
  
  if(r == l) return arr[l];                 // Single element
  
  // Edge case: Only one element in decreasing prefix [5, 6, 7]
  if(arr[l] < arr[l + 1]) return arr[l];
  
  // Edge case: Only one element in increasing suffix [7, 6, 5]
  if(arr[r] < arr[r - 1]) return arr[r];
  
  /**
   * is_before(mid): Returns true if we're still in the decreasing part
   * - In decreasing part: arr[mid] < arr[mid-1] (value still falling)
   * - In increasing part: arr[mid] > arr[mid-1] (value rising)
   */
  auto is_before = [&](int mid) {
    return arr[mid] < arr[mid - 1];
  };

  // Binary search for transition point
  while(r - l > 1) {
    int mid = (l + r) >> 1;
    if(is_before(mid)) {
      l = mid;                              // Still in decreasing part
    } else {
      r = mid;                              // In increasing part
    }
  }
  
  return arr[l];                            // l is at the valley bottom
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Example 1: Standard valley shape
  vector<int> arr{6, 5, 4, 7, 9};
  cout << valley_bottom(arr) << "\n";       // Output: 4
  
  // Example 2: Minimum at start (1-element decreasing prefix)
  arr = {5, 6, 7};
  cout << valley_bottom(arr) << "\n";       // Output: 5
  
  // Example 3: Minimum at end (1-element increasing suffix)
  arr = {7, 6, 5};
  cout << valley_bottom(arr) << "\n";       // Output: 5
  
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT
 *============================================================================
 * 
 * # Valley Bottom
 * 
 * A _valley-shaped_ array is an array of integers such that:
 * 
 * - It can be split into a non-empty prefix and a non-empty suffix,
 * - The prefix is sorted in decreasing order,
 * - The suffix is sorted in increasing order,
 * - All the elements are unique.
 * 
 * Given a valley-shaped array, `arr`, return the smallest value.
 * 
 * Example 1: arr = [6, 5, 4, 7, 9]
 * Output: 4
 * 
 * Example 2: arr = [5, 6, 7]
 * Output: 5. The prefix sorted in decreasing order is just [5].
 * 
 * Example 3: arr = [7, 6, 5]
 * Output: 5. The suffix sorted in increasing order is just [5].
 * 
 * Constraints:
 * - 2 <= arr.length <= 10^6
 * - -10^9 <= arr[i] <= 10^9
 * 
 *============================================================================*/
