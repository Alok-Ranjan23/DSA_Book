/**
 * @file current_url_with_forward.cc
 * @brief Simulate browser back/forward navigation using two stacks
 * 
 * This file implements browser back and forward button functionality where
 * users can navigate to URLs, go back, and go forward in history.
 * 
 * Key Concepts:
 * - Two stacks: history (back) and forward
 * - "go" clears forward stack (like real browsers)
 * - "back" moves pages from history to forward stack
 * - "forward" moves pages from forward to history stack
 * 
 * Time Complexity: O(n) where n is total number of actions
 * Space Complexity: O(m) where m is number of URLs visited
 */

#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

/**
 * @brief Simulates browser navigation with back/forward and returns current URL
 * @param actions Vector of (action_type, value) pairs
 *                - ("go", url): navigate to url (clears forward history)
 *                - ("back", n): go back n pages
 *                - ("forward", n): go forward n pages
 * @return The current URL after all actions are performed
 * 
 * Algorithm:
 * 1. "go": push URL to history, clear forward stack
 * 2. "back": move pages from history to forward stack
 * 3. "forward": move pages from forward to history stack
 * 4. Return top of history stack
 */
string current_url_forward(vector<pair<string,string>> actions) {
  stack<string> st;    // History stack (back navigation)
  stack<string> st2;   // Forward stack
  
  for(auto& p : actions) {
    if(p.first == "go") {
      st.push(p.second);         // Navigate to new URL
      st2 = stack<string>();     // Clear forward history (like real browsers)
    } 
    else if(p.first == "back") {
      int val = stoi(p.second);
      // Can go back at most (size-1) times to keep at least one URL
      int count = (static_cast<size_t>(val)<st.size()) ? val : st.size()-1;
      while(count--) { 
        st2.push(st.top());      // Move current page to forward stack
        st.pop();
      }
    } 
    else {  // "forward" action
      int val = stoi(p.second);
      // Can only go forward as many pages as available
      int count = (static_cast<size_t>(val)<st2.size()) ? val : st2.size();
      while(count--) { 
        st.push(st2.top());      // Move page from forward to history
        st2.pop();
      }
    }
  }
  return st.top();               // Current page is top of history stack
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Test case demonstrating back and forward navigation
  // go google -> go wikipedia -> back 1 -> forward 1 -> back 3 -> go netflix -> forward 3
  vector<pair<string,string>> actions {
    {"go","google.com"},         // history: [google]
    {"go","wikipedia.com"},      // history: [google, wikipedia]
    {"back","1"},                // history: [google], forward: [wikipedia]
    {"forward","1"},             // history: [google, wikipedia], forward: []
    {"back","3"},                // history: [google], forward: [wikipedia]
    {"go","netflix.com"},        // history: [google, netflix], forward: [] (cleared!)
    {"forward","3"}};            // Nothing to forward, stays at netflix
  
  cout<<current_url_forward(actions)<<"\n";  // Expected: netflix.com
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Browser Back/Forward Navigation
 * 
 * You are implementing the back arrow functionality of a browser with an
 * additional "forward" action. You are given a non-empty array, actions, with
 * the actions that the user has done so far. Each element in actions consists
 * of two elements. The first is the action type, "go", "back", or "forward".
 * 
 * Action Types:
 * - go: The second element is a URL string. The first action is always "go".
 * - back: The second element is a number ≥ 1 with the number of times we want
 *         to go back. Going back once means returning to the previous URL we
 *         went to with a "go" action. If there are no previous URLs, going
 *         back stays at the current one.
 * - forward: The second element is a number ≥ 1 with the number of times we
 *            want to go forward. Going forward past the last page that we
 *            have gone to does nothing.
 * 
 * Return the current URL the user is on after all actions are performed.
 * 
 * Example:
 *   actions = [["go", "google.com"],
 *              ["go", "wikipedia.com"],
 *              ["back", 1],
 *              ["forward", 1],
 *              ["back", 3],
 *              ["go", "netflix.com"],
 *              ["forward", 3]]
 * 
 *   Output: "netflix.com"
 * 
 *============================================================================*/
