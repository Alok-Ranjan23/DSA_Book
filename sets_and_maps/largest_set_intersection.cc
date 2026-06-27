/**
 * @file largest_set_intersection.cc
 * @brief Pick the set to drop so the remaining sets' intersection is largest
 *
 * Removing set i, an element survives in the intersection of the other k-1
 * sets only if it appears in all of them. By total frequency that means the
 * element appears in either k sets (always survives) or exactly k-1 sets (only
 * survives if i is the one set missing it). Counting frequencies once lets us
 * score every candidate i in linear total time.
 *
 * Key Concepts:
 * - value_count[x] = number of sets that contain x (built in one pass)
 * - intersection_size(i) = C_k + (M - present_{k-1}(i)), where C_k = #elements
 *   with count k, M = #elements with count k-1, and present_{k-1}(i) = those
 *   count-(k-1) elements that lie inside set i
 * - C_k and M are constant across i, so maximizing the intersection is the same
 *   as minimizing present_{k-1}(i); we return the smallest such index
 *
 * Time Complexity: O(T + k)
 *   - T = total elements across all sets, k = number of sets. Building the
 *     frequency map is O(T); the scoring loop visits every element once more
 *     (O(T)) plus O(k) bookkeeping. Hash ops are O(1) average.
 *
 * Space Complexity: O(D) <= O(T)
 *   - The frequency map stores one entry per distinct value.
 */
#include <iostream>
#include <unordered_map>
#include <vector>
#include <climits>
using namespace std;

/**
 * @brief Index of the set whose removal maximizes the remaining intersection
 *
 * @param sets Non-empty list of sets (each holds unique integers)
 * @return Index to exclude for the largest intersection; smallest index on tie
 *
 * Algorithm:
 * 1. Count, for every value, how many sets contain it.
 * 2. For each set i, count its elements that appear in exactly k-1 sets
 *    (these are the only ones whose survival depends on excluding i).
 * 3. The set with the fewest such elements yields the largest intersection;
 *    a strict "<" keeps the smallest index on ties.
 */
//Time O(T + k)   (T = total elements, k = number of sets; O(1) average hashing)
//Space O(D) <= O(T)  (one map entry per distinct value)
int largest_set_intersection(vector<vector<int>>& sets) {
  //Frequency Map
  unordered_map<int, int> value_count;
  for(auto& vec: sets) {
    for(auto& x: vec) value_count[x]++;       // O(T): count containing sets per value
  }
  int counter = INT_MAX;
  int index = INT_MAX;
  int k = sets.size();
  for(int i=0;i<k;++i) {
    int count_k = 0;
    for(auto& x: sets[i]) {
      // count-(k-1) elements survive only if THIS set is the one excluded
      if(value_count[x]==k-1) count_k+=1;
    }
    if(count_k<counter) {                       // fewer => larger intersection
      counter = count_k;
      index = i;
    }
  }
  return index;
}

// To execute C++, please define "int main()"
int main() {
  vector<vector<int>> sets {{1, 2, 3}, {3, 2, 1}, {1, 4, 5}, {1, 2}};
  cout<<largest_set_intersection(sets)<<"\n";
  sets = {{1, 2}, {3, 4}, {5, 6}};
  cout<<largest_set_intersection(sets)<<"\n";
  sets = {{1, 2, 3}, {4, 5}};
  cout<<largest_set_intersection(sets)<<"\n";
  sets = {{1, 2, 3}};
  cout<<largest_set_intersection(sets)<<"\n";
  return 0;
}

// # Largest Set Intersection

// You are given a non-empty array, `sets`, where each element is an array of unique integers representing a set.
// The _intersection_ of a list of sets is the set of elements that appears in every set.
// Return the index of the set that should be excluded to maximize the size of the intersection of the remaining sets.
// In case of a tie, return the smallest index.

// Example 1: sets = [[1, 2, 3], [3, 2, 1], [1, 4, 5], [1, 2]]
// Output: 2
// Explanation: Excluding the third set (index 2)
// yields a set intersection of size 2: {1, 2}.

// Example 2: sets = [[1, 2], [3, 4], [5, 6]]
// Output: 0
// Explanation: The sets don't have any elements in common,
// so the intersection will be empty regardless of which set you exclude.

// Example 3: sets = [[1, 2, 3], [4, 5]]
// Output: 1
// Explanation: After excluding a set, there will be only one set left,
// so the intersection is the remaining set.

// Example 4: sets = [[1, 2, 3]]
// Output: 0
// Explanation: There is only one set, so after excluding it,
// the intersection is empty.

// Constraints:

// - `1 ≤ sets.length ≤ 10^5`
// - `0 ≤ sets[i].length ≤ 10^5`
// - The total number of elements across all sets is at most `10^5`
// - All integers in each set are unique
// - `-10^9 ≤ sets[i][j] ≤ 10^9`
