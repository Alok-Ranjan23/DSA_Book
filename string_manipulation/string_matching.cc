/**
 * @file string_matching.cc
 * @brief String Pattern Matching with Rabin-Karp Rolling Hash Algorithm
 * 
 * This file implements string matching to find the first occurrence of a
 * pattern string within a text string. Includes both brute-force and
 * optimized Rabin-Karp approaches.
 * 
 * Key Concepts:
 * - Brute Force: Compare pattern at every position in text
 * - Rabin-Karp: Use rolling hash to skip unnecessary comparisons
 * - Rolling Hash: Update hash in O(1) by sliding window technique
 * - Hash Collision: When hashes match, verify with actual string comparison
 * 
 * Rolling Hash Formula:
 * - Initial: hash("abc") = a*128^2 + b*128^1 + c*128^0
 * - Rolling: hash("bcd") = (hash("abc") - a*128^2) * 128 + d
 * - Use modular arithmetic to prevent overflow
 * 
 * Time Complexities:
 * - Brute Force: O((n-m+1) * m) worst case
 * - Rabin-Karp: O(n + m) average case, O(n*m) worst case (many collisions)
 * 
 * Space Complexity: O(1) - only using fixed number of variables
 */

#include <iostream>
#include <string>
using namespace std;

/*============================================================================
 * BRUTE FORCE APPROACH
 *============================================================================*/

/**
 * @brief Finds first occurrence of pattern t in string s using brute force
 * @param s The text string to search in
 * @param t The pattern string to search for
 * @return Index of first match, or -1 if not found
 * 
 * Algorithm:
 * - For each starting position i in s (0 to n-m):
 *   - Compare characters s[i+j] with t[j] for j = 0 to m-1
 *   - If all match (j reaches m), return i
 * - If no match found, return -1
 * 
 * Time Complexity: O((n-m+1) * m) - nested loops
 * Space Complexity: O(1)
 */
int index_of_bruteforce(const string& s,const string& t) {
  int n = s.size();
  int m = t.size();
  for(int i=0;i<n-m+1;++i) {
    int j=0;
    while(j<m) {
      if(s.at(i+j)!=t.at(j)) break;
      j++; 
    }
    if(j==m) return i;
  }
  return -1;
}

/*============================================================================
 * RABIN-KARP ROLLING HASH APPROACH
 *============================================================================*/

/**
 * Rolling Hash Concept Visualization:
 * 
 * For string "abc" with BASE=128:
 *   hash = a*128^2 + b*128^1 + c*128^0 = prev_hash
 * 
 * To get hash of "bcd" from "abc":
 *   new_hash = (prev_hash - a*128^2) * 128 + d
 * 
 * Example sliding window:
 *   Text:    "abcdefg"
 *   Pattern: "kgf" -> compute pat_hash once
 *   Slide window of size 3 through text, updating hash in O(1)
 */
#define MOD 1000000007
#define BASE 128

/**
 * @brief Computes x^n mod MOD using fast exponentiation
 * @param x Base value (long to prevent overflow in intermediate calculations)
 * @param n Exponent
 * @return x^n mod MOD
 * 
 * Algorithm (Binary Exponentiation):
 * - If n is odd:  x^n = x * (x^2)^((n-1)/2)
 * - If n is even: x^n = (x^2)^(n/2)
 * 
 * Note: Takes mod at each step to prevent overflow in x*x
 * 
 * Time Complexity: O(log n)
 */
long power(long x, int n) {
  x %= MOD;
  if(n==0) return 1;
  if(n==1) return x;
  if(n%2) {
    return (x * power((x*x)%MOD, (n-1)/2)) % MOD;
  } 
  return power((x*x)%MOD, n/2) % MOD;
}

/**
 * @brief Computes polynomial hash value for first m characters
 * @param s String to hash
 * @param m Number of characters to include in hash
 * @return Hash value mod MOD
 * 
 * Hash Formula (Horner's method):
 *   hash("abcd") = ((a*128 + b)*128 + c)*128 + d
 *                = a*128^3 + b*128^2 + c*128^1 + d*128^0
 * 
 * Visualization for "abcd":
 *   hash = 0
 *   hash = 0*128 + 'a' = 97
 *   hash = 97*128 + 'b' = 97*128 + 98
 *   hash = (97*128+98)*128 + 'c'
 *   hash = hash*128 + 'd'
 * 
 * Time Complexity: O(m)
 */
long hash_val(const string& s, int m) {
  long hash_val=0;
  for(int i=0;i<m;++i) {
    hash_val = (hash_val*BASE + s[i])%MOD;
  }
  return hash_val;
}

