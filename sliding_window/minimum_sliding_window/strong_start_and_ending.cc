/**
 * @file strong_start_and_ending.cc
 * @brief Maximise the combined good-day prefix + good-day suffix using k large boosts (+20).
 *
 * Complement approach: instead of maximising the prefix + suffix directly, we minimise
 * the "bad middle" window. If there are B total bad days and we can boost k of them,
 * then (B - k) bad days must remain. We find the shortest contiguous window containing
 * all (B - k) bad days using a minimum sliding window (minimum_size_bad_days). The days
 * outside that window form the good prefix + good suffix, so the answer is n - min_window.
 *
 * Key Concepts:
 * - Complement / inversion technique: maximise outside = minimise inside
 * - Minimum sliding window to find the shortest window with a required count of bad days
 * - Guard: if total bad days <= k, all days can be made good → return n
 *
 * Time Complexity: O(n) where n = projected_sales.size(). count_if is O(n) and the
 *   sliding window pass is O(n) (each element visited at most twice).
 * Space Complexity: O(1) extra space.
 */

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

/**
 * @brief Finds the shortest window containing at least k bad days (sales < 10)
 * @param projected_sales Vector of projected daily sales
 * @param k Required number of bad days in the window
 * @return Length of the shortest window with at least k bad days
 */
  int n = projected_sales.size();
  int l = 0;
  int r = 0;
  int bad_days = 0;
  int min_window = std::numeric_limits<int>::max();
  while (1) {
    bool must_grow = bad_days < k;
    if(must_grow) {
      if(r==n) break;
      if(projected_sales[r]<10) bad_days+=1;
      r+=1;
    } else {
      min_window = min(min_window,r-l);
      if(projected_sales[l]<10) bad_days-=1;
      l+=1;
    }
  }
  return min_window;
}

/**
 * @brief Maximises the combined good-day prefix + good-day suffix using k boosts
 * @param projected_sales Vector of projected daily sales
 * @param k Number of available boosts (each makes any day good)
 * @return Maximum number of combined initial + final good days
 */
int strong_start_and_ending(vector<int>& projected_sales,int k) {
  int n = projected_sales.size();
  // Count total bad days
  int bad_sales = count_if(projected_sales.begin(), projected_sales.end(),[](int x) { return x < 10; });
  if (bad_sales <= k) {
    return n;
  }
  int actual_bad_sales = bad_sales - k;
  //minimum window with actual_bad_sales
  int bad_days_window = minimum_size_bad_days(projected_sales,actual_bad_sales);
  return n - bad_days_window;
}

// To execute C++, please define "int main()"
int main() {
  vector<int> projected_sales {10, 0, 0, 0, 10, 0, 0, 10}; int k = 2;
  cout<<strong_start_and_ending(projected_sales,k)<<"\n";
  projected_sales = {0, 10, 0, 10}; k = 1;
  cout<<strong_start_and_ending(projected_sales,k)<<"\n";
  projected_sales = {5, 5, 5}; k = 2;
  cout<<strong_start_and_ending(projected_sales,k)<<"\n";
  return 0;
}

// # Strong Start And Ending

// Imagine that you have a little bookstore. We have an array, `projected_sales`, with the projected number of sales per day of the fall season.

// We would like to start and close the season strong. We want to have as many consecutive _good_ days as possible starting from day `0` and as many consecutive _good_ days as possible ending on the last day.

// A _good_ day is a day with at least `10` sales.

// We can pick `k` days to boost with advertising, which we expect to boost the sales on those specific days by at least `20`. What's the maximum number of combined initial good days and final good days we can have?

// Example 1: projected_sales = [10, 0, 0, 0, 10, 0, 0, 10], k = 2
// Output: 5
// We should boost days 5 and 6 so that the projected sales after boosting are:
//     [10, 0, 0, 0, 10, 20, 20, 10]
// This way, we have 1 initial and 4 final good days.

// Example 2: projected_sales = [0, 10, 0, 10], k = 1
// Output: 3
// It does not matter which day you boost.

// Example 3: projected_sales = [5, 5, 5], k = 2
// Output: 2
// We can boost any two days.

// Constraints:

// - `0 <= len(projected_sales) <= 10^5` (the bookstore is in a fictional world with very long fall seasons)
// - `0 <= projected_sales[i] <= 10^3`
// - `0 <= k <= 10^5`
