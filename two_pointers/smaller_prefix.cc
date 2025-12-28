/**
 * @file smaller_prefix.cc
 * @brief Check if smaller prefixes have smaller sums using slow-fast pointers
 * 
 * This file implements a check for whether every prefix of length k has
 * a smaller sum than the prefix of length 2k, for all valid k.
 * 
 * Key Concepts:
 * - Slow-Fast Pointer Technique: slow at k, fast at 2k
 * - Running sum maintenance: accumulate sums as pointers advance
 * - Mathematical relationship: sum[k] < sum[2k] for all k in [1, n/2]
 * 
 * Time Complexity: O(n) where n is array length
 * Space Complexity: O(1) - only uses constant extra space
 * 
 * Algorithm:
 * - Slow pointer at position k (0, 1, 2, ...)
 * - Fast pointer at position 2k (0, 2, 4, ...)
 * - sum_less accumulates elements at slow positions
 * - sum_more accumulates elements at fast and fast+1 positions
 * - Compare sums at each step; return false if condition violated
 * 
 * Visual trace for arr = [1, 2, 2, -1]:
 * 1, 2, 2, -1
 *       s          slow pointer
 *             f    fast pointer (past end)
 * sum_less = 2 (sum of first 2 elements = 1+2)
 * sum_more = 3 (sum of first 4 elements = 1+2+2-1)
 */

#include <iostream>
#include <vector>
using namespace std;

/*
1, 2, 2, -1
      s
            f
sum_less += a[i]; //2
sum_more += a[i] + a[i+1]; //3

*/

/**
 * @brief Checks if sum of first k elements < sum of first 2k elements
 * @param arr Vector of integers (even length)
 * @return true if condition holds for all k in [1, n/2], false otherwise
 * 
 * For each k from 1 to n/2:
 * - sum[0..k-1] must be strictly less than sum[0..2k-1]
 */
bool smaller_prefix(vector<int>& arr) {
  int n = arr.size();
  int slow = 0;
  int fast = 0;
  int sum_less = 0;
  int sum_more = 0;
  while(fast < n) {
    sum_less += arr[slow];
    sum_more += arr[fast] + arr[fast+1];
    if(sum_less>=sum_more) return false;
    slow+=1;
    fast+=2;
  }
  return true;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  cout<<boolalpha;
  vector<int> arr{1,2,2,-1};
  cout<<smaller_prefix(arr)<<"\n";
  arr = {1, 2, -2, 1, 3, 5};
  cout<<smaller_prefix(arr)<<"\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Smaller Prefixes
 * 
 * Given an array of integers, arr, where the length, n, is even, return
 * whether the following condition holds for every k in range 1 ≤ k <= n/2:
 * "the sum of the first k elements is smaller than the sum of the first
 * 2k elements." If this condition is false for any k in the range, return
 * false.
 * 
 * Example 1: arr = [1, 2, 2, -1]
 * Output: True
 * The prefix [1] has a smaller sum than the prefix [1, 2], and the prefix
 * [1, 2] has a smaller sum than the prefix [1, 2, 2, -1].
 * 
 * Example 2: arr = [1, 2, -2, 1, 3, 5]
 * Output: False
 * The prefix [1, 2] has a larger sum than the prefix [1, 2, -2, 1].
 * 
 * Constraints:
 * - len(arr) is even
 * - 0 ≤ len(arr) ≤ 10^6
 * - -10^9 ≤ arr[i] ≤ 10^9
 * 
 *============================================================================*/
