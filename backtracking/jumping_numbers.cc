/**
 * @file jumping_numbers.cc
 * @brief Find all jumping numbers less than n using backtracking
 * 
 * A jumping number is a positive integer where every two consecutive digits
 * differ by exactly 1. For example, 2343 is jumping because |2-3|=1, |3-4|=1,
 * |4-3|=1. Single digit numbers (1-9) are all jumping numbers.
 * 
 * Key Concepts:
 * - BFS/DFS from each starting digit (1-9)
 * - Digit-by-digit construction with jumping constraint
 * - Only extend with digits that differ by 1 from last digit
 * 
 * Time Complexity: O(k * log(n)) where k = count of jumping numbers < n
 *   - Each jumping number is generated in O(digits) = O(log n) time
 *   - Total jumping numbers grows slowly (much less than n)
 * 
 * Space Complexity: O(k) for storing all jumping numbers
 *   - Recursion stack: O(log n) depth (max digits)
 * 
 * Approach:
 * Start with seeds 1-9. For each number, try extending by appending:
 *   - (last_digit - 1) if last_digit > 0
 *   - (last_digit + 1) if last_digit < 9
 * Continue until number exceeds n.
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/** Global vector to store all jumping numbers found */
vector<int> ans {};

/**
 * @brief Recursive function to generate jumping numbers
 * 
 * @param curr       Current jumping number being built
 * @param last_digit The last digit of curr (to check jumping condition)
 * @param n          Upper limit (exclusive)
 * 
 * Algorithm:
 * 1. If curr >= n, stop (out of range)
 * 2. Add curr to answer (it's a valid jumping number)
 * 3. Try extending with (last_digit - 1) if >= 0
 * 4. Try extending with (last_digit + 1) if <= 9
 * 
 * Example trace for n=25, starting from 1:
 * - 1 (add), extend to 10, 12
 *   - 10 (add), can extend to 101, but > 25, done
 *   - 12 (add), extend to 121, 123, but > 25, done
 */
void solve(int curr, int last_digit, int n) {
  // Base case: current number exceeds limit
  if (curr >= n) {
    return;
  }
  
  // Current number is a valid jumping number
  ans.push_back(curr);
  
  // Try appending (last_digit - 1) if valid digit
  if (last_digit > 0) {
    int next = curr * 10 + (last_digit - 1);  // Append digit
    solve(next, last_digit - 1, n);           // Recurse with new last digit
  }
  
  // Try appending (last_digit + 1) if valid digit
  if (last_digit < 9) {
    int next = curr * 10 + (last_digit + 1);  // Append digit
    solve(next, last_digit + 1, n);           // Recurse with new last digit
  }
}

/**
 * @brief Wrapper function to find all jumping numbers less than n
 * 
 * @param n Upper limit (exclusive)
 * @return Sorted vector of all jumping numbers < n
 * 
 * Starts DFS from each single digit 1-9 (all are jumping numbers).
 * Note: 0 is excluded as we want positive integers only.
 */
vector<int> jumping_numbers(int n) {
  ans.clear();
  
  // Start from each single digit (1-9 are all jumping numbers)
  for (int digit = 1; digit <= 9; digit++) {
    solve(digit, digit, n);
  }
  
  // Sort results (DFS doesn't produce sorted order)
  // DFS order: 1, 10, 12, 121, 123, 2, 21, 210, 212, 23, ...
  sort(ans.begin(), ans.end());
  
  return ans;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Example 1: n = 34
  // Expected: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 21, 23, 32]
  int n = 34;
  jumping_numbers(n);
  cout << "n = " << n << "\nOutput: [";
  for (size_t i = 0; i < ans.size(); i++) {
    cout << ans[i];
    if (i < ans.size() - 1) cout << ", ";
  }
  cout << "]\n\n";
  
  // Example 2: n = 1
  // Expected: [] (no positive integers less than 1)
  n = 1;
  jumping_numbers(n);
  cout << "n = " << n << "\nOutput: [";
  for (size_t i = 0; i < ans.size(); i++) {
    cout << ans[i];
    if (i < ans.size() - 1) cout << ", ";
  }
  cout << "]\n\n";
  
  // Example 3: n = 100
  // Shows two-digit jumping numbers
  n = 100;
  jumping_numbers(n);
  cout << "n = " << n << "\nOutput: [";
  for (size_t i = 0; i < ans.size(); i++) {
    cout << ans[i];
    if (i < ans.size() - 1) cout << ", ";
  }
  cout << "]\n";
  
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Jumping Numbers
 * 
 * A _jumping number_ is a positive integer where every two consecutive
 * digits differ by one, such as 2343. Given a positive integer, n, return
 * all jumping numbers smaller than n, ordered from smallest to largest.
 * 
 * Example 1: n = 34
 * Output: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 21, 23, 32]
 * 
 * Example 2: n = 1
 * Output: []
 * 
 * Constraints:
 * - n is a positive integer less than 10^5.
 * 
 *============================================================================*/
