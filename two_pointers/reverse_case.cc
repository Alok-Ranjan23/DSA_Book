/**
 * @file reverse_case.cc
 * @brief Check if lowercase letters match reversed uppercase letters
 * 
 * This file implements a check for whether the word formed by lowercase
 * letters equals the reverse of the word formed by uppercase letters.
 * 
 * Key Concepts:
 * - Two Pointer Technique: Start from both ends
 * - Selective character matching: skip characters based on case
 * - Case conversion using ASCII arithmetic (difference of 32)
 * 
 * Time Complexity: O(n) where n is string length
 * Space Complexity: O(1) - only uses constant extra space
 * 
 * Algorithm:
 * - Left pointer finds lowercase letters (from start)
 * - Right pointer finds uppercase letters (from end)
 * - Compare: lowercase at left should equal uppercase at right + 32
 * - Advance pointers accordingly
 */

#include <iostream>
#include <string>
using namespace std;

/**
 * @brief Checks if lowercase word equals reverse of uppercase word
 * @param s String with exactly half lowercase and half uppercase letters
 * @return true if lowercase letters reversed equal uppercase letters
 * 
 * Example: "haDrRAHd" -> lowercase "hard", uppercase "DRAH"
 *          "DRAH" reversed = "HARD" which matches "hard" (ignoring case)
 */
bool reverse_match(string& s) {
  int n = s.size();
  int l = 0;
  int h = n - 1;
  while(l<h) {
    if(s[l]>='A' && s[l]<='Z') l++;
    else if(s[h]>='a' && s[h]<='z') h--;
    else {
      if(s[l++]!=s[h--]+32) return false;
    }
  }
  return true;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  cout<<boolalpha;
  string s {"haDrRAHd"};
  cout<<reverse_match(s)<<"\n";
  s = "haHrARDd";
  cout<<reverse_match(s)<<"\n";
  s = "BbbB";
  cout<<reverse_match(s)<<"\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Reverse Case Match
 * 
 * Given a string, s, where half of the letters are lowercase and half
 * uppercase, return whether the word formed by the lowercase letters is
 * the same as the reverse of the word formed by the uppercase letters.
 * Assume that the length, n, is even.
 * 
 * Example 1:
 * Input: s = "haDrRAHd"
 * Output: true
 * Explanation:
 * - Lowercase letters: "hard"
 * - Uppercase letters: "DRAH"
 * - When reversed, "DRAH" becomes "HARD", matches "hard" ignoring case.
 * 
 * Example 2:
 * Input: s = "haHrARDd"
 * Output: false
 * Explanation:
 * - Lowercase letters: "hard"
 * - Uppercase letters: "HARD"
 * - When reversed, "HARD" becomes "DRAH", doesn't match "hard".
 * 
 * Example 3:
 * Input: s = "BbbB"
 * Output: true
 * Explanation:
 * - Lowercase letters: "bb"
 * - Uppercase letters: "BB"
 * - When reversed, "BB" becomes "BB", matches "bb" ignoring case.
 * 
 * Constraints:
 * - 0 ≤ s.length ≤ 10^6
 * - s contains only uppercase and lowercase English letters
 * 
 *============================================================================*/
