/**
 * @file tide_aerial_view.cc
 * @brief Binary Search for balanced state in time-series data
 * 
 * This file implements binary search to find the picture showing the most
 * balanced state (closest to 50% water coverage) from a series of aerial
 * photographs of a coastal region during rising tide.
 * 
 * Key Concepts:
 * - Binary search on monotonically changing property (water level)
 * - Finding closest value to a target (50% water)
 * - Nested binary search: search within each picture to count 1s
 * - Time-series data where state changes monotonically
 * 
 * Time Complexity: O(P * R * log(C)) where P=pictures, R=rows, C=columns
 *   - Binary search on pictures: O(log P)
 *   - But we compute water for boundary pictures: O(P * R * log C) worst case
 *   - Each row's 1s counted in O(log C) using binary search
 * Space Complexity: O(1)
 * 
 * Algorithm Pattern: Binary Search + Nested Binary Search
 * 
 * Visual representation of tide rising:
 *   Picture 0: [0,0,0]  Picture 1: [1,0,0]  Picture 2: [1,1,0]
 *              [0,0,0]             [0,0,0]             [0,0,0]
 *              [0,0,0]             [1,0,0]             [1,0,0]
 *   Water: 0%           Water: 22%          Water: 33% <- closest to 50%
 */

#include <iostream>
#include <vector>
using namespace std;

/*============================================================================
 * HELPER FUNCTIONS - Count Water (1s) in Pictures
 *============================================================================*/

/**
 * @brief Counts number of 1s (water cells) in a single row
 * @param row A row where all 1s are at the beginning (before all 0s)
 * @return Count of 1s in the row
 * 
 * Since 1s are always before 0s in each row (tide comes from left),
 * we binary search for the transition point from 1 to 0.
 * 
 * Example: [1, 1, 0, 0] -> returns 2
 */
int getOnesInRow(vector<int>& row) {
  // Quick checks for all-0 or all-1 rows
  if (row[0] == 0) {
    return 0;                               // Row starts with 0 -> no 1s
  }
  if (row[row.size() - 1] == 1) {
    return row.size();                      // Row ends with 1 -> all 1s
  }

  // Binary search for last position of 1
  auto isBefore = [&](int idx) { return row[idx] == 1; };

  int l = 0, r = row.size();
  while (r - l > 1) {
    int mid = (l + r) / 2;
    if (isBefore(mid)) {
      l = mid;                              // Still in 1s region
    } else {
      r = mid;                              // In 0s region
    }
  }
  
  return r;                                 // r = count of 1s
}

/**
 * @brief Counts total water cells (1s) in a picture
 * @param picture 2D grid representing aerial view
 * @return Total count of 1s in the picture
 */
int getOnesInPicture(vector<vector<int>>& picture) {
  int ones = 0;
  for (auto& row : picture) {
    ones += getOnesInRow(row);
  }
  return ones;
}

/**
 * @brief Checks if a picture is "before" the 50% mark
 * @param picture 2D grid to check
 * @return true if water coverage is less than 50%
 * 
 * "Before" means the tide hasn't reached halfway yet.
 */
bool isBefore(vector<std::vector<int>>& picture) {
  int water = getOnesInPicture(picture);
  int total = picture.size() * picture[0].size();
  return (double)water / total < 0.5;
}

/*============================================================================
 * MAIN SOLUTION - Find Most Balanced Picture
 *============================================================================*/

/**
 * @brief Finds the picture closest to 50% water coverage
 * @param pictures Array of aerial pictures (3D: pictures × rows × cols)
 * @return Index of the most balanced picture (earliest in case of tie)
 * 
 * Algorithm:
 * 1. Handle edge cases:
 *    - First picture already >= 50%: return 0
 *    - Last picture still < 50%: return last index
 * 
 * 2. Binary search for transition point:
 *    - Find where pictures change from < 50% to >= 50%
 *    - Answer is either at the transition or just before it
 * 
 * 3. Compare boundary pictures:
 *    - l = last picture with < 50% water
 *    - r = first picture with >= 50% water
 *    - Return the one closer to 50% (l wins ties)
 * 
 * Why binary search works:
 * - Tide only rises, never falls (monotonic)
 * - Once water >= 50%, it stays >= 50%
 * - We binary search for the transition point
 */
