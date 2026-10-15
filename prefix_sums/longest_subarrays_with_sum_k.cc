/**
 * @file longest_subarrays_with_sum_k.cc
 * @brief Length of the longest subarray whose elements sum to exactly k
 *
 * A subarray arr[j+1..i] has sum prefix[i] - prefix[j], so it equals k when
 * prefix[j] == prefix[i] - k. Its length is i - j, which is largest when j
 * is as small as possible. So store the FIRST index at which each prefix
 * value appears, and for each i look up prefix[i] - k.
 *
 * Key Concepts:
 * - Prefix sum + hash map from prefix value -> earliest index
 * - umap[0] = -1 represents the empty prefix "before index 0", so a
 *   subarray starting at 0 has length i - (-1) = i + 1
 * - Only insert a prefix if it is not already present; overwriting would
 *   store a later index and shorten the answers
 * - Works with negative numbers (a sliding window would not)
 * - max_len starts at -1, so -1 is returned when no subarray sums to k
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
 * @brief Return the length of the longest subarray of arr with sum k
 *
 * @param arr Input integers (may contain negatives)
 * @param k   Target sum
 * @return    Maximum length of a subarray summing to k, or -1 if none
 *
 * Algorithm:
 * 1. Build prefix_arr[i] = arr[0] + ... + arr[i].
 * 2. Start the map with {0: -1} (empty prefix).
 * 3. For each i: if prefix_arr[i] - k is in the map at index l, update
 *    max_len with i - l. Then record i for prefix_arr[i] if it is new.
 *
 * Time:  O(n) -- average O(1) hash-map operations per element
 * Space: O(n) -- prefix array + map
 */
//Time O(n)   (one pass, O(1) average map lookups)
//Space O(n)  (prefix array + first-index map)
int longest_subarrays_with_sumK(vector<int>& arr,int k) {
  int n = arr.size();
  if(n==0) return -1;
  vector<int> prefix_arr(n);                       // prefix_arr[i] = arr[0..i]
  prefix_arr[0] = arr[0];
  for(int i=1;i<n;++i) prefix_arr[i] = prefix_arr[i-1] + arr[i];
  unordered_map<int,int> umap;                     // prefix value -> FIRST index seen
  umap[0]=-1;                                      // empty prefix before index 0
  int max_len = -1;                                // -1 = no subarray found
  for(int i=0;i<n;++i) {
    if(umap.count(prefix_arr[i]-k)) {
      int l = umap.at(prefix_arr[i]-k);            // arr[l+1..i] sums to k
      max_len = max(max_len,i-l);
    }
    if(!umap.count(prefix_arr[i])) {               // keep earliest index only
        umap[prefix_arr[i]] = i;
    }
  }
  return max_len;
}

// To execute C++, please define "int main()"
int main() {
  vector<int> arr {1,2,3,2,1};int k = 3;
  cout<<longest_subarrays_with_sumK(arr,k)<<"\n";
  arr = {-1, -2, -3, 2, 1};k = -3;
  cout<<longest_subarrays_with_sumK(arr,k)<<"\n";
  return 0;
}

// # Longest Subarray With Sum K

// Given an array of integers, `arr`, and an integer `k`, return the length of the longest subarray in `arr` with sum `k`, or `-1` if there is no such subarray.

// Example 1:
// arr = [1, 2, 3, 2, 1], k = 3

// Output: 2
// The longest subarrays with sum 3 are [1, 2] and [2, 1].

// Example 2:
// arr = [-1, -2, -3, 2, 1], k = -3

// Output: 5
// The longest subarray with sum -3 is [-1, -2, -3, 2, 1].

// Constraints:

// - The length of `arr` is at most `10^5`
// - Each element in `arr` is an integer between `-10^4` and `10^4`
