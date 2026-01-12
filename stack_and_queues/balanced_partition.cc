/**
 * @file balanced_partition.cc
 * @brief Find maximum number of balanced substrings in a balanced parentheses string
 * 
 * This file implements a solution to partition a balanced parentheses string
 * into the maximum number of balanced substrings.
 * 
 * Key Concepts:
 * - Height tracking: increment on '(', decrement on ')'
 * - A balanced substring ends when height returns to 0
 * - Greedy approach: count partitions as soon as they become balanced
 * 
 * Time Complexity: O(n) - single pass through the string
 * Space Complexity: O(1) - only using two integer variables
 */

#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Counts the maximum number of balanced partitions in a string
 * @param s A balanced parentheses string (guaranteed to be balanced)
 * @return Maximum number of balanced substrings the string can be partitioned into
 * 
 * Algorithm:
 * - Track "height" (depth of nesting) as we scan
 * - Each time height returns to 0, we've found a complete balanced substring
 * - Count these occurrences
 */
int balanced_partition(string& s) {
  int height = 0;           // Current nesting depth
  int count_balanced = 0;   // Number of balanced partitions found
  
  for(auto &c : s) {
    if(c=='(') {
      height++;             // Opening bracket increases depth
    } else {
      height--;             // Closing bracket decreases depth
      if(height==0) {
        count_balanced+=1;  // Height 0 means we completed a balanced substring
      }
    }
  }
  return count_balanced;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Test: "((()))(()())()(()(()))" should partition into 4 substrings:
  // "((()))", "(()())", "()", "(()(()))"
  string s {"((()))(()())()(()(()))"};
  cout<<balanced_partition(s)<<"\n";  // Expected: 4
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Balanced Partition
 * 
 * Given a balanced parentheses string, s, a balanced partition is a partition
 * of s into substrings, each of which is itself balanced. Return the maximum
 * possible number of substrings in a balanced partition.
 * 
 * Example:
 *   s = "((()))(()())()(()(())) "
 *   Output: 4
 *   Explanation: The balanced partition with the most substrings is:
 *                "((()))", "(()())", "()", "(()(()))"
 * 
 * Constraints:
 * - The length of s is at most 10^5
 * - s consists only of '(' and ')'
 * 
 *============================================================================*/
