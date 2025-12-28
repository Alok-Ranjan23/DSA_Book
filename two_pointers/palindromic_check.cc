/**
 * @file palindromic_check.cc
 * @brief Check if a string is a palindrome using two pointers
 * 
 * This file implements the classic palindrome check using the
 * two pointer technique from both ends of the string.
 * 
 * Key Concepts:
 * - Two Pointer Technique: Start from both ends, move inward
 * - Character comparison at symmetric positions
 * - Early termination on mismatch
 * 
 * Time Complexity: O(n) where n is string length
 * Space Complexity: O(1) - only uses constant extra space
 * 
 * Algorithm:
 * - Initialize left pointer at start, right pointer at end
 * - Compare characters at both positions
 * - If mismatch found, return false immediately
 * - If pointers cross without mismatch, string is palindrome
 */

#include <iostream>
#include <string>
using namespace std;

/**
 * @brief Checks if a string is a palindrome
 * @param s String to check (passed by reference for efficiency)
 * @return true if string reads same forward and backward, false otherwise
 * 
 * Compares characters from both ends, moving inward until
 * pointers meet or a mismatch is found.
 */
bool is_palindrome(string& s) {
  int n = s.size();
  int l = 0;
  int h = n-1;
  while(l<h) {
    if(s[l++]!=s[h--]) return false;
  }
  return true;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  string s{"level"};
  cout<<boolalpha;
  cout<<is_palindrome(s)<<"\n";
  s = "naan";
  cout<<is_palindrome(s)<<"\n";
  s = "hello";
  cout<<is_palindrome(s)<<"\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Palindrome Check
 * 
 * Given a string s, return whether s is a palindrome. A palindrome is a
 * string that reads the same forward and backward.
 * 
 * Example 1: s = "level"
 * Output: true
 * 
 * Example 2: s = "naan"
 * Output: true
 * 
 * Example 3: s = "hello"
 * Output: false
 * 
 * Constraints:
 * - The length of s is at most 10^6
 * - s consists of lowercase English letters
 * 
 *============================================================================*/
