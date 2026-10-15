/**
 * @file balance_point.cc
 * @brief Find the first index where the sum of elements to its left equals
 *        the sum of elements to its right
 *
 * Checking every index by summing both sides is O(n^2). Instead, compute
 * the total once, then scan left to right keeping a running prefix sum
 * (sum of elements before i) and a running suffix sum (total minus
 * everything up to and including i). Each index is then checked in O(1).
 *
 * Key Concepts:
 * - Running prefix sum instead of a prefix array: only the current left
 *   sum is needed, so O(1) extra space is enough
 * - sum_total starts as the whole array and shrinks by arr[i] each step,
 *   so sum_total - arr[i] is the sum strictly to the right of i
 * - arr[i] itself belongs to neither side
 * - Returns the FIRST balanced index, or -1 if there is none (including
 *   an empty array)
 *
 * Time Complexity: O(n)
 *   - One pass for accumulate, one pass for the scan.
 *
 * Space Complexity: O(1)
 *   - Only a few running sums.
 */
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

/**
 * @brief Return the first balanced index of arr, or -1
 *
 * @param arr Input integers (may contain negatives)
 * @return    Smallest i with sum(arr[0..i-1]) == sum(arr[i+1..n-1]), else -1
 *
 * Algorithm:
 * 1. sum_total = sum of all elements; prefix_sum = 0.
 * 2. For each i: right sum = sum_total - arr[i]. If it equals prefix_sum,
 *    return i.
 * 3. Move arr[i] from the right side to the left side
 *    (sum_total -= arr[i], prefix_sum += arr[i]).
 *
 * Time:  O(n) -- two linear passes
 * Space: O(1) -- running sums only
 */
//Time O(n)   (accumulate + one scan)
//Space O(1)  (running sums only)
int balance_point(vector<int>& arr) {
  int n = arr.size();
  int sum_total = accumulate(arr.begin(),arr.end(),0);  // sum of arr[i..n-1] (shrinks)
  int prefix_sum = 0;                              // sum of arr[0..i-1]
  int i = 0;
  while(i<n) {
    if(prefix_sum == sum_total-arr[i]) return i;   // left == right (arr[i] excluded)
    sum_total  -= arr[i];
    prefix_sum += arr[i];
    i+=1;
  }

  return -1;                                       // no balanced index
}

/**
 * @brief Print the array followed by a label for the result
 *
 * @param arr Values to print
 */
void print_vector(vector<int>& arr) {
  for(auto& val: arr) {
    cout<<val<<" ";
  }
  cout<<"\t Balanced Point: ";
}

// To execute C++, please define "int main()"
int main() {
  vector <int> arr {3, 5, -2, 7, 2, 2, 2};
  print_vector(arr);
  cout<<balance_point(arr)<<"\n";
  return 0;
}

// # Balance Point

// Given an array of integers, `arr`, return the first _balanced index_, if there is any, or `-1` otherwise. An index is balanced if the sum of the elements to its left is the same as the sum of the elements to its right.

// Example:
// arr = [3, 5, -2, 7, 2, 2, 2]
// Output: 3
// Index 3 is balanced because 3 + 5 + (-2) equals 2 + 2 + 2.

// Constraints:

// - The length of `arr` is at most `10^5`
// - Each element in `arr` is an integer at most `10^4`
