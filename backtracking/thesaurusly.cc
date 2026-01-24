/**
 * @file thesaurusly.cc
 * @brief Generate all sentence variations by replacing words with synonyms
 * 
 * This file implements a backtracking solution to generate all possible
 * sentences by replacing words with their synonyms. Words without synonyms
 * remain unchanged.
 * 
 * Key Concepts:
 * - Backtracking with branching based on synonym availability
 * - String tokenization using stringstream
 * - HashMap (unordered_map) for O(1) synonym lookup
 * 
 * Time Complexity: O(k^m * n) where:
 *   - n = number of words in sentence
 *   - m = number of words that have synonyms
 *   - k = average number of synonyms per word
 * 
 * Space Complexity: O(k^m * n) for storing all sentence variations
 *   - Recursion stack: O(n) depth
 * 
 * Example: "I walk" with synonyms {"walk": ["stroll", "hike"]}
 * Produces: "I stroll", "I hike" (2 variations)
 */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

/** Global vector to store all generated sentence variations */
vector<vector<string>> ans {};

/**
 * @brief Splits a string by delimiter using stringstream
 * 
 * @param str       The input string to split
 * @param delimiter The character to split on
 * @return Vector of tokens (words)
 */
vector<string> splitStringStream(string& str, char delimiter) {
  vector<string> tokens;
  string token;
  stringstream ss(str);
  while (getline(ss, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

/**
 * @brief Recursive function to generate all sentence variations
 * 
 * @param tokens Vector of words from the original sentence
 * @param i      Current word index being processed
 * @param n      Total number of words
 * @param sym    HashMap mapping words to their synonym lists
 * @param curr   Current sentence being built (as vector of words)
 * 
 * Algorithm:
 * 1. Base case: if i == n, we've processed all words -> save sentence
 * 2. If current word has NO synonyms:
 *    a. Keep the original word
 *    b. Recurse to next word
 * 3. If current word HAS synonyms:
 *    a. Try EACH synonym as replacement
 *    b. Recurse to next word for each
 *    c. Backtrack after each branch
 */
void solve(vector<string>& tokens, int i, int n, 
           unordered_map<string, vector<string>>& sym, vector<string>& curr) {
  // Base case: all words processed, save this sentence variation
  if(i == n) {
    ans.push_back(curr);
    return;
  }
  
  // Check if current word has synonyms
  if(!sym.count(tokens[i])) {
    // NO synonyms: keep original word
    curr.push_back(tokens[i]);        // CHOOSE: use original
    solve(tokens, i+1, n, sym, curr); // EXPLORE: next word
    curr.pop_back();                  // UNCHOOSE: backtrack
  } else {
    // HAS synonyms: try each synonym
    vector<string> replacement = sym.at(tokens[i]);
    for(auto& word : replacement) {
      curr.push_back(word);           // CHOOSE: use this synonym
      solve(tokens, i+1, n, sym, curr); // EXPLORE: next word
      curr.pop_back();                // UNCHOOSE: backtrack
    }
  }
}

/**
 * @brief Wrapper function to generate all sentence variations
 * 
 * @param S   The input sentence (space-separated words)
 * @param sym HashMap of word -> list of synonyms
 */
void thesaurusly(string& S, unordered_map<string, vector<string>>& sym) {
  vector<string> curr;
  vector<string> tokens = splitStringStream(S, ' ');
  int n = tokens.size();
  solve(tokens, 0, n, sym, curr);
}

/**
 * @brief Helper function to print all sentence variations
 */
void print_result() {
  for(auto& vec : ans) {
    for(auto& word : vec) {
      cout << word << " ";
    }
    cout << "\n";
  }
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Example 1: Multiple synonyms for multiple words
  // "simply" -> ["just", "merely"], "walk" -> ["stroll", "hike", "wander"]
  // Expected: 2 * 3 = 6 variations
  string S {"one does not simply walk into mordor"};
  unordered_map<string, vector<string>> sym {
    {"walk", {"stroll", "hike", "wander"}},
    {"simply", {"just", "merely"}}
  };
  thesaurusly(S, sym);
  cout << "Variations of: \"" << S << "\"\n";
  print_result();
  cout << "\n";

  // Example 2: Single word with single synonym
  ans.clear();
  S = "walk";
  sym = {{"walk", {"stroll"}}};
  thesaurusly(S, sym);
  cout << "Variations of: \"" << S << "\"\n";
  print_result();
  
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Thesaurusly
 * 
 * Given a non-empty string, `sentence`, and a non-empty map, `synonyms`,
 * where each key is a single word in the sentence, and its value is a
 * non-empty list of synonyms, return all possible sentences that can be
 * created by replacing the words in the sentence with their synonyms.
 * Words without synonyms should remain unchanged.
 * 
 * Example 1:
 * sentence = "one does not simply walk into mordor"
 * synonyms = {
 *   "walk": ["stroll", "hike", "wander"],
 *   "simply": ["just", "merely"]
 * }
 * Output: [
 *           "one does not just stroll into mordor",
 *           "one does not just hike into mordor",
 *           "one does not just wander into mordor",
 *           "one does not merely stroll into mordor",
 *           "one does not merely hike into mordor",
 *           "one does not merely wander into mordor"
 *         ]
 * 
 * Example 2:
 * sentence = "walk"
 * synonyms = {"walk": ["stroll"]}
 * Output: ["stroll"]
 * 
 * Constraints:
 * - `sentence` consists of lowercase letters and spaces.
 * - The length of `sentence` is at most 500 characters.
 * - `sentence` contains at most 100 words.
 * - The synonyms map contains at most 8 entries.
 * - Each synonym list has at most 6 words.
 * 
 *============================================================================*/
