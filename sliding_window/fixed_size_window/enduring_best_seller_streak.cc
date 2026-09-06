/**
 * @file enduring_best_seller_streak.cc
 * @brief Check if there is any k-day period with the same best-selling title
 * 
 * We use a fixed-size sliding window to keep track of the frequencies of 
 * best-selling books in the current window of length k.
 * 
 * Key Concepts:
 * - Fixed-size sliding window
 * - Hash map to track frequencies of elements in the window
 * - If the window size is k and the hash map size is 1, all elements are identical
 * 
 * Time Complexity: O(n * L) where n is the length of the array and L is max string length
 * Space Complexity: O(k * L) to store the window elements in the hash map
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

/**
 * @brief Determines if there is a k-day streak of the exact same best seller
 * @param best_seller Vector containing the best-selling book title for each day
 * @param k The required length of the streak
 * @return true if a k-day streak exists, false otherwise
 */

bool enduring_seller_streak(vector<string>& best_seller,int k) {
  int n = best_seller.size();
  int l = 0;
  int r = 0;
  unordered_map<string, int> umap;
  while(r<n) {
    umap[best_seller[r]]++;
    r+=1;
    if(r-l==k) {
      if(static_cast<int>(umap.size())==1) return true;
      umap[best_seller[l]]--;
      if(umap[best_seller[l]]==0) umap.erase(best_seller[l]);
      l+=1;
    }
  }
  return false;
}

// To execute C++, please define "int main()"
int main() {
  vector<string>best_seller {"book3", "book1", "book3", "book3", "book2"}; int k = 3;
  cout<<boolalpha;cout<<enduring_seller_streak(best_seller,k)<<"\n";
  best_seller = {"book3", "book1", "book3", "book3", "book2"}; k = 2;
  cout<<enduring_seller_streak(best_seller,k)<<"\n";
  best_seller = {"book1", "book2", "book1"}; k = 2;
  cout<<enduring_seller_streak(best_seller,k)<<"\n";
  best_seller = {"book1", "book1", "book1"}; k = 3;
  cout<<enduring_seller_streak(best_seller,k)<<"\n";
  return 0;
}

// # Enduring Best Seller Streak

// We are given an array, `best_seller`, with the title of the most sold book for each day over a given period. We are also given a number `k` with `1 ≤ k ≤ len(sales)`.

// We need to return whether there is any k-day period where every day has the **same** best-selling title.

// Example 1:
// best_seller = ["book3", "book1", "book3", "book3", "book2"]
// k = 3

// Output: False
// No three consecutive days have the same best seller.

// Example 2:
// best_seller = ["book3", "book1", "book3", "book3", "book2"]
// k = 2

// Output: True
// Days 3-4 have the same best seller "book3".

// Example 3:
// best_seller = ["book1", "book2", "book1"]
// k = 2

// Output: False
// No two consecutive days have the same best seller.

// Example 4:
// best_seller = ["book1", "book1", "book1"]
// k = 3

// Output: True
// The entire array has the same best seller.

// Constraints:

// - The length of `best_seller` is at most `10^6`
// - Each book title has length at most `100`
// - `1 <= k <= len(best_seller)`
