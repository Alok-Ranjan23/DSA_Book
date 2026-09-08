/**
 * @file small_range_with_k_elements.cc
 * @brief Find the smallest range [low, high] such that at least k array elements fall within it.
 *
 * After sorting the array, the problem reduces to finding a window of exactly k consecutive
 * (sorted) elements that minimises arr[r-1] - arr[l]. A minimum sliding window grows (r++)
 * while the window has fewer than k elements; once the window has k elements, we compare
 * the range and shrink (l++).
 *
 * Key Concepts:
 * - Sort + minimum sliding window of fixed logical size k
 * - After sorting, consecutive elements give the tightest range
 *
 * Time Complexity: O(n log n) dominated by sorting. The sliding window pass is O(n).
 * Space Complexity: O(1) extra space (in-place sort).
 */

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

/**
 * @brief Finds the smallest range containing at least k elements from the array
 * @param arr Vector of integers (will be sorted in-place)
 * @param k Minimum number of elements that must fall within the range
 * @return Pair {low, high} representing the smallest valid range
 */
  int n = arr.size();
  sort(arr.begin(), arr.end());
  int l = 0, r = 0;
  int bestLow = 0, bestHigh = std::numeric_limits<int>::max();
  while (1) {
    bool mustGrow = (r - l) < k;
    if (mustGrow) {
      if (r == n) {
        break;
      }
      r++;
    } else {
      if (arr[r - 1] - arr[l] < bestHigh - bestLow) {
        bestLow = arr[l];
        bestHigh = arr[r - 1];
      }
      l++;
    }
  }
  return {bestLow, bestHigh};
}

// To execute C++, please define "int main()"
int main() {
  vector<int> arr {1, 2, 5, 7, 8}; int k = 3;
  auto p = smallest_range_kElements(arr, k);
  cout<<"[ "<<p.first<<", "<<p.second<<"]\n";
  arr = {5,5,2,2,8,8}; k = 3;
  p = smallest_range_kElements(arr, k);
  cout<<"[ "<<p.first<<", "<<p.second<<"]\n";
  arr = {0}; k = 1;
  p = smallest_range_kElements(arr, k);
  cout<<"[ "<<p.first<<", "<<p.second<<"]\n";
  return 0;
}

// # Smallest Range With K Elements

// Given an array of integers, `arr`, and a number `k` with `1 ≤ k ≤ len(arr)`, return a pair of numbers `[low, high]`, with `low ≤ high`, representing the smallest range such that there are at least `k` elements in `arr` with values at least `low` and at most `high`.

// If there are multiple valid answers, return any of them.

// Example 1: arr = [1, 2, 5, 7, 8], k = 3
// Output: [5, 8]
// The range has 3 elements in arr (5, 7, and 8).
// It is smaller than other ranges with 3 elements, such as [1, 5], because 8-5 < 5-1.

// Example 2: arr = [5, 5, 2, 2, 8, 8], k = 3
// Output: [2, 5]
// The range has 4 elements in arr (5, 5, 2, and 2).
// There is no smaller range with at least 3 elements.
// [5, 8] is also a valid answer.

// Example 3: arr = [0], k = 1
// Output: [0, 0]

// Constraints:

// - `1 <= k <= len(arr) <= 10^5`
// - `-10^9 <= arr[i] <= 10^9`
