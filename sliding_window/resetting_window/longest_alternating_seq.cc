/**
 * @file longest_alternating_seq.cc
 * @brief Find the longest subarray that alternates between good days (sales >= 10) and bad days (sales < 10).
 *
 * Uses a sliding window that expands while the day type alternates; when the alternation breaks,
 * the left pointer jumps to the current right pointer, starting a new window.
 *
 * Key Concepts:
 * - Fixed-size resetting sliding window
 * - Boolean check of alternation based on <10 comparison
 *
 * Time Complexity: O(n) where n = sales.size().
 * Space Complexity: O(1) additional space.
 */

#include <iostream>
#include <vector>
using namespace std;

int longest_alternate_sequence(vector<int>& sales) {
  int n = sales.size();
  int l = 0;
  int r = 0;
  int alternate_seq_len = 0;
  while (r<n) {
    bool can_grow = (l==r) || ((sales[r-1]<10) != (sales[r]<10));
    if(can_grow) {
      r+=1;
      alternate_seq_len = max(alternate_seq_len, r-l);
    }
    else {
      l = r;
    }
  }
  return alternate_seq_len;
}

// To execute C++, please define "int main()"
int main() {
  vector<int> sales {8, 9, 20, 0, 9};
  cout<<longest_alternate_sequence(sales)<<"\n";
  sales = {0, 0, 0};
  cout<<longest_alternate_sequence(sales)<<"\n";
  sales = {5, 10, 5, 10};
  cout<<longest_alternate_sequence(sales)<<"\n";
  return 0;
}

// # Longest Alternating Sequence

// Given the array `sales`, where `sales[i]` is the number of sales on the `i`-th day, find the longest sequence of days alternating between good days and bad days.

// A _good day_ is a day with at least `10` sales.
// A _bad day_ is a day with fewer than `10` sales.

// Example 1: sales = [8, 9, 20, 0, 9]
// Output: 3. The only good day is day 2, so the subarray [9, 20, 0] alternates from bad to good to bad.

// Example 2: sales = [0, 0, 0]
// Output: 1. Every day is bad, so we cannot find any pair of consecutive days that alternate.

// Example 3: sales = [5, 10, 5, 10]
// Output: 4. The entire array alternates between bad and good days.

// Constraints:

// - `0 <= len(sales) <= 10^5`
// - `0 <= sales[i] <= 10^3`
