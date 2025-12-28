/**
 * @file quicksort_partition.cc
 * @brief Three-way partitioning around a pivot value
 * 
 * This file implements the partition step of quicksort using three-way
 * partitioning, which handles duplicate pivot values efficiently.
 * 
 * Key Concepts:
 * - Three Pointer Technique: low, current, and high pointers
 * - Three-way partition: elements < pivot, == pivot, > pivot
 * - In-place modification with O(1) extra space
 * - Similar to Dutch National Flag problem
 * 
 * Time Complexity: O(n) where n is array length
 * Space Complexity: O(1) - only uses constant extra space
 * 
 * Algorithm:
 * - Maintain three regions: [0..l-1] < pivot, [l..i-1] = pivot, [h+1..n-1] > pivot
 * - Current pointer (i) scans through unknown region
 * - If arr[i] < pivot: swap with low, advance both i and l
 * - If arr[i] == pivot: just advance i
 * - If arr[i] > pivot: swap with high, decrement h (don't advance i)
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Partitions array around a pivot value
 * @param arr Vector of integers (modified in place)
 * @param pivot Value to partition around
 * 
 * After partitioning:
 * - All elements < pivot appear first
 * - All elements == pivot appear in middle
 * - All elements > pivot appear last
 * 
 * Order within each group is not guaranteed.
 */
void quicksort_partition(vector<int>& arr,int pivot) {
  int n = arr.size();
  int l = 0;
  int h = n-1;
  int i = 0;
  while(i<=h) {
    if(arr[i]<pivot) {
      if(i!=l) swap(arr[i],arr[l]);
      i++;l++;
    } 
    else if(arr[i]==pivot) i++;
    else {
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
  vector<int> arr {1,7,2,3,3,5,3}; int pivot=4;
  for(auto&x : arr) cout<<x<<" ";
  cout<<"\n";
  quicksort_partition(arr,pivot);
  for(auto&x : arr) cout<<x<<" ";
  cout<<"\n";
  
  arr = {1,7,2,3,3,5,3}; pivot=3;
  for(auto&x : arr) cout<<x<<" ";
  cout<<"\n";
  quicksort_partition(arr,pivot);
  for(auto&x : arr) cout<<x<<" ";
  cout<<"\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Quicksort Partition
 * 
 * Given an array of integers, arr, and an integer, pivot, modify arr in
 * place using only O(1) extra space so that:
 * (1) every element smaller than the pivot appears before every element
 *     greater than or equal to the pivot, and
 * (2) every element larger than the pivot appears after every element
 *     smaller than or equal to the pivot.
 * 
 * The relative order of elements smaller/greater than pivot doesn't matter.
 * 
 * Example 1:
 * Input: arr = [1, 7, 2, 3, 3, 5, 3], pivot = 4
 * Output: [1, 2, 3, 3, 3, 7, 5]
 * Explanation: The array is partitioned into:
 * - Elements less than 4: [1, 2, 3, 3, 3]
 * - Elements equal to 4: []
 * - Elements greater than 4: [7, 5]
 * 
 * Example 2:
 * Input: arr = [1, 7, 2, 3, 3, 5, 3], pivot = 3
 * Output: [1, 2, 3, 3, 3, 7, 5]
 * Explanation: The array is partitioned into:
 * - Elements less than 3: [1, 2]
 * - Elements equal to 3: [3, 3, 3]
 * - Elements greater than 3: [7, 5]
 * 
 * Constraints:
 * - 0 ≤ arr.length ≤ 10^6
 * - -10^9 ≤ arr[i], pivot ≤ 10^9
 * 
 *============================================================================*/
