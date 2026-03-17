/**
 * @file Spreadsheet.cc
 * @brief Spreadsheet Class with Stable Sorting of Rows and Columns
 * 
 * This file implements a Spreadsheet class that supports get/set operations
 * on a 2D grid of integers, along with stable sorting of entire rows by a
 * given column and entire columns by a given row.
 * 
 * Key Concepts:
 * - 2D grid stored as vector<vector<int>>
 * - Stable sorting preserves relative order of equal elements
 * - sort_columns_by_row: Reorders all columns based on values in one row
 *   (requires indirect index sorting + full grid reconstruction)
 * - sort_rows_by_column: Reorders all rows based on values in one column
 *   (direct stable_sort on the row vectors)
 * 
 * Algorithm (sort_columns_by_row):
 * 1. Build pairs of (column_index, value_in_target_row)
 * 2. Stable-sort pairs by value to get new column ordering
 * 3. Reconstruct entire grid according to new column order
 * 
 * Algorithm (sort_rows_by_column):
 * 1. Stable-sort the row vectors using the target column as the key
 * 
 * Time Complexities:
 * - set() / get():          O(1)
 * - sort_columns_by_row():  O(C log C + R*C) where R = rows, C = cols
 * - sort_rows_by_column():  O(R*C log R) - comparing entire rows during sort
 * 
 * Space Complexity: O(R * C) for the grid + O(R * C) temporary during column sort
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * @class Spreadsheet
 * @brief A 2D integer grid supporting cell access and stable row/column sorting
 * 
 * The grid is initialized to all zeros. Rows and columns are 0-indexed.
 * Sorting operations are stable: equal-valued elements retain their
 * original relative order.
 */
class Spreadsheet {
  vector<vector<int>> res;
  public:

  /**
   * @brief Constructor - initializes an R x C grid filled with zeros
   * @param row_size Number of rows
   * @param col_size Number of columns
   */
  Spreadsheet(int row_size, int col_size) {
    res.resize(row_size);
    for(int i=0;i<row_size;++i) 
    res[i].resize(col_size,0);
  }

  /**
   * @brief Sets the value at cell (i, j)
   * @param i Row index
   * @param j Column index
   * @param val Value to store
   */
  void set(int i, int j, int val) {
    res[i][j] = val;
  }

  /**
   * @brief Gets the value at cell (i, j)
   * @param i Row index
   * @param j Column index
   * @return Value stored at (i, j)
   */
  int get(int i, int j) {
    return res[i][j];
  }

  /**
   * @brief Sorts all columns by the values in the specified row (stable)
   * @param row The row whose values determine column ordering
   * 
   * Algorithm:
   * 1. Create (column_index, row_value) pairs for every column
   * 2. Stable-sort pairs by row_value (ascending)
   * 3. Rebuild the entire grid with columns in the new order
   * 
   * Example: If row 0 = [5, 3, 8], sorting columns by row 0 gives
   * column order [1, 0, 2] since 3 < 5 < 8.
   * All rows are reordered to match this new column arrangement.
   * 
   * Time Complexity: O(C log C + R*C)
   * Space Complexity: O(R*C) for the temporary grid
   */
  void sort_columns_by_row(int row) {
    int R = res.size();
    int C = res[0].size();
    vector<pair<int,int>> ColumnsWithRowVal;
    for(int c=0;c<C;++c) ColumnsWithRowVal.push_back({c,res[row][c]});
    
    stable_sort(ColumnsWithRowVal.begin(),ColumnsWithRowVal.end(), 
         [](const pair<int,int>& a, const pair<int,int>& b) {
          return a.second < b.second;
         });
    
    vector<vector<int>> temp(R,vector<int>(C));
    for(int i=0;i<R;++i) {
      for(int j=0;j<C;++j) {
        temp[i][j]= res[i][ColumnsWithRowVal[j].first];
      }
    }
    res = std::move(temp);
  }

  /**
   * @brief Sorts all rows by the values in the specified column (stable)
   * @param col The column whose values determine row ordering
   * 
   * Directly stable-sorts the row vectors using the target column value
   * as the comparison key.
   * 
   * Time Complexity: O(R log R * C) - each row comparison is O(1) for the
   *   key but O(C) for the swap
   */
  void sort_rows_by_column(int col) {
    stable_sort(res.begin(), res.end(), [col](const vector<int>& a, const vector<int>& b) {
      return a[col] < b[col];
    });
  }

};

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
Spreadsheet spreadsheet = Spreadsheet(3,3);
spreadsheet.set(0, 0, 5);
spreadsheet.set(0, 1, 3);
spreadsheet.set(0, 2, 8);
spreadsheet.set(1, 0, 6);
spreadsheet.set(2, 1, 1);
spreadsheet.sort_columns_by_row(0);
spreadsheet.sort_rows_by_column(1);
cout<<spreadsheet.get(1, 1)<<"\n";
return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Spreadsheet
 * 
 * Design a class called Spreadsheet with the following API. Spreadsheets
 * have between 1 and 100 rows and columns. The values at each cell are integers.
 * 
 * Spreadsheet API:
 * - new(rows, cols): initializes a spreadsheet with the specified size and 0
 *   in every cell.
 * - set(row, col, value): sets the cell at (row, col) to value.
 * - get(row, col): gets the value at (row, col).
 * - sort_columns_by_row(row): sorts all columns based on values in the given
 *   row. Sorting should be stable.
 * - sort_rows_by_column(col): sorts all rows based on values in the given
 *   column. Sorting should be stable.
 * 
 * Rows and columns start at 0. Assume no rows or columns will be out of bounds.
 * 
 * Constraints:
 * - 1 <= rows, cols <= 100
 * - All values set in cells are integers between -10^9 and 10^9
 * 
 *============================================================================*/
