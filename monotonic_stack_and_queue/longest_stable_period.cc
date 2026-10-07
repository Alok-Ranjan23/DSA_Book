/**
 * @file longest_stable_period.cc
 * @brief Longest subarray whose (max - min) is at most t
 *
 * Variable-size sliding window [l, r). The window is extended by arr[r] only
 * if the new range max(window max, arr[r]) - min(window min, arr[r]) stays
 * <= t; otherwise it shrinks from the left. Two monotonic deques provide the
 * window max and min in O(1).
 *
 * Key Concepts:
 * - dq_max: indices with non-increasing values (front = window max);
 *   dq_min: indices with non-decreasing values (front = window min)
 * - Check BEFORE mutating: the deques are only touched (back-pops + push)
 *   when the window actually grows, so they always describe exactly [l, r)
 * - Whenever l < r the window is non-empty, and its max/min are always still
 *   in the deques, so dq_max.front() / dq_min.front() are safe to read
 * - Shrinking only needs to evict index l from a deque front if it is there;
 *   indices popped earlier from the back were dominated and are irrelevant
 *
 * Time Complexity: O(n)
 *   - Every loop iteration advances either r or l, and each moves at most n
 *     times, so there are at most 2n iterations. Each index is pushed to and
 *     popped from each deque at most once, so all back-pops cost O(n) total.
 *
 * Space Complexity: O(n)
 *   - The deques only hold indices from the current window, which can be the
 *     whole array in the worst case (e.g. all temperatures equal).
 */
#include <iostream>
#include <vector>
#include <deque>
using namespace std;

/**
 * @brief Return the length of the longest subarray with max - min <= t
 *
 * @param arr Daily temperatures (length >= 2)
 * @param t   Allowed temperature spread (t >= 0)
 * @return    Length of the longest stable period (at least 1)
 *
 * Algorithm:
 * 1. can_grow is true if the window is empty (l == r) or if adding arr[r]
 *    keeps max - min <= t (computed from the deque fronts and arr[r]).
 * 2. If it can grow: pop dominated indices from both deque backs, push r,
 *    advance r, and update max_len with r - l.
 * 3. Otherwise: evict l from either deque front if present and advance l.
 *
 * Time:  O(n) -- at most 2n iterations; amortized O(1) deque work per index
 * Space: O(n) -- deques bounded by the window length
 */
//Time O(n)   (l and r each move at most n times; each index pushed/popped once)
//Space O(n)  (deques bounded by window size)
int longest_stable_period(vector<int>& arr,int t) {
  int l=0,r=0;
  int n=arr.size();
  deque<int> dq_max;                               // values non-increasing, front = max of [l, r)
  deque<int> dq_min;                               // values non-decreasing, front = min of [l, r)
  int max_len = 0;
  while(r<n) {
    // empty window always grows; otherwise check the spread including arr[r]
    bool can_grow = (l == r) ||
        (max(arr[dq_max.front()],arr[r]) - min(arr[dq_min.front()],arr[r]) <= t);
    if(can_grow) {
      while (!dq_max.empty() && arr[dq_max.back()] < arr[r]) dq_max.pop_back();
      while (!dq_min.empty() && arr[dq_min.back()] > arr[r]) dq_min.pop_back();
      dq_max.push_back(r);
      dq_min.push_back(r);
      r+=1;
      max_len = max(max_len,r-l);
    } else {                                       // too unstable: shrink from the left
      if (l == dq_max.front()) dq_max.pop_front();
      if (l == dq_min.front()) dq_min.pop_front();
      l+=1;
    }
  } 
  return max_len;
}

// To execute C++, please define "int main()"
int main() {
  vector<int> arr {12, 16, 14, 15, 13, 17};int t = 3;
  cout<<longest_stable_period(arr, t)<<"\n";
  arr = {30, 10}; t = 100;
  cout<<longest_stable_period(arr, t)<<"\n";
  arr = {30, 10}; t = 1;
  cout<<longest_stable_period(arr, t)<<"\n";
  return 0;
}

// # Longest Stable Period

// We are planning an expedition, and we don't know exactly how many days it will take. We don't want to carry too many different types of clothes, so we want to know the longest period of time where temperatures are stable, meaning that they don't change by more than `t` degrees. That will be the ideal time for our expedition.

// Given an array `temperatures` with at least two integers, where each element represents the average temperature on a given day, and a number `t`, return the length of the longest subarray where the difference between the maximum and minimum temperature is at most `t`.

// Example 1: temperatures = [12, 16, 14, 15, 13, 17], t = 3
// Output: 4. The longest stable period is [16, 14, 15, 13].

// Example 2: temperatures = [30, 10], t = 100
// Output: 2

// Example 3: temperatures = [30, 10], t = 1
// Output: 1

// Constraints:

// - `2 <= temperatures.length <= 10^5`
// - `-100 <= temperatures[i] <= 100` (temperatures in reasonable range)
// - `0 <= t <= 200` (temperature difference threshold)
