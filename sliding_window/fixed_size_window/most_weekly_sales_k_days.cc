/**
 * @file most_weekly_sales_k_days.cc
 * @brief Find the starting index of the k-day period with maximum sales
 * 
 * We use a fixed-size sliding window of length k to compute the running sum.
 * Alongside the maximum sum, we keep track of the starting index where it occurred.
 * 
 * Key Concepts:
 * - Fixed-size sliding window (window size k)
 * - Running sum to avoid recalculating elements
 * - Saving the starting index (left pointer) associated with the max sum
 * 
 * Time Complexity: O(n) - array elements are visited and removed at most once
 * Space Complexity: O(1) - maintaining just a few tracking variables
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Finds the starting day of the highest-selling k-day window
 * @param sales Vector containing daily sales data
 * @param k The number of consecutive days in the window
 * @return The starting index (0-indexed) of the best k-day period
 */

int most_weekly_sales(vector<int>& sales, int k) {
  int n          = sales.size();
  int l          = 0;
  int r          = 0;
  int window_sum = 0;
  int curr_max   = 0;
  int index      = -1;
  while(r<n) {
    window_sum += sales[r];
    r+=1;
    if(r-l==k) {
      if(window_sum>curr_max) {
        curr_max = window_sum;
        index = l;
      }
      window_sum -= sales[l];
      l+=1;
    }
  }
  return index; 
}

// To execute C++, please define "int main()"
int main() {
  vector<int> sales {8,1,3,7}; int k = 2;
  cout<<most_weekly_sales(sales,k)<<"\n";
  sales = {5, 10, 15, 5}; k = 1; 
  cout<<most_weekly_sales(sales,k)<<"\n";
  sales = {1, 2, 3};k=3;
  cout<<most_weekly_sales(sales,k)<<"\n";
  return 0;
}

// # Most Sales In K Days

// Given the array `sales` and a number `k` with `1 ≤ k ≤ len(sales)`, find the most sales in any k-day period.

// Return the first day of that period (days start at `0`). If there are multiple k-day periods with the most sales, return the first day of the first one.

// Example 1: sales = [8, 1, 3, 7], k = 2
// Output: 2
// The subarray of length 2 with maximum sum is [3, 7], which starts at index 2.

// Example 2: sales = [5, 10, 15, 5], k = 1
// Output: 2
// The day with most sales is day 2 with 15 sales.

// Example 3: sales = [1, 2, 3], k = 3
// Output: 0
// The only valid period is the entire array.

// Constraints:

// - The length of `sales` is at most `10^6`
// - Each element in `sales` is a non-negative integer less than `10^3`
// - `1 ≤ k ≤ len(sales)`
