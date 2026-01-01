/**
 * @file queen_reach.cc
 * @brief Mark all cells reachable by queens on a chessboard
 * 
 * Given a board with queens, marks all cells that are either occupied
 * by a queen or reachable by any queen in a single move.
 * 
 * Key Concepts:
 * - Queen moves any number of cells in 8 directions
 * - Queen is blocked by other queens (cannot pass through)
 * - In-place modification of the board
 * - A cell is "safe" (0) only if no queen can reach it
 * 
 * Algorithm:
 * 1. Find all queens on the board
 * 2. For each queen, extend in all 8 directions
 * 3. Mark each reachable empty cell as unsafe (1)
 * 
 * Time Complexity: O(n² × q) where q = number of queens
 *                  (each queen can reach O(n) cells in each direction)
 * Space Complexity: O(q) for storing queen positions
 */

#include <iostream>
#include <vector>
using namespace std;

/** 8 direction vectors for queen movement (orthogonal + diagonal) */
const vector<pair<int,int>> direction {{0,1},{-1,0},{0,-1},{1,0},{1,-1},{-1,-1},{-1,1},{1,1}};

/*============================================================================
 * HELPER FUNCTIONS
 *============================================================================*/

/**
 * @brief Prints the board in a simple format
 * @param board Reference to the 2D vector to print
 */
void print(vector<vector<int>>& board) {
  for(auto& row : board) {
    for(auto& cell : row) {
      cout<<cell<<" ";
    }
    cout<<"\n";
  }
}

/*============================================================================
 * MAIN ALGORITHM
 *============================================================================*/

/**
 * @brief Marks all cells reachable by queens as unsafe
 * @param board n×n binary grid (modified in-place)
 *              Input:  0 = empty, 1 = queen
 *              Output: 0 = safe, 1 = unsafe (queen or reachable)
 * 
 * A safe cell is one that no queen can reach in a single move.
 */
void queen_reach(vector<vector<int>>& board) {
  int row = board.size();
  int col = board[0].size();
  
  auto isSafe = [&](int r_new,int c_new) {
    return r_new >= 0 && r_new < row && c_new >= 0 && c_new < col && board[r_new][c_new] == 0;
  };
  vector<pair<int,int>> queens;
  for(int i=0;i<row;++i) {
    for(int j=0;j<col;++j) {
      if(board[i][j] == 1) queens.push_back({i,j});
    }
  }

  for(auto& [r,c]: queens) {
    for(auto& p: direction) {
      int r_new = r + p.first;
      int c_new = c + p.second;
      while(isSafe(r_new,c_new)) {
        board[r_new][c_new] = 1;
        r_new += p.first;
        c_new += p.second;
      }
    }
  }
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  vector<vector<int>> board {
    {0, 0, 0, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {1, 0, 0, 0}
  };
  cout<<"===== Initial Board =====\n";
  print(board);
  cout<<"===== Board After Queen's Moves =====\n";
  queen_reach(board);
  print(board);

  board  = {{1}};
  cout<<"===== Initial Board =====\n";
  print(board);
  cout<<"===== Board After Queen's Moves =====\n";
  queen_reach(board);
  print(board);

  board  = {{0}};
  cout<<"===== Initial Board =====\n";
  print(board);
  cout<<"===== Board After Queen's Moves =====\n";
  queen_reach(board);
  print(board);
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 *
 * # Queen's Reach

// Imagine that an `n x n` chessboard has a number of queens in it. Remember that in chess, a queen can move any number of cells horizontally, vertically, or diagonally.

// We are given an `nxn` binary grid, `board`, with `n > 0`, where `0` indicates that the cell is unoccupied, and a `1` indicates a queen (the color of the queen doesn't matter). Return a binary board with the same dimensions. In the returned board, `0` denotes that a cell is 'safe', and a `1` denotes that a cell is not safe. A cell is _safe_ if there isn't a queen in it and no queen on the board can reach it in a single move.

// Example 1:
// board = [[0, 0, 0, 1],
//          [0, 0, 0, 0],
//          [0, 0, 0, 0],
//          [1, 0, 0, 0]]
// Output: [[1, 1, 1, 1],
//          [1, 0, 1, 1],
//          [1, 1, 0, 1],
//          [1, 1, 1, 1]]

// Example 2:
// board = [[1]]
// Output: [[1]]
// Explanation: The only cell has a queen, so it's not safe.

// Example 3:
// board = [[0]]
// Output: [[0]]
// Explanation: With no queens, all cells are safe.

// https://iio-beyond-ctci-images.s3.us-east-1.amazonaws.com/queens-reach-1.png

// Constraints:

// - `1 ≤ n ≤ 100`
// - `board[i][j]` is either `0` or `1`
 *
 *============================================================================*/
