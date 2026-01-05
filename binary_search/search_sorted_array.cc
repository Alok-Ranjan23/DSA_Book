/**
 * @file search_sorted_array.cc
 * @brief Classic Binary Search implementation for sorted arrays
 * 
 * This file implements the fundamental binary search algorithm to find
 * a target value in a sorted array. Binary search is one of the most
 * important algorithms in computer science, reducing search time from
 * O(n) to O(log n).
 * 
 * Key Concepts:
 * - Divide and conquer approach
 * - Eliminates half the search space each iteration
 * - Requires sorted input
 * - Uses two pointers (left and right) to track search boundaries
 * 
 * Time Complexity: O(log n) - halves search space each iteration
 * Space Complexity: O(1) - only uses a constant number of variables
 * 
 * Algorithm Pattern: Standard Binary Search
 */

#include <iostream>
#include <vector>
using namespace std;

/*============================================================================
 * BINARY SEARCH IMPLEMENTATION
 *============================================================================*/

/**
 * @brief Searches for a target value in a sorted array
 * @param arr Reference to the sorted array
 * @param target The value to search for
 * @return Index of target if found, -1 otherwise
 * 
 * Algorithm:
 * 1. Initialize left (l) and right (r) pointers to array bounds
 * 2. Early exit if target is outside array's value range
 * 3. While search space is valid (l <= r):
 *    a. Calculate midpoint
 *    b. If arr[mid] == target, return mid
 *    c. If arr[mid] < target, search right half (l = mid + 1)
 *    d. If arr[mid] > target, search left half (r = mid - 1)
 * 4. Return -1 if target not found
 * 
 * Note: Using (l+r)>>1 for midpoint is safe here since array indices
 * won't overflow int for arrays up to 10^6 elements.
 */
int b_search(vector<int>& arr, int target) {
  int n = arr.size();
  if(n == 0) return -1;                         // Empty array check
  
  int l = 0;
  int r = n - 1;
  
  // Early termination: target outside array's value range
  if(arr[l] > target || arr[r] < target) return -1;
  
  while(l <= r) {
    int mid = (l + r) >> 1;                     // Equivalent to (l+r)/2
    
    if(arr[mid] == target) return mid;          // Found!
    if(arr[mid] < target) l = mid + 1;          // Target in right half
    else r = mid - 1;                           // Target in left half
  }
  
  return -1;                                    // Target not found
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Example 1: Target exists in array
  vector<int> arr{-2, 0, 3, 4, 7, 9, 11};
  int target = 3;
  int index = b_search(arr, target);
  if(index == -1) {
    cout << "The target " << target << " is not in the array.\n";
  } else {
    cout << "The target " << target << " is at index " << index << ".\n";
  }
  
  // Example 2: Target does not exist
  arr = {-2, 0, 3, 4, 7, 9, 11};
  target = 2;
  index = b_search(arr, target);
  if(index == -1) {
    cout << "The target " << target << " is not in the array.\n";
  } else {
    cout << "The target " << target << " is at index " << index << ".\n";
  }
  
  // Example 3: Target at first position
  arr = {1, 2, 3};
  target = 1;
  index = b_search(arr, target);
  if(index == -1) {
    cout << "The target " << target << " is not in the array.\n";
  } else {
    cout << "The target " << target << " is at index " << index << ".\n";
  }
  
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT
 *============================================================================
 * 
 * # Search in Sorted Array
 * 
 * Given a sorted array of integers, `arr`, and a target value, `target`, 
 * return the target's index if it exists in the array or `-1` if it doesn't.
 * 
 * Example 1: arr = [-2, 0, 3, 4, 7, 9, 11], target = 3
 * Output: 2. The target 3 is at index 2.
 * 
 * Example 2: arr = [-2, 0, 3, 4, 7, 9, 11], target = 2
 * Output: -1. The target 2 is not in the array.
 * 
 * Example 3: arr = [1, 2, 3], target = 1
 * Output: 0. The target 1 is at index 0.
 * 
 * Constraints:
 * - 0 <= arr.length <= 10^6
 * - -10^9 <= arr[i], target <= 10^9
 * - arr is sorted in ascending order, without duplicates
 * 
 *============================================================================*/
