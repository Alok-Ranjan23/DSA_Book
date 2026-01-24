/**
 * @file tobe_nottobe.cc
 * @brief Generate all possible sentences by including/excluding each word
 * 
 * Inspired by Shakespeare's "To be or not to be", this file implements a
 * backtracking solution that generates all possible sentences by deciding
 * whether each word should "be" (included) or "not be" (excluded).
 * 
 * Key Concepts:
 * - Subset enumeration applied to words in a sentence
 * - Binary decision tree: include or exclude each word
 * - String tokenization using stringstream
 * 
 * Time Complexity: O(2^n * n) where n = number of words
 *   - 2^n possible combinations (each word in or out)
 *   - Each combination takes O(n) to store
 * 
 * Space Complexity: O(2^n * n) for storing all sentence variations
 *   - Recursion stack: O(n) depth
 * 
 * Example: "I love dogs" produces 2^3 = 8 variations:
 * "", "I", "love", "dogs", "I love", "I dogs", "love dogs", "I love dogs"
 */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

/** Global vector to store all generated sentence variations */
vector<vector<string>> ans;

/**
 * @brief Splits a string by delimiter using stringstream
 * 
 * @param sentence  The input string to split
 * @param delimiter The character to split on
 * @return Vector of tokens (words)
 */
vector<string> splitStringStream(string& sentence, char delimiter) {
  vector<string> tokens;
  string token;
  stringstream ss(sentence);
  while (getline(ss, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

/**
 * @brief Recursive function to generate all word combinations
 * 
 * @param tokens Vector of words from the original sentence
 * @param i      Current word index being considered
 * @param size_  Total number of words
 * @param res    Current sentence being built (as vector of words)
 * 
 * Algorithm:
 * 1. Base case: if i == size_, we've decided for all words -> save result
 * 2. For current word tokens[i]:
 *    a. "TO BE": include the word, recurse
 *    b. "NOT TO BE": exclude the word (backtrack), recurse without it
 * 
 * This is identical to subset enumeration, applied to sentence words.
 */
void solve(vector<string>& tokens, int i, int size_, vector<string>& res) {
  // Base case: made decisions for all words, save this combination
  if(i == size_) {
    ans.push_back(res);
    return;
  }
  
  // Branch 1: "TO BE" - include current word
  res.push_back(tokens[i]);           // CHOOSE: include word
  solve(tokens, i+1, size_, res);     // EXPLORE: next word
  res.pop_back();                     // UNCHOOSE: remove word (backtrack)
  
  // Branch 2: "NOT TO BE" - exclude current word
  solve(tokens, i+1, size_, res);     // EXPLORE: skip to next word
}

/**
 * @brief Helper function to print all sentence variations
 */
void print_result() {
  for(auto& vec : ans) {
    cout << "\"";
    for(size_t i = 0; i < vec.size(); ++i) {
      cout << vec[i];
      if(i < vec.size() - 1) cout << " ";
    }
    cout << "\"\n";
  }
}

/**
 * @brief Wrapper function to generate all sentence variations
 * 
 * @param sentence The input sentence (space-separated words)
 */
void tobe_or_nottobe(string& sentence) {
  vector<string> tokens = splitStringStream(sentence, ' ');
  vector<string> res;
  int n = tokens.size();
  solve(tokens, 0, n, res);
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Example 1: "I love dogs" -> 2^3 = 8 combinations
  string sentence = "I love dogs";
  cout << "All variations of: \"" << sentence << "\"\n";
  tobe_or_nottobe(sentence);
  print_result();
  cout << "\n";
  
  // Example 2: Single word "hello" -> 2^1 = 2 combinations
  ans.clear();
  sentence = "hello";
  cout << "All variations of: \"" << sentence << "\"\n";
  tobe_or_nottobe(sentence);
  print_result();
  cout << "\n";
  
  // Example 3: Empty string -> 1 combination (empty)
  ans.clear();
  sentence = "";
  cout << "All variations of: \"" << sentence << "\"\n";
  tobe_or_nottobe(sentence);
  print_result();
  
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # To Be or Not to Be
 * 
 * Inspired by Shakespeare's iconic line, you decide to write a function,
 * `shakespearify()`, which takes in a string, `sentence`, consisting of
 * letters and spaces. For each word in the string, the function chooses
 * if it should "be" or "not be" included in the sentence, returning all
 * possible outcomes. The order of the output strings does not matter.
 * 
 * Example 1: sentence = "I love dogs"
 * Output: [
 *          "",
 *          "I",
 *          "love",
 *          "dogs",
 *          "I love",
 *          "I dogs",
 *          "love dogs",
 *          "I love dogs"
 *         ]
 * 
 * Example 2: sentence = "hello"
 * Output: ["", "hello"]
 * 
 * Example 3: sentence = ""
 * Output: [""]
 * 
 * Constraints:
 * - The sentence consists of lowercase letters and spaces.
 * - The sentence has at most 12 words and at most 100 characters.
 * 
 *============================================================================*/
