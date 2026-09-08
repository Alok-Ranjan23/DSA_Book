/**
 * @file shortest_period_over_20_sales.cc
 * @brief Find the shortest subarray whose sum exceeds 20.
 *
 * A minimum sliding window grows (r++) while window_sum <= 20 (condition not yet met).
 * Once window_sum > 20, we record the window size and shrink (l++) to try for a
 * shorter valid window. The loop breaks when r reaches the end and we still need to grow.
 *
 * Key Concepts:
 * - Minimum sliding window pattern (grow until condition met, then shrink)
 * - while(1) loop with explicit r == n break for the grow phase
 *
 * Time Complexity: O(n) where n = sales.size(). Each element is visited at most
 *   twice (once by r, once by l).
 * Space Complexity: O(1) extra space.
 */

#include <iostream>
#include <limits>
#include <vector>
using namespace std;

/**
 * @brief Finds the shortest period of consecutive days with total sales over 20
 * @param sales Vector of daily sales figures
 * @return Length of the shortest valid period, or -1 if none exists
 */
  int n = sales.size();
  int l = 0;
  int r = 0;
  int min_window = numeric_limits<int>::max();
  int window_sum = 0;
  while(1) {
    bool must_grow = window_sum <= 20;
    if(must_grow) {
      if(r==n) break;
      window_sum += sales[r];
      r+=1;
    } else {
      min_window = min(min_window, r-l);
      window_sum -= sales[l];
      l+=1;
    }
  }
  if(min_window==numeric_limits<int>::max()) return -1;
  return min_window;
}

// To execute C++, please define "int main()"
int main() {
  vector<int> sales {5, 10, 15, 5, 10};
  cout<<shortest_period_over_20_sales(sales)<<"\n";
  sales = {5, 10, 4, 5, 10};
  cout<<shortest_period_over_20_sales(sales)<<"\n";
  sales = {5, 5, 5, 5};
  cout<<shortest_period_over_20_sales(sales)<<"\n";

}

// # Shortest Period With Over 20 Sales

// Given an array, `sales`, where `sales[i]` is the number of sales on day `i`, find the shortest period of time with over 20 sales, or `-1` if there isn't any.

// Example 1: sales = [5, 10, 15, 5, 10]
// Output: 2. The subarray [10, 15] has over 20 sales.

// Example 2: sales = [5, 10, 4, 5, 10]
// Output: 4. [5, 10, 4, 5] and [10, 4, 5, 10] have over 20 sales.

// Example 3: sales = [5, 5, 5, 5]
// Output: -1. There is no subarray with more than 20 sales.

// Constraints:

// - `0 <= len(sales) <= 10^5`
// - `0 <= sales[i] <= 10^3`
