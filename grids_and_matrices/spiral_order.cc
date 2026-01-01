/**
 * @file spiral_order.cc
 * @brief Generate an n×n grid filled in spiral order from center
 * 
 * Creates a square grid with numbers 0 to n²-1 arranged in a spiral pattern,
 * starting from the center and going clockwise (initially downward).
 * 
 * Key Concepts:
 * - Layer-by-layer filling from outside to inside (reverse order)
 * - Four directional movements per layer: right→up→left→down
 * - Values decrease as we fill from outer layers inward
 * 
 * Algorithm:
 * - Start with val = n²-1 (highest value) at outer edge
 * - Fill outer ring, then shrink boundaries and repeat
 * - Order: right column (bottom→top), top row (right→left),
 *          left column (top→bottom), bottom row (left→right)
 * 
 * Time Complexity: O(n²) - visit each cell exactly once
 * Space Complexity: O(n²) for the output grid
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
 * @param board Reference to the 2D vector to print
 */
void print(vector<vector<int>>& board) {
  for(auto& rows: board) {
    for(auto& val: rows) {
      cout<<setw(3)<<val<<" ";
    }
    cout<<"\n";
  }
  cout<<"===========================\n";
}

/*============================================================================
 * MAIN ALGORITHM
 *============================================================================*/

/**
 * @brief Generates and prints an n×n spiral-ordered grid
 * @param n Size of the grid (must be positive and odd)
 * 
 * Fills the grid with values 0 to n²-1 in spiral order,
 * starting from center going down, then clockwise.
 * 
 * Visual for n=3:    4 5 6
 *                    3 0 7
 *                    2 1 8
 */
void spiral_order(int n) {
  vector<vector<int>> board(n,vector<int>(n,0));
  int rows = n;
  int cols = n;
  int i = 0, j = 0;
  int val = rows * cols - 1;
  while(i<rows && j<cols) {
    for(int k = rows - 1; k>=i; --k) {
      board[k][cols-1] = val--;
    }
    cols--;
    for(int k = cols-1;k>=j;--k) {
      board[i][k] = val--;
    }
    i++;
    for(int k=i;k<rows;++k) {
      board[k][j] = val--;
    }
    j++;
    for(int k=j;k<cols;++k) {
      board[rows-1][k] = val--;
    }
    rows--;
  }
  print(board);
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  int n = 5;
  spiral_order(n);
  n = 1;
  spiral_order(n);
  n = 3;
  spiral_order(n);
  n = 7;
  spiral_order(n);
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 *
 * # Spiral Order

// Given a positive and odd integer `n`, return an `nxn` grid of integers filled as follows: the grid should have every number from `0` to `n^2 - 1` in _spiral order_, starting by going down from the center and turning clockwise.

// Example 1:
// n = 5
// Output: [[16, 17, 18, 19, 20],
//          [15,  4,  5,  6, 21],
//          [14,  3,  0,  7, 22],
//          [13,  2,  1,  8, 23],
//          [12, 11, 10,  9, 24]]

// Example 2:
// n = 1
// Output: [[0]]

// Example 3:
// n = 3
// Output: [[4, 5, 6],
//          [3, 0, 7],
//          [2, 1, 8]]

// https://iio-beyond-ctci-images.s3.us-east-1.amazonaws.com/spiral-order-1.png

// Constraints:

// - `0 < n < 1000`
// - `n` is odd
 *
 *============================================================================*/
