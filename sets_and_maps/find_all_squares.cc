/**
 * @file find_all_squares.cc
 * @brief Find every pair of indices (i, j) where arr[i]^2 == arr[j]
 *
 * For each value we want to know whether its square also exists in the array.
 * A hash map from value -> index lets us answer "does this square exist, and
 * where?" in O(1) average time, so a single linear scan finds all pairs.
 *
 * Key Concepts:
 * - value -> index lookup table built with an unordered_map
 * - Trading O(N) extra space for O(N) lookups instead of an O(N^2) scan
 *
 * Time Complexity: O(N)
 *   - N = number of elements. Building the map is O(N); the second pass does
 *     one O(1) average hash lookup per element. (Worst case O(N^2) only under
 *     pathological hash collisions.)
 *
 * Space Complexity: O(N)
 *   - The map stores one entry per element
 */
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/**
 * @brief Return all index pairs (i, j) such that arr[i]^2 == arr[j]
 *
 * @param arr Vector of unique integers
 * @return Vector of (i, j) pairs; each i whose square arr[i]^2 exists in arr
 *         is paired with the index j of that square
 *
 * Algorithm:
 * 1. Map every value to its index so squares can be located in O(1).
 * 2. For each element, compute its square and, if that square is present,
 *    record the (current index, square's index) pair.
 */
//Time O(N)   (single linear scan with O(1) average hash lookups)
//Space O(N)  (one map entry per element)
vector<pair<int,int>> find_all_squares(vector<int>& arr) {
  unordered_map<int, int> umap;
  vector<pair<int,int>> res;
  int n = arr.size();
  for(int i=0;i<n;++i) umap[arr[i]] = i;       // value -> index lookup table
  for(int i=0;i<n;++i) {
    // arr[i] can be up to 1e9, so the square needs 64-bit width
    long int squared = (long int)arr[i] * arr[i];
    if(umap.find(squared)!= umap.end()) {
      res.push_back({i,umap[squared]});
    }
  }
  return res;
}

// To execute C++, please define "int main()"
int main() {
  vector<int> arr {4, 10, 3, 100, 5, 2, 10000};
  vector<pair<int,int>> res = find_all_squares(arr);
  for(auto& p : res) cout<<p.first<<" "<<p.second<<"\n";
  cout<<"---------------------------\n";

  arr = {1};
  res = find_all_squares(arr);
  for(auto& p : res) cout<<p.first<<" "<<p.second<<"\n";
  cout<<"---------------------------\n";
  return 0;
}

// # Find All Squares

// Given an array of unique integers, `arr`, return a list with all pairs of indices, `[i, j]`, such that `arr[i]^2 == arr[j]`. You can return the pairs in any order.

// Example 1: arr = [4, 10, 3, 100, 5, 2, 10000]
// Output: [[5, 0], [1, 3], [3, 6]]. The 3 pairs of values that satisfy the constraint are (2, 4), (10, 100), and (100, 10000). We return [5, 0] because arr[5] is 2 and arr[0] is 4, and similarly for the other two pairs. Other orders like [[1, 3], [0, 5], [3, 6]] would also be valid.

// Example 2: arr = [1]
// Output: [[0, 0]]. Since 1 is its own square, a 1 forms a pair with itself.

// Constraints:

// - The length of `arr` is at most `10^6`
// - `1 ≤ arr[i] ≤ 10^9`
// - All elements in `arr` are unique
