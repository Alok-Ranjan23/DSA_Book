/**
 * @file segmented_video_votes.cc
 * @brief Net vote count at every minute after applying range votes
 *
 * Each vote [l, r, v] adds v (+1 or -1) to every minute in [l, r]. Instead
 * of looping over each range, record +v at l and -v at r+1 in a difference
 * array. The prefix sum of the difference array is the final net vote per
 * minute.
 *
 * Key Concepts:
 * - Difference array: the inverse of a prefix sum. A range add becomes two
 *   point updates; one prefix pass applies all of them at once
 * - r+1 == n is skipped, since the range runs to the end of the video
 * - Order of votes does not matter (addition is commutative)
 *
 * Time Complexity: O(n + m)
 *   - O(1) per vote (m votes) and one O(n) prefix pass. Applying each range
 *     directly would be O(n * m).
 *
 * Space Complexity: O(n)
 *   - The diff array and the returned prefix_sum array.
 */
#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Return the net vote count for each minute of the video
 *
 * @param votes Votes, each [l, r, v] with 0 <= l <= r < n and v in {1, -1}
 * @param n     Video length in minutes (n >= 1)
 * @return      Vector of length n with the net votes at each minute
 *
 * Algorithm:
 * 1. For every vote, diff[l] += v and (if r+1 < n) diff[r+1] -= v.
 * 2. prefix_sum[i] = diff[0] + ... + diff[i]; return prefix_sum.
 *
 * Time:  O(n + m) -- O(1) per vote + one prefix pass
 * Space: O(n)     -- diff + result
 */
//Time O(n + m)  (O(1) per vote + one prefix pass)
//Space O(n)     (diff + result)
vector<int> segmented_video_votes(vector<vector<int>>& votes, int n) {
  vector<int>diff(n);                              // difference array of votes
  for(auto& vote: votes) {
    int l = vote[0];
    int r = vote[1];
    int v = vote[2];
    diff[l] += v;                                  // range starts at l
    if(r+1<n) diff[r+1]-=v;                        // range stops after r
  }
  vector<int> prefix_sum (n);                      // prefix_sum[i] = net votes at minute i
  prefix_sum[0] = diff[0];
  for(int i=1;i<n;++i) {
    prefix_sum[i] = prefix_sum[i-1] + diff[i];
  }
  return prefix_sum;
}

// To execute C++, please define "int main()"
int main() {
  vector<vector<int>> votes {{3, 4, 1},{0, 0, 1},{1, 3, 1},{0, 5, -1}};int n = 6; 
  for(auto& val: segmented_video_votes(votes,n)) {cout<<val<<" ";} cout<<"\n";  
  return 0;
}

// # Segmented Video Votes

// YouTube is testing an experimental API that allows users to like or dislike specific segments of a video instead of the entire video. You are provided with:

// `n`: the length of the video in minutes.

// `votes`: an array where each element represents a user's vote and is structured as an array with 3 integers:

// - `l`: the starting minute of the vote (inclusive)
// - `r`: the ending minute of the vote (inclusive)
// - `v`: the vote value (1 for like, -1 for dislike)

// Each vote satisfies `0 ≤ l ≤ r < n`. The votes can be in any order and may overlap.
// Your task is to return an array of length `n`, where each index `i` contains the _net vote count_ at minute `i`.

// Example:
// n = 6
// votes = [
//   [3, 4, 1],
//   [0, 0, 1],
//   [1, 3, 1],
//   [0, 5, -1]
// ]

// Output: [0, 0, 0, 1, 0, -1]
// The net vote counts after applying each vote are:

// - [0, 0, 0, 1, 1, 0]
// - [1, 0, 0, 1, 1, 0]
// - [1, 1, 1, 2, 1, 0]
// - [0, 0, 0, 1, 0, -1]

// Constraints:

// - `1 <= n <= 10^5`
// - `0 <= votes.length <= 10^5`
// - `votes[i].length` is `3`
// - `0 <= votes[i][0] <= votes[i][1] < n`
// - `votes[i][2]` is either `1` or `-1`
