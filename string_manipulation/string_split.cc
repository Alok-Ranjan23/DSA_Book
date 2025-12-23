/**
 * @file string_split.cc
 * @brief Split String by Delimiter Character (without built-in split)
 * 
 * This file implements a custom string split function that breaks a string
 * into tokens based on a single character delimiter.
 * 
 * Key Concepts:
 * - Tokenization: Breaking string into parts at delimiter positions
 * - Empty Tokens: Consecutive delimiters produce empty strings
 * - Edge Cases: Empty input, delimiter at start/end, no delimiter found
 * 
 * Algorithm:
 * 1. Iterate through each character in the string
 * 2. If character is delimiter: save current token, reset accumulator
 * 3. If not delimiter: append character to accumulator
 * 4. After loop ends: save final token (handles no trailing delimiter)
 * 
 * Behavior:
 * - "a,b,c" split by ',' -> ["a", "b", "c"]
 * - "a,,c" split by ','  -> ["a", "", "c"]  (empty token preserved)
 * - ",a,"  split by ','  -> ["", "a", ""]   (leading/trailing delimiters)
 * - ""     split by ','  -> []              (empty input = empty result)
 * 
 * Time Complexity: O(n) where n = s.length
 * Space Complexity: O(n) for storing all tokens
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

/**
 * @brief Splits a string by a delimiter character
 * @param s The string to split (const ref for efficiency)
 * @param c The delimiter character
 * @return Vector of strings (tokens between delimiters)
 * 
 * Algorithm:
 * - Maintain accumulator string 'st' for current token
 * - On delimiter: move current token to result, clear accumulator
 * - On regular char: append to accumulator using +=
 * - After loop: push final token
 * 
 * Example: s = "a,b,c", c = ','
 *   'a' != ',' -> st = "a"
 *   ',' == ',' -> push "a", st = ""
 *   'b' != ',' -> st = "b"
 *   ',' == ',' -> push "b", st = ""
 *   'c' != ',' -> st = "c"
 *   end        -> push "c"
 *   Result: ["a", "b", "c"]
 * 
 * Optimization: Uses += for O(1) amortized append, std::move to avoid copies
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
vector<string> string_split(const string& s, char c) {
  vector<string> res;
  
  // Edge case: empty string returns empty vector
  if (s.empty()) return res;
  
  string st;
  for (char ch : s) {
    if (ch == c) {
      // Delimiter found: move current token and reset
      res.push_back(std::move(st));
      st.clear();
    }
    else {
      // Regular character: efficient append
      st += ch;
    }
  }
  
  // Push final token (handles no trailing delimiter)
  res.push_back(std::move(st));
  
  return res;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  // Test 1: Basic split by space
  // "split by space" -> ["split", "by", "space"]
  string s {"split by space"}; 
  char c = ' ';
  for (auto& x : string_split(s, c)) cout << x << "\n";
  cout << "\n";
  
  // Test 2: Multiple consecutive delimiters create empty strings
  // "beekeeper needed" split by 'e' -> ["b", "", "k", "", "p", "r n", "", "d", "d"]
  s = "beekeeper needed"; 
  c = 'e';
  for (auto& x : string_split(s, c)) cout << x << "\n";
  cout << "\n";
  
  // Test 3: Leading/trailing delimiters and consecutive delimiters
  // "/home/./..//Documents/" -> ["", "home", ".", "..", "", "Documents", ""]
  s = "/home/./..//Documents/"; 
  c = '/';
  for (auto& x : string_split(s, c)) cout << x << "\n";
  cout << "\n";
  
  // Test 4: Empty string returns empty vector
  // "" -> []
  s = ""; 
  c = '?';
  for (auto& x : string_split(s, c)) cout << x << "\n";
  cout << "\n";
  
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # String Split
 * 
 * Without using a built-in string split method, implement a `split(s, c)` 
 * method, which receives a string `s` and a character `c` and splits `s` 
 * at each occurrence of `c`, returning a list of strings.
 * 
 * Example 1: s = "split by space", c = ' '
 * Output: ["split", "by", "space"]
 * 
 * Example 2: s = "beekeeper needed", c = 'e'
 * Output: ["b", "", "k", "", "p", "r n", "", "d", "d"]
 * 
 * Example 3: s = "/home/./..//Documents/", c = '/'
 * Output: ["", "home", ".", "..", "", "Documents", ""]
 * 
 * Example 4: s = "", c = '?'
 * Output: []
 * 
 * Constraints:
 * - The length of the input string is at most 10^6
 * - The delimiter is a single character
 * 
 *============================================================================*/
