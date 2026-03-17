/**
 * @file frequency_sort.cc
 * @brief Sort Characters by Frequency using Bucket Sort
 * 
 * This file implements a function that sorts the unique characters of a
 * string from most frequent to least frequent, breaking ties alphabetically.
 * Uses bucket sort for optimal O(N + K) time complexity.
 * 
 * Key Concepts:
 * - Counting Array: 26-element array for lowercase letter frequencies
 * - Bucket Sort: Index = frequency count, bucket holds characters with
 *   that frequency. Avoids comparison-based O(K log K) sorting.
 * - Lexicographic Tie-Breaking: Scanning counters left-to-right (a..z)
 *   naturally inserts characters alphabetically within same-frequency buckets
 * 
 * Algorithm:
 * 1. Count frequency of each character in the input string: O(N)
 * 2. Track the highest frequency seen (determines bucket array size)
 * 3. Create buckets[0..highest_count], each holding a queue of char indices
 * 4. Fill buckets: for each char (a-z), place it in buckets[its_count]: O(26)
 * 5. Traverse buckets from highest to lowest, collecting characters: O(N)
 * 
 * Why Bucket Sort over Heap / std::sort?
 * - Heap approach: O(N + K log K) where K = 26 unique chars
 * - Bucket sort: O(N + K) — avoids log factor entirely
 * - Since K = 26 is constant, both are O(N), but bucket sort has smaller constants
 * - Scanning a..z during bucket filling gives free alphabetical tie-breaking
 * 
 * Time Complexity: O(N + K) where N = input length, K = 26 (alphabet size)
 * Space Complexity: O(N) for the bucket storage
 */

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <queue>
using namespace std;

/*============================================================================
 * FUNCTION IMPLEMENTATION
 *============================================================================*/

/**
 * @brief Sorts unique characters of a string by frequency (descending),
 *        breaking ties alphabetically
 * @param input The input string of lowercase letters
 * @return Vector of characters sorted by frequency (most to least frequent)
 * 
 * Step 1 - Frequency Count: O(N)
 *   Count occurrences of each letter using a 26-element array.
 *   Also track the maximum frequency for bucket array sizing.
 * 
 * Step 2 - Bucket Creation:
 *   Create (highest_count + 1) buckets. Each bucket[i] is a queue
 *   holding characters that appear exactly i times.
 * 
 * Step 3 - Fill Buckets: O(26)
 *   For each character index 0..25 with non-zero count, push it into
 *   the corresponding bucket. Left-to-right scan ensures alphabetical
 *   order within each bucket.
 * 
 * Step 4 - Collect Results: O(N)
 *   Traverse buckets from highest index to 1, popping characters.
 *   Characters with higher frequency appear first.
 * 
 * Time Complexity: O(N + K) = O(N), K = 26 is constant
 */
vector<char> sort_by_freq(string& input) {
  vector<int> counter(26,0);
  int highest_count = 0;
  for(auto &c: input) {
    highest_count = max(highest_count, ++counter[c-'a']);
  }

  vector<queue<int>> bucket (highest_count + 1);

  for(int i=0;i<26;++i) {
    if(counter[i]!=0) {
      bucket[counter[i]].push(i);
    }
  }

  vector<char> results;
  for(int i=highest_count;i>0;--i) {
    while(!bucket[i].empty()) {  
      results.push_back(bucket[i].front()+'a'); 
      bucket[i].pop();
    }
  }
  return results;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Test 1: Mixed frequencies — expected: i,a,c,l,s,e,o,p,r,u,d,f,g,t,x
  string word = "supercalifragilisticexpialidocious";
  vector<char> res = sort_by_freq(word);
  for(auto&x : res) cout<<x<<" ";
  cout<<"\n";

  // Test 2: Distinct frequencies — expected: c,b,a (4,3,2)
  word = "aabbbcccc";
  res = sort_by_freq(word);
  for(auto&x : res) cout<<x<<" ";
  cout<<"\n";

  // Test 3: All same frequency — expected: a,b,c (alphabetical tie-break)
  word = "abc";
  res = sort_by_freq(word);
  for(auto&x : res) cout<<x<<" ";
  cout<<"\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Sorting By Frequency
 * 
 * Given a string, `word`, consisting of lowercase letters only, return a
 * sorted array with all the letters in `word` sorted from most frequent to
 * least frequent. If two frequencies are the same, break the tie alphabetically.
 * 
 * Constraints:
 * - The length of `word` is at most 10^5
 * - `word` contains only lowercase letters
 * 
 *============================================================================*/
