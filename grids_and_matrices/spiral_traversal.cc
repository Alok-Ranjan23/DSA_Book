/**
 * @file spiral_traversal.cc
 * @brief Traverse a matrix in spiral order (classic layer-peeling approach)
 *
 * Direction per layer:
 *   → top row    (left to right),  then top++
 *   ↓ right col  (top to bottom),  then right--
 *   ← bottom row (right to left),  then bottom--  [only if top <= bottom]
 *   ↑ left col   (bottom to top),  then left++    [only if left <= right]
 *
 * Time Complexity : O(m*n) — every cell visited exactly once
 * Space Complexity: O(1)   — output vector aside, no extra space
 */

#include <iostream>
#include <vector>
using namespace std;

vector<int> spiral_traversal(vector<vector<int>>& matrix) {
  vector<int> result;
  if (matrix.empty()) return result;

  int top    = 0,               bottom = matrix.size() - 1;
  int left   = 0,               right  = matrix[0].size() - 1;

  while (top <= bottom && left <= right) {

    // ── Step 1: top row, left → right ──────────────────────────────────────
    for (int k = left; k <= right; k++)
      result.push_back(matrix[top][k]);
    top++;

    // ── Step 2: right col, top → bottom ────────────────────────────────────
    for (int k = top; k <= bottom; k++)
      result.push_back(matrix[k][right]);
    right--;

    // ── Step 3: bottom row, right → left  (guard: row still exists) ────────
    if (top <= bottom) {
      for (int k = right; k >= left; k--)
        result.push_back(matrix[bottom][k]);
      bottom--;
    }

    // ── Step 4: left col, bottom → top    (guard: col still exists) ────────
    if (left <= right) {
      for (int k = bottom; k >= top; k--)
        result.push_back(matrix[k][left]);
      left++;
    }
  }

  return result;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

void print(const string& label, vector<vector<int>>& m) {
  cout << label << "\n";
  for (auto& row : m) {
    for (int v : row) cout << v << " ";
    cout << "\n";
  }
  cout << "Spiral: ";
  auto res = spiral_traversal(m);
  for (int v : res) cout << v << " ";
  cout << "\n===========================\n";
}

int main() {
  // Example 1: 3x3
  vector<vector<int>> m1 = {{1,2,3},{4,5,6},{7,8,9}};
  print("3x3", m1);

  // Example 2: 1x1
  vector<vector<int>> m2 = {{42}};
  print("1x1", m2);

  // Example 3: 1-row
  vector<vector<int>> m3 = {{1,2,3,4}};
  print("1x4", m3);

  // Example 4: 1-col
  vector<vector<int>> m4 = {{1},{2},{3},{4}};
  print("4x1", m4);

  // Example 5: 4x4
  vector<vector<int>> m5 = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
  print("4x4", m5);

  // Example 6: 3x5 (non-square)
  vector<vector<int>> m6 = {{1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15}};
  print("3x5", m6);

  return 0;
}
