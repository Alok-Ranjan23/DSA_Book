/**
 * @file chess_moves.cc
 * @brief Calculate reachable cells for chess pieces (King, Knight, Queen)
 * 
 * Given a chessboard with some occupied cells, determines which cells
 * a piece at a given position can reach in a single move.
 * 
 * Key Concepts:
 * - Direction vectors for each piece type
 * - King: 8 adjacent cells (including diagonals)
 * - Knight: L-shaped jumps (2+1 or 1+2 in any direction)
 * - Queen: unlimited distance in 8 directions (blocked by pieces)
 * 
 * Movement Patterns:
 * - King/Queen share same 8 directions (Queen extends them)
 * - Knight has 8 unique L-shaped moves
 * - Queen stops when hitting an occupied cell
 * 
 * Time Complexity: O(n) for Queen (can traverse entire row/col/diagonal)
 *                  O(1) for King and Knight (fixed number of moves)
 * Space Complexity: O(k) where k = number of reachable cells
 */

#include <iostream>
#include <utility>
#include <vector>
using namespace std;

/** King/Queen direction vectors: 8 directions (orthogonal + diagonal) */
const vector<pair<int,int>> king_moves {{0,1},{-1,0},{0,-1},{1,0},{1,-1},{-1,-1},{-1,1},{1,1}};

/** Knight direction vectors: 8 L-shaped jumps */
const vector<pair<int,int>> knight_moves {{1,2},{-1,2},{-1,-2},{1,-2},{2,-1},{-2,-1},{-2,1},{2,1}};

/*============================================================================
 * MAIN ALGORITHM
 *============================================================================*/

/**
 * @brief Finds all cells reachable by a piece in one move
 * @param board n×n binary grid (0 = empty, 1 = occupied)
 * @param piece Type of piece: "king", "knight", or "queen"
 * @param r Starting row position
 * @param c Starting column position
 * @return Vector of (row, col) pairs for all reachable empty cells
 * 
 * Note: The piece can only land on empty cells (value 0).
 */
vector<pair<int, int>> reach_pieces(vector<vector<int>>& board,string& piece, int r, int c) {
  pair<int,int> pos{r,c};
  int row = board.size();
  int col = board[0].size();
  auto isSafe = [&](int new_r,int new_c) {
    return new_r >= 0 && new_r < row && new_c >= 0 && new_c < col && board[new_r][new_c] == 0;
  };
  const vector<pair<int,int>> moves = (piece == "knight") ? knight_moves: king_moves;
  vector<pair<int,int>> res;
  for(const auto& p : moves) {
    int new_r = pos.first + p.first;
    int new_c = pos.second + p.second;
    if(piece=="queen") {
      while(isSafe(new_r, new_c)) {
        res.push_back({new_r,new_c});
        new_r += p.first;
        new_c += p.second;
      }
    }
    else if(isSafe(new_r,new_c)) {
      res.push_back({new_r,new_c});
    }
  }
  return res;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  vector<vector<int>> board {
    {0, 0, 0, 1, 0, 0},
    {0, 1, 1, 1, 0, 0},
    {0, 1, 0, 1, 1, 0},
    {1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0}
  };string piece {"king"}; int r = 3, c = 5;
  for(auto [x,y]: reach_pieces(board,piece,r,c)) cout<<x<<" "<<y<<"\n";
  cout<<"===============================\n";
  piece = "knight"; r = 4, c = 3;
  for(auto [x,y]: reach_pieces(board,piece,r,c)) cout<<x<<" "<<y<<"\n";
  cout<<"===============================\n";
  piece = "queen"; r = 4, c = 4;
  for(auto [x,y]: reach_pieces(board,piece,r,c)) cout<<x<<" "<<y<<"\n";
  cout<<"===============================\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 *
 * # Chess Moves

// For context, this is how the King, Knight, and Queen move on a chessboard:

// https://iio-beyond-ctci-images.s3.us-east-1.amazonaws.com/chess-moves-1.png

// The king can go to any adjacent cell, including diagonals. The knight 'jumps' one cell in one dimension and two in the other, even if there are pieces in between. The queen can move _any number of cells_ in any direction, including diagonals, but cannot go through occupied cells.

// We are given three inputs:

// - `board`, an `nxn` binary grid, where a `0` denotes an empty cell, `1` denotes an occupied cell (for this problem, it doesn't matter what piece is in it)
// - `piece`, which is one of `"king"`, `"knight"`, or `"queen"`
// - `r` and `c`, with `0 ≤ r < n` and `0 ≤ c < n`, which denote an unoccupied position in the board

// Return a list of all the **unoccupied** cells in `board` that can be reached by the given `piece` in one move starting from `[r, c]`. The order of the output cells does not matter.

// Example 1:
// board = [[0, 0, 0, 1, 0, 0],
//          [0, 1, 1, 1, 0, 0],
//          [0, 1, 0, 1, 1, 0],
//          [1, 1, 1, 1, 0, 0],
//          [0, 0, 0, 0, 0, 0],
//          [0, 1, 0, 0, 0, 0]]
// piece = "king"
// r = 3
// c = 5
// Output: [[2, 5], [3, 4], [4, 4], [4, 5]]

// Example 2:
// board = [[0, 0, 0, 1, 0, 0],
//          [0, 1, 1, 1, 0, 0],
//          [0, 1, 0, 1, 1, 0],
//          [1, 1, 1, 1, 0, 0],
//          [0, 0, 0, 0, 0, 0],
//          [0, 1, 0, 0, 0, 0]]
// piece = "knight"
// r = 4
// c = 3
// Output: [[2, 2], [3, 5], [5, 5]]

// Example 3:
// board = [[0, 0, 0, 1, 0, 0],
//          [0, 1, 1, 1, 0, 0],
//          [0, 1, 0, 1, 1, 0],
//          [1, 1, 1, 1, 0, 0],
//          [0, 0, 0, 0, 0, 0],
//          [0, 1, 0, 0, 0, 0]]
// piece = "queen"
// r = 4
// c = 4
// Output: [[3, 4], [3, 5], [4, 0], [4, 1], [4, 2], [4, 3], [4, 5], [5, 3], [5, 4], [5, 5]]

// https://iio-beyond-ctci-images.s3.us-east-1.amazonaws.com/chess-moves-2.png

// Constraints:

// - `1 ≤ n ≤ 100`
// - `board[i][j]` is either `0` or `1`
// - `0 ≤ r, c < n`
// - `piece` is one of `"king"`, `"knight"`, or `"queen"`
 *
 *============================================================================*/
