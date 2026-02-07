/**
 * @file escape_with_all_clues.cc
 * @brief Find the shortest path from (0,0) that collects all clues without revisiting any cell
 * 
 * This file implements a backtracking solution to find the shortest path in a
 * grid that collects every clue (cell with value 2). The grid contains walkable
 * spaces (0), obstacles (1), and clues (2). Movement is 4-directional and no
 * cell may be visited more than once.
 * 
 * Key Concepts:
 * - 4-directional movement (up, down, left, right) without revisiting cells
 * - Backtracking with visited array to explore all valid paths
 * - Pruning: abandon paths that are already >= current best length
 * - Track shortest path globally; update whenever all clues are collected
 * 
 * Time Complexity: O(4^(R*C)) in worst case
 *   - At each cell, up to 4 directions to explore
 *   - Pruning via visited array and best-length check reduces actual work
 * 
 * Space Complexity: O(R*C)
 *   - Visited array: O(R*C)
 *   - Path vector: O(R*C) in worst case
 *   - Recursion stack: O(R*C) depth
 * 
 * Algorithm Insight:
 * Instead of BFS over (position, clues, visited) states, we use DFS with
 * backtracking:
 * 1. CHOOSE: Visit the current cell, mark visited, collect clue if present
 * 2. EXPLORE: Recurse into all 4 valid neighbors
 * 3. UNCHOOSE: Unvisit the cell and remove it from the path
 * We keep track of the best (shortest) complete path found so far and prune
 * branches that can't improve upon it.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

/** 
 * Direction vectors for 4-directional movement
 * {row_offset, col_offset}: UP, DOWN, LEFT, RIGHT
 */
