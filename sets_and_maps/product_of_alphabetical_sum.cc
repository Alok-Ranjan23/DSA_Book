/**
 * @file product_of_alphabetical_sum.cc
 * @brief Decide if three words have alphabetical sums whose product == target
 *
 * The alphabetical sum of a word maps 'a'->1 ... 'z'->26 and adds the letters.
 * We only care about which sums are achievable, so we collect the distinct
 * sums into a set, then search for a factor triple num1*num2*num3 == target
 * where every factor is an achievable sum (the same word may be reused).
 *
 * Key Concepts:
 * - Reducing words to their distinct alphabetical sums (unordered_set)
 * - Triple-product search by fixing two factors and looking up the third
 *
 * Bounded-domain note: each word has at most 3 letters, so an alphabetical sum
 * lies in [1, 75] (max = 'x'+'y'+'z' = 24+25+26). Hence the set holds at most
 * S <= 75 distinct values -- a constant independent of N.
 *
 * Time Complexity: O(N + S^2), with S = #distinct sums <= 75
 *   - O(N) to read the words and compute their sums (each word length <= 3).
 *   - The nested loops run S*S iterations with an O(1) average set lookup.
 *   - Since S is capped at 75, S^2 is a constant, so this is effectively O(N).
 *
 * Space Complexity: O(S) <= O(75) = O(1) auxiliary
 *   - The set stores at most 75 distinct sums regardless of input size.
 */
#include <ios>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

/**
 * @brief Test whether some triple of alphabetical sums multiplies to target
 *
 * @param words  List of lowercase words, each 1-3 letters
 * @param target Desired product of three alphabetical sums
 * @return true if num1*num2*num3 == target for achievable sums (reuse allowed)
 *
 * Algorithm:
 * 1. Compute each word's alphabetical sum and store the distinct values.
 * 2. For each divisor num1 of target, reduce to new_target = target/num1.
 * 3. For each divisor num2 of new_target, the third factor must be
 *    new_target/num2; return true if that value is also an achievable sum.
 *
 * Time:  O(N + S^2), S = #distinct sums <= 75  (effectively O(N))
 * Space: O(S) <= O(1)
 */
//Time O(N + S^2), S = distinct sums <= 75 (effectively O(N))
//Space O(S) <= O(1)  (at most 75 distinct sums)
bool pdt_alphabetical_sum(vector<string>& words,int target) {
  auto alphabetical_sum = [](string word) {
    int word_sum = 0;
    for(auto& c: word) {
      word_sum += (c - 'a') + 1;
    }
    return word_sum;
  };

  unordered_set<int> alpha_sum;
  for(auto & word: words) {                 // O(N): collect distinct sums
    int word_sum = alphabetical_sum(word);
    alpha_sum.insert(word_sum);
  }

  for(int num1 : alpha_sum) {               // O(S^2) over a bounded domain
    if(target % num1 != 0) continue;        // num1 must divide target
    int new_target = target / num1 ;
    for(int num2 : alpha_sum) {
      if(new_target % num2 != 0) continue;  // num2 must divide the remainder
      // third factor is fixed; success iff it is also achievable
      if(alpha_sum.find(new_target / num2) != alpha_sum.end()) return true;
    }
  }
  return false;
}

// To execute C++, please define "int main()"
int main() {
  //Example 1
  vector <string> words {"abc","fg","hij","klm","nop","qrs","vwx"}; int target {1620};
  cout<<boolalpha;
  cout<<pdt_alphabetical_sum(words,target)<<"\n";
  //Example 2
  words = {"a","b"}; target = 2;
  cout<<pdt_alphabetical_sum(words,target)<<"\n";
  //Example 3
  words = {"a","b","c"}; target = 7;
  cout<<pdt_alphabetical_sum(words,target)<<"\n";
  return 0;
}

// # Product of Alphabetical Sums

// Given a list of lowercase strings, `words`, where each string has between `1` and `3` letters, determine if there exist three strings such that the product of their _alphabetical sums_ is a given target value, `target`. The alphabetical sum of a string is the sum of the positions of its letters in the alphabet (e.g., the alphabetical sum of "abz" is `1 + 2 + 26 = 29`). Return true if such a triplet exists. The same string can be used more than once.

// Example 1: words = ["abc", "fg", "hij", "klm", "nop", "qrs", "vwx"], target = 1620
// Output: true
// Explanation: The triplet is "abc", "abc", "nop": 6 * 6 * 45 = 1620.

// Example 2: words = ["a", "b"], target = 2
// Output: true
// Explanation: The triplet is "a", "a", "b": 1 * 1 * 2 = 2.

// Example 3: words = ["a", "b", "c"], target = 7
// Output: false
// Explanation: No triplet of strings has a product of alphabetical sums equal to 7.

// Constraints:

// - `0 ≤ words.length ≤ 10^5`
// - Each string in `words` has length between `1` and `3`
// - All strings contain only lowercase English letters
// - `1 ≤ target ≤ 10^6`
