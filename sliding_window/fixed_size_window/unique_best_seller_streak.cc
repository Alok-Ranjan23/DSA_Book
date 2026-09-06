/**
 * @file unique_best_seller_streak.cc
 * @brief Check if there is any k-day period with unique best-selling titles
 * 
 * We use a fixed-size sliding window to keep track of the frequencies of 
 * best-selling books in the current window of length k.
 * 
 * Key Concepts:
 * - Fixed-size sliding window
 * - Hash map to track frequencies of elements in the window
 * - If the window size is k and the hash map size is also k, all elements are unique
 * 
 * Time Complexity: O(n * L) where n is the length of the array and L is max string length
 * Space Complexity: O(k * L) to store up to k unique window elements in the hash map
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

/**
 * @brief Determines if there is a k-day streak where every day has a different best seller
 * @param best_seller Vector containing the best-selling book title for each day
 * @param k The required length of the streak
 * @return true if a k-day streak of unique books exists, false otherwise
 */

bool unique_seller_streak(vector<string>& best_seller,int k) {
  int n = best_seller.size();
  int l = 0;
  int r = 0;
  unordered_map<string, int> umap;
  while(r<n) {
    umap[best_seller[r]]++;
    r+=1;
    if(r-l==k) {
      if(static_cast<int>(umap.size())==k) return true;
      umap[best_seller[l]]--;
      if(umap[best_seller[l]]==0) umap.erase(best_seller[l]);
      l+=1;
    }
  }
  return false;
}

// To execute C++, please define "int main()"
int main() {
  vector<string>best_seller {"book3", "book1", "book3", "book3", "book2", "book3", "book4", "book3"}; int k = 3;
  cout<<boolalpha;cout<<unique_seller_streak(best_seller,k)<<"\n";
  best_seller = {"book3", "book1", "book3", "book3", "book2", "book3", "book4", "book3"}; k = 4;
  cout<<unique_seller_streak(best_seller,k)<<"\n";
  best_seller = {"book1", "book2", "book3"}; k = 3;
  cout<<unique_seller_streak(best_seller,k)<<"\n";
  return 0;
}

// # Unique Best Seller Streak

// We are given an array, `best_seller`, with the title of the most sold book for each day over a given period. We are also given a number `k` with `1 ≤ k ≤ len(sales)`.

// We need to return whether there is any k-day period where each day has a **different** best-selling title.

// Example 1:
// best_seller = ["book3", "book1", "book3", "book3", "book2", "book3", "book4", "book3"]
// k = 3

// Output: True
// There is a 3-day period without a repeated value: ["book2", "book3", "book4"]

// Example 2:
// best_seller = ["book3", "book1", "book3", "book3", "book2", "book3", "book4", "book3"]
// k = 4

// Output: False
// There are no 4-day periods without a repeated value

// Example 3:
// best_seller = ["book1", "book2", "book3"]
// k = 3

// Output: True
// The entire array has no repeated values

// Constraints:

// - The length of `best_seller` is at most `10^6`
// - Each book title has length at most `100`
// - `1 <= k <= len(best_seller)`
