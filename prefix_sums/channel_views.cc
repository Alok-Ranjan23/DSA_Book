/**
 * @file channel_views.cc
 * @brief Answer many range-sum queries: total views in each period [l, r]
 *
 * The textbook prefix-sum problem. Summing each period directly costs
 * O(r - l + 1) per query. Precompute prefix_sum[i] = views[0] + ... +
 * views[i] once; then any range sum is a difference of two prefix values.
 *
 * Key Concepts:
 * - Inclusive prefix sum: prefix_sum[i] covers views[0..i]
 * - Range sum [l, r] = prefix_sum[r] - prefix_sum[l-1]
 * - l == 0 is a special case (no prefix_sum[-1]); a size n+1 prefix array
 *   with prefix[0] = 0 would remove this branch
 *
 * Time Complexity: O(n + p)
 *   - O(n) to build the prefix array, then O(1) per query (p queries).
 *     Naive summing would be O(n * p).
 *
 * Space Complexity: O(n)
 *   - The prefix array (plus the p results returned).
 */
#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Return the number of views in each period
 *
 * @param views   Views per day (length n > 0)
 * @param periods Pairs [l, r] with 0 <= l <= r < n, both inclusive
 * @return        res[i] = views[l] + ... + views[r] for periods[i]
 *
 * Algorithm:
 * 1. Build prefix_sum[i] = prefix_sum[i-1] + views[i].
 * 2. For each [l, r]: answer is prefix_sum[r] if l == 0, otherwise
 *    prefix_sum[r] - prefix_sum[l-1].
 *
 * Time:  O(n + p) -- linear build + O(1) per query
 * Space: O(n)     -- prefix array
 */
//Time O(n + p)  (build once, O(1) per query)
//Space O(n)     (prefix array)
vector<int> channel_views(vector<int>& views,vector<pair<int,int>>& periods) {
  vector<int> res;
  int n = views.size();
  vector<int> prefix_sum(n,0);                     // prefix_sum[i] = views[0..i]
  prefix_sum[0] = views[0];
  for(int i=1;i<n;++i) prefix_sum[i] = prefix_sum[i-1] + views[i];
  for(auto & p : periods) {
    int l = p.first;
    int r = p.second;
    if(l==0) res.push_back(prefix_sum[r]);         // whole prefix
    else res.push_back(prefix_sum[r]-prefix_sum[l-1]);  // views[l..r]
  }
  return res;
}

// To execute C++, please define "int main()"
int main() {
  vector<int> views {3, 5, 4, 8, 7, 2, 5, 3, 2, 3};
  vector<pair<int,int>> periods {{0,1},{0,5},{5,8},{3,3}};
  for (auto& x: channel_views(views,periods)) {cout<<x<<" ";}cout<<"\n";
  return 0;
}

// # Channel Views

// A YouTuber wants to analyze their channel's performance to see if viewer engagement varies during certain times of the year. We are given:

// - An array, `views`, of length `n > 0`, where `views[i]` represents the number of views on day `i`.
// - An array, `periods`, of length `p > 0`, where each element is a pair `[l, r]` with `0 ≤ l ≤ r < n`. Each pair represents a time period from day `l` to day `r` _inclusive_.

// Return an array, `results`, of integers with length `p`, where `result[i]` is the number of views during period `i`.

// Example:
// views = [3, 5, 4, 8, 7, 2, 5, 3, 2, 3]
// periods = [[0, 1], [0, 5], [5, 8], [3, 3]]

// Output: [8, 29, 12, 8]
// For instance, element 0 is 8 because 3 + 5 = 8.

// Constraints:

// - The length of `views` is at most `10^5`
// - `0 <= views[i] < 10^4`
// - The length of `periods` is at most `10^5`
// - `periods[i].length == 2`
// - `0 <= periods[i][0] <= periods[i][1] < n`
