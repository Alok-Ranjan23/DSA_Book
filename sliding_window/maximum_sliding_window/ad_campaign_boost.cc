/**
 * @file ad_campaign_boost.cc
 * @brief Find the longest streak of consecutive good days using at most k large boosts (+20).
 *
 * Since a +20 boost makes any day good regardless of its original value, the problem
 * reduces to: find the longest window with at most k bad days (sales < 10).
 * A maximum sliding window expands while bad_days <= k and shrinks from the left
 * when the constraint is violated.
 *
 * Key Concepts:
 * - Maximum sliding window with at most K replacements
 * - No l == r guard needed: every element can be made good with a boost,
 *   so can_grow is always true for an empty window (boost_sales = 0 < k)
 *
 * Time Complexity: O(n) where n = projected_sales.size(). Each element is visited
 *   at most twice (once by r, once by l).
 * Space Complexity: O(1) extra space.
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Finds the maximum number of consecutive good days achievable with at most k large boosts
 * @param projected_sales Vector of projected daily sales
 * @param k Number of available boosts (each boost adds +20, making any day good)
 * @return Length of the longest streak of consecutive good days
 */
  int n = projected_sales.size();
  int l = 0;
  int r = 0;
  int boost_sales = 0;
  int max_window  = 0;
  while(r<n) {
    bool can_grow = projected_sales[r]>=10 || boost_sales < k;
    if(can_grow) {
      if(projected_sales[r]<10) boost_sales +=1;
      r+=1;
      max_window = max(max_window,r-l);
    }
    else {
      if(projected_sales[l] < 10) {
        boost_sales-=1;
      }
      l+=1;
    }
  }
  return max_window;
}

// To execute C++, please define "int main()"
int main() {
  vector<int> projected_sales {5, 0, 20, 0, 5}; int k=2;
  cout<<ad_campaign_boost(projected_sales,k)<<"\n";
  projected_sales = {0, 10, 0, 10}; k=1;
  cout<<ad_campaign_boost(projected_sales,k)<<"\n";
  projected_sales = {5, 5, 5}; k=3;
  cout<<ad_campaign_boost(projected_sales,k)<<"\n";
  return 0;
}

// # Ad Campaign Boost

// Imagine that you have a little bookstore. We have an array, `projected_sales`, with the projected number of sales per day in the future.

// We are trying to pick `k` days for an advertising campaign, which we expect to boost the sales on those specific days by at least `20`.

// If we pick the days for the advertising campaign correctly, what is the maximum number of consecutive good days in a row we can get?

// A _good day_ is a day with at least `10` sales.

// Example 1: projected_sales = [5, 0, 20, 0, 5], k = 2
// Output: 3.
// The only good day is day 2. We can boost:
//   - days 0 and 1,
//   - days 1 and 3, or
//   - days 3 and 4.
// For instance, if we boost days 0 and 1, the projected sales become:
// [25, 20, 20, 0, 5], with 3 consecutive good days.

// Example 2: projected_sales = [0, 10, 0, 10], k = 1
// Output: 3. We can boost day 2; boosting day 0 is suboptimal.

// Example 3: projected_sales = [5, 5, 5], k = 3
// Output: 3. We can boost all days to make them good days.

// Constraints:

// - `1 <= k <= len(projected_sales) <= 10^5`
// - `0 <= projected_sales[i] <= 10^3`
