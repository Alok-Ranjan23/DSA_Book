/**
 * @file string_join.cc
 * @brief Join Array of Strings with Delimiter (without built-in join)
 * 
 * This file implements a custom string join function that concatenates
 * an array of strings with a specified delimiter between them.
 * 
 * Key Concepts:
 * - String Concatenation: Building result by appending strings
 * - Delimiter Handling: Insert separator only between elements, not at edges
 * - Edge Cases: Empty array returns empty string
 * 
 * Algorithm:
 * 1. Handle empty array edge case (return "")
 * 2. Start with first element (no leading delimiter)
 * 3. For remaining elements: append delimiter + element
 * 
 * Time Complexity: O(m) where m = total output length
 * - Uses reserve() to pre-allocate memory (single allocation)
 * - Uses += for O(1) amortized append operations
 * 
 * Space Complexity: O(m) where m = total output string length
 * - Result string holds: sum of all arr[i].length + (n-1) * s.length
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

/**
 * @brief Joins an array of strings with a delimiter
 * @param arr Vector of strings to join (const ref for efficiency)
 * @param s Delimiter string to insert between elements (const ref)
 * @return Concatenated string with delimiters
 * 
 * Algorithm:
 * - Return "" if array is empty
 * - Pre-calculate total size and reserve memory (avoids reallocations)
 * - Initialize result with first element (avoids leading delimiter)
 * - Loop from index 1: append delimiter + current element using +=
 * 
 * Example: arr = ["a", "b", "c"], s = "-"
 *   Start: res = "a"
 *   i=1:   res += "-" += "b" -> "a-b"
 *   i=2:   res += "-" += "c" -> "a-b-c"
 * 
 * Optimization: Using reserve() and += avoids O(n) reallocations,
 * reducing from O(n * m) to O(m) where m = total output length.
 * 
 * Time Complexity: O(m) - single pass with pre-allocated memory
 * Space Complexity: O(m) - final result string
 */
//O(m)
string string_join(const vector<string>& arr, const string& s) {
  int n = arr.size();
  
  // Edge case: empty array returns empty string
  if (n == 0) return "";
  
  // Pre-calculate total size for single allocation
  size_t total = 0;
  for (const auto& str : arr) total += str.size();
  total += s.size() * (n - 1);  // delimiters between elements
  
  string res;
  res.reserve(total);
  
  // Start with first element (no delimiter before it)
  res = arr[0];
  
  // Append delimiter + element for remaining elements
  for (int i = 1; i < n; ++i) {
    res += s;
    res += arr[i];
  }
  
  return res;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  
  // Test 1: Basic join with space delimiter
  // Expected: "join by space"
  vector<string> arr = {"join", "by", "space"}; 
  string s{" "};
  cout << string_join(arr, s) << "\n";
  
  // Test 2: Multi-char delimiter with empty strings in array
  // arr = ["b", "", "k", "", "p", "r n", "", "d", "d!!"], s = "ee"
  // Expected: "beeeekeeeepeer neeeedeed!!"
  arr = {"b", "", "k", "", "p", "r n", "", "d", "d!!"}; 
  s = "ee";
  cout << string_join(arr, s) << "\n";
  
  // Test 3: Empty array should return empty string
  // Expected: ""
  arr = {}; 
  s = "x";
  cout << string_join(arr, s) << "\n";
  
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # String Join
 * 
 * Without using a built-in string join method, implement a `join(arr, s)` 
 * method, which receives an array of strings, `arr`, and a string, `s`, 
 * and returns a single string consisting of the strings in `arr` with `s` 
 * in between them.
 * 
 * Example 1: arr = ["join", "by", "space"], s = " "
 * Output: "join by space"
 * 
 * Example 2: arr = ["b", "", "k", "", "p", "r n", "", "d", "d!!"], s = "ee"
 * Output: "beeeekeeeepeer neeeedeed!!"
 * 
 * Example 3: arr = [], s = "x"
 * Output: ""
 * 
 * If strings in your language are immutable, assume that you have access 
 * to a function `array_to_string(arr)`, which takes an array of individual 
 * characters and returns a string with those characters in `O(len(arr))` 
 * time.
 * 
 * Constraints:
 * - 0 <= s.length <= 500
 * - 0 <= arr.length <= 10^5
 * - 0 <= arr[i].length <= 10^5
 * - the sum of the lengths of the strings in `arr` is at most 10^5
 * 
 *============================================================================*/
