/**
 * @file array_intersection.cc
 * @brief Find intersection of two sorted arrays using two pointers
 * 
 * This file implements the array intersection algorithm that finds all
 * common elements between two sorted arrays, including duplicates.
 * 
 * Key Concepts:
 * - Two Pointer Technique: One pointer for each array
 * - Exploiting sorted property to achieve linear time
 * - Handling duplicates correctly by advancing both pointers
 * 
 * Time Complexity: O(n + m) where n and m are array lengths
 * Space Complexity: O(min(n, m)) for the result array
 * 
 * Algorithm:
 * - Compare elements at both pointers
 * - If arr1[i] < arr2[j]: advance i (element can't be in intersection)
 * - If arr1[i] > arr2[j]: advance j (element can't be in intersection)
 * - If equal: add to result and advance both pointers
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Finds the intersection of two sorted arrays
 * @param arr1 First sorted array (passed by reference)
 * @param arr2 Second sorted array (passed by reference)
 * @return Vector containing all common elements (including duplicates)
 * 
 * The function uses two pointers, one for each array, and advances
 * them based on comparison of current elements.
 */
vector<int> array_intersection(vector<int>& arr1,vector<int>& arr2) {
  vector<int> res;
  int n1 = arr1.size();
  int n2 = arr2.size();
  int i=0,j=0;
  while(i<n1 && j<n2) {
    if(arr1[i]<arr2[j]) i++;
    else if(arr1[i]>arr2[j]) j++;
    else {
      res.push_back(arr1[i]);i++;j++;
    }
  }
  return res;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  vector<int> arr1 {1,2,3};
  vector<int> arr2 {1,3,5};
  for(auto&x: array_intersection(arr1,arr2)) cout<<x<<" ";
  cout<<"\n";
  arr1 = {1,1,1};
  arr2 = {1,1};
  for(auto&x: array_intersection(arr1,arr2)) cout<<x<<" ";
  cout<<"\n";
  arr1 = {1,1,1,1};
  arr2 = {};
  for(auto&x: array_intersection(arr1,arr2)) cout<<x<<" ";
  cout<<"\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Array Intersection
 * 
 * Given two sorted arrays, `arr1` and `arr2`, return their _intersection_.
 * 
 * The intersection is a new array that contains all elements that appear in
 * both arrays, in sorted order, including duplicates.
 * 
 * Example 1:
 * Input:
 * arr1 = [1, 2, 3]
 * arr2 = [1, 3, 5]
 * Output: [1, 3]
 * Explanation: 1 and 3 appear in both arrays.
 * 
 * Example 2:
 * Input:
 * arr1 = [1, 1, 1]
 * arr2 = [1, 1]
 * Output: [1, 1]
 * Explanation: Two 1s appear in both arrays.
 * 
 * Example 3:
 * Input:
 * arr1 = [1, 2, 2, 3]
 * arr2 = []
 * Output: []
 * 
 * Constraints:
 * - The input arrays are sorted in ascending order
 * - 0 ≤ arr1.length, arr2.length ≤ 10^6
 * - -10^9 ≤ arr1[i], arr2[i] ≤ 10^9
 * 
 *============================================================================*/
