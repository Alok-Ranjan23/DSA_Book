/**
 * @file boosting_multiple_days.cc
 * @brief Find the longest streak of consecutive good days by distributing k unit boosts (+1 each).
 *
 * Each boost adds +1 to a chosen day, and the same day can be boosted multiple times.
 * The cost to make a bad day good is (10 - sales[i]). A maximum sliding window expands
 * while the total boost cost of bad days in the window fits within the remaining budget k.
 * When the budget is exhausted and the day still can't be fixed:
 * - If l == r (empty window), the element needs more boosts than the total budget → skip.
 * - Otherwise, shrink from the left and refund the boost cost of the departing element.
 *
 * Key Concepts:
 * - Maximum sliding window with a continuous resource budget
 * - l == r guard needed: a day with sales[i] + k_total < 10 can never be made good
 *
 * Time Complexity: O(n) where n = projected_sales.size(). Each element is visited
 *   at most twice (once by r, once by l).
 * Space Complexity: O(1) extra space.
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Finds the maximum number of consecutive good days achievable by distributing k unit boosts
 * @param projected_sales Vector of projected daily sales
 * @param k Total number of unit boosts available (each adds +1, same day can be boosted multiple times)
 * @return Length of the longest streak of consecutive good days
 */
  int n = projected_sales.size();
  int l = 0;
  int r = 0;
  int max_window = 0;
  while(r<n) {
    bool can_grow = projected_sales[r]>=10 || (projected_sales[r]+k>=10);
    if(can_grow) {
      if(projected_sales[r]<10) k-=(10-projected_sales[r]);
      r+=1;
      max_window = max(max_window, r-l);
    } else if (l == r){
      l = r+1;
      r = r+1;
    } else {
      if(projected_sales[l]<10) k+=(10-projected_sales[l]);
      l+=1;
    }
  }
  return max_window;
}

// To execute C++, please define "int main()"
int main() {
  vector<int> projected_sales {5, 5, 15, 0, 10}; int k = 12;
  cout<<boost_days_multiple_times(projected_sales,k)<<"\n";
  projected_sales = {5, 5, 15, 0, 10}; k = 15;
  cout<<boost_days_multiple_times(projected_sales,k)<<"\n";
  projected_sales = {0, 0, 0}; k = 29;
  cout<<boost_days_multiple_times(projected_sales,k)<<"\n";
  return 0;
}

// # Boosting Days Multiple Times

// Imagine that you have a little bookstore. We have an array, `projected_sales`, with the projected number of sales per day in the future.

// We are doing an advertising campaign and have a total of `k` boosts that we can use on any of the days. We expect each boost to increase the sales on the chosen day by `1`. **You can boost the same day multiple times.**

// If we use the boosts correctly, what is the maximum number of consecutive good days in a row we can get?

// A _good day_ is a day with at least `10` sales.

// Example 1: projected_sales = [5, 5, 15, 0, 10], k = 12
// Output: 3
// We can reach 3 consecutive good days in two ways:
//   - boosting days 0 and 1 to reach 10 sales each, or
//   - boosting day 3 to reach 10 sales.

// Example 2: projected_sales = [5, 5, 15, 0, 10], k = 15
// Output: 4
// We can boost days 1 and 3 to reach 10 sales each.

// Example 3: projected_sales = [0, 0, 0], k = 29
// Output: 2
// We can use all boosts on days 0 and 1 to reach 10 sales each.

// Constraints:

// - `0 <= len(projected_sales) <= 10^5`
// - `0 <= projected_sales[i] <= 10^3`
// - `0 <= k <= 10^7`
