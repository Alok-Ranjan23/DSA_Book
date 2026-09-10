/**
 * @file count_good_subarrays_with_atleast_k_sales.cc
 * @brief Count subarrays with no bad days and at least k total sales.
 *
 * Two-phase approach:
 * 1. Split the array into maximal segments of consecutive good days (sales >= 10).
 * 2. For each segment, count subarrays with sum >= k using a minimum sliding window.
 *
 * Key Concepts:
 * - Segment splitting: break array at bad days into independent good-day runs
 * - Minimum sliding window for counting subarrays with sum >= k
 * - Counting trick: once sum >= k at position [l, r-1], all extensions
 *   [l, r-1], [l, r], ..., [l, n-1] are also valid → add (n - r + 1)
 *
 * Time Complexity: O(n) where n = sales.size(). The splitting pass is O(n),
 *   and the sum of all segment lengths is at most n, so the total sliding
 *   window work across all segments is also O(n).
 * Space Complexity: O(n) for storing the good-day segments.
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Counts subarrays (of a good-day-only segment) with total sales >= k
 *
 * Uses a minimum sliding window: grow (r++) while sum < k, then once sum >= k,
 * all subarrays starting at l and ending at r-1, r, r+1, ..., n-1 are valid.
 * So we add (n - r + 1) and shrink (l++) to find more valid windows.
 *
 * @param sales Vector of sales in a good-day-only segment
 * @param k Minimum total sales required
 * @return Number of subarrays with sum >= k
 */
int atLeastK_sales(vector<int>& sales, int k) {
  int n = sales.size();
  int l = 0;
  int r = 0;
  int sum_window = 0;
  int count_subarrays = 0;
  while(1) {
    bool must_grow = sum_window < k;
    if(must_grow) {
      if(r == n) break;
      sum_window += sales[r];
      r += 1;
    } else {
      count_subarrays += (n - r + 1);
      sum_window -= sales[l];
      l += 1;
    }
  }
  return count_subarrays;
}

/**
 * @brief Splits the sales array into maximal segments of consecutive good days
 * @param sales Vector of daily sales figures
 * @return Vector of segments, each a vector of sales from consecutive good days
 */
vector<vector<int>> count_good_subarrays(vector<int>& sales) {
  int n = sales.size();
  int l = 0;
  int r = 0;
  vector<vector<int>> good_subarrays;
  while(r<n) {
    bool can_grow = sales[r]>= 10;
    if(can_grow) {
      r+=1;
    } else {
      good_subarrays.push_back(vector<int>(sales.begin()+l, sales.begin()+r));
      l=r+1;
      r=r+1;
    }
  }
  if(l<n) good_subarrays.push_back(vector<int>(sales.begin()+l,sales.end()));
  return good_subarrays;
}


/**
 * @brief Counts subarrays with no bad days and at least k total sales
 * @param sales Vector of daily sales figures
 * @param k Minimum total sales required in the subarray
 * @return Number of valid subarrays
 */
int count_good_subarrays_atleast_k_sales(vector<int>& sales, int k) {
  vector<vector<int>> good_subarrays = count_good_subarrays(sales);
  int total = 0;
  for(auto& arr : good_subarrays) {
    total+= atLeastK_sales(arr,k);
  }

  return total;
}

// To execute C++, please define "int main()"
int main() {
  vector<int> sales {15, 20, 5, 30, 25}; int k = 50;
  cout<<count_good_subarrays_atleast_k_sales(sales, k)<<"\n";
  sales  = {10, 20, 30}; k = 40;
  cout<<count_good_subarrays_atleast_k_sales(sales, k)<<"\n";
  sales  = {0, 5, 8}; k = 10;
  cout<<count_good_subarrays_atleast_k_sales(sales, k)<<"\n";
  return 0;
}

// # Count Good Subarrays With At Least K Sales

// You are given an array, `sales`, where `sales[i]` is the number of sales on day `i`, and a positive number `k`.

// Return the number of subarrays with no bad days and at least `k` total sales.

// A _bad day_ is a day with fewer than `10` sales.

// Example 1: sales = [15, 20, 5, 30, 25], k = 50
// Output: 1
// The only subarray with no bad days and at least 50 total sales is:
//   - [30, 25]

// Example 2: sales = [10, 20, 30], k = 40
// Output: 2
// There are no bad days. The subarrays with at least 40 total sales are:
//   - [10, 20, 30]
//   - [20, 30]

// Example 3: sales = [0, 5, 8], k = 10
// Output: 0
// All days are bad days.

// Constraints:

// - `0 <= sales.length <= 10^5`
// - `0 <= sales[i] <= 10^3`
// - `1 <= k <= 10^7`
