/**
 * @file dutch_flag_problem.cc
 * @brief Dutch National Flag sorting using three-way partitioning
 * 
 * This file implements the Dutch National Flag algorithm, also known as
 * three-way partitioning. It sorts an array of three distinct values
 * in a single pass.
 * 
 * Key Concepts:
 * - Three Pointer Technique: low, current, and high pointers
 * - Single-pass O(n) sorting for three distinct values
 * - In-place modification with O(1) extra space
 * - Similar to sorting an array containing only 0, 1, 2
 * 
 * Time Complexity: O(n) where n is array length
 * Space Complexity: O(1) - only uses constant extra space
 * 
 * Algorithm:
 * - Maintain three regions: [0..l-1] = R, [l..i-1] = W, [h+1..n-1] = B
 * - Current pointer (i) scans through unknown region
 * - 'R' at i: swap with low, advance both i and l
 * - 'W' at i: just advance i
 * - 'B' at i: swap with high, decrement h (don't advance i)
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Sorts array of R/W/B characters in Dutch flag order
 * @param arr Vector of characters containing 'R', 'W', 'B' (modified in place)
 * 
 * After sorting: all 'R's come first, then 'W's, then 'B's.
 * This is equivalent to sorting 0, 1, 2 problem.
 */
// rwb is any order ---> RWB order 
// similar problem ---> sort an array containing only 0,1,2
void dutch_flag_problem(vector<char>& arr) {
  int n = arr.size();
  int l = 0;
  int h = n-1;
  int i = 0;
  while(i<=h) {
    if (arr[i] == 'R') { 
      swap(arr[l],arr[i]);
      i++;
      l++;
    }
    else if (arr[i] == 'W') i++;
    else if (arr[i] == 'B') {
      swap(arr[i],arr[h]);
      h--;
    }
  }
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  vector<char> arr {'R', 'W', 'B', 'B', 'W', 'R', 'W'};
  for(auto& x: arr) cout<<x<<" ";
  cout<<"\n";
  dutch_flag_problem(arr);
  for(auto& x: arr) cout<<x<<" ";
  cout<<"\n";
  arr = {'B','R'};
  for(auto& x: arr) cout<<x<<" ";
  cout<<"\n";
  dutch_flag_problem(arr);
  for(auto& x: arr) cout<<x<<" ";
  cout<<"\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Dutch Flag Problem
 * 
 * Given an array, `arr`, containing only of the characters 'R' (red),
 * 'W' (white), and 'B' (blue), sort the array in place so that the same
 * colors are adjacent, with the colors in the order red, white, and blue.
 * 
 * Example 1:
 * Input: arr = ['R', 'W', 'B', 'B', 'W', 'R', 'W']
 * Output: ['R', 'R', 'W', 'W', 'W', 'B', 'B']
 * 
 * Example 2:
 * Input: arr = ['B', 'R']
 * Output: ['R', 'B']
 * 
 * Constraints:
 * - 0 ≤ arr.length ≤ 10^6
 * - arr[i] is either 'R', 'W', or 'B'
 * 
 *============================================================================*/
