/**
 * @file valley_sort.cc
 * @brief Sort a valley-shaped array using two pointers
 * 
 * This file implements sorting of a valley-shaped array where the array
 * has a decreasing prefix followed by an increasing suffix.
 * 
 * Key Concepts:
 * - Two Pointer Technique: Start from both ends, move inward
 * - Valley array property: largest elements are at both ends
 * - Build result from back: place largest elements first
 * - Merge-like operation: similar to merging two sorted sequences
 * 
 * Time Complexity: O(n) where n is array length
 * Space Complexity: O(n) for the result array
 * 
 * Algorithm:
 * - In a valley array, arr[0] is the max of descending prefix,
 *   arr[n-1] is the max of ascending suffix
 * - Compare elements at both ends: the larger one belongs at the back
 * - Fill result array from right to left (largest to smallest)
 * - Move the pointer that contributed the larger element
 * 
 * Why this works:
 * - Valley array = reversed sorted left half + sorted right half
 * - Both ends always contain the next largest unprocessed element
 * - By always picking the larger of the two ends, we build sorted order
 * 
 * Visual example for arr = [8, 4, 2, 6]:
 *   8 (left max)          6 (right max)
 *      4                
 *         2 (valley/min)
 * 
 *   Step 1: 8 > 6 → result[3] = 8, l++
 *   Step 2: 4 < 6 → result[2] = 6, h--
 *   Step 3: 4 > 2 → result[1] = 4, l++
 *   Step 4: 2 = 2 → result[0] = 2, done
 *   Result: [2, 4, 6, 8]
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Sorts a valley-shaped array in ascending order
 * @param arr Valley-shaped vector (modified in place)
 * 
 * A valley-shaped array has a decreasing prefix and increasing suffix.
 * The algorithm compares elements at both ends and places the larger
 * one at the back of the result, effectively merging the two halves.
 * 
 * Note: Uses O(n) auxiliary space for correctness. An in-place O(1)
 * solution would require complex rotation-based merging.
 */
void valley_sort(vector<int>& arr) {
  int n = arr.size();
  if (n <= 1) return;
  
  vector<int> result(n);
  int l = 0, h = n - 1;
  int idx = n - 1;  // Fill result from the back (largest first)
  
  // Compare ends and pick the larger element for the back of result
  while (l <= h) {
    if (arr[l] > arr[h]) {
      result[idx--] = arr[l++];  // Left end is larger
    } else {
      result[idx--] = arr[h--];  // Right end is larger (or equal)
    }
  }
  
  arr = result;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  vector<int> arr {8,4,2,6};
  for(auto&x: arr) cout<<x<<" ";
  cout<<"\n";
  valley_sort(arr);
  for(auto&x: arr) cout<<x<<" ";
  cout<<"\n";
  arr = {1,2};
  for(auto&x: arr) cout<<x<<" ";
  cout<<"\n";
  valley_sort(arr);
  for(auto&x: arr) cout<<x<<" ";
  cout<<"\n";
  arr = {2,2,1,1};
  for(auto&x: arr) cout<<x<<" ";
  cout<<"\n";
  valley_sort(arr);
  for(auto&x: arr) cout<<x<<" ";
  cout<<"\n";
  // Additional test case that failed with old algorithm
  arr = {5,3,1,2,4};
  for(auto&x: arr) cout<<x<<" ";
  cout<<"\n";
  valley_sort(arr);
  for(auto&x: arr) cout<<x<<" ";
  cout<<"\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Sort Valley Shaped Array
 * 
 * A valley-shaped array is an array of integers such that:
 * - It can be split into a non-empty prefix and a non-empty suffix
 * - The prefix is sorted in decreasing order (duplicates allowed)
 * - The suffix is sorted in increasing order (duplicates allowed)
 * 
 * Given a valley-shaped array, arr, return a new array with the elements
 * sorted.
 * 
 * Example 1: arr = [8, 4, 2, 6]
 * Output: [2, 4, 6, 8]
 * Explanation: The decreasing prefix could be [8, 4] or [8, 4, 2].
 * The corresponding increasing suffixes would be [2, 6] or [6].
 * 
 * Example 2: arr = [1, 2]
 * Output: [1, 2]
 * The array is already sorted (the decreasing prefix is just [1]).
 * 
 * Example 3: arr = [2, 2, 1, 1]
 * Output: [1, 1, 2, 2]
 * 
 * Constraints:
 * - 0 ≤ arr.length ≤ 10^6
 * - -10^9 ≤ arr[i] ≤ 10^9
 * 
 *============================================================================*/
