/**
 * @file parity_sorting.cc
 * @brief Partition array by parity (evens before odds) using two pointers
 * 
 * This file implements in-place parity sorting where all even numbers
 * are moved before all odd numbers.
 * 
 * Key Concepts:
 * - Two Pointer Technique: Writer-Seeker pattern
 * - Partition problem: Separate elements by a condition
 * - In-place modification with O(1) extra space
 * - Relative order within groups not preserved
 * 
 * Time Complexity: O(n) where n is array length
 * Space Complexity: O(1) - only uses constant extra space
 * 
 * Algorithm:
 * - Pointer i marks where next even should go
 * - Pointer j scans through the array
 * - When j finds even number, swap with position i and advance i
 * - Always advance j
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Partitions array so even numbers come before odd numbers
 * @param arr Vector of integers (modified in place)
 * 
 * After the operation, all even numbers appear before all odd numbers.
 * The relative order within even/odd groups is not guaranteed.
 */
void parity_sorting(vector<int>& arr) {
  int n = arr.size();
  int i = 0,j = 0;
  while(j<n) {
    if(arr[j]%2 == 0) {
      int temp = arr[i];
      arr[i]   = arr[j];
      arr[j]   = temp;
      i++;
    }
    j++;
  }
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  vector<int> arr {1, 2, 3, 4, 5};
  for(auto&x : arr) cout<<x<<" ";
  cout<<"\n";
  parity_sorting(arr);
  for(auto&x : arr) cout<<x<<" ";
  cout<<"\n";
  arr = {5, 1, 3, 1, 5};
  for(auto&x : arr) cout<<x<<" ";
  cout<<"\n";
  parity_sorting(arr);
  for(auto&x : arr) cout<<x<<" ";
  cout<<"\n";
  arr = {1, 3, 2, 4};
  for(auto&x : arr) cout<<x<<" ";
  cout<<"\n";
  parity_sorting(arr);
  for(auto&x : arr) cout<<x<<" ";
  cout<<"\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Parity Sorting
 * 
 * Given an array of integers arr, modify it in place so that all even
 * numbers come before all odd numbers. The relative order of even numbers
 * does not need to be maintained. The same goes for odd numbers.
 * 
 * Example 1:
 * Input: arr = [1, 2, 3, 4, 5]
 * Output: [2, 4, 1, 3, 5]
 * Explanation: There are other valid outputs, e.g. [4, 2, 3, 1, 5].
 * 
 * Example 2:
 * Input: arr = [5, 1, 3, 1, 5]
 * Output: [5, 1, 3, 1, 5]
 * Explanation: Since all numbers are odd, any ordering is valid.
 * 
 * Example 3:
 * Input: arr = [1, 3, 2, 4]
 * Output: [2, 4, 1, 3]
 * Explanation: Any arrangement where evens come before odds is valid.
 * 
 * Constraints:
 * - The length of arr is at most 10^6
 * - Each element in arr is an integer in the range [-10^9, 10^9]
 * 
 *============================================================================*/
