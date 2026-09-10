/**
 * @file count_subarrays_bad_days_range.cc
 * @brief Count subarrays whose number of bad days falls within [k1, k2].
 *
 * Uses the identity: range(k1, k2) = atMost(k2) - atMost(k1-1).
 * When k1 == 0, range(0, k2) = atMost(k2) directly (since atMost(-1) = 0).
 * The atMost helper uses a maximum sliding window counting trick.
 *
 * Key Concepts:
 * - Range counting via two atMost queries
 * - Reuse of the atMost sliding window counting function
 *
 * Time Complexity: O(n) where n = sales.size(). Two O(n) passes of atMost.
 * Space Complexity: O(1) extra space.
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Counts subarrays with at most k bad days (helper)
 * @param sales Vector of daily sales figures
 * @param k Maximum number of bad days allowed
 * @return Number of valid subarrays
 */
  int n = sales.size();
  int l = 0, r = 0;
  int count_subarrays = 0;
  int bad_days = 0;
  while(r<n) {
    bool can_grow = sales[r]>=10 || bad_days < k;
    if(can_grow) {
      if(sales[r]<10) bad_days +=1;
      r+=1;
      count_subarrays += (r-l);
    } else {
      if(sales[l]<10) bad_days-=1;
      l+=1;
    }
  }
  return count_subarrays;
}


/**
 * @brief Counts subarrays with bad days in range [k1, k2]: atMost(k2) - atMost(k1-1)
 * @param sales Vector of daily sales figures
 * @param k1 Minimum number of bad days required
 * @param k2 Maximum number of bad days allowed
 * @return Number of subarrays with bad days count in [k1, k2]
 */
int count_subarrays_bad_days_range(vector<int>& sales,int k1, int k2) {
  if(k1==0) return count_subarrays_atmostK_bad_days(sales, k2);
  return count_subarrays_atmostK_bad_days(sales, k2) - count_subarrays_atmostK_bad_days(sales, k1-1);
}

// To execute C++, please define "int main()"
int main() {
  vector<int> sales {0, 20, 5}; int k1 = 2; int k2 = 2;
  cout<<count_subarrays_bad_days_range(sales,k1, k2)<<"\n";
  sales = {0, 20, 5}; k1 = 1; k2 = 2;
  cout<<count_subarrays_bad_days_range(sales,k1, k2)<<"\n";
  sales = {10, 20, 30}; k1 = 1; k2 = 2;
  cout<<count_subarrays_bad_days_range(sales,k1, k2)<<"\n";
  return 0;
}

// # Count Subarrays With Bad Days In Range

// We are given an array, `sales`, where `sales[i]` is the number of sales on day `i`. We are also given two numbers, `k1` and `k2`, with `0 ≤ k1 ≤ k2`.

// Count the number of subarrays with at least `k1` bad days and at most `k2` bad days.

// A _bad day_ is a day with fewer than 10 sales.

// Example 1: sales = [0, 20, 5], k1 = 2, k2 = 2
// Output: 1
// The subarray [0, 20, 5] has 2 bad days.

// Example 2: sales = [0, 20, 5], k1 = 1, k2 = 2
// Output: 5
// - The subarray [0, 20, 5] has 2 bad days.
// - The subarrays [0], [0, 20], [20, 5], and [5] have 1 bad day.

// Example 3: sales = [10, 20, 30], k1 = 1, k2 = 2
// Output: 0
// No subarrays have any bad days.

// Constraints:

// - `0 <= sales.length <= 10^5`
// - `0 <= sales[i] <= 10^3`
// - `0 <= k1 <= k2 <= 10^5`
