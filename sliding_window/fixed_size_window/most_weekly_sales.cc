/**
 * @file most_weekly_sales.cc
 * @brief Find the maximum sales in any 7-day period
 * 
 * We use a fixed-size sliding window of length 7 to keep a running 
 * sum of sales and track the maximum sum seen so far.
 * 
 * Key Concepts:
 * - Fixed-size sliding window (window size k = 7)
 * - Running sum to avoid recalculating the window elements
 * 
 * Time Complexity: O(n) - each element is added and removed at most once
 * Space Complexity: O(1) - only integer variables for sums and pointers are used
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Computes the maximum sum over any contiguous 7-day window
 * @param sales Vector containing the daily sales figures
 * @return The maximum sales found in any 7-day period, or 0 if fewer than 7 days exist
 */

int most_weekly_sales(vector<int>& sales) {
  int n          = sales.size();
  int l          = 0;
  int r          = 0;
  int window_sum = 0;
  int curr_max   = 0;
  while(r<n) {
    window_sum += sales[r];
    r+=1;
    if(r-l==7) {
      curr_max = max(curr_max,window_sum);
      window_sum -= sales[l];
      l+=1;
    }
  }
  return curr_max; 
}

// To execute C++, please define "int main()"
int main() {
  vector<int> sales {0, 3, 7, 12, 10, 5, 0, 1, 0, 15, 12, 11, 1};
  cout<<most_weekly_sales(sales)<<"\n";
  sales = {0, 3, 7, 12};
  cout<<most_weekly_sales(sales)<<"\n";
  sales = {1, 2, 3, 4, 5, 6, 7};
  cout<<most_weekly_sales(sales)<<"\n";
  return 0;
}

// # Most Weekly Sales

// Given an array, `sales`, find the most sales in any 7-day period.

// Example 1: sales = [0, 3, 7, 12, 10, 5, 0, 1, 0, 15, 12, 11, 1]
// Output: 44
// The 7-day period with the most sales is [5, 0, 1, 0, 15, 12, 11].

// Example 2: sales = [0, 3, 7, 12]
// Output: 0
// There is no 7-day period.

// Example 3: sales = [1, 2, 3, 4, 5, 6, 7]
// Output: 28
// The only 7-day period is the entire array.

// Constraints:

// - The length of `sales` is at most `10^6`
// - Each element in `sales` is a non-negative integer less than `10^3`
