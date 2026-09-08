/**
 * @file shortest_with_all_letters.cc
 * @brief Find the shortest substring of s1 containing every character of s2 with required frequency.
 *
 * A minimum sliding window with a hash map tracks character frequencies from s2.
 * A counter char_to_match holds how many distinct characters still need more occurrences.
 * The window grows (r++) while char_to_match > 0 (condition not yet met). Once all
 * characters are satisfied, we record the window size and shrink (l++) to try for
 * a shorter valid window.
 *
 * Key Concepts:
 * - Minimum sliding window pattern
 * - Hash map for character frequency tracking
 * - char_to_match counter tracks distinct characters still unsatisfied (not total chars)
 *
 * Time Complexity: O(n + m) where n = s1.size() and m = s2.size().
 *   Each character in s1 is visited at most twice (once by r, once by l).
 *   Building the frequency map from s2 takes O(m).
 * Space Complexity: O(m) for the hash map storing character frequencies from s2
 *   (at most 26 entries for lowercase English letters).
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <limits>
using namespace std;

/**
 * @brief Finds the length of the shortest substring of s1 containing all characters of s2
 * @param s1 The source string to search within
 * @param s2 The pattern string whose characters must all appear with sufficient frequency
 * @return Length of the shortest valid substring, or -1 if none exists
 */
  int n = s1.size();
  unordered_map <char, int> umap;
  for(auto& x: s2) umap[x]++;
  int char_to_match = umap.size();
  int window_size = numeric_limits<int>::max();
  int l = 0;
  int r = 0;
  while(1) {
    bool must_grow = char_to_match > 0;
    if(must_grow) {
      if(r==n) break;
      if(umap.count(s1[r])) {
        umap[s1[r]]--;
        if(umap[s1[r]]==0) char_to_match-=1;
      }
      r+=1;
    } 
    else {
      window_size = min(window_size, r - l);
      if (umap.count(s1[l])) {
        umap[s1[l]]++;
        if (umap[s1[l]] == 1) {
          char_to_match+=1;
        }
      }
      l+=1;
    }
  }
  if(window_size==numeric_limits<int>::max()) return -1;
  return window_size;
}

// To execute C++, please define "int main()"
int main() {
  string s1{"helloworld"}, s2{"well"};
  cout<<shortest_with_all_letters(s1,s2)<<"\n";
  s1 = "helloworld", s2 = "weell";
  cout<<shortest_with_all_letters(s1,s2)<<"\n";
  return 0;
}

// # Shortest With All Letters

// Given a string, `s1`, and a shorter but non-empty string, `s2`, return the length of the shortest substring of `s1` that has every letter in `s2` at least as many times as they appear in `s2`. If there is no such substring, return `-1`.

// Example 1: s1 = "helloworld", s2 = "well"
// Output: 5. The substring "ellow" in s1 has all the letters in s2.

// Example 2: s1 = "helloworld", s2 = "weelll"
// Output: -1. s1 does not have 2 e's.

// Constraints:

// - `1 <= len(s2) < len(s1) <= 10^5`
// - All characters are lowercase English letters
