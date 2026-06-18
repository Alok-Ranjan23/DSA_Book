/**
 * @file word_expansion_class.cc
 * @brief Check if s2 is s1 plus exactly one extra letter, reordered
 *
 * A Checker is built around a fixed string s1. expands_into(s2) asks whether
 * s2 can be formed by adding exactly one letter to s1 and shuffling. We count
 * the letters of s2, subtract the letters of s1, and verify that exactly one
 * letter remains with a leftover count of one.
 *
 * Key Concepts:
 * - Character frequency counting with an unordered_map
 * - Anagram-style comparison by cancelling matched characters
 *
 * Time Complexity: O(n + m)
 *   - n = s1.size(), m = s2.size(). One pass over each string; every map
 *     operation is O(1) average.
 *
 * Space Complexity: O(1)
 *   - The map holds at most 26 distinct lowercase letters, a constant
 */
#include <ios>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

class Checker {
  private:
  string s1;
  public:
  Checker(string s1_);
  bool expands_into(const string& s2);
};

Checker::Checker(string t1_): s1{t1_} {}

/**
 * @brief Determine whether s2 equals s1 with exactly one added letter, reordered
 *
 * @param s2 Candidate expanded string
 * @return true if s2 is s1 plus one extra letter (in any order), else false
 *
 * Algorithm:
 * 1. If s2 is not strictly longer than s1, it cannot be an expansion.
 * 2. Count the frequency of every character in s2.
 * 3. Cancel one occurrence per character of s1; remove a key when it hits 0.
 * 4. A valid expansion leaves exactly one leftover character with count 1.
 */
//Time O(n + m)  (n = s1 length, m = s2 length; O(1) average map ops)
//Space O(1)     (at most 26 distinct lowercase letters in the map)
bool Checker::expands_into(const string& s2) {
  if(s2.size()<=s1.size()) return false;
  unordered_map <char, int> umap;
  for(auto& ch: s2) umap[ch]++;       // frequency count of s2
  for(auto & c : s1) {                // cancel each char of s1
    if(umap.find(c) != umap.end()) {
      umap[c]-=1;
      if(umap[c]==0) umap.erase(c);
    }
  }
  // Exactly one extra letter must remain
  return umap.size()==1 && umap.begin()->second==1;
}

// To execute C++, please define "int main()"
int main() {
  cout<<boolalpha;
  // Example 1:
  Checker checker = Checker("tea");
  cout<<checker.expands_into("tea")<<"\n";       // returns False
  cout<<checker.expands_into("team")<<"\n";      // returns True
  cout<<checker.expands_into("seam")<<"\n";      // returns False
  cout<<"------------------------------\n";
  // Example 2:
  Checker checker2 = Checker("on");
  cout<<checker2.expands_into("nooo")<<"\n";     // returns False
  cout<<checker2.expands_into("not")<<"\n";      // returns True
  cout<<checker2.expands_into("now")<<"\n";      // returns True
  cout<<"------------------------------\n";
  // Example 3:
  Checker checker3 = Checker("");
  cout<<checker3.expands_into("a")<<"\n";        // returns True
  cout<<checker3.expands_into("")<<"\n";         // returns False
  cout<<checker3.expands_into("ab")<<"\n";       // returns False
  cout<<"------------------------------\n";
  return 0;
}

// # Word Expansion Class

// Implement a class, `Checker`, that receives a string `s` upon initialization. The class must support a method, `expands_into(s2)`, which takes another string and checks if `s2` can be formed by adding exactly one letter to `s1` and reordering the letters. All letters in both strings are lowercase alphabetical characters.

// Example 1:
// checker = Checker("tea")
// print(checker.expands_into("tea"))   # returns False
// print(checker.expands_into("team"))  # returns True
// print(checker.expands_into("seam"))  # returns False

// Example 2:
// checker = Checker("on")
// print(checker.expands_into("nooo"))  # returns False
// print(checker.expands_into("not"))   # returns True
// print(checker.expands_into("now"))   # returns True

// Example 3:
// checker = Checker("")
// print(checker.expands_into("a"))     # returns True
// print(checker.expands_into(""))      # returns False
// print(checker.expands_into("ab"))    # returns False

// Constraints:

// - The length of `s` and `s2` is at most `10^5`
// - All characters are lowercase English letters
