/**
 * @file longest_balanced_subsequence.cc
 * @brief Find the longest balanced parentheses subsequence
 * 
 * This file implements a solution to find the longest balanced subsequence
 * by removing the minimum number of parentheses to make the string balanced.
 * 
 * Key Concepts:
 * - Track indices of unmatched brackets (not just count)
 * - Unmatched ')' when stack is empty
 * - Unmatched '(' remaining on stack after processing
 * - Build result by excluding invalid indices
 * 
 * Time Complexity: O(n) - single pass to find invalid, single pass to build result
 * Space Complexity: O(n) - for stack and invalid indices set
 */

#include <iostream>
#include <string>
#include <stack>
#include <unordered_set>

using namespace std;

/**
 * @brief Finds the longest balanced subsequence of parentheses
 * @param s Input string containing only '(' and ')'
 * @return A longest balanced subsequence (may not be unique)
 * 
 * Algorithm:
 * 1. First pass: identify indices of unmatched brackets
 *    - ')' with empty stack -> invalid (unmatched closing)
 *    - '(' remaining on stack -> invalid (unmatched opening)
 * 2. Second pass: build result excluding invalid indices
 */
string longest_balanced(string& s) {
  unordered_set<int> invalidIndices;  // Indices to remove
  stack<int> st;                       // Stack of '(' indices
  int n = s.size();

  // First pass: find all unmatched brackets
  for (int i = 0; i < n; ++i) {
    if (s[i] == '(') {
      st.push(i);                      // Push index of opening bracket
    } else if (st.empty()) {
      invalidIndices.insert(i);        // Unmatched ')' - no '(' to match
    } else {
      st.pop();                        // Matched pair - pop the '('
    }
  }

  // Remaining '(' on stack are unmatched
  while (!st.empty()) {
    invalidIndices.insert(st.top());
    st.pop();
  }

  // Second pass: build result excluding invalid indices
  string res;
  for (int i = 0; i < n; i++) {
    if (invalidIndices.find(i) == invalidIndices.end()) {
      res += s[i];                     // Include only valid characters
    }
  }
  return res;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Example 1: "))(())(()" -> "(())()" by removing indices 0,1,6
  string s {"))(())(()"};
  cout<<longest_balanced(s)<<"\n";  // Expected: (())()
  
  // Example 2: "(()()" -> "()()" by removing index 0 or 4
  s = "(()()";
  cout<<longest_balanced(s)<<"\n";  // Expected: ()() or (())
  
  // Example 3: "())(()" -> "()()" by removing indices 3,4 or 2,5
  s = "())(()";
  cout<<longest_balanced(s)<<"\n";  // Expected: ()()
  
  // Example 4: "(" -> "" (single unmatched bracket)
  s = "(";
  cout<<longest_balanced(s)<<"\n";  // Expected: (empty string)
  
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Longest Balanced Subsequence
 * 
 * Given a string of parentheses, s, return the longest balanced subsequence.
 * 
 * A subsequence of s (not a subarray) is a string obtained by removing some of
 * the letters in s. In other words, you have to delete the smallest number of
 * characters necessary to make s balanced and return the resulting string.
 * There may be more than one valid answer.
 * 
 * Example 1:
 *   s = "))(())(()"
 *   Output: "(())()"
 *   Explanation: We removed the following characters:
 *      "))(())(()"
 *       ^^    ^
 *   We could have also removed:
 *      "))(())(()"
 *       ^^     ^
 * 
 * Example 2:
 *   s = "(()()"
 *   Output: "()()"
 *   Explanation: We removed the following character:
 *      "(()()"
 *       ^
 *   We could have also removed:
 *      "(()()"
 *          ^
 *   So "(())" is also a valid output.
 * 
 * Example 3:
 *   s = "())(()"
 *   Output: "()()"
 *   Explanation: We removed the following characters:
 *      "())(()"
 *         ^^
 *   We could have also removed:
 *      "())(()"
 *        ^  ^
 * 
 * Example 4:
 *   s = "("
 *   Output: ""
 * 
 * Constraints:
 * - 0 <= s.length <= 10^5
 * - s consists only of '(' and ')'
 * 
 *============================================================================*/
