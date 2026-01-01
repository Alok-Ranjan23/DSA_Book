/**
 * @file matrix_operation.cc
 * @brief Implementation of common matrix operations (in-place)
 * 
 * Implements a Matrix class with fundamental matrix transformations:
 * transposition, rotation (clockwise/counterclockwise), and reflections.
 * All operations modify the matrix in-place using O(1) extra space.
 * 
 * Key Concepts:
 * - Transposition: swap elements across main diagonal (rows ↔ columns)
 * - Rotation: combination of transposition + reflection
 * - Reflection: reverse rows (horizontal) or columns (vertical)
 * 
 * Rotation Formulas:
 * - Clockwise 90°     = Transpose + Horizontal Reflection
 * - Anticlockwise 90° = Transpose + Vertical Reflection
 * 
 * Time Complexity: O(n²) for all operations on n×n matrix
 * Space Complexity: O(1) - all operations are in-place
 */

#include <iostream>
#include <vector>
using namespace std;

/*============================================================================
 * CLASS DEFINITION
 *============================================================================*/

/**
 * @class MatrixOp
 * @brief A class for performing in-place matrix transformations
 * 
 * Supports transposition, rotations, and reflections on square matrices.
 * All operations modify the internal matrix without allocating new memory.
 */
class MatrixOp {
  private:
  vector<vector<int>> inputs;
  public:
  MatrixOp(vector<vector<int>> grid = {}): inputs {grid} {}
  ~MatrixOp() {}
  void transposition();
  void clockwise_rotation();
  void anti_clockwise_rotation();
  void horizontal_reflection();
  void vertical_reflection();
  void print();
};

/*============================================================================
 * IMPLEMENTATION SECTION
 *============================================================================*/

/**
 * transposition() - Swap rows and columns
 * 
 * Element at [i][j] moves to [j][i].
 * Only swap upper triangle with lower triangle to avoid double-swapping.
 */
void MatrixOp::transposition() {
  int row = inputs.size();
  int col = inputs[0].size();
  for(int i=0;i<row;++i) {
    for(int j=i+1;j<col;++j) {
      int temp     = inputs[i][j];
      inputs[i][j] = inputs[j][i];
      inputs[j][i] = temp;
    }
  }
}

/**
 * clockwise_rotation() - Rotate matrix 90° clockwise
 * 
 * Formula: Clockwise = Transpose + Horizontal Reflection
 * Example: [1,2]  transpose→  [1,3]  h_reflect→  [3,1]
 *          [3,4]              [2,4]              [4,2]
 */
void MatrixOp::clockwise_rotation() {
  transposition();
  horizontal_reflection();
}

/**
 * anti_clockwise_rotation() - Rotate matrix 90° counterclockwise
 * 
 * Formula: Anticlockwise = Transpose + Vertical Reflection
 * Example: [1,2]  transpose→  [1,3]  v_reflect→  [2,4]
 *          [3,4]              [2,4]              [1,3]
 */
void MatrixOp::anti_clockwise_rotation() {
  transposition();
  vertical_reflection();
}

/**
 * horizontal_reflection() - Mirror along vertical axis
 * 
 * First column becomes last, second becomes second-last, etc.
 * Uses two-pointer technique to swap columns from outside in.
 */
void MatrixOp::horizontal_reflection() {
  int row = inputs.size();
  int col = inputs[0].size();
  for(int i=0;i<row;++i) {
    int l = 0; 
    int h = col - 1;
    while(l<h) {
      int temp     = inputs[i][l];
      inputs[i][l] = inputs[i][h];
      inputs[i][h] = temp;
      l+=1;
      h-=1;
    }
  }
}

/**
 * vertical_reflection() - Mirror along horizontal axis
 * 
 * First row becomes last, second becomes second-last, etc.
 * Uses two-pointer technique to swap rows from outside in.
 */
void MatrixOp::vertical_reflection() {
  int row = inputs.size();
  int col = inputs[0].size();
  for(int j=0;j<col;++j) {
    int l = 0;
    int h = row - 1;
    while(l<h) {
      int temp     = inputs[l][j];
      inputs[l][j] = inputs[h][j];
      inputs[h][j] = temp;
      l+=1;
      h-=1;
    }
  }
}

/**
 * print() - Display the current matrix state
 */
void MatrixOp::print() {
  int row = inputs.size();
  int col = inputs[0].size();
  for(int i=0;i<row;++i) {
    for(int j=0;j<col;++j) {
      cout<<inputs[i][j]<<" ";
    }
    cout<<"\n";
  }
  cout<<"=========================\n";
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  vector<vector<int>> grid {{1,2},{3,4}};
  MatrixOp obj1 = MatrixOp(grid);
  obj1.print();
  obj1.transposition();
  obj1.print();
  MatrixOp obj2 = MatrixOp(grid);
  obj2.print();
  obj2.clockwise_rotation();
  obj2.print();
  MatrixOp obj3 = MatrixOp(grid);
  obj3.print();
  obj3.horizontal_reflection();
  obj3.print();
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 *
 * # Matrix Operations

// Basic matrix operations sometimes come up in coding interviews because they involve interesting grid transformations, but they usually don't assume background knowledge.

// https://iio-beyond-ctci-images.s3.us-east-1.amazonaws.com/matrix-operations-1.png

// - **Transposition**: The first row becomes the first column, the second row becomes the second column, and so on.
// - **Rotation**: A transformation that turns the matrix 90 degrees, clockwise or counterclockwise.
// - **Horizontal reflection**: The first column becomes the last column, the second column becomes the second last, and so on.
// - **Vertical reflection**: The first row becomes the last row, the second row becomes the second last, and so on.

// Implement a `Matrix` class that can be initialized with a square grid of floating point numbers. It must have methods for transposition, clockwise rotation, anticlockwise rotation, horizontal reflection, and vertical reflection. All the methods take zero parameters and should modify the matrix _in place_, using only `O(1)` extra space, and return nothing.

// Example 1: Transposition
// grid = [[1, 2],
//         [3, 4]]
// After transpose():
//        [[1, 3],
//         [2, 4]]

// Example 2: Clockwise Rotation
// grid = [[1, 2],
//         [3, 4]]
// After rotate_clockwise():
//        [[3, 1],
//         [4, 2]]

// Example 3: Horizontal Reflection
// grid = [[1, 2],
//         [3, 4]]
// After reflect_horizontally():
//        [[2, 1],
//         [4, 3]]

// Constraints:

// - 1 ≤ n ≤ 1000 where n is the size of the square matrix
// - -10^4 ≤ grid[i][j] ≤ 10^4
 *
 *============================================================================*/
