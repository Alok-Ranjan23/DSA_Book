/**
 * @file count_subarray_exactly_kBad.cc
 * @brief Count subarrays with exactly k bad days (sales < 10).
 *
 * Uses the identity: exactly(k) = atMost(k) - atMost(k-1).
 * When k == 0, exactly(0) = atMost(0) directly.
 * The atMost helper uses a maximum sliding window counting trick.
 *
 * Key Concepts:
 * - Inclusion-exclusion: exactly(k) = atMost(k) - atMost(k-1)
 * - Two passes of the atMost sliding window
 *
 * Time Complexity: O(n) where n = sales.size(). Two O(n) passes of atMost.
 * Space Complexity: O(1) extra space.
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Counts the number of subarrays with at most k bad days (helper)
 * @param sales Vector of daily sales figures
 * @param k Maximum number of bad days allowed
 * @return Number of valid subarrays
 */
  int n = sales.size();
  int l = 0;
  int r = 0;
  int bad_days=0;
  int count_subarray = 0;
  while(r<n) {
    bool can_grow = sales[r]>=10 || bad_days < k;
    if(can_grow) {
      if(sales[r]<10) bad_days+=1;
      r+=1;
      count_subarray += (r-l);
    } else {
      if(sales[l]<10) bad_days-=1;
      l+=1;
    }
  }
  return count_subarray;
}

/**
 * @brief Counts subarrays with exactly k bad days: atMost(k) - atMost(k-1)
 * @param sales Vector of daily sales figures
 * @param k Exact number of bad days required
 * @return Number of subarrays with exactly k bad days
 */
int count_exactly_k_bad_days(vector<int>& sales, int k) {
  if(k==0) return count_atmost_k_bad_days(sales, k);
  return count_atmost_k_bad_days(sales, k) - count_atmost_k_bad_days(sales, k-1);
}

// To execute C++, please define "int main()"
int main() {
  vector<int> sales {0,20,5}; int k = 1;
  cout<<count_exactly_k_bad_days(sales,k)<<"\n";
  sales = {10,20,30}; k = 1;
  cout<<count_exactly_k_bad_days(sales,k)<<"\n";
  sales = {0,5,8}; k = 2;
  cout<<count_exactly_k_bad_days(sales,k)<<"\n";
  return 0;
}

// # Count Subarrays With Exactly K Bad Days

// Given an array, `sales`, where `sales[i]` is the number of sales on day `i`, count the number of subarrays with exactly `k` bad days.

// A _bad day_ is a day with fewer than 10 sales.

// Example 1: sales = [0, 20, 5], k = 1
// Output: 4
// The subarrays [0], [0, 20], [20, 5], and [5] have 1 bad day each.

// Example 2: sales = [10, 20, 30], k = 1
// Output: 0
// No subarrays have exactly 1 bad day.

// Example 3: sales = [0, 5, 8], k = 2
// Output: 2
// The subarrays [0, 5] and [5, 8] have exactly 2 bad days.

// Constraints:

// - `0 <= sales.length <= 10^5`
// - `0 <= sales[i] < 10^3`
// - `0 <= k <= 10^5`
