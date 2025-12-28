/**
 * @file three_way_merge.cc
 * @brief Merge three sorted arrays without duplicates using three pointers
 * 
 * This file implements a three-way merge that combines three sorted arrays
 * into a single sorted array, removing all duplicates.
 * 
 * Key Concepts:
 * - Three Pointer Technique: One pointer for each array
 * - Finding minimum among three values per iteration
 * - Duplicate elimination: skip values already in result
 * - Handle exhausted arrays by using INT_MAX sentinel
 * 
 * Time Complexity: O(n1 + n2 + n3) where ni are array lengths
 * Space Complexity: O(k) where k is number of unique elements
 * 
 * Algorithm:
 * - Find smallest value among current positions of all three arrays
 * - Advance ALL pointers that point to this smallest value
 * - Skip if this value was already added to result (handles duplicates)
 * - Add to result otherwise
 */

#include <iostream>
#include <limits>
#include <vector>
using namespace std;

/**
 * @brief Merges three sorted arrays into one sorted array without duplicates
 * @param arr1 First sorted array
 * @param arr2 Second sorted array
 * @param arr3 Third sorted array
 * @return Vector containing all unique elements in sorted order
 * 
 * Uses INT_MAX as sentinel for exhausted arrays.
 * Advances all pointers pointing to the minimum to handle duplicates
 * across arrays efficiently.
 */
vector<int> three_way_merge(vector<int> arr1, vector<int> arr2, vector<int> arr3) {
  vector<int> res;
  int n1 = arr1.size();
  int n2 = arr2.size();
  int n3 = arr3.size();
  int i=0,j=0,k=0;
  while(i<n1 || j<n2 || k<n3) {
    int smallest=numeric_limits<int>::max();
    if(i<n1 && smallest>=arr1[i]) {
      smallest=arr1[i];
    }
    if(j<n2 && smallest>=arr2[j]) {
      smallest=arr2[j];
    }
    if(k<n3 && smallest>=arr3[k]) {
      smallest=arr3[k];
    }
    if(i<n1 && smallest==arr1[i]) i++;
    if(j<n2 && smallest==arr2[j]) j++;
    if(k<n3 && smallest==arr3[k]) k++;
    if(!res.empty() && smallest==res.back()) continue;
    res.push_back(smallest);
  }
  return res;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  vector<int> arr1 {2,3,3,4,5,7};
  vector<int> arr2 {3,3,9};
  vector<int> arr3 {3,3,9};
  for(auto&x: three_way_merge(arr1,arr2,arr3))cout<<x<<" ";
  cout<<"\n";
  arr1 = {1,2,3};
  arr2 = {2,3,4};
  arr3 = {3,4,5};
  for(auto&x: three_way_merge(arr1,arr2,arr3))cout<<x<<" ";
  cout<<"\n";
  arr1 = {1,1,1,1};
  arr2 = {1,1,1};
  arr3 = {1,1};
  for(auto&x: three_way_merge(arr1,arr2,arr3))cout<<x<<" ";
  cout<<"\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Three Way Merge Without Duplicates
 * 
 * Given three sorted arrays, arr1, arr2, and arr3, return a new array with
 * the elements of all three arrays, in sorted order, without duplicates.
 * 
 * Example 1:
 * Input:
 * arr1 = [2, 3, 3, 4, 5, 7]
 * arr2 = [3, 3, 9]
 * arr3 = [3, 3, 9]
 * Output: [2, 3, 4, 5, 7, 9]
 * Explanation: The value 3 appears multiple times but only once in output.
 * 
 * Example 2:
 * Input:
 * arr1 = [1, 2, 3]
 * arr2 = [2, 3, 4]
 * arr3 = [3, 4, 5]
 * Output: [1, 2, 3, 4, 5]
 * Explanation: Each duplicate value is included only once.
 * 
 * Example 3:
 * Input:
 * arr1 = [1, 1, 1, 1]
 * arr2 = [1, 1, 1]
 * arr3 = [1, 1]
 * Output: [1]
 * Explanation: All ones are merged into a single occurrence.
 * 
 * Constraints:
 * - The input arrays are sorted in ascending order
 * - 0 ≤ arr1.length, arr2.length, arr3.length ≤ 10^6
 * - -10^9 ≤ arr1[i], arr2[i], arr3[i] ≤ 10^9
 * 
 *============================================================================*/
