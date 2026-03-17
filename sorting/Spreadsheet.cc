#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Spreadsheet {
  vector<vector<int>> res;
  public:
  Spreadsheet(int row_size, int col_size) {
    res.resize(row_size);
    for(int i=0;i<row_size;++i) 
    res[i].resize(col_size,0);
  }

  void set(int i, int j, int val) {
    res[i][j] = val;
  }

  int get(int i, int j) {
    return res[i][j];
  }

  void sort_columns_by_row(int row) {
    //step1: fix {col, and , row value in all col}
    int R = res.size();
    int C = res[0].size();
    vector<pair<int,int>> ColumnsWithRowVal;
    for(int c=0;c<C;++c) ColumnsWithRowVal.push_back({c,res[row][c]});
    
    //step2: sort this vector ColumnsWithRowVal to get the row sorted
    stable_sort(ColumnsWithRowVal.begin(),ColumnsWithRowVal.end(), 
         [](const pair<int,int>& a, const pair<int,int>& b) {
          return a.second < b.second;
         });
    
    //step3: make a copy to 
    vector<vector<int>> temp(R,vector<int>(C));
    for(int i=0;i<R;++i) {
      for(int j=0;j<C;++j) {
        temp[i][j]= res[i][ColumnsWithRowVal[j].first];
      }
    }
    res = std::move(temp);
  }

  void sort_rows_by_column(int col) {
    stable_sort(res.begin(), res.end(), [col](const vector<int>& a, const vector<int>& b) {
      return a[col] < b[col];
    });
  }

};


// To execute C++, please define "int main()"
int main() {
Spreadsheet spreadsheet = Spreadsheet(3,3);
//spreadsheet.new(3, 3);
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

// Your previous Plain Text content is preserved below:

// Hello! Your interview question is below. Write code in this pad just like you would normally – your AI Interviewer will be able to see it.

// # Spreadsheet

// Design a class called Spreadsheet with the following API. Spreadsheets have between `1` and `100` rows and columns. The values at each cell are integers.

// Spreadsheet API:

// - `new(rows, cols)`: initializes a spreadsheet with the specified size and 0 in every cell.
// - `set(row, col, value)`: sets the cell at (row, col) to value.
// - `get(row, col)`: gets the value at (row, col).
// - `sort_columns_by_row(row)`: sorts all the columns based on the values in the given row. Sorting should be stable.
// - `sort_rows_by_column(col)`: sorts all the rows based on the values in the given column. Sorting should be stable.

// Rows and columns start at `0`. Assume that no rows or columns will be out of bounds.

// Example 1:
// spreadsheet = Spreadsheet()
// spreadsheet.new(3, 3)
// spreadsheet.set(0, 0, 5)
// spreadsheet.set(0, 1, 3)
// spreadsheet.set(0, 2, 8)
// spreadsheet.set(1, 0, 6)
// spreadsheet.set(2, 1, 1)
// spreadsheet.sort_columns_by_row(0)
// spreadsheet.sort_rows_by_column(1)
// spreadsheet.get(1, 1)  # Returns 5

// Example 2:
// spreadsheet = Spreadsheet()
// spreadsheet.new(1, 1)
// spreadsheet.set(0, 0, 42)
// spreadsheet.get(0, 0)  # Returns 42

// Example 3:
// spreadsheet = Spreadsheet()
// spreadsheet.new(3, 2)
// spreadsheet.sort_rows_by_column(0)
// spreadsheet.get(0, 0)  # Returns 0

// Here is a visualization of Example 1:

// https://iio-beyond-ctci-images.s3.us-east-1.amazonaws.com/sorting-fig6.png

// Constraints:

// - `1 ≤ rows, cols ≤ 100`
// - All values set in cells are integers between `-10^9` and `10^9`
