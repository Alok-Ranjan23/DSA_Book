/**
 * @file count_subarray_atleast_kBad.cc
 * @brief Count subarrays with at least k bad days (sales < 10).
 *
 * Uses the complement approach: atLeast(k) = total_subarrays - atMost(k-1).
 * The atMost helper uses a maximum sliding window counting trick where each
 * grow step contributes (r - l) new subarrays.
 *
 * Key Concepts:
 * - Complement technique: atLeast(k) = total - atMost(k-1)
 * - Reuse of the atMost sliding window counting function
 *
 * Time Complexity: O(n) where n = sales.size(). The atMost helper is O(n).
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
 * @brief Counts subarrays with at least k bad days using complement: total - atMost(k-1)
 * @param sales Vector of daily sales figures
 * @param k Minimum number of bad days required
 * @return Number of subarrays with at least k bad days
 */
int count_exactly_k_bad_days(vector<int>& sales, int k) {
  int n = sales.size();
  if(k==0) return n*(n+1)/2;
  return  n*(n+1)/2 - count_atmost_k_bad_days(sales, k-1);
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

// # Count Subarrays With At Least K Bad Days

// Given an array, `sales`, where `sales[i]` is the number of sales on day `i`, count the number of subarrays with at least `k` bad days.

// A _bad day_ is a day with fewer than 10 sales.

// Example 1: sales = [0, 20, 5], k = 1
// Output: 5
//   - the subarrays [0], [0, 20], [20, 5], and [5] have 1 bad day each
//   - [0, 20, 5] has 2 bad days

// Example 2: sales = [10, 20, 30], k = 1
// Output: 0
// No subarrays have any bad days.

// Example 3: sales = [0, 5, 8], k = 2
// Output: 3
// The subarrays [0, 5], [5, 8], and [0, 5, 8] have at least 2 bad days.

// Constraints:

// - `0 <= sales.length <= 10^5`
// - `0 <= sales[i] < 10^3`
// - `0 <= k <= 10^5`