vector<pair<int,int>> dir {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

/**
 * @brief Recursive backtracking function to explore all paths
 * 
 * @param room            The input grid (0=walkable, 1=obstacle, 2=clue)
 * @param rows            Total number of rows in the grid
 * @param cols            Total number of columns in the grid
 * @param K               Total number of clues to collect
 * @param r               Current row index
 * @param c               Current column index
 * @param cluesCollected  Number of clues collected so far
 * @param path            Current path being built (passed by reference)
 * @param visited         2D boolean array tracking visited cells
 * @param bestLen         Length of the shortest complete path found so far
 * @param bestPath        The shortest complete path found so far
 * 
 * Algorithm:
 * 1. CHOOSE: Add (r,c) to path, mark visited, collect clue if cell == 2
 * 2. Goal check: If all clues collected, update bestPath if shorter
 * 3. Prune: If current path length >= bestLen, abandon this branch
 * 4. EXPLORE: Try all 4 directions for unvisited, in-bounds, non-obstacle cells
 * 5. UNCHOOSE: Unmark visited, remove (r,c) from path
 */
void dfs(vector<vector<int>>& room, int rows, int cols, int K,
         int r, int c, int cluesCollected,
         vector<vector<int>>& path, vector<vector<bool>>& visited,
         int& bestLen, vector<vector<int>>& bestPath) {
  // CHOOSE: Add current cell to path
  path.push_back({r, c});
  visited[r][c] = true;
  if (room[r][c] == 2) cluesCollected++;

  // Goal check: all clues collected — update best if this path is shorter
  if (cluesCollected == K) {
    if ((int)path.size() < bestLen) {
      bestLen = path.size();
      bestPath = path;
    }
    // UNCHOOSE and return (no need to explore further)
    visited[r][c] = false;
    path.pop_back();
    return;
  }

  // Prune: no need to go deeper if we can't beat current best
  if ((int)path.size() >= bestLen) {
    visited[r][c] = false;
    path.pop_back();
    return;
  }

  // EXPLORE: Try all 4 directions
  for (auto& [drow, dcol] : dir) {
    int nr = r + drow, nc = c + dcol;
    if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
    if (room[nr][nc] == 1 || visited[nr][nc]) continue;  // obstacle or already visited

    dfs(room, rows, cols, K, nr, nc, cluesCollected,
        path, visited, bestLen, bestPath);
  }

  // UNCHOOSE: Backtrack — remove current cell from path
  visited[r][c] = false;
  path.pop_back();
}

/**
 * @brief Wrapper function to find shortest path collecting all clues
 * 
 * @param room The input grid (0=walkable, 1=obstacle, 2=clue)
 * @return Shortest path as list of [row, col] pairs, or empty if impossible
 * 
 * Steps:
 * 1. Count total number of clues (K) in the grid
 * 2. Initialize path, bestPath, visited array, and bestLen
 * 3. Handle edge case where (0,0) itself is a clue
 * 4. Call DFS backtracking starting from (0,0)
 */
vector<vector<int>> escapeWithAllClues(vector<vector<int>>& room) {
  // Step 1: Count clues
  const int rows = room.size();
  const int cols = room[0].size();

  int K = 0;
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
      if (room[i][j] == 2) K++;

  // Step 2: Initialize tracking structures
  vector<vector<int>> path, bestPath;
  vector<vector<bool>> visited(rows, vector<bool>(cols, false));
  int bestLen = INT_MAX;

  // Step 3: Handle (0,0) being a clue, then start DFS
  int initialClues = (room[0][0] == 2) ? 1 : 0;
  dfs(room, rows, cols, K, 0, 0, initialClues,
      path, visited, bestLen, bestPath);

  return bestPath;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Example 1: room = [[0, 1, 0],
  //                    [0, 2, 0],
  //                    [0, 0, 2]]
  // Expected: [[0,0], [1,0], [1,1], [1,2], [2,2]]
  //       or: [[0,0], [1,0], [1,1], [2,1], [2,2]]
  vector<vector<int>> room1 = {{0, 1, 0}, {0, 2, 0}, {0, 0, 2}};
  auto path1 = escapeWithAllClues(room1);
  cout << "Example 1: ";
  for (auto& p : path1) cout << "[" << p[0] << "," << p[1] << "] ";
  cout << "\n";

  // Example 2: room = [[0, 0, 0],
  //                    [2, 1, 2]]
  // Expected: [] (impossible without revisiting)
  vector<vector<int>> room2 = {{0, 0, 0}, {2, 1, 2}};
  auto path2 = escapeWithAllClues(room2);
  cout << "Example 2: " << (path2.empty() ? "[]" : "path found") << "\n";

  // Example 3: room = [[0, 0, 1, 2],
  //                    [0, 1, 0, 0]]
  // Expected: [] (clue is unreachable)
  vector<vector<int>> room3 = {{0, 0, 1, 2}, {0, 1, 0, 0}};
  auto path3 = escapeWithAllClues(room3);
  cout << "Example 3: " << (path3.empty() ? "[]" : "path found") << "\n";

  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Escape With All Clues
 * 
 * We are building an escape room puzzle where a player has to collect all the
 * clues in a room to unlock the way out. The room is represented by a non-empty
 * grid, `room`, consisting of walkable spaces (`0`), obstacles (`1`), and
 * clues (`2`). The player starts on the top-left cell of the grid, which is
 * guaranteed to be an open space, and can move to adjacent cells (diagonals not
 * allowed). If it is possible to collect all the clues **without repeating any
 * cell**, return an array with the list of cells in the shortest path to collect
 * them, starting with `[0, 0]`. Otherwise, return an empty array. If there are
 * multiple shortest paths, return any of them. It is guaranteed that there is at
 * least one clue.
 * 
 * Example 1: room = [[0, 1, 0],
 *                    [0, 2, 0],
 *                    [0, 0, 2]]
 * Output: [[0,0], [1,0], [1,1], [1,2], [2,2]].
 * The other valid output is [[0,0], [1,0], [1,1], [2,1], [2,2]].
 * 
 * Example 2: room = [[0, 0, 0],
 *                    [2, 1, 2]]
 * Output: []. It is not possible to get both clues without revisiting a cell.
 * 
 * Example 3: room = [[0, 0, 1, 2],
 *                    [0, 1, 0, 0]]
 * Output: []. It is not possible to reach the clue.
 * 
 * Constraints:
 * - `room` is a 2D grid of `0`s, `1`s, and `2`s.
 * - `room` has at least one `2`.
 * - `room[0][0]` is `0`.
 * - `room` has at least `1` to `6` rows and `1` to `6` columns.
 * 
 *============================================================================*/
