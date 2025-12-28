/**
 * @file missing_number_in_range.cc
 * @brief Find missing numbers in a range from a sorted array using two pointers
 * 
 * This file implements an algorithm to find all numbers in a given range
 * that do not appear in a sorted array.
 * 
 * Key Concepts:
 * - Two Pointer Technique: One for array, one for range values
 * - Virtual pointer for range: iterate through [low, high]
 * - Exploiting sorted property for efficient comparison
 * 
 * Time Complexity: O(n + k) where n = array length, k = high - low
 * Space Complexity: O(k) for the result array
 * 
 * Algorithm:
 * - Pointer i scans the array, n1 represents current range value
 * - If arr[i] < n1: advance i (skip elements below range)
 * - If arr[i] == n1: both exist, advance both
 * - If arr[i] > n1: n1 is missing, add to result and advance n1
 * - After array exhausted, all remaining range values are missing
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Finds all numbers in range [low, high] missing from sorted array
 * @param arr Sorted array of integers
 * @param low Lower bound of range (inclusive)
 * @param high Upper bound of range (inclusive)
 * @return Vector of missing numbers in the range
 * 
 * Efficiently skips array elements outside the range and identifies
 * all range values not present in the array.
 */
vector<int> missing_number(vector<int>& arr,int low,int high) {
  int n  = arr.size();
  int i  = 0;
  int n1 = low;
  vector<int> res;
  while(i<n && n1<=high) {
    if(arr[i]<n1) i++;
    else if(arr[i]==n1) {
      i++; n1++;
    }
    else {
      res.push_back(n1);
      n1++;
    }
  }
  while(n1<=high) {
    res.push_back(n1++);
  }
  return res;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  vector<int> arr {6, 9, 12, 15, 18}; int low = 9, high = 13;
  for(auto&x: missing_number(arr,low,high)) cout<<x<<" ";
  cout<<"\n";
  arr = {}; low = 9, high = 9;
  for(auto&x: missing_number(arr,low,high)) cout<<x<<" ";
  cout<<"\n";
  arr = {6,7,8,9}; low = 7, high = 8;
  for(auto&x: missing_number(arr,low,high)) cout<<x<<" ";
  cout<<"\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Missing Numbers in Range
 * 
 * Given a sorted array of integers, arr, and two values indicating a range,
 * low and high, with low <= high, return a new array with all the numbers
 * in the range that do not appear in arr.
 * 
 * Example 1:
 * Input: arr = [6, 9, 12, 15, 18], low = 9, high = 13
 * Output: [10, 11, 13]
 * Explanation: The numbers 10, 11, and 13 are in range [9, 13] but not in arr.
 * 
 * Example 2:
 * Input: arr = [], low = 9, high = 9
 * Output: [9]
 * Explanation: 9 is in the range [9, 9] but arr is empty.
 * 
 * Example 3:
 * Input: arr = [6, 7, 8, 9], low = 7, high = 8
 * Output: []
 * Explanation: Every number in the range [7, 8] appears in arr.
 * 
 * Constraints:
 * - arr is sorted in ascending order
 * - 0 ≤ arr.length ≤ 10^6
 * - -10^9 ≤ low ≤ high ≤ 10^9
 * - All elements in arr are in the range [-10^9, 10^9]
 * - high - low ≤ 10^6
 * 
 *============================================================================*/