/**
 * @brief Updates hash by removing leftmost char and adding new rightmost char
 * @param a The text string
 * @param rm_idx Index of character to remove (leftmost of current window)
 * @param sz Size of the pattern/window
 * @param first_hash Current hash value (modified in place)
 * @param po Precomputed BASE^(sz-1) mod MOD (avoids recomputing power each call)
 * 
 * Rolling Hash Update:
 * 1. Remove contribution of leftmost char: hash -= a[rm_idx] * po
 * 2. Shift remaining: hash *= BASE
 * 3. Add new rightmost char: hash += a[rm_idx + sz]
 * 
 * Note: Uses +MOD before modulo to handle negative values
 * 
 * Time Complexity: O(1) - power is precomputed and passed in
 */
void rolling_hash(const string& a,int rm_idx, int sz, long& first_hash, long po) {
   first_hash = (first_hash - (a[rm_idx]*po)%MOD + MOD) % MOD;
   first_hash = (first_hash*BASE + a[rm_idx+sz]) % MOD;
}

/**
 * @brief Compares substring of a starting at pos with string b
 * @param a Text string
 * @param pos Starting position in a
 * @param b Pattern string to compare
 * @return true if a[pos..pos+b.size()-1] equals b
 * 
 * Note: Avoids creating substring copies for O(1) space comparison
 * 
 * Time Complexity: O(m) where m = b.size()
 */
bool matches(const string& a, int pos, const string& b) {
  for(int j = 0; j < (int)b.size(); ++j) {
    if(a[pos+j] != b[j]) return false;
  }
  return true;
}

/**
 * @brief Finds first occurrence of pattern b in string a using Rabin-Karp
 * @param a The text string to search in
 * @param b The pattern string to search for
 * @return Index of first match, or -1 if not found
 * 
 * Algorithm:
 * 1. Handle edge cases (pattern longer than text, empty pattern)
 * 2. Compute hash of pattern (pat_hash)
 * 3. Compute hash of first window in text (first_hash)
 * 4. If hashes match AND strings match, return 0
 * 5. Precompute po = BASE^(m-1) once for O(1) rolling hash updates
 * 6. Slide window through text:
 *    - Update first_hash using rolling_hash (O(1) per iteration)
 *    - If hashes match AND strings match, return index
 * 7. Return -1 if no match found
 * 
 * Note: String comparison after hash match handles hash collisions
 * 
 * Optimization: Precomputing po avoids O(log m) power call per iteration,
 * reducing rolling_hash from O(log m) to O(1) per window slide.
 * Uses in-place comparison instead of substr to avoid O(m) copies.
 * 
 * Time Complexity: O(n + m) average, O(n*m) worst case (many collisions)
 * Space Complexity: O(1)
 */
int index_of(const string& a, const string& b) {
  int n = a.size();
  int m = b.size();
  if(m>n)  return -1;
  if(m==0) return 0;
  long pat_hash  = hash_val(b,m);
  long first_hash = hash_val(a,m);  // Hash first m chars directly
  if(pat_hash==first_hash && matches(a,0,b)) {
    return 0;
  }
  long po = power(BASE,m-1);
  for(int i=1;i<n-m+1;++i) {
    rolling_hash(a,i-1,m,first_hash,po);
    if(first_hash==pat_hash && matches(a,i,b)) {
      return i;
    }
  }
  return -1;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  // Test 1: Pattern at end of string
  // "hello world", find "world" -> Expected: 6
  string s {"hello world"}; string t {"world"};
  cout<<index_of(s,t)<<"\n";
  
  // Test 2: Pattern at beginning of string
  // "needle in a haystack", find "needle" -> Expected: 0
  s = "needle in a haystack"; t = "needle";
  cout<<index_of(s,t)<<"\n";
  
  // Test 3: Pattern not in string
  // "needle in a haystack", find "not" -> Expected: -1
  s = "needle in a haystack"; t = "not";
  cout<<index_of(s,t)<<"\n";
  
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # String Matching
 * 
 * Implement an `index_of(s, t)` method, which returns the first index 
 * where string `t` appears in string `s`, or -1 if `s` does not contain `t`.
 * 
 * Example 1: s = "hello world", t = "world"
 * Output: 6
 * 
 * Example 2: s = "needle in a haystack", t = "needle"
 * Output: 0
 * 
 * Example 3: s = "needle in a haystack", t = "not"
 * Output: -1
 * 
 * Constraints:
 * - The input strings can contain any valid ASCII character
 * - The length of `s` is at most `10^5`
 * - The length of `t` is at most `10^5`
 * - `t` can be empty, in which case return `0`
 * - `s` can be empty, in which case return `-1` if `t` is non-empty, 
 *   `0` if `t` is empty
 * 
 *============================================================================*/
