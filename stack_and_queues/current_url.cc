/**
 * @file current_url.cc
 * @brief Simulate browser back navigation using a stack
 * 
 * This file implements browser back button functionality where users can
 * navigate to URLs and go back multiple steps in history.
 * 
 * Key Concepts:
 * - Stack perfectly models browser history (LIFO)
 * - "go" action pushes URL onto stack
 * - "back" action pops URLs (but keeps at least one)
 * 
 * Time Complexity: O(n) where n is total number of actions
 * Space Complexity: O(m) where m is number of "go" actions
 */

#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

/**
 * @brief Simulates browser navigation and returns current URL
 * @param actions Vector of (action_type, value) pairs
 *                - ("go", url): navigate to url
 *                - ("back", n): go back n pages
 * @return The current URL after all actions are performed
 * 
 * Algorithm:
 * 1. For "go": push URL onto history stack
 * 2. For "back": pop up to n URLs, but always keep at least one
 * 3. Return the top of stack (current page)
 */
string current_url(vector<pair<string,string>> actions) {
  stack<string> st;       // Browser history stack
  
  for(auto& p : actions) {
    if(p.first == "go") {
      st.push(p.second);  // Navigate to new URL
    } else {
      // "back" action: go back 'val' pages
      int val = stoi(p.second);
      // Can't go back past the first page, so limit count to size-1
      int count = (static_cast<size_t>(val)<st.size()) ? val : st.size()-1;
      while(count--) st.pop();
    }
  }
  return st.top();        // Current page is at top of stack
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Test case: navigate through multiple URLs with back actions
  // go google -> go wikipedia -> go amazon -> back 4 -> go youtube -> go netflix -> back 1
  // After back 4 from amazon: stays at google (can only go back 2, stays at first)
  // After go youtube, go netflix: google -> youtube -> netflix
  // After back 1: google -> youtube
  vector<pair<string,string>> actions {
    {"go","google.com"},
    {"go","wikipedia.com"},
    {"go","amazon.com"},
    {"back","4"},           // Try to go back 4, but only 2 pages behind, stay at google
    {"go","youtube.com"},
    {"go","netflix.com"},
    {"back","1"}};          // Go back 1 to youtube
  
  cout<<current_url(actions)<<"\n";  // Expected: youtube.com
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Browser Back Navigation
 * 
 * You are implementing the back arrow functionality of a browser. You are given
 * a non-empty array, actions, with the actions that the user has done so far.
 * Each element in actions consists of two elements. The first is the action
 * type, "go" or "back".
 * 
 * Action Types:
 * - go: The second element is a URL string. The first action is always "go".
 * - back: The second element is a number ≥ 1 with the number of times we want
 *         to go back. Going back once means returning to the previous URL we
 *         went to with a "go" action. If there are no previous URLs, going
 *         back stays at the current one.
 * 
 * Return the current URL the user is on after all actions are performed.
 * 
 * Example:
 *   actions = [["go", "google.com"],
 *              ["go", "wikipedia.com"],
 *              ["go", "amazon.com"],
 *              ["back", 4],
 *              ["go", "youtube.com"],
 *              ["go", "netflix.com"],
 *              ["back", 1]]
 * 
 *   Output: "youtube.com"
 * 
 *============================================================================*/
