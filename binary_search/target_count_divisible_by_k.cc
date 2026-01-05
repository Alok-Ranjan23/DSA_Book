/**
 * @file target_count_divisible_by_k.cc
 * @brief Binary Search to count occurrences and check divisibility
 * 
 * This file implements binary search to find the leftmost and rightmost
 * occurrences of a target in a sorted array with duplicates, then checks
 * if the count is divisible by k.
 * 
 * Key Concepts:
 * - Finding first and last occurrence using binary search variants
 * - Lower bound: first element >= target
 * - Upper bound: first element > target (or last element == target)
 * - Count = rightmost - leftmost + 1
 * 
 * Time Complexity: O(log n) - two binary searches
 * Space Complexity: O(1) - constant extra space
 * 
 * Algorithm Pattern: Binary Search Bounds (Lower/Upper Bound)
 * 
 * Visual for arr = [1, 2, 2, 2, 2, 2, 2, 3], target = 2:
 *   Indices:  0  1  2  3  4  5  6  7
 *   Values:   1  2  2  2  2  2  2  3
 *                ^--------------^
 *                leftmost=1  rightmost=6
 *                count = 6 - 1 + 1 = 6
 */

#include <iostream>
#include <vector>
using namespace std;

/*============================================================================
 * BINARY SEARCH FOR BOUNDS
 *============================================================================*/

/**
 * @brief Finds the leftmost (first) occurrence of target
 * @param arr Sorted array (may contain duplicates)
 * @param target Value to find
 * @return Index of first occurrence, or -1 if not found
 * 
 * Algorithm:
 * Standard binary search with modification:
 * - When arr[m] == target, check if it's the first occurrence
 * - If m == l OR arr[m-1] != target, we found the leftmost
 * - Otherwise, continue searching left (r = m - 1)
 * 
 * Key insight: When we find target, we need to verify there's no
 * earlier occurrence by checking arr[m-1].
 */
int leftmost_occurrence(vector<int>& arr, int target) {
  int n = arr.size();
  if(n == 0) return -1;
  
  int l = 0;
  int r = n - 1;
  
  while(l <= r) {
    int m = l + (r - l) / 2;
    
    // Found target - check if it's the leftmost
    if(arr[m] == target && (l == m || arr[m - 1] != target)) {
      return m;
    }
    
    if(arr[m] >= target) {
      r = m - 1;          // Target might be at m or to the left
    } else {
      l = m + 1;          // Target is to the right
    }
  }
  
  return -1;
}

/**
 * @brief Finds the rightmost (last) occurrence of target
 * @param arr Sorted array (may contain duplicates)
 * @param target Value to find
 * @return Index of last occurrence, or -1 if not found
 * 
 * Algorithm:
 * Mirror of leftmost_occurrence:
 * - When arr[m] == target, check if it's the last occurrence
 * - If m == r OR arr[m+1] != target, we found the rightmost
 * - Otherwise, continue searching right (l = m + 1)
 */
int rightmost_occurrence(vector<int>& arr, int target) {
  int n = arr.size();
  if(n == 0) return -1;
  
  int l = 0;
  int r = n - 1;
  
  while(l <= r) {
    int m = l + (r - l) / 2;
    
    // Found target - check if it's the rightmost
    if(arr[m] == target && (r == m || arr[m + 1] != target)) {
      return m;
    }
    
    if(arr[m] <= target) {
      l = m + 1;          // Target might be at m or to the right
    } else {
      r = m - 1;          // Target is to the left
    }
  }
  
  return -1;
}

/*============================================================================
 * MAIN SOLUTION
 *============================================================================*/

/**
 * @brief Checks if count of target in array is divisible by k
 * @param arr Sorted array
 * @param target Value to count
 * @param k Divisor to check against
 * @return true if count is divisible by k (including count = 0)
 * 
 * Note: 0 is divisible by any number (0 % k == 0), so if target
 * doesn't exist, we return true.
 */
bool target_count_divisible(vector<int>& arr, int target, int k) {
  int left = leftmost_occurrence(arr, target);
  
  // Target not found - count is 0, which is divisible by any k
  if(left == -1) return true;
  
  int right = rightmost_occurrence(arr, target);
  int count = right - left + 1;
  
  return (count % k == 0);
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  cout << boolalpha;  // Print true/false instead of 1/0
  
  // Example 1: 2 occurs 6 times, 6 % 3 == 0 -> true
  vector<int> arr{1, 2, 2, 2, 2, 2, 2, 3};
  int target = 2, k = 3;
  cout << target_count_divisible(arr, target, k) << "\n";  // true
  
  // Example 2: 2 occurs 6 times, 6 % 4 != 0 -> false
  arr = {1, 2, 2, 2, 2, 2, 2, 3};
  target = 2; k = 4;
  cout << target_count_divisible(arr, target, k) << "\n";  // false
  
  // Example 3: 4 occurs 0 times, 0 % 3 == 0 -> true
  arr = {1, 2, 2, 2, 2, 2, 2, 3};
  target = 4; k = 3;
  cout << target_count_divisible(arr, target, k) << "\n";  // true
  
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT
 *============================================================================
 * 
 * # Target Count Divisible by K
 * 
 * Given a sorted array of integers, `arr`, a target value, `target`, 
 * and a positive integer, `k`, return whether the number of occurrences 
 * of the target in the array is a multiple of `k`.
 * 
 * Example 1: arr = [1, 2, 2, 2, 2, 2, 2, 3], target = 2, k = 3
 * Output: True. 2 occurs 6 times, which is a multiple of 3.
 * 
 * Example 2: arr = [1, 2, 2, 2, 2, 2, 2, 3], target = 2, k = 4
 * Output: False. 2 occurs 6 times, which is not a multiple of 4.
 * 
 * Example 3: arr = [1, 2, 2, 2, 2, 2, 2, 3], target = 4, k = 3
 * Output: True. 4 occurs 0 times, and 0 is a multiple of any number.
 * 
 * Constraints:
 * - 1 <= arr.length <= 10^6
 * - -10^9 <= arr[i], target <= 10^9
 * - 1 <= k <= 10^6
 * - arr is sorted in ascending order
 * 
 *============================================================================*/
