/**
 * @file count_good_start_good_end.cc
 * @brief Count subarrays that start and end on a good day (sales >= 10).
 *
 * Observation: if there are g good days, the answer is the number of ways to
 * pick a pair (i, j) with i <= j from those g positions = g * (g + 1) / 2.
 * This works because any subarray sales[i..j] where both i and j are good-day
 * indices is valid, regardless of the elements in between.
 *
 * Key Concepts:
 * - Combinatorial counting: C(g,2) + g = g*(g+1)/2
 * - No sliding window needed — a single pass to count good days suffices
 *
 * Time Complexity: O(n) where n = sales.size(). Single pass to count good days.
 * Space Complexity: O(1) extra space.
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Counts subarrays that start and end on a good day (sales >= 10)
 * @param sales Vector of daily sales figures
 * @return Number of valid subarrays
 */
  int goodDays = 0;
  for(auto& val: sales) {
    if(val>=10) goodDays+=1;
  }
  return (long long)goodDays * (goodDays + 1) / 2;
}

// To execute C++, please define "int main()"
int main() {
  vector<int> sales {0, 20, 5, 15, 10};
  cout<<count_good_start_good_end(sales)<<"\n";
  sales = {0, 5, 8};
  cout<<count_good_start_good_end(sales)<<"\n";
  sales = {10, 20, 30};
  cout<<count_good_start_good_end(sales)<<"\n";
  return 0;
}

// # Count Subarrays With Good Start And Ending

// Given an array, `sales`, where `sales[i]` is the number of sales on day `i`, return the number of subarrays that start and end on a good day.

// A _good day_ is a day with at least 10 sales.

// Example 1: sales = [0, 20, 5, 15, 10]
// Output: 6
// The good days are at indices 1, 3, and 4
// The valid subarrays are:
// - [20]
// - [15]
// - [10]
// - [20, 5, 15]
// - [15, 10]
// - [20, 5, 15, 10]

// Example 2: sales = [0, 5, 8]
// Output: 0
// There are no good days.

// Example 3: sales = [10, 20, 30]
// Output: 6
// All days are good, so all subarrays count.

// Constraints:

// - `0 <= sales.length <= 10^5`
// - `0 <= sales[i] < 10^3`
