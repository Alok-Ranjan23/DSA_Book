/**
 * @file atmost_k_unique.cc
 * @brief Find the longest subarray containing at most k distinct elements.
 *
 * A maximum sliding window is used with a hash map to track the frequency of each
 * distinct element in the current window. The window grows while the number of distinct
 * elements is <= k; otherwise it shrinks from the left.
 *
 * Key Concepts:
 * - Maximum sliding window with hash map for distinct-count tracking
 * - No l == r guard needed: an empty window always has 0 distinct elements (< k, since k >= 1)
 *
 * Time Complexity: O(n * L) where n = best_seller.size() and L is the max string length
 *   (due to hashing). Each element is visited at most twice.
 * Space Complexity: O(k * L) for the hash map storing up to k distinct entries.
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

/**
 * @brief Finds the longest period with at most k distinct best-selling books
 * @param best_seller Vector of daily best-selling book titles
 * @param k Maximum number of distinct titles allowed in the window
 * @return Length of the longest valid period
 */
  int n = best_seller.size();
  int l = 0;
  int r = 0;
  unordered_map<string, int> umap;
  int max_window = 0;
  while(r<n) {
    bool can_grow = umap.count(best_seller[r]) || static_cast<int>(umap.size()) < k;
    if(can_grow) {
      umap[best_seller[r]]++;
      r+=1;
      max_window = max(max_window,r-l);
    }
    else {
      umap[best_seller[l]]--;
      if(umap[best_seller[l]]==0) umap.erase(best_seller[l]);
      l+=1;
    }
  }
  return max_window;
}
// To execute C++, please define "int main()"
int main() {
  vector<string> best_seller {"book1", "book1", "book2", "book1", "book3", "book1"}; int k = 2;
  cout<<atmost_k_distinct(best_seller,k)<<"\n";
  best_seller = {"book1", "book2", "book3"}; k = 1;
  cout<<atmost_k_distinct(best_seller,k)<<"\n";
  best_seller = {"book1", "book1", "book1"}; k = 2;
  cout<<atmost_k_distinct(best_seller,k)<<"\n";
  return 0;
}

// # Longest Period At Most K Distinct

// We are given an array of strings, `best_seller`, where `best_seller[i]` is the title of the most sold book for day `i`, and a number `k ≥ 1`.

// Find the maximum consecutive days with at most `k` **distinct** best-selling books.

// Example 1:
// best_seller = ["book1", "book1", "book2", "book1", "book3", "book1"]
// k = 2

// Output: 4
// The subarray ["book1", "book1", "book2", "book1"] contains only 2 distinct titles

// Example 2:
// best_seller = ["book1", "book2", "book3"]
// k = 1

// Output: 1
// Each day has a different best seller

// Example 3:
// best_seller = ["book1", "book1", "book1"]
// k = 2

// Output: 3
// The entire array has only 1 distinct title

// Constraints:

// - `0 <= len(best_seller) <= 10^6`
// - `1 <= k <= len(best_seller)`
// - `1 <= len(best_seller[i]) <= 100`
