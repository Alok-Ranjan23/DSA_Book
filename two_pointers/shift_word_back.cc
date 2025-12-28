/**
 * @file shift_word_back.cc
 * @brief Move earliest subsequence of a word to end of array
 * 
 * This file implements the algorithm to find the earliest occurrence of
 * a word as a subsequence and move those letters to the end of the array.
 * 
 * Key Concepts:
 * - Writer-Seeker Pattern: Classic two pointer technique
 * - Subsequence identification: Letters in order but not contiguous
 * - In-place modification with O(1) extra space
 * - Preserves relative order of both moved and remaining letters
 * 
 * Time Complexity: O(n) where n is array length
 * Space Complexity: O(1) - only uses constant extra space
 * 
 * Algorithm:
 * - Seeker scans through array
 * - If current char matches next needed char of word, skip it (advance seeker)
 * - Otherwise, writer copies the char and both advance
 * - After scan, append the word characters to remaining positions
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

/**
 * @brief Moves earliest subsequence of word to end of array
 * @param arr Vector of characters (modified in place)
 * @param word String representing the word to find and move
 * 
 * Finds the earliest occurrence of 'word' as a subsequence in 'arr'
 * and moves those exact letters (in order) to the end of the array.
 */
//This is a writer-seeker pattern problem
void shift_word_back(vector<char>& arr,string& word) {
  int n_arr = arr.size();
  int writer = 0;int seeker = 0;
  int n_word = word.size();
  int i_word = 0;
  while(seeker < n_arr) {
    if(i_word==n_word || arr[seeker]!=word[i_word]) {
      arr[writer] = arr[seeker];
      writer+=1;
      seeker+=1;
    } else {
      seeker+=1;
      i_word+=1;
    }
  }
  i_word=0;
  while(writer<n_arr) {
    arr[writer++] = word[i_word++];
  }
  return;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  vector<char> arr {'s', 'e', 'e', 'k', 'e', 'r', 'a', 'n', 'd', 'w', 'r', 'i', 't', 'e', 'r'};
  string word {"edit"};
  for(auto& c: arr) cout<<c<<" ";
  cout<<"\n";
  shift_word_back(arr,word);
  for(auto& c: arr) cout<<c<<" ";
  cout<<"\n";
  arr = {'b','a','c','b'}; word = "ab";
  for(auto& c: arr) cout<<c<<" ";
  cout<<"\n";
  shift_word_back(arr,word);
  for(auto& c: arr) cout<<c<<" ";
  cout<<"\n";
  arr = {'b','a','b','c'}; word = "b";
  for(auto& c: arr) cout<<c<<" ";
  cout<<"\n";
  shift_word_back(arr,word);
  for(auto& c: arr) cout<<c<<" ";
  cout<<"\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Shift Word to Back
 * 
 * You are given an array of letters, arr, and a string, word. We know that
 * word appears within arr as a subsequence (its letters appear in order,
 * though not necessarily contiguously).
 * 
 * Identify the earliest occurrence of word in arr (that is, the first
 * subsequence from left to right that spells out word) and move all those
 * letters, in order, to the end of arr.
 * 
 * You must do this in place, using only O(1) extra space, and preserve the
 * relative order of both the moved letters and the remaining letters.
 * 
 * Example: arr = [s, e, e, k, e, r, a, n, d, w, r, i, t, e, r], word = "edit"
 * Output: [s, e, k, e, r, a, n, w, r, e, r, e, d, i, t]
 * 
 * The subsequence that needs to be moved is:
 *     [s, e, e, k, e, r, a, n, d, w, r, i, t, e, r]
 *         ^                    ^        ^  ^
 * 
 * Example: arr = [b, a, c, b], word = "ab"
 * Output: [b, c, a, b]
 * We cannot move the first 'b' because we need to find 'a' first.
 * 
 * Example: arr = [b, a, b, c], word = "b"
 * Output: [a, b, c, b]
 * We must move the first 'b' to the end, not the second one.
 * 
 * Constraints:
 * - 0 ≤ arr.length ≤ 10^6
 * - 0 ≤ word.length ≤ arr.length
 * - arr and word contain only lowercase English letters
 * 
 *============================================================================*/
