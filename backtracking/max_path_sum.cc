/**
 * @file max_path_sum.cc
 * @brief Find the maximum sum path from top-left to bottom-right in a grid
 * 
 * This file implements a backtracking solution to find the path with the
 * largest sum in a grid, where movement is restricted to down or right only.
 * 
 * Key Concepts:
 * - Backtracking with path sum tracking
 * - Grid traversal with restricted movement (down/right only)
 * - Global maximum tracking across all valid paths
 * 
 * Time Complexity: O(2^(R+C)) where R=rows, C=cols
 *   - At each cell, we branch into 2 directions
 *   - Path length is (R-1)+(C-1) = R+C-2 moves
 * 
 * Space Complexity: O(R+C) for recursion stack depth
 * 
 * Note: This backtracking approach is for educational purposes.
 * For optimal performance, use Dynamic Programming: O(R*C) time and space.
 */

#include <iostream>
#include <vector>
using namespace std;

/** Global variable to store the maximum path sum found */
int MAX_PATH_SUM = 0;

/**
 * @brief Recursive backtracking function to explore all paths
 * 
 * @param grid      The input grid of positive integers
 * @param i         Current row index
 * @param j         Current column index
 * @param row       Total number of rows in the grid
 * @param col       Total number of columns in the grid
 * @param path_sum  Running sum of the current path (passed by reference)
 * 
 * Algorithm:
 * 1. Check if we've reached just beyond the bottom-right cell (success)
 * 2. Check if we've gone out of bounds (failure)
 * 3. Add current cell value to path sum
 * 4. Recursively explore: go DOWN, then go RIGHT
 * 5. Backtrack: remove current cell value from path sum
 */
void solve(vector<vector<int>>& grid, int i, int j, int row, int col, int& path_sum) {
  // Base case: Reached one step past the bottom-right corner
  // This means we've successfully traversed the entire path
  if((i == row && j == col-1) || (j == col && i == row-1)) {
    MAX_PATH_SUM = max(MAX_PATH_SUM, path_sum);
    return;
  }
  
  // Out of bounds check: gone beyond grid limits
  if(i == row || j == col) {
    return;
  }
  
  // CHOOSE: Add current cell to path
  path_sum += grid[i][j];
  
  // EXPLORE: Try both possible directions
  solve(grid, i+1, j, row, col, path_sum);  // Go DOWN
  solve(grid, i, j+1, row, col, path_sum);  // Go RIGHT
  
  // UNCHOOSE: Backtrack by removing current cell from path
  path_sum -= grid[i][j];
}

/**
 * @brief Wrapper function to find max path sum in the grid
 * 
 * @param grid The input grid of positive integers
 * 
 * Initializes the starting position and path sum, then calls
 * the recursive solver. Result is stored in MAX_PATH_SUM.
 */
void max_path_sum(vector<vector<int>>& grid) {
  int row = grid.size();
  int col = grid[0].size();
  int i = 0;          // Start row
  int j = 0;          // Start column
  int path_sum = 0;   // Initial path sum
  solve(grid, i, j, row, col, path_sum);
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Example 1: 3x3 grid
  // Expected path: 1 -> 4 -> 7 -> 8 -> 9 = 29
  MAX_PATH_SUM = 0;
  vector<vector<int>> grid {
    {1, 4, 3},
    {2, 7, 6},
    {5, 8, 9}
  };
  max_path_sum(grid);
  cout << MAX_PATH_SUM << "\n";  // Output: 29
  
  // Example 2: Single cell grid
  // Expected: 5 (only one cell)
  MAX_PATH_SUM = 0;
  grid = {{5}};
  max_path_sum(grid);
  cout << MAX_PATH_SUM << "\n";  // Output: 5
  
  // Example 3: Single row grid
  // Expected path: 1 -> 2 -> 3 = 6
  MAX_PATH_SUM = 0;
  grid = {{1, 2, 3}};
  max_path_sum(grid);
  cout << MAX_PATH_SUM << "\n";  // Output: 6
  
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Max-Sum Path
 * 
 * Given a non-empty grid of positive integers, `grid`, find the path from 
 * the top-left corner to the bottom-right corner with the largest sum. 
 * You can only go down or to the right (not diagonal).
 * 
 * Example 1: grid = [[1, 4, 3],
 *                    [2, 7, 6],
 *                    [5, 8, 9]]
 * Output: 29. The maximum path is 1 -> 4 -> 7 -> 8 -> 9.
 * 
 * Example 2: grid = [[5]]
 * Output: 5
 * 
 * Example 3: grid = [[1, 2, 3]]
 * Output: 6. The maximum path is 1 -> 2 -> 3.
 * 
 * Constraints:
 * - 1 <= R, C <= 1000, where R is rows and C is columns
 * - 1 <= grid[i][j] <= 1000
 * 
 *============================================================================*/
