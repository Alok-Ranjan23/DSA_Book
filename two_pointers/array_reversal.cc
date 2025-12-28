/**
 * @file array_reversal.cc
 * @brief In-place array reversal using two pointers
 * 
 * This file implements the classic array reversal algorithm using
 * the two pointer technique with O(1) extra space.
 * 
 * Key Concepts:
 * - Two Pointer Technique: Start from both ends, move inward
 * - In-place modification: Swap elements without extra array
 * - Symmetric traversal pattern
 * 
 * Time Complexity: O(n) where n is array length
 * Space Complexity: O(1) - only uses constant extra space
 * 
 * Algorithm:
 * - Initialize left pointer at start, right pointer at end
 * - Swap elements at both pointers
 * - Move pointers toward center until they meet
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Reverses an array of characters in place
 * @param arr Vector of characters to reverse (modified in place)
 * 
 * Uses two pointers starting from opposite ends, swapping
 * elements and moving toward the center until pointers cross.
 */
void reverse(vector<char>& arr) {
  int n = arr.size();
  int l = 0;
  int h = n-1;
  while(l<h) {
    int t  = arr[l];
    arr[l] = arr[h];
    arr[h] = t;
    l++;h--;
  }

}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  vector<char> arr {'h','e','l','l','o'};
  for(auto&x: arr) cout<<x<<" ";
  cout<<"\n";
  reverse(arr);
  for(auto&x: arr) cout<<x<<" ";
  cout<<"\n";
  arr = {'a'};
  for(auto&x: arr) cout<<x<<" ";
  cout<<"\n";
  reverse(arr);
  for(auto&x: arr) cout<<x<<" ";
  cout<<"\n";
  arr = {};
  for(auto&x: arr) cout<<x<<" ";
  cout<<"\n";
  reverse(arr);
  for(auto&x: arr) cout<<x<<" ";
  cout<<"\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Array Reversal
 * 
 * Reverse an array of letters, `arr`, in place using `O(1)` extra space.
 * 
 * Example 1:
 * Input: arr = ['h', 'e', 'l', 'l', 'o']
 * Output: ['o', 'l', 'l', 'e', 'h']
 * 
 * Example 2:
 * Input: arr = ['a']
 * Output: ['a']
 * 
 * Example 3:
 * Input: arr = []
 * Output: []
 * 
 * Constraints:
 * - 0 ≤ arr.length ≤ 10^5
 * - arr contains only letters
 * 
 *============================================================================*/
