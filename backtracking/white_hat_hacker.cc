/**
 * @file white_hat_hacker.cc
 * @brief Find a password using backtracking to try all valid combinations
 * 
 * This file implements a brute-force password cracker using backtracking.
 * The password constraints (lowercase letters, no repeats, max 10 chars)
 * reduce the search space significantly from 26^10 to P(26,10) permutations.
 * 
 * Key Concepts:
 * - Permutation generation with early termination on success
 * - Boolean array to track used characters (no repeats)
 * - Depth-first search through password space
 * 
 * Time Complexity: O(P(26, k)) in worst case where k = password length
 *   - P(26, k) = 26!/(26-k)! = 26 * 25 * 24 * ... * (26-k+1)
 *   - For k=10: ~19 trillion combinations in worst case
 *   - Early termination when password found
 * 
 * Space Complexity: O(k) where k = max password length (10)
 *   - Recursion stack depth: at most 10
 *   - Boolean array: 26 elements
 *   - Current password string: at most 10 chars
 * 
 * Note: This is for educational purposes. In practice, passwords would
 * have additional complexity (uppercase, numbers, symbols) and would
 * be protected by rate limiting and hashing.
 * 
 * IMPORTANT: The algorithm searches lexicographically (a, ab, abc, ..., b, ba, ...).
 * Passwords starting with late letters (like "xyz") take EXTREMELY long because
 * we must exhaust all permutations starting with earlier letters first!
 */

#include <iostream>
#include <string>
using namespace std;

/** Lambda function to check if password attempt matches the target */
auto check_password = [](const string& ref, const string& curr) { 
  return ref == curr; 
};

/**
 * @brief Recursive backtracking function to find the password
 * 
 * @param ref   The target password (for simulation/testing)
 * @param curr  Current password attempt being built
 * @param used  Boolean array tracking which letters have been used
 * @return true if password found, false otherwise
 * 
 * Algorithm:
 * 1. If current string is non-empty, check if it's the password
 * 2. If password found, return true (early termination)
 * 3. If max length (10) reached, return false
 * 4. Try adding each unused letter (a-z):
 *    a. Mark letter as used
 *    b. Add letter to current string
 *    c. Recurse - if found, propagate success
 *    d. Backtrack: remove letter, mark as unused
 */
bool hack(const string& ref, string& curr, bool used[26]) {
  // Check if current string is the password (must have at least 1 char)
  if (!curr.empty() && check_password(ref, curr)) {
    return true;  // PASSWORD FOUND!
  }
  
  // Max password length is 10 characters
  if (curr.length() == 10) {
    return false;
  }
  
  // Try adding each unused letter
  for (int i = 0; i < 26; i++) {
    if (!used[i]) {
      used[i] = true;                     // CHOOSE: mark letter as used
      curr.push_back('a' + i);            // Add letter to password
      
      if (hack(ref, curr, used)) {
        return true;                      // FOUND: propagate success up
      }
      
      // UNCHOOSE: Backtrack
      curr.pop_back();                    // Remove letter
      used[i] = false;                    // Mark as available again
    }
  }
  
  return false;  // Password not found in this branch
}

/**
 * @brief Wrapper function to find the password
 * 
 * @param ref The target password (for simulation)
 * @return The discovered password, or empty string if not found
 */
string find_password(const string& ref) {
  bool used[26] = {false};  // Track which letters have been used
  string curr = "";         // Current password attempt
  
  if (hack(ref, curr, used)) {
    return curr;
  }
  
  return "";  // Password not found (shouldn't happen with valid input)
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // IMPORTANT: The DFS search order is: a, ab, abc, abcd, ...
  // Any password NOT starting with 'a' requires exhausting ALL permutations
  // starting with 'a' first (billions of combinations!).
  // 
  // Therefore, we only test passwords starting with 'a' for quick results.
  
  // Example 1: Password "a" - found on 1st check (instant)
  string test1 = "a";
  cout << "Searching for password: \"a\"" << endl;
  cout << "Password found: " << find_password(test1) << endl << endl;
  
  // Example 2: Password "ab" - found on 2nd check (instant)
  string test2 = "ab";
  cout << "Searching for password: \"ab\"" << endl;
  cout << "Password found: " << find_password(test2) << endl << endl;
  
  // Example 3: Password "abc" - found on 3rd check (instant)
  string test3 = "abc";
  cout << "Searching for password: \"abc\"" << endl;
  cout << "Password found: " << find_password(test3) << endl << endl;
  
  // Example 4: Password "abdc" - found quickly (still early in search)
  string test4 = "abdc";
  cout << "Searching for password: \"abdc\"" << endl;
  cout << "Password found: " << find_password(test4) << endl;
  
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # White Hat Hacker
 * 
 * You are trying to hack into an account (for good reasons, I'm sure).
 * You know that the password:
 * 
 * - has at least 1 and at most 10 letters,
 * - uses only lowercase English letters,
 * - does not repeat any letter.
 * 
 * You have a script that tries to log in with a given password and returns
 * a boolean indicating if it was successful. Write a function to find the
 * password. You can call `check_password(s)` to check if `s` is the password.
 * 
 * Example:
 * check_password("a")   // returns False
 * check_password("abc") // returns False
 * check_password("ac")  // returns False
 * check_password("ab")  // returns False
 * check_password("bc")  // returns True
 * Output: "bc"
 * 
 * Constraints:
 * - There is no explicit limit to how many times you can call check_password()
 * 
 *============================================================================*/
