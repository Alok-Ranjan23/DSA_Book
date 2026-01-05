/**
 * @file race_overtake.cc
 * @brief Binary Search to find the overtaking point in a race
 * 
 * This file implements binary search to find the exact moment when
 * Player 2 overtakes Player 1 in a racing game, given position arrays.
 * 
 * Key Concepts:
 * - Binary search on a monotonic property (p1[i] > p2[i] -> p1[i] < p2[i])
 * - Finding first index where condition changes
 * - Exploiting the guarantee that overtake happens exactly once
 * 
 * Time Complexity: O(log n) - binary search on array
 * Space Complexity: O(1) - constant extra space
 * 
 * Algorithm Pattern: Binary Search for First True
 * 
 * Visual representation:
 *   Index:  0   1   2   3   4
 *   P1:     2   4   6   8   10    (ahead initially)
 *   P2:     1   3   5   9   11    (behind, then overtakes)
 *   p1>p2:  T   T   T   F   F     <- Find first F
 */

#include <iostream>
#include <vector>
using namespace std;

/*============================================================================
 * RACE OVERTAKING DETECTION
 *============================================================================*/

/**
 * @brief Finds the index where Player 2 first overtakes Player 1
 * @param p1 Position array for Player 1 (starts ahead)
 * @param p2 Position array for Player 2 (ends ahead)
 * @return Index where p2[i] > p1[i] for the first time
 * 
 * Algorithm:
 * We're looking for the first index where p1[i] < p2[i].
 * 
 * Given guarantees:
 * - p1[0] > p2[0] (Player 1 starts ahead)
 * - p1[n-1] < p2[n-1] (Player 2 ends ahead)
 * - Exactly one overtake happens
 * 
 * This means the array of comparisons looks like:
 *   [p1>p2, p1>p2, ..., p1>p2, p1<p2, p1<p2, ...]
 *   [True,  True,  ..., True,  False, False, ...]
 * 
 * We binary search for the first False (first p1[m] < p2[m]).
 * 
 * Note: The condition p1[m] < p2[m] is True for the overtake point and after.
 */
int race_overtaking(vector<int>& p1, vector<int>& p2) {
  int n = p1.size();
  int l = 0;
  int r = n - 1;
  int ans = -1;
  
  while(l <= r) {
    int m = (l + r) >> 1;
    
    if(p1[m] < p2[m]) {       // Player 2 is ahead at position m
      ans = m;                // This could be the answer
      r = m - 1;              // But check if there's an earlier overtake
    } else {
      l = m + 1;              // Player 1 still ahead, look later
    }
  }
  
  return ans;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Example 1: Overtake at index 3
  vector<int> p1{2, 4, 6, 8, 10};
  vector<int> p2{1, 3, 5, 9, 11};
  int index = race_overtaking(p1, p2);
  cout << index << "\n";  // Output: 3
  
  // Example 2: Overtake at index 3
  p1 = {2, 3, 4, 5, 6};
  p2 = {1, 2, 3, 6, 7};
  index = race_overtaking(p1, p2);
  cout << index << "\n";  // Output: 3
  
  // Example 3: Overtake at index 1
  p1 = {3, 4, 5};
  p2 = {2, 5, 6};
  index = race_overtaking(p1, p2);
  cout << index << "\n";  // Output: 1
  
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT
 *============================================================================
 * 
 * # Race Overtaking
 * 
 * You are given two arrays of positive integers, `p1` and `p2`, 
 * representing players in a racing game. The two arrays are sorted, 
 * non-empty, and have the same length, `n`. The `i`-th element of each 
 * array corresponds to where that player was on the track at the `i`-th 
 * second of the race. We know that:
 * 
 * 1. Player 1 started ahead (p1[0] > p2[0])
 * 2. Player 2 overtook player 1 _once_.
 * 3. Player 2 remained ahead until the end (p1[n - 1] < p2[n - 1]).
 * 
 * Assume the arrays have no duplicates, and that p1[i] != p2[i] for 
 * any index.
 * 
 * Return the index at which player 2 overtook player 1.
 * 
 * Example 1: p1 = [2, 4, 6, 8, 10], p2 = [1, 3, 5, 9, 11]
 * Output: 3. At index 3, p2 (9) becomes greater than p1 (8).
 * 
 * Example 2: p1 = [2, 3, 4, 5, 6], p2 = [1, 2, 3, 6, 7]
 * Output: 3. At index 3, p2 (6) becomes greater than p1 (5).
 * 
 * Example 3: p1 = [3, 4, 5], p2 = [2, 5, 6]
 * Output: 1. At index 1, p2 (5) becomes greater than p1 (4).
 * 
 * Constraints:
 * - 2 <= p1.length = p2.length <= 10^6
 * - 0 <= p1[i], p2[i] <= 10^9
 * - p1 and p2 are strictly increasing
 * - There is exactly one point where p2 overtakes p1
 * 
 *============================================================================*/
