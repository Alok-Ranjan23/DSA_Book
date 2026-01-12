/**
 * @file compress_array_by_k.cc
 * @brief Compress array by merging K consecutive equal elements
 * 
 * This file implements a k-compression algorithm where exactly k consecutive
 * equal elements are merged into their sum, cascading until no more k-blocks
 * remain.
 * 
 * Key Concepts:
 * - Stack stores pairs of (value, consecutive_count)
 * - When count reaches k, merge k elements into sum (value * k)
 * - Cascading: after merge, new value might form another k-block
 * 
 * Time Complexity: O(n) - each element processed constant times amortized
 * Space Complexity: O(n) - stack storage for element-count pairs
 */

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

/**
 * @brief Compresses array by merging k consecutive equal elements
 * @param arr Input array of integers
 * @param k Number of consecutive equal elements required for merge (k >= 2)
 * @return K-compressed array
 * 
 * Algorithm:
 * 1. Stack stores (value, count) pairs
 * 2. For each element, check if it matches stack top
 * 3. If match and count reaches k-1, merge: new_value = value * k
 * 4. After merge, continue checking (cascade effect)
 * 5. Expand stack back to array (each pair expands to 'count' copies)
 */
vector<int> compress_array_by_k(vector<int>& arr, int k) {
  stack<pair<int,int>> st;  // (value, consecutive_count)
  
  for(auto&x : arr) {
    int count = 1;
    
    // Check for matches and potential merges
    while(!st.empty() && st.top().first==x) {
      count = st.top().second;
      st.pop();
      
      if(count==k-1) {
        // k elements found! Merge them into sum
        x = x*k;          // New value is sum of k equal elements
        count = 1;        // Reset count for the new merged value
        // Continue loop to check if new value matches next stack top
      } else {
        count+=1;         // Not yet k elements, increment count
        break;            // Stop checking, will push updated count
      }
    } 
    st.push({x,count});
  }
  
  // Expand stack to result array
  vector<int> res;
  while(st.empty()==false) {
    int count = st.top().second;
    int val = st.top().first;
    while(count--)        // Push 'count' copies of value
      res.push_back(val);
    st.pop();
  }
  reverse(res.begin(),res.end());  // Stack was LIFO, reverse to get original order
  return res;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Example 1: k=3, [1,9,9,3,3,3,4] -> [1,27,4]
  // Steps: [1,9,9,3,3,3,4] -> [1,9,9,9,4] -> [1,27,4]
  vector<int> arr {1,9,9,3,3,3,4}; int k=3;
  for(auto&x: compress_array_by_k(arr,k)) cout<<x<<" "; 
  cout<<"\n";  // Expected: 1 27 4
  
  // Example 2: k=2, [8,4,2,2] -> [16]
  arr = {8,4,2,2}; k=2;
  for(auto&x: compress_array_by_k(arr,k)) cout<<x<<" ";
  cout<<"\n";  // Expected: 16
  
  // Example 3: k=5, [4,4,4,4] -> [4,4,4,4] (only 4 elements, need 5)
  arr = {4,4,4,4}; k=5;
  for(auto&x: compress_array_by_k(arr,k)) cout<<x<<" ";
  cout<<"\n";  // Expected: 4 4 4 4
  
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Compress Array by K
 * 
 * Given an array of integers, arr, and an integer k ≥ 2, a k-compress operation
 * finds the first block of k consecutive equal numbers and combines them into
 * their sum. If there are no k consecutive equal numbers, the array is
 * considered fully k-compressed.
 * 
 * Example 1:
 *   arr = [1, 9, 9, 3, 3, 3, 4], k = 3
 *   Output: [1, 27, 4]
 *   Steps: [1, 9, 9, 3, 3, 3, 4] -> [1, 9, 9, 9, 4] -> [1, 27, 4]
 * 
 * Example 2:
 *   arr = [8, 4, 2, 2], k = 2
 *   Output: [16]
 * 
 * Example 3:
 *   arr = [4, 4, 4, 4], k = 5
 *   Output: [4, 4, 4, 4]
 * 
 *============================================================================*/
