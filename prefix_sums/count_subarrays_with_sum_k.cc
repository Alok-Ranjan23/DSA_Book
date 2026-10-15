/**
 * @file count_subarrays_with_sum_k.cc
 * @brief Count the subarrays whose elements sum to exactly k
 *
 * A subarray arr[j+1..i] has sum prefix[i] - prefix[j]. It equals k exactly
 * when prefix[j] == prefix[i] - k. So, scanning left to right, the number of
 * subarrays ending at i with sum k is the number of earlier prefixes equal
 * to prefix[i] - k. A hash map of prefix-sum frequencies answers that in
 * O(1).
 *
 * Key Concepts:
 * - Prefix sum + hash map (the "two-sum on prefix sums" pattern)
 * - umap[0] = 1 represents the empty prefix, so subarrays starting at
 *   index 0 are counted
 * - Look up BEFORE inserting the current prefix, so a subarray is never
 *   matched with itself (matters when k == 0)
 * - Works with negative numbers (a sliding window would not)
 * - Result is long long: an all-zero array with k = 0 has n(n+1)/2
 *   subarrays (~5 * 10^9 for n = 10^5), which overflows int
 *
 * Time Complexity: O(n)
 *   - One pass to build prefixes and one pass with O(1) average hash-map
 *     operations. Checking every subarray would be O(n^2).
 *
 * Space Complexity: O(n)
 *   - The prefix array and up to n distinct keys in the map.
 */
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/**
 * @brief Return the number of subarrays of arr with sum k
 *
 * @param arr Input integers (may contain negatives)
 * @param k   Target sum
 * @return    Number of (start, end) pairs with arr[start..end] summing to k
 *
 * Algorithm:
 * 1. Build prefix_arr[i] = arr[0] + ... + arr[i].
 * 2. Start the map with {0: 1} (empty prefix).
 * 3. For each prefix value: add umap[value - k] to count, then increment
 *    umap[value].
 *
 * Time:  O(n) -- average O(1) hash-map operations per element
 * Space: O(n) -- prefix array + map
 */
//Time O(n)   (one pass, O(1) average map lookups)
//Space O(n)  (prefix array + frequency map)
long long count_subarrays_with_sumK(vector<int>& arr,int k) {
  int n = arr.size();
  if(n==0) return 0;
  vector<int> prefix_arr(n);                       // prefix_arr[i] = arr[0..i]
  prefix_arr[0] = arr[0];
  for(int i=1;i<n;++i) prefix_arr[i] = prefix_arr[i-1] + arr[i];
  unordered_map<int,int> umap;                     // prefix value -> how many times seen
  umap[0]=1;                                       // empty prefix
  long long count = 0;
  for(auto& val: prefix_arr) {
    if(umap.count(val-k)) count+=umap[val-k];      // earlier prefixes that leave sum k
    umap[val]++;                                   // insert after lookup
  }
  return count;
}

// To execute C++, please define "int main()"
int main() {
  vector<int> arr {1,2,3,2,1};int k = 3;
  cout<<count_subarrays_with_sumK(arr,k)<<"\n";
  arr = {-1, -2, -3, 2, 1};k = -3;
  cout<<count_subarrays_with_sumK(arr,k)<<"\n";
  return 0;
}

// # Count Subarrays With Sum K

// Given an array of integers, `arr`, and an integer `k`, return the number of subarrays in `arr` with sum `k`.

// Example 1:
// arr = [1, 2, 3, 2, 1], k = 3

// Output: 3
// The subarrays with sum 3 are [1, 2], [3], and [2, 1].

// Example 2:
// arr = [-1, -2, -3, 2, 1], k = -3

// Output: 4
// The subarrays with sum -3 are
//     [-1, -2]
//     [-3]
//     [-2, -3, 2]
//     [-1, -2, -3, 2, 1]

// Constraints:

// - The length of `arr` is at most `10^5`
// - Each element in `arr` is an integer between `-10^4` and `10^4`
