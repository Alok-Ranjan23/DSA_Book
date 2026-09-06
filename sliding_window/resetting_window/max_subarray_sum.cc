/**
 * @file max_subarray_sum.cc
 * @brief Compute the maximum sum of any non‑empty subarray (Kadane's algorithm variant).
 *
 * The implementation first handles the all‑negative case by returning the largest element.
 * For the general case it slides a window forward, expanding while the running sum stays
 * non‑negative; otherwise the window is reset. This yields the same result as the classic
 * Kadane DP in O(n) time.
 *
 * Key Concepts:
 * - Resetting sliding window / Kadane's algorithm
 * - Early guard for all‑negative arrays
 *
 * Time Complexity: O(n) where n = arr.size().
 * Space Complexity: O(1) extra space.
 */

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int max_subarray_sum(vector<int>& arr) {
  //Edge Case All Negative elements
  int max_val = *max_element(arr.begin(),arr.end());
  if(max_val<0) return max_val;
  int n = arr.size();
  int r = 0;
  int window_sum = 0;
  int max_sum = 0;
  while(r<n) {
    bool can_grow = window_sum + arr[r] >= 0;
    if(can_grow) {
      window_sum += arr[r];
      r+=1;
      max_sum = max(max_sum, window_sum);
    }
    else {
      window_sum = 0;
      r = r+1;
    }
  }
  return max_sum;
}

// To execute C++, please define "int main()"
int main() {
  vector<int> arr {1, 2, 3, -2, 1};
  cout<<max_subarray_sum(arr)<<"\n";
  arr = {1, 2, 3, -2, 7};
  cout<<max_subarray_sum(arr)<<"\n";
  arr = {1, 2, 3, -8, 7};
  cout<<max_subarray_sum(arr)<<"\n";
  arr = {-2, -3, -4};
  cout<<max_subarray_sum(arr)<<"\n";
  return 0;
}

// # Max Subarray Sum

// Given a non-empty array `arr` of integers (which can be negative), find the non-empty subarray with the maximum sum and return its sum.

// Example 1: arr = [1, 2, 3, -2, 1]
// Output: 6. The subarray with the maximum sum is [1, 2, 3].

// Example 2: arr = [1, 2, 3, -2, 7]
// Output: 11. The subarray with the maximum sum is the whole array.

// Example 3: arr = [1, 2, 3, -8, 7]
// Output: 7. The subarray with the maximum sum is [7].

// Example 4: arr = [-2, -3, -4]
// Output: -2. The subarray cannot be empty.

// Constraints:

// - `1 <= len(arr) <= 10^5`
// - Each element in `arr` is an integer between `-10^6` and `10^6`
