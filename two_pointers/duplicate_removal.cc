/**
 * @file duplicate_removal.cc
 * @brief In-place duplicate removal from sorted array using reader-writer pattern
 * 
 * This file implements the duplicate removal algorithm using the
 * reader-writer (fast-slow) two pointer technique.
 * 
 * Key Concepts:
 * - Reader-Writer Pattern: Reader scans, writer overwrites unique elements
 * - Exploiting sorted property: duplicates are adjacent
 * - In-place modification with O(1) extra space
 * 
 * Time Complexity: O(n) where n is array length
 * Space Complexity: O(1) - only uses constant extra space
 * 
 * Algorithm:
 * - Writer stays at position where next unique element should go
 * - Reader scans through entire array
 * - When reader finds a new unique element, copy to writer position
 * - Return writer position as count of unique elements
 */

#include <iostream>
#include <vector>
using namespace std;

/*
 * Visual trace for arr = [1, 2, 3, 5, 3, 3, 5]:
 * 1      2        3        5      3        3        5
 *                                 w      
 *                                                       r   
 */

/**
 * @brief Removes duplicates from a sorted array in place
 * @param arr Sorted vector of integers (modified in place)
 * @return Number of unique elements in the array
 * 
 * After the operation, the first 'return value' elements contain
 * all unique elements. Elements beyond that are undefined.
 */
int duplicate_removal(vector<int>& arr) {
  int n      = arr.size();
  int writer = 0;
  int reader = 0;
  while(reader<n) {
    if(reader==0 || arr[reader-1]!=arr[reader]) {
      arr[writer] = arr[reader];
      writer+=1;
    }
    reader++;
  }
  return writer;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  vector<int> arr {1,2,2,3,3,3,5};
  cout<<duplicate_removal(arr)<<"\n";
  arr = {};
  cout<<duplicate_removal(arr)<<"\n";
  arr = {1,1,1};
  cout<<duplicate_removal(arr)<<"\n";

  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # In-Place Duplicate Removal
 * 
 * Given a sorted array of integers, `arr`, remove duplicates in place while
 * preserving the order, and return the number of unique elements. It doesn't
 * matter what remains in `arr` beyond the unique elements.
 * 
 * Example 1:
 * Input: arr = [1, 2, 2, 3, 3, 3, 5]
 * Output: 4
 * After the operation, the first 4 elements should be [1, 2, 3, 5]
 * The last 3 values could be anything
 * 
 * Example 2:
 * Input: arr = []
 * Output: 0
 * After the operation, the array remains empty
 * 
 * Example 3:
 * Input: arr = [1, 1, 1]
 * Output: 1
 * After the operation, the first element should be [1]
 * The last 2 values could be anything.
 * 
 * Constraints:
 * - The array is sorted in non-decreasing order
 * - The length of arr is at most 10^6
 * 
 *============================================================================*/
