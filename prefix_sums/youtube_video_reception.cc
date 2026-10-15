/**
 * @file youtube_video_reception.cc
 * @brief Number of positive days (likes > dislikes) in each period [l, r]
 *
 * Turn each day into a 0/1 flag (1 if positive), then the question "how
 * many positive days in [l, r]?" becomes a range sum over those flags. A
 * prefix sum of the flags answers every period in O(1).
 *
 * Key Concepts:
 * - Prefix COUNT: a prefix sum over a boolean condition counts how many
 *   elements satisfy it in any range
 * - (likes[i] > dislikes[i]) converts to 1 or 0 when added to an int
 * - Range count [l, r] = positive_arr[r] - positive_arr[l-1], with l == 0
 *   handled separately
 *
 * Time Complexity: O(n + p)
 *   - O(n) to build the prefix counts, then O(1) per period (p periods).
 *
 * Space Complexity: O(n)
 *   - The prefix count array (plus the p results returned).
 */
#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Return the number of positive days in each period
 *
 * @param likes    Likes per day (length n)
 * @param dislikes Dislikes per day (length n)
 * @param periods  Pairs [l, r] with 0 <= l <= r < n, both inclusive
 * @return         res[i] = count of days d in periods[i] with likes > dislikes
 *
 * Algorithm:
 * 1. positive_arr[i] = number of positive days in [0, i].
 * 2. For each [l, r]: answer is positive_arr[r] if l == 0, otherwise
 *    positive_arr[r] - positive_arr[l-1].
 *
 * Time:  O(n + p) -- linear build + O(1) per query
 * Space: O(n)     -- prefix count array
 */
//Time O(n + p)  (build once, O(1) per query)
//Space O(n)     (prefix count array)
vector<int> youtube_video_reception(vector<int>& likes,vector<int>& dislikes,vector<pair<int,int>>& periods) {
  vector<int> res;
  int n = likes.size();
  vector<int> positive_arr(n);                     // positive days in [0, i]
  positive_arr[0] = likes[0]>dislikes[0];          // bool -> 0/1
  for(int i=1;i<n;++i) positive_arr[i] = positive_arr[i-1] + (likes[i]>dislikes[i]);
  for(auto & p : periods) {
    int l = p.first;
    int r = p.second;
    if(l==0) res.push_back(positive_arr[r]);       // whole prefix
    else res.push_back(positive_arr[r]-positive_arr[l-1]);  // days l..r
  }
  return res;
}

// To execute C++, please define "int main()"
int main() {
  vector<int> likes {6, 3, 4, 8, 7, 2, 6, 5, 0, 1};
  vector<int> dislikes {6, 0, 8, 0, 0, 0, 1, 8, 0, 2};
  vector<pair<int,int>> periods {{0,1},{0,5},{5,8},{3,3}};
  for (auto& x: youtube_video_reception(likes,dislikes,periods)) {cout<<x<<" ";}cout<<"\n";
  return 0;
}

// # YouTube Video Reception

// A YouTuber has fetched the number of likes and dislikes of a video each day since its publication. We say a day is _positive_ if it has more likes than dislikes.

// We are given:

// - Two arrays, `likes` and `dislikes`, of length `n`, representing the likes and dislikes on each day.
// - An array `periods` of length `p`, where each element is a pair `[l, r]` with `0 ≤ l ≤ r < n`. Each pair represents a time period from day `l` to day `r` _inclusive_.

// Return an array, `results`, of length `p`, where `results[i]` is the number of positive days during `period[i]`.

// Example:
// likes    = [6, 3, 4, 8, 7, 2, 6, 5, 0, 1]
// dislikes = [6, 0, 8, 0, 0, 0, 1, 8, 0, 2]
// periods  = [[0, 1], [0, 5], [5, 8], [3, 3]]

// Output: [1, 4, 2, 1]
// For instance, element 0 (for the period [0, 1]) is 1 because
// day 0 doesn't have more likes than dislikes, but day 1 does.

// Constraints:

// - The length of `likes` and `dislikes` is the same and is at most `10^5`
// - Each element in `likes` and `dislikes` is a non-negative integer less than `10^4`
// - The length of `periods` is at most `10^5`
// - `periods[i].length == 2`
// - `0 <= periods[i][0] <= periods[i][1] < n`
