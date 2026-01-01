/**
 * @file valid_sudoku.cc
 * @brief Implementation of Sudoku board validation
 * 
 * Validates whether a 9x9 Sudoku board has any conflicts (duplicate numbers
 * in rows, columns, or 3x3 subgrids). Empty cells are represented by 0.
 * 
 * Key Concepts:
 * - Hash set for O(1) duplicate detection
 * - Three separate checks: rows, columns, and 3x3 subgrids
 * - 0 represents empty cells and is ignored during validation
 * 
 * Algorithm:
 * 1. Check each row for duplicates
 * 2. Check each column for duplicates
 * 3. Check each 3x3 subgrid for duplicates
 * 
 * Time Complexity: O(1) - fixed 9x9 board (or O(n²) for n×n board)
 * Space Complexity: O(1) - hash set holds at most 9 elements
 */

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

/*============================================================================
 * HELPER FUNCTIONS
 *============================================================================*/

/**
 * @brief Checks if a vector has no duplicate non-zero values
 * @param inputs Vector of integers to check
 * @return true if no duplicates (excluding zeros), false otherwise
 * 
 * Uses a hash set for O(n) time complexity where n is the input size.
 */
bool hasNoDup(vector<int>& inputs) {
  unordered_set<int> us;
  for(auto& val : inputs) {
    if(val==0) continue;
    else if(us.count(val)) return false;
    else us.insert(val);
  }
  return true;
}


/*============================================================================
 * MAIN ALGORITHM
 *============================================================================*/

/**
 * @brief Validates a Sudoku board for conflicts
 * @param board 9x9 grid with values 0-9 (0 = empty)
 * @return true if no conflicts exist, false otherwise
 * 
 * A conflict is a duplicate number (other than 0) in:
 * - Any row
 * - Any column
 * - Any 3x3 subgrid
 */
bool is_valid(vector<vector<int>>& board) {
  for(auto & row : board) {
    if(!hasNoDup(row)) return false;
  }
  int rows = board.size();
  int cols = board[0].size();
  for(int j=0;j<cols;++j) {
    vector<int> col_values;
    for(int i=0;i<rows;++i) {
      col_values.push_back(board[i][j]);
    }
    if(!hasNoDup(col_values)) return false;
  }
  for(int i=0;i<rows;i+=3) {
    for(int j=0;j<cols;j+=3) {
      vector<int> subgrid_values;
      for(int i_ = i; i_<i+3;++i_) {
        for(int j_ = j; j_<j+3;++j_) {
          subgrid_values.push_back(board[i_][j_]);
        }
      }
      if(!hasNoDup(subgrid_values)) return false;
    }
  }
  return true;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  vector<vector<int>> board {
    {5, 0, 0, 0, 0, 0, 0, 0, 6},
    {0, 0, 9, 0, 5, 0, 3, 0, 0},
    {0, 3, 0, 0, 0, 2, 0, 0, 0},
    {8, 0, 0, 7, 0, 0, 0, 0, 9},
    {0, 0, 2, 0, 0, 0, 8, 0, 0},
    {4, 0, 0, 0, 0, 6, 0, 0, 3},
    {0, 0, 0, 3, 0, 0, 0, 4, 0},
    {0, 0, 3, 0, 8, 0, 2, 0, 0},
    {9, 0, 0, 0, 0, 0, 0, 0, 7}
  };
  cout<<boolalpha;
  cout<<is_valid(board)<<"\n";
  board = {
    {5, 0, 0, 0, 0, 0, 0, 0, 6},
    {0, 0, 9, 0, 5, 0, 3, 0, 0},
    {0, 3, 0, 0, 0, 2, 0, 0, 0},
    {8, 0, 0, 7, 0, 0, 0, 0, 9},
    {0, 0, 2, 0, 0, 0, 8, 0, 0},
    {4, 0, 0, 0, 0, 6, 0, 0, 3},
    {0, 0, 0, 3, 0, 0, 0, 4, 0},
    {0, 0, 3, 0, 8, 0, 7, 0, 0},
    {9, 0, 0, 0, 0, 0, 0, 0, 7}
  };
  cout<<is_valid(board)<<"\n";
    board = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0}
  };
  cout<<is_valid(board)<<"\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 *
 * # Valid Sudoku

// Given a 9x9 grid `board` representing a Sudoku, return `true` if the board does not have any conflicts and `false` otherwise. The board contains only numbers between 0 and 9 in each cell, with 0's denoting empty cells.

// A conflict is a duplicate number (other than 0) along a row, a column, or a 3x3 subgrid (shown with the thicker outline). For the purposes of this problem, it doesn't matter if the Sudoku has a valid solution or not -- only whether it has a conflict in the already-filled cells.

// For those who don't know the rules of Sudoku: the grid starts off with some cells pre-filled with numbers. The player is asked to fill in the empty cells with the numbers 1 through 9, such that there are no duplicates in the same row, column, or subgrid (the 3x3 sections shown with the thicker outline).

// Example 1:
// board = +-------+-------+-------+
//         | 5 . . | . . . | . . 6 |
//         | . . 9 | . 5 . | 3 . . |
//         | . 3 . | . . 2 | . . . |
//         +-------+-------+-------+
//         | 8 . . | 7 . . | . . 9 |
//         | . . 2 | . . . | 8 . . |
//         | 4 . . | . . 6 | . . 3 |
//         +-------+-------+-------+
//         | . . . | 3 . . | . 4 . |
//         | . . 3 | . 8 . | 2 . . |
//         | 9 . . | . . . | . . 7 |
//         +-------+-------+-------+
// Output: true

// Example 2:
// board = +-------+-------+-------+
//         | 5 . . | . . . | . . 6 |
//         | . . 9 | . 5 . | 3 . . |
//         | . 3 . | . . 2 | . . . |
//         +-------+-------+-------+
//         | 8 . . | 7 . . | . . 9 |
//         | . . 2 | . . . | 8 . . |
//         | 4 . . | . . 6 | . . 3 |
//         +-------+-------+-------+
//         | . . . | 3 . . | . 4 . |
//         | . . 3 | . 8 . | 7 . . |
//         | 9 . . | . . . | . . 7 |
//         +-------+-------+-------+
// Output: false
// Explanation: The bottom-right 3x3 subgrid has a duplicate, 7.

// Example 3:
// board = +-------+-------+-------+
//         | . . . | . . . | . . . |
//         | . . . | . . . | . . . |
//         | . . . | . . . | . . . |
//         +-------+-------+-------+
//         | . . . | . . . | . . . |
//         | . . . | . . . | . . . |
//         | . . . | . . . | . . . |
//         +-------+-------+-------+
//         | . . . | . . . | . . . |
//         | . . . | . . . | . . . |
//         | . . . | . . . | . . . |
//         +-------+-------+-------+
// Output: true
// Explanation: An empty board has no conflicts.

// https://iio-beyond-ctci-images.s3.us-east-1.amazonaws.com/valid-sudoku-1.png

// Constraints:

// - board.length == 9
// - board[i].length == 9
// - board[i][j] is a digit between 0 and 9.
 *
 *============================================================================*/
