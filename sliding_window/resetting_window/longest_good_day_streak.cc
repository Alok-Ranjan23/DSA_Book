/**
 * @file longest_good_day_streak.cc
 * @brief Find the longest consecutive stretch of days where sales are at least 10.
 *
 * A resetting sliding window is employed: when a day with sales < 10 is encountered the
 * window is discarded and restarted after that day.
 *
 * Key Concepts:
 * - Fixed-size resetting sliding window
 * - Simple boolean check `sales[i] >= 10`
 *
 * Time Complexity: O(n) where n = sales.size().
 * Space Complexity: O(1) extra space.
 */

#include <iostream>
#include <vector>
using namespace std;

int longest_good_day_streak(vector<int>& sales) {
  int n = sales.size();
  int l = 0;
  int r = 0;
  int good_days = 0;
  while(r<n) {
    bool can_grow = sales[r]>=10;
    if(can_grow) {
      r+=1;
      good_days = max(good_days,r-l);
    }
    else {
      l = r+1;
      r = r+1;
    }
  }
  return good_days;
}

// To execute C++, please define "int main()"
int main() {
  vector<int> sales {0, 14, 7, 12, 10, 20};
  cout<<longest_good_day_streak(sales)<<"\n";
  sales = {10, 10, 10};
  cout<<longest_good_day_streak(sales)<<"\n";
  sales = {5, 5,5};
  cout<<longest_good_day_streak(sales)<<"\n";
  return 0;
}

// # Longest Good Day Streak

// Given an array, `sales`, where `sales[i]` is the number of sales on the `i`-th day, find the most consecutive days with no bad days.

// A _bad day_ is a day with fewer than `10` sales.

// Example 1: sales = [0, 14, 7, 12, 10, 20]
// Output: 3. The subarray [12, 10, 20] has no bad days.

// Example 2: sales = [10, 10, 10]
// Output: 3. All days are good days.

// Example 3: sales = [5, 5, 5]
// Output: 0. There are no good days.

// Constraints:

// - `0 <= len(sales) <= 10^5`
// - `0 <= sales[i] <= 10^3`
