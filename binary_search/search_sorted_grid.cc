/**
 * @file search_sorted_grid.cc
 * @brief Staircase Search in a row-wise and column-wise sorted 2D grid
 * 
 * This file implements an efficient search algorithm for a 2D grid where
 * each row is sorted and the last element of each row is smaller than
 * the first element of the next row (fully sorted grid).
 * 
 * Key Concepts:
 * - Staircase Search (also called Saddleback Search)
 * - Start from top-right (or bottom-left) corner
 * - Each comparison eliminates one row or one column
 * - Works for any row-wise and column-wise sorted matrix
 * 
 * Time Complexity: O(m + n) where m = rows, n = columns
 *                  At most m + n comparisons (traverse at most one row + one column)
 * Space Complexity: O(1) - only uses constant extra space
 * 
 * Algorithm Pattern: Staircase Search / Elimination-based Search
 * 
 * Note: For a fully sorted grid, binary search treating grid as 1D array
 * would be O(log(m*n)), but staircase search is simpler and more general.
 */

#include <iostream>
#include <vector>
using namespace std;

/*============================================================================
 * GRID SEARCH IMPLEMENTATION
 *============================================================================*/

/**
 * @brief Searches for a target in a sorted 2D grid using staircase search
 * @param grid Reference to the 2D grid (each row sorted, rows are consecutive)
 * @param target The value to search for
 * @return Pair of (row, col) indices if found, (-1, -1) otherwise
 * 
 * Algorithm (Starting from top-right corner):
 * 1. Initialize: row = 0 (top), col = cols-1 (rightmost)
 * 2. While within grid bounds:
 *    a. If grid[row][col] == target: Found! Return position
 *    b. If grid[row][col] > target: Move left (eliminate column)
 *    c. If grid[row][col] < target: Move down (eliminate row)
 * 3. Return (-1, -1) if not found
 * 
 * Why this works:
 * - At top-right: current element is largest in its row, smallest in its column
 * - If current > target: target can't be in this column (all below are larger)
 * - If current < target: target can't be in this row (all left are smaller)
 * 
 * Visual (searching for 5):
 *   [1, 2, 4, 5]    Start at 5 (top-right)
 *   [6, 7, 8, 9]    Found!
 */
pair<int, int> grid_search(vector<vector<int>>& grid, int target) {
  int rows = grid.size();
  int cols = grid[0].size();
  
  int l = 0;              // Current row (starts at top)
  int r = cols - 1;       // Current col (starts at rightmost)
  
  pair<int, int> p{-1, -1};  // Default: not found
  
  // Staircase traversal from top-right corner
  while(l < rows && r >= 0) {
    if(grid[l][r] == target) {
      p = {l, r};         // Found the target
      break;
    }
    else if(grid[l][r] > target) {
      r -= 1;             // Current too large, move left
    }
    else {
      l += 1;             // Current too small, move down
    }
  }
  
  return p;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Example 1: Target exists in grid
  vector<vector<int>> grid = {{1, 2, 4, 5}, {6, 7, 8, 9}};
  int target = 4;
  auto p = grid_search(grid, target);
  cout << "[" << p.first << ", " << p.second << "]\n";  // [0, 2]
  
  // Example 2: Target does not exist
  grid = {{1, 2, 4, 5}, {6, 7, 8, 9}};
  target = 3;
  p = grid_search(grid, target);
  cout << "[" << p.first << ", " << p.second << "]\n";  // [-1, -1]
  
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT
 *============================================================================
 * 
 * # Search in Sorted Grid
 * 
 * You are given a 2D grid of integers, `grid`, where each row is sorted 
 * (without duplicates), and the last value in each row is smaller than 
 * the first value in the following row. You are also given a target value, 
 * `target`. If the target is in the grid, return an array with its row 
 * and column indices. Otherwise, return [-1, -1].
 * 
 * Example 1:
 * target = 4
 * grid = [[1, 2, 4, 5],
 *         [6, 7, 8, 9]]
 * Output: [0, 2]. The number 4 is found in row 0 and column 2.
 * 
 * Example 2:
 * target = 3
 * grid = [[1, 2, 4, 5],
 *         [6, 7, 8, 9]]
 * Output: [-1, -1].
 * 
 * Constraints:
 * - 1 <= grid.length, grid[i].length <= 10000
 * - -10^4 <= grid[i][j], target <= 10^4
 * - The grid has no duplicates
 * 
 *============================================================================*/
