/**
 * @file largest_rectangle.cc
 * @brief Largest all-blue rectangle in a histogram-like mosaic
 *
 * Column i has tiles[i] blue tiles stacked from the bottom, so the mosaic is a
 * histogram. Any maximal rectangle has a height equal to some column's height
 * tiles[i], and extends left and right until it hits a strictly shorter
 * column. So for each i the best rectangle using height tiles[i] spans the
 * open interval (PSE[i], NSE[i]) and has area tiles[i] * (NSE[i] - PSE[i] - 1).
 *
 * Key Concepts:
 * - Next Smaller Element (NSE) and Previous Smaller Element (PSE), each
 *   computed with one monotonic-stack pass
 * - Sentinels n (no smaller to the right) and -1 (no smaller to the left)
 *   make the width formula work at the borders without special cases
 * - Area can reach n * n = 10^12 for n = 10^6, so it is computed in
 *   long long to avoid int overflow
 *
 * Time Complexity: O(n)
 *   - Each stack pass pushes every index once and pops it at most once:
 *     O(n) per pass. The final max-area loop is O(n).
 *
 * Space Complexity: O(n)
 *   - Two index arrays (nse, pse) plus a stack of up to n indices.
 */
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

/**
 * @brief For each index, the nearest index to the right with a strictly
 *        smaller value
 *
 * @param tiles Column heights
 * @return      res[i] = smallest j > i with tiles[j] < tiles[i], or n if none
 *
 * Scan right-to-left, popping indices with height >= tiles[i]; the remaining
 * top (if any) is the next strictly smaller column.
 *
 * Time:  O(n) -- each index pushed once, popped at most once
 * Space: O(n) -- stack + result
 */
//Time O(n)   (each index pushed/popped at most once)
//Space O(n)  (stack + result)
vector<int> next_smaller_elements(vector<int>& tiles) {
  int n = tiles.size();
  vector<int> res(n,n);                            // n = right border sentinel
  stack<int> st;
  for(int i=n-1;i>=0;--i) {
    while(!st.empty() && tiles[st.top()]>=tiles[i]) st.pop();
    if(!st.empty()) res[i] = st.top();
    st.push(i);
  }
  return res;
}

/**
 * @brief For each index, the nearest index to the left with a strictly
 *        smaller value
 *
 * @param tiles Column heights
 * @return      res[i] = largest j < i with tiles[j] < tiles[i], or -1 if none
 *
 * Scan left-to-right, popping indices with height >= tiles[i].
 *
 * Time:  O(n) -- each index pushed once, popped at most once
 * Space: O(n) -- stack + result
 */
//Time O(n)   (each index pushed/popped at most once)
//Space O(n)  (stack + result)
vector<int> previous_smaller_elements(vector<int>& tiles) {
  int n = tiles.size();
  vector<int> res(n,-1);                           // -1 = left border sentinel
  stack<int> st;
  for(int i=0;i<n;++i) {
    while(!st.empty() && tiles[st.top()]>=tiles[i]) st.pop();
    if(!st.empty()) res[i] = st.top();
    st.push(i);
  }
  return res;
}

/**
 * @brief Return the area of the largest rectangle made only of blue tiles
 *
 * @param tiles tiles[i] = number of blue tiles in column i (0 <= tiles[i] <= n)
 * @return      Maximum area (long long, may reach 10^12)
 *
 * Algorithm:
 * 1. Compute NSE and PSE for every column.
 * 2. Column i can be the limiting height of a rectangle spanning
 *    (PSE[i], NSE[i]), i.e. width NSE[i] - PSE[i] - 1.
 * 3. Return the maximum of tiles[i] * width over all i.
 *
 * Time:  O(n) -- two O(n) stack passes plus one O(n) loop
 * Space: O(n) -- nse and pse arrays
 */
//Time O(n)
//Space O(n)
long long largest_rectangle(vector<int>& tiles) {
  int n = tiles.size();
  vector<int> nse = next_smaller_elements(tiles);
  vector<int> pse = previous_smaller_elements(tiles);
  long long largest_rect = 0;
  for(int i=0;i<n;++i) {
    // height tiles[i] x width between the two strictly smaller neighbours
    largest_rect = max(largest_rect, static_cast<long long>(tiles[i])*(nse[i]-pse[i]-1));
  }
  return largest_rect;
}

// To execute C++, please define "int main()"
int main() {
  vector<int> tiles {1, 2, 3};
  cout<<largest_rectangle(tiles)<<"\n";
  tiles  = {2, 1, 2};
  cout<<largest_rectangle(tiles)<<"\n";
  tiles  = {1, 2, 5, 2, 1};
  cout<<largest_rectangle(tiles)<<"\n";
  return 0;
}

// # Largest Rectangle

// You have an `n x n` mosaic made of blue and red tiles, where `n > 0`. You are given an array of integers, `tiles`, of length `n`, where `tiles[i]` indicates the number of blue tiles in column `i` of the mosaic (columns are 0-indexed). For each column, all the blue tiles are contiguously at the bottom and the red tiles are contiguously at the top.

// Return the size of the largest rectangle that can be formed using only blue tiles. The rectangle cannot contain partial tiles.

// Example 1: tiles = [1, 2, 3]
// Output: 4. The mosaic is 3x3, and it looks like:
// R R B
// R B B
// B B B
// The largest blue rectangle is 2x2 at the bottom left corner.

// Example 2: tiles = [2, 1, 2]
// Output: 3.
// R R R
// B R B
// B B B

// Example 3: tiles = [1, 2, 5, 2, 1]
// Output: 6.
// R R B R R
// R R B R R
// R R B R R
// R B B B R
// B B B B B

// Constraints:

// - `1 <= n <= 10^6`
// - `0 <= tiles[i] <= n`
