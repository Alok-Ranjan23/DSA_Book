/**
 * @file ad_campaign_small_boost.cc
 * @brief Find the longest streak of consecutive good days using at most k small boosts (+5).
 *
 * Unlike the large-boost variant, a +5 boost cannot make every day good (e.g. sales=4
 * gives 4+5=9 < 10). The maximum sliding window expands while the day is already good
 * or can be made good with an available boost. When can_grow is false:
 * - If l == r (empty window), the element is un-fixable → skip both pointers.
 * - Otherwise, shrink from the left and refund the boost if the departing element was boosted.
 *
 * Key Concepts:
 * - Maximum sliding window with conditional resource usage
 * - l == r guard needed: some elements can never satisfy can_grow
 *
 * Time Complexity: O(n) where n = projected_sales.size(). Each element is visited
 *   at most twice (once by r, once by l).
 * Space Complexity: O(1) extra space.
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Finds the maximum number of consecutive good days achievable with at most k small boosts (+5)
 * @param projected_sales Vector of projected daily sales
 * @param k Number of available boosts (each boost adds +5)
 * @return Length of the longest streak of consecutive good days
 */
  int n = projected_sales.size();
  int l = 0;
  int r = 0;
  int max_window = 0;
  int boost_days = 0;
  while(r<n) {
    bool can_grow = projected_sales[r]>=10 || (boost_days<k && projected_sales[r]+5>=10) ;
    if(can_grow) {
      if(projected_sales[r]<10) boost_days+=1;
      r+=1;
      max_window = max(max_window, r-l);
    } else if (l == r){
      l = r+1;
      r = r+1;
    } else {
      if(projected_sales[l]<10 && projected_sales[l]>=5) boost_days-=1;
      l+=1;
    }
  }
  return max_window;
}

// To execute C++, please define "int main()"
int main() {
  vector<int> projected_sales {8,4,8}; int k = 3;
  cout<<ad_campaign_small_boosts(projected_sales,k)<<"\n";
  projected_sales = {10,5,8}; k = 1;
  cout<<ad_campaign_small_boosts(projected_sales,k)<<"\n";
  projected_sales = {8,8,8}; k = 3;
  cout<<ad_campaign_small_boosts(projected_sales,k)<<"\n";
  return 0;
}

// # Ad Campaign With Small Boosts

// Imagine that you have a little bookstore. We have an array, `projected_sales`, with the projected number of sales per day in the future.

// We are trying to pick `k` days for an advertising campaign, which we expect to boost the sales on those specific days by `5` sales. **You cannot boost the same day more than once.**

// If we pick the days for the advertising campaign correctly, what is the maximum number of consecutive good days in a row we can get?

// A _good day_ is a day with at least `10` sales.

// Example 1: projected_sales = [8, 4, 8], k = 3
// Output: 1. We can boost all 3 days, resulting in [13, 9, 13] projected sales.
// The max consecutive good days is 1.

// Example 2: projected_sales = [10, 5, 8], k = 1
// Output: 2. We should boost day 1, resulting in [10, 10, 8] projected sales.

// Example 3: projected_sales = [8, 8, 8], k = 3
// Output: 3. We can boost all days to reach 13 sales each.

// Constraints:

// - `0 <= len(projected_sales) <= 10^5`
// - `0 <= projected_sales[i] <= 10^3`
// - `0 <= k <= len(projected_sales)`
