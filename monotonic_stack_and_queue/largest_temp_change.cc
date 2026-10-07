/**
 * @file largest_temp_change.cc
 * @brief Maximum (max - min) over every window of exactly k days
 *
 * Slide a fixed-size window of length k across the array and, for each
 * window, take max - min. Two monotonic deques give the window max and min in
 * O(1) at every step, so the whole scan is linear instead of O(n * k).
 *
 * Key Concepts:
 * - dq_max holds indices with non-increasing values (front = window max);
 *   before pushing r, pop from the back every index with a smaller value --
 *   it can never be a window max again while r is in the window
 * - dq_min is the mirror (non-decreasing values, front = window min)
 * - Fixed-size window [l, r): once r - l == k, record the answer, evict
 *   index l from the deque fronts if it is there, then advance l
 *
 * Time Complexity: O(n)
 *   - r advances n times; each index is pushed to and popped from each deque
 *     at most once, so all inner while-loops together cost O(n).
 *
 * Space Complexity: O(k)
 *   - Every index in a deque lies in the current window, so each deque holds
 *     at most k indices.
 */
#include <iostream>
#include <vector>
#include <deque>
#include <limits>
using namespace std;

/**
 * @brief Return the largest max - min among all k-length subarrays
 *
 * @param arr Daily temperatures (length >= 2)
 * @param k   Window length (2 <= k <= arr.size())
 * @return    max over all windows of (window max - window min)
 *
 * Algorithm:
 * 1. For each new index r: pop smaller values off dq_max's back and larger
 *    values off dq_min's back, then push r to both.
 * 2. When the window [l, r] reaches size k, update res with
 *    arr[dq_max.front()] - arr[dq_min.front()].
 * 3. Remove l from either deque front if it is there, then advance l.
 *
 * Time:  O(n) -- amortized O(1) per index (each pushed/popped once per deque)
 * Space: O(k) -- deques only hold indices inside the window
 */
//Time O(n)   (each index pushed/popped at most once per deque)
//Space O(k)  (deques hold only in-window indices)
int largest_temp_change(vector<int>& arr,int k) {
  int l=0,r=0;
  int n=arr.size();
  deque<int> dq_max;                               // values non-increasing, front = max
  deque<int> dq_min;                               // values non-decreasing, front = min
  int res = numeric_limits<int>::min();
  while(r<n) {
    while(!dq_max.empty() && arr[dq_max.back()]<arr[r]) dq_max.pop_back();
    while(!dq_min.empty() && arr[dq_min.back()]>arr[r]) dq_min.pop_back();
    dq_max.push_back(r);
    dq_min.push_back(r);
    r+=1;
    if(r-l==k) {                                   // window [l, r) has exactly k days
      res = max(res,arr[dq_max.front()] - arr[dq_min.front()]);
      if(l==dq_max.front()) dq_max.pop_front();    // evict l if it is the max
      if(l==dq_min.front()) dq_min.pop_front();    // evict l if it is the min
      l+=1;
    }
  } 
  return res;
}

// To execute C++, please define "int main()"
int main() {
  vector<int> arr {12, 13, 12, 13, 13, 12, 11, 12};int k = 3;
  cout<<largest_temp_change(arr, k)<<"\n";
  arr = {10, 30}; k = 2;
  cout<<largest_temp_change(arr, k)<<"\n";
  return 0;
}

// # Largest Temperature Change

// We are trying to install sensors that are sensitive to sudden temperature changes. The sensors should be fine as long as the temperature doesn't change too much within any k-day period.

// Given an array `temperatures` with at least two integers, where each element represents the average temperature on a given day, and a number `k` with `2 ≤ k ≤ len(temperatures)`, return the maximum difference between average temperatures in a k-day period.

// Example 1: temperatures = [12, 13, 12, 13, 13, 12, 11, 12], k = 3
// Output: 2. The 3-day period with the maximum difference is [13, 12, 11], which has a difference of 13 - 11.

// Example 2: temperatures = [10, 30], k = 2
// Output: 20

// Constraints:

// - `2 <= temperatures.length <= 10^5`
// - `-100 <= temperatures[i] <= 100` (temperatures in reasonable range)
// - `2 <= k <= temperatures.length`
