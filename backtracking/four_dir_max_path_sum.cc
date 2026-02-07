/**
 * @file four_dir_max_path_sum.cc
 * @brief Find the maximum sum path in a grid with 4-directional movement
 * 
 * This file implements a backtracking solution to find the path with the
 * largest sum from top-left to bottom-right, allowing movement in all four
 * cardinal directions (up, down, left, right) without revisiting cells.
 * 
 * Key Concepts:
 * - 4-directional movement (unlike 2-dir version which only goes down/right)
 * - Visited array to prevent revisiting cells (required for 4-dir movement)
 * - Grid can contain NEGATIVE values, making path selection non-trivial
 * - Backtracking explores ALL valid paths to find global maximum
 * 
 * Time Complexity: O(4^(R*C)) in worst case
 *   - At each cell, up to 4 directions to explore
 *   - Maximum path length is R*C (visiting all cells)
 *   - Pruning via visited array reduces actual complexity significantly
 * 
 * Space Complexity: O(R*C)
 *   - Visited array: O(R*C)
 *   - Recursion stack: O(R*C) depth in worst case (Hamiltonian path)
 * 
 * Comparison with 2-directional version:
 * - 2-dir (down/right only): O(2^(R+C)) time, no visited array needed
 * - 4-dir (all directions): O(4^(R*C)) time, visited array required
 */

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

/** Global variable to store the maximum path sum found */
int MAX_PATH_SUM = INT_MIN;

/** 
 * Direction vectors for 4-directional movement
 * {row_offset, col_offset}: UP, RIGHT, DOWN, LEFT
 */
vector<pair<int,int>> dir {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

/**
 * @brief Recursive backtracking function to explore all paths
 * 
 * @param grid     The input grid of integers (can be negative)
 * @param i        Current row index
 * @param j        Current column index
 * @param row      Total number of rows in the grid
 * @param col      Total number of columns in the grid
 * @param path_sum Running sum of the current path (passed by reference)
 * @param visited  2D boolean array tracking visited cells
 * 
 * Algorithm:
 * 1. Add current cell to path (mark visited, add value to sum)
 * 2. If at destination (bottom-right), update MAX_PATH_SUM
 * 3. Otherwise, try all 4 directions for unvisited, in-bounds cells
 * 4. Backtrack: unmark visited, subtract value from sum
 */
void solve(vector<vector<int>>& grid, int i, int j, int row, int col, 
           int& path_sum, vector<vector<bool>>& visited) {
  
  /**
   * @brief Lambda to check if a cell is safe to visit
   * @return true if cell is in-bounds AND not yet visited
   */
  auto is_safe = [&](int i_, int j_) { 
    return (i_ >= 0 && i_ < row && j_ >= 0 && j_ < col && !visited[i_][j_]);
  };

  // CHOOSE: Add current cell to path
  path_sum += grid[i][j];
  visited[i][j] = true;
  
  // EXPLORE: Try all 4 directions (if not at destination)
  for (auto& p : dir) {
    // If we've reached destination, don't explore further
    if (i == row-1 && j == col-1) break;
    
    int next_i = i + p.first;
    int next_j = j + p.second;
    
    if (is_safe(next_i, next_j)) {
      solve(grid, next_i, next_j, row, col, path_sum, visited);
    }
  }
  
  // Update maximum if we've reached the destination
  if (i == row-1 && j == col-1) {
    MAX_PATH_SUM = max(MAX_PATH_SUM, path_sum);
  }
  
  // UNCHOOSE: Backtrack - remove current cell from path
  path_sum -= grid[i][j];
  visited[i][j] = false;
}

/**
 * @brief Wrapper function to find max path sum in the grid
 * 
 * @param grid The input grid of integers
 * 
 * Initializes the starting position, path sum, and visited array,
 * then calls the recursive solver. Result is stored in MAX_PATH_SUM.
 */
void max_path_sum(vector<vector<int>>& grid) {
  int row = grid.size();
  int col = grid[0].size();
  int i = 0;          // Start row (top-left)
  int j = 0;          // Start column (top-left)
  int path_sum = 0;   // Initial path sum
  
  // Initialize visited array (all false)
  vector<vector<bool>> visited(row, vector<bool>(col, false));
  
  solve(grid, i, j, row, col, path_sum, visited);
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Example: 3x3 grid with positive and negative values
  // Grid visualization:
  //   [[ 1, -4,  3],
  //    [-2,  7, -6],
  //    [ 5, -4,  9]]
  //
  // Optimal path: (0,0) -> (0,1) -> (1,1) -> (1,0) -> (2,0) -> (2,1) -> (2,2)
  // Values:          1  ->  -4  ->   7  ->  -2  ->   5  ->  -4  ->   9  = 12
  
  MAX_PATH_SUM = INT_MIN;  // Reset for each test (handles negative sums)
  
  vector<vector<int>> grid {
    { 1, -4,  3},
    {-2,  7, -6},
    { 5, -4,  9}
  };
  
  max_path_sum(grid);
  
  cout << "Grid:" << endl;
  cout << "[[ 1, -4,  3]," << endl;
  cout << " [-2,  7, -6]," << endl;
  cout << " [ 5, -4,  9]]" << endl;
  cout << "Maximum path sum: " << MAX_PATH_SUM << endl;  // Output: 12
  
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # 4-Directional Max-Sum Path
 * 
 * Given an RxC grid of integers (which can be negative), `grid`, find the
 * path from the top-left corner to the bottom-right corner with the largest
 * sum and return its sum. You can go in all four directions (diagonals not
 * allowed), but you can't visit a cell more than once.
 * 
 * Example: grid = [[ 1, -4,  3],
 *                  [-2,  7, -6],
 *                  [ 5, -4,  9]]
 * Output: 12
 * The maximum path is 1 -> -4 -> 7 -> -2 -> 5 -> -4 -> 9, which has sum 12.
 * 
 * Constraints:
 * - `grid` has 1 to 5 rows and 1 to 5 columns.
 * - `grid[i][j]` is an integer between -100 and 100.
 * 
 *============================================================================*/
