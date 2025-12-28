/**
 * @file prefix_suffix_swap.cc
 * @brief Rotate array by moving prefix to end using reversal algorithm
 * 
 * This file implements array rotation using the three-reversal technique
 * to move the first third of array to the end.
 * 
 * Key Concepts:
 * - Reversal Algorithm: Three reversals to achieve rotation
 * - In-place rotation with O(1) extra space
 * - Mathematical insight: reverse(A) + reverse(B) then reverse(all) = B + A
 * 
 * Time Complexity: O(n) where n is array length
 * Space Complexity: O(1) - only uses constant extra space
 * 
 * Algorithm:
 * - Given array of length n divisible by 3
 * - Step 1: Reverse first n/3 elements (prefix)
 * - Step 2: Reverse remaining 2n/3 elements (suffix)
 * - Step 3: Reverse entire array
 * - Result: suffix followed by prefix
 * 
 * Visual trace for arr = ['b','a','d','r','e','v','i','e','w']:
 * b a d | r e v i e w
 * Step 1: d a b | r e v i e w
 * Step 2: d a b | w e i v e r
 * Step 3: r e v i e w | b a d
 */

#include <iostream>
#include <vector>
using namespace std;

/*
b a d r e v i e w
0     3
    2           8
d a b w e i v e r
0               8
r e v i e w b a d
*/

/**
 * @brief Helper function to reverse a portion of array
 * @param arr Vector to modify
 * @param l Left index (inclusive)
 * @param h Right index (inclusive)
 */
void reverse(vector<char>& arr, int l, int h) {
  while(l<h) {
    int temp = arr[l];
    arr[l]   = arr[h];
    arr[h]   = temp;
    l+=1;
    h-=1;
  }
}

/**
 * @brief Moves first n/3 elements to the end of array
 * @param arr Vector of characters (modified in place, length divisible by 3)
 * 
 * Uses the three-reversal technique:
 * 1. Reverse prefix [0, n/3-1]
 * 2. Reverse suffix [n/3, n-1]
 * 3. Reverse entire array [0, n-1]
 */
void prefix_suffix_swap(vector<char>& arr) {
  int n = arr.size();
  reverse(arr,0,n/3-1);
  reverse(arr,n/3,n-1);
  reverse(arr,0,n-1);
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  vector<char> arr {'b', 'a', 'd', 'r', 'e', 'v', 'i', 'e', 'w'};
  for(auto&x : arr) cout<<x<<" ";
  cout<<"\n";
  prefix_suffix_swap(arr);
  for(auto&x : arr) cout<<x<<" ";
  cout<<"\n";

  arr = {'a','b','c'};
  for(auto&x : arr) cout<<x<<" ";
  cout<<"\n";
  prefix_suffix_swap(arr);
  for(auto&x : arr) cout<<x<<" ";
  cout<<"\n";

  arr = {};
  for(auto&x : arr) cout<<x<<" ";
  cout<<"\n";
  prefix_suffix_swap(arr);
  for(auto&x : arr) cout<<x<<" ";
  cout<<"\n";

  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Prefix Suffix Swap
 * 
 * We are given an array of letters, arr, with a length, n, which is a
 * multiple of 3. The goal is to modify arr in place to move the prefix
 * of length n/3 to the end and the suffix of length 2n/3 to the beginning.
 * 
 * Example 1:
 * Input: arr = ['b', 'a', 'd', 'r', 'e', 'v', 'i', 'e', 'w']
 * Output: ['r', 'e', 'v', 'i', 'e', 'w', 'b', 'a', 'd']
 * Explanation: The first third (bad) moves to end, rest (review) stays.
 * 
 * Example 2:
 * Input: arr = ['a', 'b', 'c']
 * Output: ['b', 'c', 'a']
 * 
 * Example 3:
 * Input: arr = []
 * Output: []
 * 
 * Constraints:
 * - The length of arr is divisible by 3
 * - 0 ≤ arr.length ≤ 10^6
 * - arr[i] is a letter
 * 
 *============================================================================*/
