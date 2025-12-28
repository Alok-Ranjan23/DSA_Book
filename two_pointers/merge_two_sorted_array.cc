/**
 * @file merge_two_sorted_array.cc
 * @brief Merge two sorted arrays into one sorted array using two pointers
 * 
 * This file implements the classic merge operation from merge sort,
 * combining two sorted arrays into a single sorted array.
 * 
 * Key Concepts:
 * - Two Pointer Technique: One pointer for each array
 * - Comparison-based merging: always pick the smaller element
 * - Handle remaining elements after one array is exhausted
 * 
 * Time Complexity: O(n + m) where n and m are array lengths
 * Space Complexity: O(n + m) for the result array
 * 
 * Algorithm:
 * - Compare elements at both pointers
 * - Add smaller element to result and advance that pointer
 * - When one array exhausted, append remaining elements from other
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Merges two sorted arrays into a single sorted array
 * @param arr1 First sorted array
 * @param arr2 Second sorted array
 * @return New vector containing all elements in sorted order
 * 
 * Uses reserve() to pre-allocate memory for efficiency.
 * Handles duplicates and includes all elements from both arrays.
 */
vector<int> merge_two_sorted(vector<int>& arr1, vector<int>& arr2) {
  int n1 = arr1.size();
  int n2 = arr2.size();
  int i=0,j=0;
  vector<int> res;
  res.reserve(n1+n2);
  while(i<n1 && j<n2) {
    if(arr1[i]<arr2[j]) {
      res.push_back(arr1[i++]);
    }
    else {
      res.push_back(arr2[j++]);
    }
  }
  if(j==n2) {
    while(i<n1) res.push_back(arr1[i++]);
  }
  if(i==n1) {
    while(j<n2) res.push_back(arr2[j++]);
  }
  return res;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  vector<int> arr1 {1,3,4,5};
  vector<int> arr2 {2,4,4};
  for(auto&x: merge_two_sorted(arr1,arr2)) cout<<x<<" ";
  cout<<"\n";
  arr1 = {-1};
  arr2 = {};
  for(auto&x: merge_two_sorted(arr1,arr2)) cout<<x<<" ";
  cout<<"\n";
  arr1 = {1,3,5};
  arr2 = {2,4,6};
  for(auto&x: merge_two_sorted(arr1,arr2)) cout<<x<<" ";
  cout<<"\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Merge Two Sorted Arrays
 * 
 * Given two sorted arrays of integers, arr1 and arr2, return a new array
 * that contains all the elements in arr1 and arr2 in sorted order,
 * including duplicates.
 * 
 * Example 1:
 * Input:
 * arr1 = [1, 3, 4, 5]
 * arr2 = [2, 4, 4]
 * Output: [1, 2, 3, 4, 4, 4, 5]
 * Explanation: All elements are merged in sorted order.
 * 
 * Example 2:
 * Input:
 * arr1 = [-1]
 * arr2 = []
 * Output: [-1]
 * Explanation: When one array is empty, the result is just the other array.
 * 
 * Example 3:
 * Input:
 * arr1 = [1, 3, 5]
 * arr2 = [2, 4, 6]
 * Output: [1, 2, 3, 4, 5, 6]
 * 
 * Constraints:
 * - arr1 and arr2 are sorted in ascending order
 * - 0 ≤ arr1.length, arr2.length ≤ 10^6
 * - -10^9 ≤ arr1[i], arr2[i] ≤ 10^9
 * 
 *============================================================================*/
