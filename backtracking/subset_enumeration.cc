/**
 * @file subset_enumeration.cc
 * @brief Generate all subsets (power set) of an array using backtracking
 * 
 * This file implements the classic include/exclude pattern to generate all
 * possible subsets of an input array. Each element can either be included
 * or excluded from a subset.
 * 
 * Key Concepts:
 * - Binary decision tree: include or exclude each element
 * - Backtracking: add element, recurse, remove element
 * - Power set has 2^n subsets for n elements
 * 
 * Time Complexity: O(2^n * n)
 *   - 2^n subsets total
 *   - Each subset takes O(n) to copy
 * 
 * Space Complexity: O(2^n * n) for storing all subsets
 *   - Recursion stack: O(n) depth
 * 
 * Visual representation for [x, y, z]:
 *                    []
 *           /                  \
 *        [x]                   []
 *       /    \              /      \
 *    [x,y]   [x]          [y]      []
 *    /  \    / \         /  \     /  \
 * [xyz][xy][xz][x]    [yz] [y]  [z]  []
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Recursive function to generate all subsets
 * 
 * @param S      The input array
 * @param i      Current index being considered (0 to n-1)
 * @param size_  Total size of the input array
 * @param res    Current subset being built
 * @param ans    Vector to store all generated subsets
 * 
 * Algorithm:
 * 1. Base case: if i == size_, we've made decisions for all elements -> save subset
 * 2. For current element S[i]:
 *    a. INCLUDE: add to current subset, recurse
 *    b. EXCLUDE: remove from subset (backtrack), recurse without it
 */
void solve(vector<char>& S, int i, int size_, vector<char>& res, vector<vector<char>>& ans) {
  // Base case: processed all elements, save current subset
  if(i == size_) {
    ans.push_back(res);
    return;
  }
  
  // Branch 1: INCLUDE current element
  res.push_back(S[i]);              // CHOOSE: add element
  solve(S, i+1, size_, res, ans);   // EXPLORE: continue to next element
  res.pop_back();                   // UNCHOOSE: remove element (backtrack)
  
  // Branch 2: EXCLUDE current element
  solve(S, i+1, size_, res, ans);   // EXPLORE: continue without element
}

/**
 * @brief Wrapper function to generate all subsets
 * 
 * @param S The input array of unique characters
 * @return Vector of all subsets (power set)
 */
vector<vector<char>> subset_enumeration(vector<char>& S) {
  vector<vector<char>> ans;
  int n = S.size();
  vector<char> res;  // Current subset being built
  solve(S, 0, n, res, ans);
  return ans;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Example: Three elements ['x', 'y', 'z']
  // Expected: 2^3 = 8 subsets
  vector<char> S {'x', 'y', 'z'};
  vector<vector<char>> subsets = subset_enumeration(S);
  
  cout << "All subsets of {x, y, z}:\n";
  for(auto& s : subsets) {
    cout << "{ ";
    for(auto& c : s) {
      cout << c << " ";
    }
    cout << "}\n";
  }
  
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Subset Enumeration
 * 
 * Given a set of elements, `S`, a subset of `S` is another set obtained by
 * removing any number of elements from `S` (including none or all of them).
 * As usual with sets, order does not matter.
 * 
 * Given an array of unique characters, `S`, return all possible subsets
 * in any order.
 * 
 * Example: S = ['x', 'y', 'z']
 * Output: [[],
 *          ['x'],
 *          ['y'],
 *          ['z'],
 *          ['x', 'y'],
 *          ['x', 'z'],
 *          ['y', 'z'],
 *          ['x', 'y', 'z']]
 * 
 * Constraints:
 * - The elements in `S` are unique.
 * - The length of `S` is at most 12.
 * 
 *============================================================================*/
