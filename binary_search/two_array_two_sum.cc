/**
 * @file two_array_two_sum.cc
 * @brief Binary Search for Two-Sum across two arrays
 * 
 * This file implements a solution to find two elements from different
 * arrays that sum to zero, using binary search on the sorted array.
 * 
 * Key Concepts:
 * - For each element x in unsorted_arr, search for -x in sorted_arr
 * - Binary search on sorted array for O(log n) lookup
 * - Total complexity: O(m * log n) where m = unsorted, n = sorted
 * - O(1) extra space (no hash tables)
 * 
 * Time Complexity: O(m * log n) - m linear scans × log n binary searches
 * Space Complexity: O(1) - no extra space used
 * 
 * Algorithm Pattern: Binary Search + Linear Scan
 * 
 * Alternative approaches:
 * - Hash table: O(m + n) time, O(n) space
 * - Two pointers (if both sorted): O(m + n) time, O(1) space
 * - This approach: O(m log n) time, O(1) space
 */

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

/*============================================================================
 * BINARY SEARCH HELPER
 *============================================================================*/

/**
 * @brief Standard binary search in sorted array
 * @param arr Sorted array to search in
 * @param target Value to find
 * @return Index of target if found, -1 otherwise
 */
int b_search(vector<int>& arr, int target) {
  int n = arr.size();
  if(n == 0) return -1;
  
  int l = 0;
  int r = n - 1;
  
  // Early exit optimization
  if(arr[l] > target || arr[r] < target) return -1;
  
  while(l <= r) {
    int mid = (l + r) >> 1;
    if(arr[mid] == target) return mid;
    if(arr[mid] < target) l = mid + 1;
    else r = mid - 1;
  }
  
  return -1;
}

/*============================================================================
 * TWO ARRAY TWO SUM SOLUTION
 *============================================================================*/

/**
 * @brief Finds two elements from different arrays that sum to zero
 * @param sorted_arr Sorted array to search in (using binary search)
 * @param unsorted_arr Unsorted array to iterate through
 * @return Pair of indices (sorted_index, unsorted_index), or (-1, -1) if not found
 * 
 * Algorithm:
 * 1. For each element x in unsorted_arr:
 *    a. Compute complement = -x (value needed to sum to 0)
 *    b. Binary search for complement in sorted_arr
 *    c. If found, return both indices
 * 2. Return (-1, -1) if no pair sums to 0
 * 
 * Why binary search on sorted_arr?
 * - sorted_arr supports efficient O(log n) lookups
 * - We must iterate unsorted_arr linearly anyway (can't binary search it)
 * 
 * Visual for sorted = [-5,-4,-1,4,6,6,7], unsorted = [-3,7,18,4,6]:
 *   i=0: looking for -(-3)=3 in sorted -> not found
 *   i=1: looking for -7=-7 in sorted -> not found
 *   i=2: looking for -18=-18 in sorted -> not found
 *   i=3: looking for -4=-4 in sorted -> found at index 1!
 *   Return [1, 3]
 */
pair<int, int> two_array_two_sum(vector<int>& sorted_arr, vector<int>& unsorted_arr) {
  int n = unsorted_arr.size();
  pair<int, int> p{-1, -1};
  
  for(int i = 0; i < n; ++i) {
    int target = -unsorted_arr[i];          // Complement that sums to 0
    int index = b_search(sorted_arr, target);
    
    if(index != -1) {
      p = {index, i};                       // Found a valid pair
      break;
    }
  }
  
  return p;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Example 1: -4 + 4 = 0
  vector<int> sorted_arr{-5, -4, -1, 4, 6, 6, 7};
  vector<int> unsorted_arr{-3, 7, 18, 4, 6};
  pair<int, int> p = two_array_two_sum(sorted_arr, unsorted_arr);
  cout << "[" << p.first << ", " << p.second << "]\n";  // [1, 3]
  
  // Example 2: No pair sums to 0
  sorted_arr = {1, 2, 3};
  unsorted_arr = {1, 2, 3};
  p = two_array_two_sum(sorted_arr, unsorted_arr);
  cout << "[" << p.first << ", " << p.second << "]\n";  // [-1, -1]
  
  // Example 3: -2 + 2 = 0
  sorted_arr = {-2, 0, 1, 2};
  unsorted_arr = {0, 2, -2, 4};
  p = two_array_two_sum(sorted_arr, unsorted_arr);
  cout << "[" << p.first << ", " << p.second << "]\n";  // [0, 1]
  
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT
 *============================================================================
 * 
 * # 2-Array 2-Sum
 * 
 * You are given two non-empty arrays of integers, `sorted_arr` and 
 * `unsorted_arr`. The first one is sorted, but the second is not. The 
 * goal is to find one element from each array with sum `0`. If you can 
 * find them, return an array with their indices, starting with the 
 * element in `sorted_arr`. Otherwise, return `[-1, -1]`. Use `O(1)` 
 * _extra space_ and do not modify the input.
 * 
 * Example 1:
 * sorted_arr = [-5, -4, -1, 4, 6, 6, 7]
 * unsorted_arr = [-3, 7, 18, 4, 6]
 * Output: [1, 3]
 * Explanation: We can use -4 from the sorted array and 4 from the 
 *              unsorted array.
 * 
 * Example 2:
 * sorted_arr = [1, 2, 3]
 * unsorted_arr = [1, 2, 3]
 * Output: [-1, -1]
 * Explanation: No pair of elements sums to 0.
 * 
 * Example 3:
 * sorted_arr = [-2, 0, 1, 2]
 * unsorted_arr = [0, 2, -2, 4]
 * Output: [0, 1]
 * Explanation: We can use -2 from the sorted array and 2 from the 
 *              unsorted array.
 * 
 * Constraints:
 * - 1 <= sorted_arr.length, unsorted_arr.length <= 10^6
 * - -10^9 <= sorted_arr[i], unsorted_arr[i] <= 10^9
 * - sorted_arr is sorted in ascending order
 * - The arrays have no duplicates
 * - Use O(1) extra space and do not modify the input
 * 
 *============================================================================*/
