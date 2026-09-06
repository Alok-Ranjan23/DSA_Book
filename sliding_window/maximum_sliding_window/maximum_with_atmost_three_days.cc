/**
 * @file maximum_with_atmost_three_days.cc
 * @brief Find the longest subarray with at most 3 bad days (sales < 10).
 *
 * A maximum sliding window expands while bad_days <= 3. When a 4th bad day would
 * be included, the window shrinks from the left until bad_days drops below 3 again.
 *
 * Key Concepts:
 * - Maximum sliding window with at most K bad elements (K = 3 hardcoded)
 * - No l == r guard needed: every element can enter an empty window
 *   (bad_days = 0 < 3 is always true)
 *
 * Time Complexity: O(n) where n = sales.size(). Each element is visited at most twice.
 * Space Complexity: O(1) extra space.
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Finds the longest period of consecutive days with at most 3 bad days
 * @param sales Vector of daily sales figures
 * @return Length of the longest valid period
 */
  int n = sales.size();
  int l = 0;
  int r = 0;
  int bad_days   = 0;
  int max_window = 0;
  while(r<n) {
    bool can_grow = (sales[r]>=10 || bad_days<3);
    if(can_grow) {
      if(sales[r]<10) bad_days+=1;
      r+=1;
      max_window = max(max_window,r-l);
    }
    else {
      if(sales[l]<10) bad_days-=1;
      l+=1;
    }
  }
  return max_window;
}

// To execute C++, please define "int main()"
int main() {
  vector <int> sales {0, 14, 7, 9, 0, 20, 10, 0, 10};
  cout<<maximum_atmost_three_bad_days(sales)<<"\n";
  sales = {10, 10, 10};
  cout<<maximum_atmost_three_bad_days(sales)<<"\n";
  sales = {5, 5, 5, 5};
  cout<<maximum_atmost_three_bad_days(sales)<<"\n";
  return 0;
}

// # Maximum With At Most 3 Bad Days

// Given an array `sales`, where `sales[i]` is the number of sales on the `i`-th day, find the most consecutive days with at most `3` bad days.

// A _bad day_ is a day with fewer than `10` sales.

// Example 1: sales = [0, 14, 7, 9, 0, 20, 10, 0, 10]
// Output: 6.
// There are two 6-day periods with at most 3 bad days:
//   - [14, 7, 9, 0, 20, 10]
//   - [9, 0, 20, 10, 0, 10]

// Example 2: sales = [10, 10, 10]
// Output: 3. All days are good days.

// Example 3: sales = [5, 5, 5, 5]
// Output: 3. We can include at most 3 bad days.

// Constraints:

// - `0 <= len(sales) <= 10^5`
// - `0 <= sales[i] <= 10^3`
