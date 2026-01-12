/**
 * @file compress_array.cc
 * @brief Compress array by merging consecutive equal elements
 * 
 * This file implements an array compression algorithm where consecutive
 * equal elements are repeatedly merged (summed) until no consecutive
 * equal elements remain.
 * 
 * Key Concepts:
 * - Stack-based approach for efficient cascading merges
 * - When new element equals stack top, merge and check again (cascade)
 * - Single pass achieves what would require multiple iterations naively
 * 
 * Time Complexity: O(n) - each element pushed/popped at most O(log max_val) times
 * Space Complexity: O(n) - stack storage for elements
 */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/**
 * @brief Compresses array by merging consecutive equal elements
 * @param arr Input array of integers
 * @return Compressed array with no consecutive equal elements
 * 
 * Algorithm:
 * 1. Process each element from left to right
 * 2. If current element equals stack top, pop and add to current (merge)
 * 3. Continue merging while top equals current (cascade effect)
 * 4. Push the (possibly merged) element onto stack
 * 5. Convert stack to result array (reverse order)
 */
vector<int> compress_array(vector<int>& arr) {
  stack<int> st;
  
  for(auto&x : arr) {
    // Cascade merge: keep merging while top equals current
    while(!st.empty() && st.top()==x) {
      x += st.top();    // Merge: sum the two equal elements
      st.pop();         // Remove the merged element from stack
    }
    st.push(x);         // Push the (possibly merged) element
  }
  
  // Convert stack to vector (stack is LIFO, so reverse)
  int n = st.size();
  vector<int> res(n);
  int i = n - 1;
  while(st.empty()==false) {
    res[i--] = st.top();
    st.pop();
  }
  return res;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Example 1: [8,4,2,2,2,4] -> [16,2,4]
  // Steps: [8,4,2,2,2,4] -> [8,4,4,2,4] -> [8,8,2,4] -> [16,2,4]
  vector<int> arr {8,4,2,2,2,4};
  for(auto&x: compress_array(arr)) cout<<x<<" "; 
  cout<<"\n";  // Expected: 16 2 4
  
  // Example 2: [4,4,4,4] -> [16]
  // Steps: [4,4,4,4] -> [8,4,4] -> [8,8] -> [16]
  arr = {4,4,4,4};
  for(auto&x: compress_array(arr)) cout<<x<<" ";
  cout<<"\n";  // Expected: 16
  
  // Example 3: [1,2,3,4] -> [1,2,3,4] (no consecutive equals)
  arr = {1,2,3,4};
  for(auto&x: compress_array(arr)) cout<<x<<" ";
  cout<<"\n";  // Expected: 1 2 3 4
  
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Compress Array
 * 
 * Given an array of integers, arr, a compress operation finds the first pair of
 * consecutive equal numbers and combines them into their sum. If there are no
 * consecutive equal numbers, the array is considered fully compressed.
 * 
 * Your goal is to repeatedly compress the array until it is fully compressed.
 * 
 * Example 1:
 *   arr = [8, 4, 2, 2, 2, 4]
 *   Output: [16, 2, 4]
 *   Steps: [8, 4, 2, 2, 2, 4] -> [8, 4, 4, 2, 4] -> [8, 8, 2, 4] -> [16, 2, 4]
 * 
 * Example 2:
 *   arr = [4, 4, 4, 4]
 *   Output: [16]
 *   Steps: [4, 4, 4, 4] -> [8, 4, 4] -> [8, 8] -> [16]
 * 
 * Example 3:
 *   arr = [1, 2, 3, 4]
 *   Output: [1, 2, 3, 4]
 * 
 *============================================================================*/
