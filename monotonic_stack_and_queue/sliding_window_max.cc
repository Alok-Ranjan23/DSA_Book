/**
 * @file sliding_window_max.cc
 * @brief Maximum of every contiguous window of size k, from left to right
 *
 * A monotonic deque of indices keeps the "max candidates" of the current
 * window with values non-increasing from front to back, so the front is
 * always the window maximum. The window is [l, r) and slides one step at a
 * time once it reaches size k.
 *
 * Key Concepts:
 * - Before pushing r, pop every index with a smaller value from the back:
 *   r is newer and larger, so those indices can never be a window max again
 * - Equal values are kept (pop only on strictly smaller), which is harmless
 *   and keeps the front-eviction check by index simple
 * - When the window slides, index l leaves; it is evicted only if it is the
 *   deque front (otherwise it was already popped from the back)
 *
 * Example trace (arr = 10 20 30 40 30 20 10, k = 3), deque holds indices:
 *   window [40 30 20] -> dq = {3, 4, 5}; after 40 leaves -> dq = {4, 5}
 *
 * Time Complexity: O(n)
 *   - r advances n times and each index is pushed once and popped at most
 *     once (from the back or the front), so all deque work is O(n) total.
 *     Brute force would be O(n * k).
 *
 * Space Complexity: O(k) auxiliary + O(n - k + 1) output
 *   - The deque only holds indices inside the current window (at most k).
 */
#include <iostream>
#include <vector>
#include <deque>
using namespace std;

// 10 20 30 40 30 20 10
//                 l,     r
// dq: {4,5}
/**
 * @brief Return the maximum of each k-length window
 *
 * @param arr Input values (non-empty)
 * @param k   Window size (1 <= k <= arr.size())
 * @return    Vector of n - k + 1 window maxima, left to right
 *
 * Algorithm:
 * 1. For each r: pop smaller values from the deque's back, push r, advance r.
 * 2. When r - l == k, record arr[dq.front()], evict l if it is the front,
 *    and advance l.
 *
 * Time:  O(n) -- amortized O(1) deque work per index
 * Space: O(k) -- deque holds only in-window indices (plus the output)
 */
//Time O(n)   (each index pushed/popped at most once)
//Space O(k)  (deque bounded by window size; output is n-k+1)
vector<int> sliding_max(vector<int>& arr,int k) {
  int l=0,r=0;
  int n=arr.size();
  deque<int> dq;                                   // values non-increasing, front = window max
  vector<int> res;
  while(r<n) {
    while(!dq.empty() && arr[dq.back()]<arr[r]) dq.pop_back();   // drop dominated indices
    dq.push_back(r);
    r+=1;
    if(r-l==k) {                                   // window [l, r) has exactly k elements
      res.push_back(arr[dq.front()]);
      if(l==dq.front()) dq.pop_front();            // l is leaving the window
      l+=1;
    }
  } 
  return res;
}

// To execute C++, please define "int main()"
int main() {
  vector<int> arr {10, 20, 30, 40, 30, 20, 10};int k = 2;
  for(auto& val: sliding_max(arr,k)) {cout<<val<<" ";} cout<<"\n";
  arr = {10, 20, 30, 40, 30, 20, 10}; k = 3;
  for(auto& val: sliding_max(arr,k)) {cout<<val<<" ";} cout<<"\n";
  return 0;
}

// # Sliding Window Max

// Given a non-empty integer array, `arr`, and a subarray size, `k`, find the maximum element in each subarray of size `k`, from left to right.

// Example 1: arr = [10, 20, 30, 40, 30, 20, 10], k = 2
// Output: [20, 30, 40, 40, 30, 20]

// Example 2: arr = [10, 20, 30, 40, 30, 20, 10], k = 3
// Output: [30, 40, 40, 40, 30]

// Constraints:

// - `1 <= arr.length <= 10^5`
// - `-10^9 <= arr[i] <= 10^9`
// - `1 <= k <= arr.length`
