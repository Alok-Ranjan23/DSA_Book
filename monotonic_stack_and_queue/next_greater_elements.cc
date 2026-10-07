/**
 * @file next_greater_elements.cc
 * @brief For every index, find the first index to its right with a strictly
 *        greater value
 *
 * Classic monotonic-stack problem. Scanning from right to left, the stack
 * holds candidate indices whose values strictly decrease from bottom to top.
 * For index i, all candidates with value <= arr[i] are useless (i is closer
 * and at least as large), so they are popped; the remaining top is the
 * answer.
 *
 * Key Concepts:
 * - Right-to-left scan with a stack of indices (not values) so the answer
 *   can be an index
 * - Pop on <= gives a STRICTLY greater element; equal values do not count
 *   (e.g. [5, 5, 5] -> all -1)
 * - -1 sentinel means "no greater element to the right"
 *
 * Time Complexity: O(n)
 *   - Each index is pushed exactly once and popped at most once, so the
 *     total cost of the inner while-loop over the whole scan is O(n).
 *     Brute force would be O(n^2).
 *
 * Space Complexity: O(n)
 *   - The result array (n) and the stack (up to n, e.g. for a strictly
 *     decreasing input).
 */
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

/**
 * @brief Return NGE where NGE[i] is the first j > i with arr[j] > arr[i]
 *
 * @param arr Input values
 * @return    Vector of indices, -1 where no greater element exists
 *
 * Algorithm:
 * 1. Iterate i from n-1 down to 0.
 * 2. Pop indices whose value is <= arr[i].
 * 3. If the stack is non-empty, its top is NGE[i]; push i.
 *
 * Time:  O(n) -- amortized O(1) per index
 * Space: O(n) -- stack + result
 */
//Time O(n)   (each index pushed/popped at most once)
//Space O(n)  (stack + result)
vector<int> next_greater_element(vector<int>& arr) {
  int n = arr.size();
  vector<int> nge(n,-1);                           // -1 = no greater element to the right
  stack <int> st;
  for(int i=n-1;i>=0;--i) {
    while(!st.empty() && arr[st.top()] <= arr[i]) st.pop();   // not strictly greater
    if(!st.empty()) nge[i] = st.top();
    st.push(i);
  }
  return nge;
}

// To execute C++, please define "int main()"
int main() {
  vector <int> arr {5, 3, 10, 8, 8, 10};
  for(auto&nge: next_greater_element(arr)) {cout<<nge<<" ";}cout<<"\n";
  arr = {4, 2, 6, 4, 5, 2, 4,  7, 3,  7};
  for(auto&nge: next_greater_element(arr)) {cout<<nge<<" ";}cout<<"\n";
  arr = {5, 5, 5, 5, 5};
  for(auto&nge: next_greater_element(arr)) {cout<<nge<<" ";}cout<<"\n";
  arr = {5, 6, 7, 8, 9};
  for(auto&nge: next_greater_element(arr)) {cout<<nge<<" ";}cout<<"\n";
  return 0;
}

// # Next Greater Element

// Given an array of integers, `arr`, return an array of the same length, `NGE`, such that `NGE[i]` is the first index `j` after `i` such that `arr[j] > arr[i]`. If there is no such `j`, then `NGE[i] = -1`.

// Example 1:
// Index:   0  1   2  3  4   5
// arr =   [5, 3, 10, 8, 8, 10]
// Output: [2, 2, -1, 5, 5, -1]

// Example 2:
// Index:   0  1  2  3  4  5  6   7  8   9
// arr =   [4, 2, 6, 4, 5, 2, 4,  7, 3,  7]
// Output: [2, 2, 7, 4, 7, 6, 7, -1, 9, -1]

// Example 3:
// Index:    0   1   2   3   4
// arr =   [ 5,  5,  5,  5,  5]
// Output: [-1, -1, -1, -1, -1]

// Example 4:
// Index:   0  1  2  3   4
// arr =   [5, 6, 7, 8,  9]
// Output: [1, 2, 3, 4, -1]

// Constraints:

// - `1 <= arr.length <= 10^5`
// - `-10^9 <= arr[i] <= 10^9`
