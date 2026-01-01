/**
 * @file snowprints.cc
 * @brief Track an arctic fox's closest approach to a river
 * 
 * Given a binary grid representing snowprints, find how close the fox
 * got to the river (above row 0) while crossing from left to right.
 * 
 * Key Concepts:
 * - Path following through grid
 * - Fox can move up/down by at most 1 row between columns
 * - Each column has exactly one '1' marking the fox's position
 * - Track minimum row index (closest to river at row 0)
 * 
 * Algorithm:
 * 1. Find starting position in column 0
 * 2. For each column, find where fox moves to in next column
 * 3. Track minimum row reached throughout the path
 * 
 * Time Complexity: O(C) where C = number of columns
 * Space Complexity: O(1) - only tracking current position and minimum
 */

#include <iostream>
#include <vector>
using namespace std;

/** Direction offsets: up (-1), same (0), down (+1) */
const vector<int> dir {-1,0,1};

/*============================================================================
 * MAIN ALGORITHM
 *============================================================================*/

/**
 * @brief Finds how close the fox got to the river
 * @param grid Binary grid where 1 = snowprint, 0 = no print
 * @return Minimum row index reached (0 = touching the river)
 *         Returns -1 if no fox found in first column
 * 
 * The river is above row 0, so smaller row index = closer to river.
 */
int closest_river(vector<vector<int>>& grid) {
  int rows = grid.size();
  int cols = grid[0].size();
  int r=-1;
  for(int i=0;i<rows;++i) {
    if(grid[i][0]==1) {
      r = i;
      break;
    }
  }
  if(r==-1) return -1;
  int c = 0;
  int res = r;
  while(c<cols) {
    for(auto& r_dir : dir) {
      int r_new = r + r_dir;
      if(r_new>=0 && r_new<rows && c+1<cols && grid[r_new][c+1]==1) {
        res = min(r_new,res);
        break;
      }
    }
    r = res;
    c+=1;
  }
  return res;
}
/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  vector<vector<int>> grid {
    {0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0},
    {1, 1, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 1}};
  cout<<closest_river(grid)<<"\n";
  grid = {
    {0, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 1, 0},
    {1, 1, 0, 1, 0, 1},
    {0, 0, 0, 0, 0, 0}};
  cout<<closest_river(grid)<<"\n";
  grid = {{1, 1, 1,}};
  cout<<closest_river(grid)<<"\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 *
 * # Snowprints

// We are tracking _Elsa_, an arctic fox, through a rectangular snowy field represented by a binary grid, `field`, where `1` denotes snowprints and `0` denotes no snowprints. We know that the fox crossed the field from left to right, so each column has exactly one `1`. Between two consecutive columns, the row of the `1` may remain the same, go up by one, or go down by one. Above the field (above the first row), there is an icy river. Return how close the fox got to the river, in terms of the number of rows between it and the river.

// Example 1:
// field = [[0, 0, 0, 0, 0, 0],
//          [0, 0, 1, 0, 0, 0],
//          [1, 1, 0, 1, 0, 0],
//          [0, 0, 0, 0, 1, 1]]
// Output: 1
// Explanation: The fox was closest to the river at column 2 (0-based), where it was 1 row away.

// Example 2:
// field = [[0, 0, 0, 1, 0, 0],
//          [0, 0, 1, 0, 1, 0],
//          [1, 1, 0, 0, 0, 1],
//          [0, 0, 0, 0, 0, 0]]
// Output: 0
// Explanation: The fox touched row 0, which is right next to the river.

// Example 3:
// field = [[1, 1, 1]]
// Output: 0
// Explanation: The fox stayed in row 0 the whole time.

// https://iio-beyond-ctci-images.s3.us-east-1.amazonaws.com/snowprints-1.png
// Above is a picture representation of Example 1.

// Constraints:

// - `1 ≤ R, C ≤ 1000`, where `R` is the number of rows and `C` is the number of columns
// - `field[i][j]` is either `0` or `1`
// - Each column has exactly one `1`
// - The fox's path is valid (moves at most one row up/down between columns)
 *
 *============================================================================*/
