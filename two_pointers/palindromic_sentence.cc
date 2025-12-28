/**
 * @file palindromic_sentence.cc
 * @brief Check if a sentence is a palindrome ignoring non-letters and case
 * 
 * This file implements palindrome check for sentences where only letters
 * matter, ignoring spaces, punctuation, and case differences.
 * 
 * Key Concepts:
 * - Two Pointer Technique: Start from both ends, move inward
 * - Character filtering: Skip non-alphabetic characters
 * - Case-insensitive comparison using ASCII arithmetic
 * 
 * Time Complexity: O(n) where n is string length
 * Space Complexity: O(1) - only uses constant extra space
 * 
 * Algorithm:
 * - Left and right pointers start from ends
 * - Skip non-letter characters by advancing pointers
 * - Compare letters case-insensitively (using +32 ASCII offset)
 * - Return false on mismatch, true if pointers cross
 */

#include <iostream>
#include <string>
using namespace std;

/**
 * @brief Checks if a sentence is a palindrome (letters only, case-insensitive)
 * @param s String to check (may contain spaces, punctuation)
 * @return true if letters form a palindrome ignoring case, false otherwise
 * 
 * Uses ASCII comparison: 'a' = 'A' + 32, so we check if
 * s[l] == s[h] OR s[l]+32 == s[h] OR s[l] == s[h]+32
 */
bool palindromic_sentence(string& s) {
  int n = s.size();
  int l = 0;
  int h = n-1;
  while(l<h) {
    if(!((s[l]>='A' && s[l]<='Z') || (s[l]>='a' && s[l]<='z'))) l++;
    else if(!((s[h]>='A' && s[h]<='Z') || (s[h]>='a' && s[h]<='z'))) h--;
    else {
      if(s[l]!=s[h] && s[l]+32!=s[h] && s[l]!=s[h]+32) return false;
      l++;h--;
    }
  }
  return true;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  string s {"Bob wondered, 'Now, Bob?'"};
  cout<<boolalpha;
  cout<<palindromic_sentence(s)<<"\n";
  s = "race a car";
  cout<<palindromic_sentence(s)<<"\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Palindromic Sentence
 * 
 * Given a string s, return whether its letters form a palindrome ignoring
 * punctuation, spaces, and casing.
 * 
 * Example 1:
 * Input: s = "Bob wondered, 'Now, Bob?'"
 * Output: true
 * Explanation: Considering only letters and ignoring case, we get
 * "bobwonderednowbob" which is a palindrome.
 * 
 * Example 2:
 * Input: s = "race a car"
 * Output: false
 * Explanation: Considering only letters and ignoring case, we get
 * "raceacar" which is not a palindrome.
 * 
 * Constraints:
 * - 0 ≤ s.length ≤ 10^6
 * - s consists of printable ASCII characters
 * 
 *============================================================================*/
