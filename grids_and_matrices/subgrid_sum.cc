/**
 * @file subgrid_sum.cc
 * @brief Implementation of Subgrid Sum calculation for a 2D grid
 * 
 * Given a rectangular grid, this algorithm computes a new grid where each cell
 * contains the sum of all values in the subgrid from that cell to the bottom-right corner.
 * 
 * Key Concepts:
 * - Dynamic Programming approach (bottom-right to top-left traversal)
 * - In-place modification of the grid
 * - Inclusion-Exclusion principle to avoid double counting
 * 
 * Algorithm:
 * - Traverse from bottom-right to top-left
 * - For each cell: add right neighbor + bottom neighbor - diagonal (to avoid double count)
 * - This works because right, bottom, and diagonal cells are already processed
 * 
 * Time Complexity: O(R * C) where R = rows, C = columns
 * Space Complexity: O(1) - modifies grid in-place
 */

#include <iostream>
#include <vector>
#include <iomanip> 
using namespace std;

/*============================================================================
 * HELPER FUNCTIONS
 *============================================================================*/

/**
 * @brief Prints the grid in a formatted manner
 * @param grid Reference to the 2D vector to print
 */
void print(vector<vector<int>>& grid) {
  for(auto& rows: grid) {
    for(auto& val: rows) {
      cout<<setw(3)<<val<<" ";
    }
    cout<<"\n";
  }
}

/*============================================================================
 * MAIN ALGORITHM
 *============================================================================*/

/**
 * @brief Computes subgrid sum for each cell in-place
 * @param grid Reference to the 2D vector (modified in-place)
 * 
 * For each cell [r,c], computes the sum of all elements in the subgrid
 * with [r,c] as top-left corner and [R-1,C-1] as bottom-right corner.
 * 
 * DP Recurrence (Inclusion-Exclusion):
 *   grid[r][c] = grid[r][c] + grid[r][c+1] + grid[r+1][c] - grid[r+1][c+1]
 *                             (right)        (bottom)       (subtract overlap)
 */
void subgrid_sum(vector<vector<int>>& grid) {
  cout<<"===== SUBGRID SUM =====\n";
  int rows = grid.size();
  int cols = grid[0].size();
  for(int r = rows-1; r>=0;r--) {
    for(int c = cols-1; c>=0;c--) {
      if(c+1<cols) {
        grid[r][c] = grid[r][c] + grid[r][c+1];
      }
      if(r+1<rows) {
        grid[r][c] = grid[r][c] + grid[r+1][c];
      }
      if(r+1<rows && c+1<cols) {
        grid[r][c] = grid[r][c] - grid[r+1][c+1];
      }
    }
  }
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  vector<vector<int>> grid {
    {-1,2,3},
    {4,0,0},
    {-2,0,9}};
  print(grid);
  subgrid_sum(grid);
  print(grid);
  cout<<"===========================\n";
  grid = {{5}};
  print(grid);
  subgrid_sum(grid);
  print(grid);
  cout<<"===========================\n";
  grid = {{1,2,3}};
  print(grid);
  subgrid_sum(grid);
  print(grid);
  cout<<"===========================\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 *
 * # Subgrid Sums

// Given a rectangular `RxC` grid of integers, `grid`, with `R > 0` and `C > 0`, return a new grid with the same dimensions where each cell `[r, c]` contains the sum of all the elements in the subgrid with `[r, c]` in the top-left corner and `[R - 1, C - 1]` in the bottom-right corner.

// Example 1:
// grid =  [[-1,  2,  3],
//          [ 4,  0,  0],
//          [-2,  0,  9]]
// Output: [[15, 14, 12],
//          [11,  9,  9],
//          [ 7,  9,  9]]

// Example 2:
// grid =  [[5]]
// Output: [[5]]
// Explanation: For a 1x1 grid, each cell's subgrid is just itself.

// Example 3:
// grid =  [[1, 2, 3]]
// Output: [[6, 5, 3]]
// Explanation: For a single row, each cell's subgrid includes all elements to its right.

// Constraints:

// - 1 ≤ R, C ≤ 10^3
// - -10^3 ≤ grid[i][j] ≤ 10^3
 *
 *============================================================================*/
