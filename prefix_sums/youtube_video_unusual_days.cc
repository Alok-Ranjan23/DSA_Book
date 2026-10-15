/**
 * @file youtube_video_unusual_days.cc
 * @brief Highest total deviation of any day, where total deviation of day i
 *        is the sum over all days j of |score[i] - score[j]|
 *
 * Brute force compares every pair of days: O(n^2). The abs() is what blocks
 * prefix sums, so sort the scores first. In sorted order, every score to
 * the left of i is <= score[i] and every score to the right is >= score[i],
 * so each |difference| has a known sign and the sum splits into
 *   left  part = score[i] * i            - sum(score[0..i-1])
 *   right part = sum(score[i+1..n-1])    - score[i] * (n-1-i)
 * Both range sums come from one prefix-sum array in O(1).
 *
 * Key Concepts:
 * - Sort to remove abs(): order is irrelevant to each day's total
 *   deviation, it only fixes the sign of every difference
 * - Prefix sum of size n+1 with prefix[0] = 0, so no l == 0 special case:
 *   left sum = prefix[i], right sum = prefix[n] - prefix[i+1]
 * - long long: the answer can reach ~99,999 * 19,998 ~= 2 * 10^9, right at
 *   the int limit
 * - Pattern: "sum of absolute differences" = sort + prefix sums
 *
 * Time Complexity: O(n log n)
 *   - Sorting dominates; building the prefix array and the final scan are
 *     O(n).
 *
 * Space Complexity: O(n)
 *   - The score and prefix arrays.
 */
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Return the maximum total deviation over all days
 *
 * @param likes    Likes per day (length n)
 * @param dislikes Dislikes per day (length n)
 * @return         max over i of sum_j |score[i] - score[j]|, 0 if n == 0
 *
 * Algorithm:
 * 1. score[i] = likes[i] - dislikes[i]; sort score.
 * 2. prefix[i+1] = prefix[i] + score[i].
 * 3. For each i, deviation = (score[i]*i - prefix[i])
 *                          + (prefix[n] - prefix[i+1] - score[i]*(n-1-i));
 *    keep the maximum.
 *
 * Time:  O(n log n) -- sort, then linear passes
 * Space: O(n)       -- score + prefix
 */
//Time O(n log n)  (sort + linear prefix pass + linear scan)
//Space O(n)       (score + prefix arrays)
long long max_deviation(vector<int>& likes,vector<int>& dislikes) {
  int n = likes.size();
  if(n==0) return 0;

  // Step 1: reception score of each day.
  vector<long long> score(n);
  for(int i=0;i<n;++i) {
    score[i] = likes[i] - dislikes[i];
  }

  // Step 2: sort, so for score[i] everything on the left is <= it and
  // everything on the right is >= it. This lets us drop the abs().
  sort(score.begin(), score.end());

  // Step 3: prefix sums. prefix[i] = score[0] + ... + score[i-1], prefix[0] = 0.
  vector<long long> prefix(n+1, 0);
  for(int i=0;i<n;++i) {
    prefix[i+1] = prefix[i] + score[i];
  }

  // Step 4: total deviation of each day in O(1) using the prefix sums.
  long long best = 0;
  for(int i=0;i<n;++i) {
    long long left_count  = i;              // days with score <= score[i]
    long long right_count = n-1-i;          // days with score >= score[i]
    long long left_sum    = prefix[i];                // score[0..i-1]
    long long right_sum   = prefix[n] - prefix[i+1];  // score[i+1..n-1]

    long long left_part  = score[i]*left_count - left_sum;    // sum of (score[i] - score[j])
    long long right_part = right_sum - score[i]*right_count;  // sum of (score[j] - score[i])

    best = max(best, left_part + right_part);
  }
  return best;
}

// To execute C++, please define "int main()"
int main() {
  vector<int> likes    {3,6,1};
  vector<int> dislikes {0,1,9};
  cout<<max_deviation(likes,dislikes)<<"\n";
  return 0;
}

// # YouTube Video Unusual Days

// A YouTuber has fetched the number of likes and dislikes of a video each day since its publication, with the goal of finding days with unusually high or low like-to-dislike ratios.

// We are given two arrays, `likes` and `dislikes`, of length `n`, representing the likes and dislikes on each day.

// The _reception score_ of a day is the number of likes minus the number of dislikes. The _deviation_ between two days is the absolute value of the difference in their reception scores. The _total deviation_ of a given day is the sum of the deviations between it and every other day.

// Find the highest _total deviation_ of any day and return it.

// Example:
// likes    = [3, 6, 1]
// dislikes = [0, 1, 9]

// Output: 24
// The reception scores are [3, 5, -8]. The total deviation of each day is:
// day 0: |3 - 5| + |3 - (-8)| = 2 + 11 = 13
// day 1: |5 - 3| + |5 - (-8)| = 2 + 13 = 15
// day 2: |-8 - 3| + |-8 - 5| = 11 + 13 = 24

// Constraints:

// - The length of `likes` and `dislikes` is at most `10^5`
// - Each element in `likes` and `dislikes` is a non-negative integer less than `10^4`