int tide_aerial_view(vector<vector<vector<int>>>& pictures) {
  // Edge case: first picture already has >= 50% water
  if (!isBefore(pictures[0])) {
    return 0;
  }
  
  // Edge case: last picture still has < 50% water
  if (isBefore(pictures[pictures.size() - 1])) {
    return pictures.size() - 1;
  }

  // Binary search for transition point
  int l = 0, r = pictures.size() - 1;
  while (r - l > 1) {
    int mid = (l + r) / 2;
    if (isBefore(pictures[mid])) {
      l = mid;                              // < 50%, look right
    } else {
      r = mid;                              // >= 50%, look left
    }
  }

  // Compare l (< 50%) and r (>= 50%) to find closest to 50%
  int lWater = getOnesInPicture(pictures[l]);
  int rWater = getOnesInPicture(pictures[r]);
  double midPoint = pictures[0].size() * pictures[0][0].size() / 2.0;
  
  // Return earlier index (l) in case of tie
  return abs(lWater - midPoint) <= abs(rWater - midPoint) ? l : r;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Example 1: Pictures 2 and 3 are equally balanced, return earlier (2)
  vector<vector<vector<int>>> pictures{
    {
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0}
    },
    {
      {1, 0, 0},
      {0, 0, 0},
      {1, 0, 0}
    },
    {
      {1, 1, 0},
      {0, 0, 0},
      {1, 0, 0}
    },
    {
      {1, 1, 0},
      {1, 1, 1},
      {1, 0, 0}
    },
    {
      {1, 1, 1},
      {1, 1, 1},
      {1, 1, 0}
    }
  };
  cout << tide_aerial_view(pictures) << "\n";  // Output: 2
  
  // Example 2: Only one picture, return 0
  pictures = {
    {
      {1, 1},
      {1, 1}
    }
  };
  cout << tide_aerial_view(pictures) << "\n";  // Output: 0
  
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT
 *============================================================================
 * 
 * # Tide Aerial View
 * 
 * You are provided a series of aerial-view pictures of the same coastal 
 * region, taken a few minutes apart from each other around the time the 
 * tide rises. Each picture consists of an n×n binary grid, where `0` 
 * represents a part of the region above water, and `1` represents a 
 * part below water.
 * 
 * - The tide appears from the left side and rises toward the right, so, 
 *   in each picture, for each row, all the 1's will be before all the 0's.
 * - Once a region is under water, it stays under water.
 * - All pictures are different.
 * 
 * Determine which picture shows the most even balance between regions 
 * above and below water (i.e., where the number of 1's most closely 
 * equals the number of 0's). In the event of a tie, return the earliest 
 * picture.
 * 
 * Example 1:
 * 
 * Picture 0: [0,0,0]  Picture 1: [1,0,0]  Picture 2: [1,1,0]
 *            [0,0,0]             [0,0,0]             [0,0,0]
 *            [0,0,0]             [1,0,0]             [1,0,0]
 * 
 * Picture 3: [1,1,0]  Picture 4: [1,1,1]
 *            [1,1,1]             [1,1,1]
 *            [1,0,0]             [1,1,0]
 * 
 * Output: 2. Pictures at index 2 and 3 are equally far from having 50% 
 * water. We break the tie by picking the earlier one, 2.
 * 
 * Example 2:
 * Picture 0: [1,1]
 *            [1,1]
 * Output: 0. It's the only picture.
 * 
 * Constraints:
 * - 1 <= pictures.length <= 500
 * - All pictures have dimension n × n, where 1 <= n <= 500
 * 
 *============================================================================*/
