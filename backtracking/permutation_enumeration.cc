/**
 * @file permutation_enumeration.cc
 * @brief Generate all permutations of an array using backtracking
 * 
 * This file implements the classic swap-based algorithm to generate all
 * possible permutations of an input array. A permutation is a rearrangement
 * of elements where order matters.
 * 
 * Key Concepts:
 * - In-place swapping to generate permutations
 * - Backtracking: swap, recurse, swap back
 * - Each position gets each element exactly once across all permutations
 * 
 * Time Complexity: O(n! * n)
 *   - n! permutations total
 *   - Each permutation takes O(n) to copy into result
 * 
 * Space Complexity: O(n! * n) for storing all permutations
 *   - Recursion stack: O(n) depth
 * 
 * Algorithm Insight:
 * For array [A, B, C], at index 0 we try each element:
 * - Fix A at 0: permute [B, C] -> [A,B,C], [A,C,B]
 * - Fix B at 0: permute [A, C] -> [B,A,C], [B,C,A]
 * - Fix C at 0: permute [A, B] -> [C,A,B], [C,B,A]
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

/** Global vector to store all generated permutations */
vector<vector<string>> ans;

/**
 * @brief Recursive function to generate all permutations
 * 
 * @param arr   The array to permute (modified in-place during recursion)
 * @param index Current position being filled (0 to n-1)
 * 
 * Algorithm:
 * 1. Base case: if index == n, we've filled all positions -> save permutation
 * 2. For each element from index to n-1:
 *    a. SWAP: bring that element to current index
 *    b. RECURSE: fill remaining positions
 *    c. SWAP BACK: restore original order (backtrack)
 */
void permutation_enumeration(vector<string>& arr, int index) {
  int n = arr.size();
  
  // Base case: all positions filled, save this permutation
  if(index == n) {
    ans.push_back(arr);
    return;
  }
  
  // Try each remaining element at the current position
  for(int i = index; i < n; ++i) {
    swap(arr[index], arr[i]);             // CHOOSE: place arr[i] at index
    permutation_enumeration(arr, index+1); // EXPLORE: permute rest
    swap(arr[index], arr[i]);             // UNCHOOSE: restore (backtrack)
  }
}

/**
 * @brief Helper function to print all permutations
 */
void print_result() {
  for(auto& vec : ans) {
    for(auto& val : vec) {
      cout << val << " ";
    }
    cout << "\n";
  }
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Example 1: Three elements ['x', 'y', 'z']
  // Expected: 3! = 6 permutations
  vector<string> arr {"x", "y", "z"};
  permutation_enumeration(arr, 0);
  print_result();
  
  // Example 2: Single element ['x']
  // Expected: 1! = 1 permutation
  ans.clear();
  arr = {"x"};
  permutation_enumeration(arr, 0);
  print_result();
  
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Permutation Enumeration
 * 
 * A _permutation_ of a list is a list with the same elements but in any order.
 * Finding all permutations means finding all possible orderings of the input.
 * 
 * Given an array of unique characters, `arr`, return all possible permutations,
 * in any order.
 * 
 * Example 1: arr = ['x', 'y', 'z']
 * Output: [['x', 'y', 'z'],
 *          ['x', 'z', 'y'],
 *          ['y', 'x', 'z'],
 *          ['y', 'z', 'x'],
 *          ['z', 'x', 'y'],
 *          ['z', 'y', 'x']]
 * 
 * Example 2: arr = ['x']
 * Output: [['x']]
 * 
 * Constraints:
 * - The elements in `arr` are unique.
 * - The length of `arr` is at most 10.
 * 
 *============================================================================*/
