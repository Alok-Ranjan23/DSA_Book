/**
 * @file custom_brackets.cc
 * @brief Check if string is balanced with custom bracket definitions
 * 
 * This file implements a balanced brackets checker that works with
 * user-defined bracket pairs, not just standard ()[]{}. 
 * 
 * Key Concepts:
 * - Map opening brackets to their closing counterparts
 * - Set of closing brackets for O(1) lookup
 * - Stack tracks unmatched opening brackets
 * - Non-bracket characters are ignored
 * 
 * Time Complexity: O(n + b) where n is string length, b is number of bracket types
 * Space Complexity: O(n + b) for stack and lookup structures
 */

#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/**
 * @brief Checks if string is balanced according to custom bracket definitions
 * @param s The input string to check
 * @param brackets Vector of 2-character strings, each defining a bracket pair
 *                 (first char = opening, second char = closing)
 * @return true if s is balanced, false otherwise
 * 
 * Algorithm:
 * 1. Build map: opening -> closing bracket
 * 2. Build set of closing brackets
 * 3. Scan string:
 *    - Opening bracket: push to stack
 *    - Closing bracket: must match stack top, else unbalanced
 *    - Other characters: ignore
 * 4. Balanced if stack is empty at end
 */
bool isbalanced(string& s, vector<string>& brackets) {
  // Build lookup structures
  unordered_map<char,char> umap;  // opening -> closing
  unordered_set<char> us;          // set of closing brackets
  
  for(auto&x : brackets) {
    umap[x[0]] = x[1];             // Map: opening bracket -> closing bracket
    us.insert(x[1]);               // Add closing bracket to set
  }
  
  stack<char> st;                  // Stack of unmatched opening brackets
  
  for(auto&c : s) {
    if(umap.count(c)) {
      st.push(c);                  // Opening bracket: push to stack
    }
    else if(us.count(c)) {         // Closing bracket
      if(st.size()>0 && umap[st.top()]==c) {
        st.pop();                  // Matches top: pop (matched pair)
      }
      else if(st.size() == 0) {
        return false;              // Closing with nothing to match: unbalanced
      }
      // Note: if closing doesn't match non-empty stack top,
      // the unmatched opening stays on stack, causing false at end
    }
    else {
      continue;                    // Non-bracket character: ignore
    }
  }
  
  return st.empty();               // Balanced only if all brackets matched
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  cout<<boolalpha;  // Print "true"/"false" instead of 1/0
  
  // Example 1: Standard balanced expression
  string s{"((a+b)*[c-d]-{e/f})"};
  vector<string> brackets {"()","[]","{}"};
  cout<<isbalanced(s,brackets)<<"\n";  // Expected: true
  
  // Example 2: Mismatched closing bracket
  s = "()[}";
  brackets = {"()","[]","{}"};
  cout<<isbalanced(s,brackets)<<"\n";  // Expected: false
  
  // Example 3: Improper nesting
  s = "([)]";
  brackets = {"()","[]","{}"};
  cout<<isbalanced(s,brackets)<<"\n";  // Expected: false
  
  // Example 4: HTML-style with emoticon interference
  s = "<div> hello :) </div>";
  brackets = {"<>","()"};
  cout<<isbalanced(s,brackets)<<"\n";  // Expected: false (d not matching >)
  
  // Example 5: Reversed brackets - ) is opening, ( is closing!
  s = ")))(()((";
  brackets = {")("};
  cout<<isbalanced(s,brackets)<<"\n";  // Expected: true
  
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Custom Brackets
 * 
 * Given a string, s, and an array of strings, brackets, where each element
 * consists of two characters, representing matching opening and closing
 * brackets, return whether s is balanced according to those brackets.
 * 
 * Rules:
 * - Characters not in brackets do not affect whether s is balanced.
 * - A pair of matching brackets of one type cannot surround only half of a
 *   matching pair of another type of brackets.
 * - Assume that brackets does not contain any repeated characters.
 * 
 * Example 1:
 *   s = "((a+b)*[c-d]-{e/f})", brackets = ["()", "[]", "{}"]
 *   Output: True
 * 
 * Example 2:
 *   s = "()[}", brackets = ["()", "[]", "{}"]
 *   Output: False
 * 
 * Example 3:
 *   s = "([)]", brackets = ["()", "[]", "{}"]
 *   Output: False
 * 
 * Example 4:
 *   s = "<div> hello :) </div>", brackets = ["<>", "()"]
 *   Output: False
 * 
 * Example 5:
 *   s = ")))(()((", brackets = [")("]
 *   Output: True
 * 
 *============================================================================*/
