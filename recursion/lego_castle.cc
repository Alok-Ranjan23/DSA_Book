/**
 * @file lego_castle.cc
 * @brief Calculate the number of 1x1 blocks needed to build an n-story Lego castle
 * 
 * Castle construction rules:
 * - A 1-story castle is a single 1x1 block
 * - An n-story castle = two (n-1)-story castles side by side, 1 unit apart,
 *   with a row of blocks on top connecting them
 * 
 * Key Concepts:
 * - Mutual recursion: lego_castle() calls top_blocks() and itself
 * - top_blocks(n) computes width of n-story castle's top row
 * - Pattern: top_blocks(n) = 2^(n-1) + 2^(n-2) + ... + 2 + 1 = 2^n - 1
 * 
 * Time Complexity: O(n) for each function due to linear recursion
 * Space Complexity: O(n) recursion stack depth
 */

#include <iostream>
using namespace std;

/**
 * @brief Computes the number of blocks in the top row of an n-story castle
 * @param n Number of stories (n >= 2)
 * @return Number of blocks in the top connecting row
 * 
 * Recurrence:
 * - top_blocks(2) = 3 (two 1-block castles + 1 gap)
 * - top_blocks(n) = 2 * top_blocks(n-1) + 1
 * 
 * This follows from the castle structure: the top row spans
 * two (n-1)-story castles plus the gap between them.
 */
long long top_blocks(int n) {
  if(n==2) return n+1;
  return 2*top_blocks(n-1) + 1 ;
}

/**
 * @brief Computes total blocks needed for an n-story castle
 * @param n Number of stories (n >= 1)
 * @return Total number of 1x1 blocks required
 * 
 * Recurrence:
 * - lego_castle(1) = 1 (base case: single block)
 * - lego_castle(n) = 2 * lego_castle(n-1) + top_blocks(n)
 * 
 * Logic: Two (n-1)-story sub-castles plus the top row connecting them.
 */
long long lego_castle(int n) {
  if(n == 1) return 1;
  return 2*lego_castle(n-1) + top_blocks(n); 
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  cout<<lego_castle(1)<<"\n";
  cout<<lego_castle(2)<<"\n";
  cout<<lego_castle(3)<<"\n";
  cout<<lego_castle(4)<<"\n";
  cout<<lego_castle(5)<<"\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Lego Castle
 * 
 * You want to build an `n`-story 2D Lego castle following these instructions:
 * 
 * - A 1-story castle is just a `1x1` block.
 * - An `n`-story castle is made with two `(n-1)`-story castles, side by side, 
 *   one unit apart, with a row of blocks above them connecting them.
 * 
 * https://iio-beyond-ctci-images.s3.us-east-1.amazonaws.com/recursion-fig11.png
 * 
 * Given `n > 0`, how many `1x1` blocks will you need to buy to build an 
 * `n`-story castle?
 * 
 * Example 1: n = 1
 * Output: 1
 * 
 * Example 2: n = 2
 * Output: 5
 * 
 * Example 3: n = 3
 * Output: 17
 * 
 * Example 4: n = 4
 * Output: 49
 * 
 * Example 5: n = 5
 * Output: 129
 * 
 * Constraints:
 * - `1 ≤ n ≤ 57`
 * - Assume that the solution will fit in a signed `64`-bit integer.
 * 
 *============================================================================*/
