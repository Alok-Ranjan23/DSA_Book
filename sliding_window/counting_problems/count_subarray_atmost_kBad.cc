/**
 * @file count_subarray_atmost_kBad.cc
 * @brief Count subarrays with at most k bad days (sales < 10).
 *
 * Uses a maximum sliding window that grows while the number of bad days in the
 * window is <= k. Each time r advances, (r - l) new valid subarrays are added
 * (all subarrays ending at r-1 that start anywhere in [l, r-1]).
 * When bad_days exceeds k, the window shrinks from the left.
 *
 * Key Concepts:
 * - Maximum sliding window adapted for counting (not just max length)
 * - Counting trick: each grow step contributes (r - l) new subarrays
 *
 * Time Complexity: O(n) where n = sales.size(). Each element is visited at most
 *   twice (once by r, once by l).
 * Space Complexity: O(1) extra space.
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Counts the number of subarrays with at most k bad days
 * @param sales Vector of daily sales figures
 * @param k Maximum number of bad days allowed in a subarray
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


// To execute C++, please define "int main()"
int main() {
  vector<int> sales {0,20,5}; int k = 1;
  cout<<count_atmost_k_bad_days(sales,k)<<"\n";
  sales = {10,20,30}; k = 1;
  cout<<count_atmost_k_bad_days(sales,k)<<"\n";
  sales = {0,5,8}; k = 1;
  cout<<count_atmost_k_bad_days(sales,k)<<"\n";
  return 0;
}

// # Count Subarrays With At Most K Bad Days

// Given an array, `sales`, where `sales[i]` is the number of sales on day `i`, count the number of subarrays with at most `k` bad days.

// A _bad day_ is a day with fewer than 10 sales.

// Example 1: sales = [0, 20, 5], k = 1
// Output: 5
//   - [20] has 0 bad days
//   - [0], [0, 20], [20, 5], and [5] have 1 bad day each

// Example 2: sales = [10, 20, 30], k = 1
// Output: 6
// All subarrays have 0 bad days

// Example 3: sales = [0, 5, 8], k = 1
// Output: 3
// Only [0], [5], and [8] have at most 1 bad day

// Constraints:

// - `0 <= sales.length <= 10^5`
// - `0 <= sales[i] < 10^3`
// - `0 <= k <= 10^5`
