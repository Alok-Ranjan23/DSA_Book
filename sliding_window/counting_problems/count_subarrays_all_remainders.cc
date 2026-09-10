/**
 * @file count_subarrays_all_remainders.cc
 * @brief Count subarrays containing all three remainders (0, 1, 2) modulo 3.
 *
 * Uses the complement: allRemainders = total - atMostTwoRemainders.
 * The atmost_two_remainders helper uses a maximum sliding window with a hash map
 * tracking distinct (arr[i] % 3) values. The window can hold at most 2 distinct
 * remainders; each grow step contributes (r - l) new subarrays.
 *
 * Key Concepts:
 * - Complement technique: atLeast(3 distinct) = total - atMost(2 distinct)
 * - Maximum sliding window with hash map for distinct-count tracking
 * - Counting trick: each grow step adds (r - l) subarrays
 *
 * Time Complexity: O(n) where n = arr.size(). The hash map has at most 3 entries
 *   so all map operations are O(1). Each element visited at most twice.
 * Space Complexity: O(1) extra space (hash map has at most 3 keys: 0, 1, 2).
 */

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/**
 * @brief Counts subarrays with at most 2 distinct remainders mod 3 (helper)
 * @param arr Vector of positive integers
 * @return Number of subarrays with at most 2 distinct remainders
 */
  int n = arr.size();
  int l = 0;
  int r = 0;
  int count_subarray = 0;
  unordered_map<int, int> umap;
  while(r<n) {
    bool can_grow = umap.count(arr[r]%3) || static_cast<int>(umap.size()) < 2;
    if(can_grow) {
      umap[arr[r]%3]++;
      r+=1;
      count_subarray += (r-l);
    } else {
      umap[arr[l]%3]--;
      if(umap[arr[l]%3]==0) umap.erase(arr[l]%3);
      l+=1;
    }
  }
  return count_subarray;
}

/**
 * @brief Counts subarrays containing all 3 remainders (0, 1, 2) mod 3
 * @param arr Vector of positive integers
 * @return Number of subarrays with all three remainders present
 */
int count_subarray_with_all_remainders(vector<int>& arr) {
  int n = arr.size();
  int total_subarrays = n*(n+1)/2;
  return total_subarrays - atmost_two_remainders(arr);
}

// To execute C++, please define "int main()"
int main() {
  vector<int> arr {9, 8, 7};
  cout<<count_subarray_with_all_remainders(arr)<<"\n";
  arr = {1, 2, 3, 4, 5};
  cout<<count_subarray_with_all_remainders(arr)<<"\n";
  arr = {1, 3, 4, 6, 7, 9};
  cout<<count_subarray_with_all_remainders(arr)<<"\n"; 
  return 0;
}

// # Count Subarrays With All Remainders

// Given an array of positive integers, `arr`, return the number of subarrays that have at least one of each of the following:

// 1. a multiple of 3
// 2. a number with remainder 1 when divided by 3
// 3. a number with remainder 2 when divided by 3

// Example 1: arr = [9, 8, 7]
// Output: 1
// The subarray [9, 8, 7] counts because:
//   - 9 % 3 is 0
//   - 7 % 3 is 1
//   - 8 % 3 is 2

// Example 2: arr = [1, 2, 3, 4, 5]
// Output: 6
// The subarrays are:
//   - [1, 2, 3]
//   - [2, 3, 4]
//   - [3, 4, 5]
//   - [1, 2, 3, 4]
//   - [2, 3, 4, 5]
//   - [1, 2, 3, 4, 5]

// Example 3: arr = [1, 3, 4, 6, 7, 9]
// Output: 0
// There are no numbers with remainder 2 when divided by 3.

// Constraints:

// - `0 <= arr.length <= 10^5`
// - `1 <= arr[i] <= 10^9`
