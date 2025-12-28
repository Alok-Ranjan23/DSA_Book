/**
 * @file two_sum.cc
 * @brief Find if two elements sum to zero using two pointers
 * 
 * This file implements the two-sum problem variant where we check if
 * any two distinct elements in a sorted array sum to zero.
 * 
 * Key Concepts:
 * - Two Pointer Technique: Start from both ends
 * - Exploiting sorted property for efficient search
 * - Sum comparison to decide which pointer to move
 * 
 * Time Complexity: O(n) where n is array length
 * Space Complexity: O(1) - only uses constant extra space
 * 
 * Algorithm:
 * - Left pointer at start (smallest), right pointer at end (largest)
 * - If sum == 0: found a pair, return true
 * - If sum > 0: decrease sum by moving right pointer left
 * - If sum < 0: increase sum by moving left pointer right
 * - If pointers cross: no pair exists
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Checks if two distinct elements sum to zero
 * @param arr Sorted vector of integers
 * @return true if arr[i] + arr[j] == 0 for some i != j, false otherwise
 * 
 * Uses the two-pointer technique on sorted array:
 * - arr[l] + arr[h] > 0 means we need smaller sum, so decrement h
 * - arr[l] + arr[h] < 0 means we need larger sum, so increment l
 */
bool two_sum(vector<int>& arr) {
  int n = arr.size();
  int l=0,h=n-1;
  while(l<h) {
    if(arr[l]+arr[h]==0) return true;
    else if(arr[l] + arr[h]>0) h--;
    else l++;
  }
  return false;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  vector<int> arr {-5, -2, -1, 1, 1, 10};
  cout<<boolalpha;
  cout<<two_sum(arr)<<"\n";
  arr = {-3, 0, 0, 1, 2};
  cout<<two_sum(arr)<<"\n";
  arr = {-5, -3, -1, 0, 2, 4, 6};
  cout<<two_sum(arr)<<"\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # 2-Sum
 * 
 * Given a sorted array of integers, arr, return whether there are two
 * distinct indices, i and j, such that arr[i] + arr[j] = 0.
 * 
 * Example 1:
 * Input: arr = [-5, -2, -1, 1, 1, 10]
 * Output: true
 * Explanation: The elements -1 and 1 sum to zero.
 * 
 * Example 2:
 * Input: arr = [-3, 0, 0, 1, 2]
 * Output: true
 * Explanation: The two 0s sum to zero.
 * 
 * Example 3:
 * Input: arr = [-5, -3, -1, 0, 2, 4, 6]
 * Output: false
 * Explanation: No two elements sum to zero.
 * 
 * Constraints:
 * - arr is sorted in ascending order
 * - 0 ≤ arr.length ≤ 10^6
 * - -10^9 ≤ arr[i] ≤ 10^9
 * 
 *============================================================================*/
