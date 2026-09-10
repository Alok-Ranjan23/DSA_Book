/**
 * @file count_subarrays_with_drops.cc
 * @brief Count subarrays by drop count: atMost(k), exactly(k), and atLeast(k).
 *
 * A "drop" is a pair of consecutive elements where arr[i-1] > arr[i].
 * The subarrays_atmost_k_drops helper uses a maximum sliding window tracking
 * the number of drops within the window. Each grow step contributes (r - l)
 * new subarrays. The main function derives all three counts:
 * - atMost(k):   directly from the helper
 * - exactly(k):  atMost(k) - atMost(k-1)
 * - atLeast(k):  total - atMost(k-1)
 *
 * Key Concepts:
 * - Maximum sliding window adapted for pair-based (drop) counting
 * - Drop tracking: increment on grow when arr[r-1] > arr[r],
 *   decrement on shrink when arr[l] > arr[l+1]
 * - Complement and inclusion-exclusion for exactly/atLeast
 *
 * Time Complexity: O(n) where n = arr.size(). Two O(n) passes of the helper.
 * Space Complexity: O(1) extra space.
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Counts subarrays with at most k drops (helper)
 * @param arr Vector of integers
 * @param k Maximum number of drops allowed in a subarray
 * @return Number of valid subarrays
 */
  int n = arr.size();
  int l = 0;
  int r = 0;
  int drops = 0;
  int count_subarrays = 0;
  while(r<n) {
    bool can_grow = r==0 || arr[r-1] <= arr[r] || drops < k;
    if(can_grow) {
      if(r>0 && arr[r-1]>arr[r]) drops+=1;
      r+=1;
      count_subarrays += (r-l);
    } else {
      if(arr[l]>arr[l+1]) drops-=1;
      l+=1;
    }
  }
  return count_subarrays;
}

/**
 * @brief Computes atMost(k), exactly(k), and atLeast(k) drop counts for all subarrays
 * @param arr Vector of integers
 * @param k Target number of drops
 * @return Vector of 3 ints: {atMost(k), exactly(k), atLeast(k)}
 */
vector<int> count_subarrays_with_drops(vector<int>& arr, int k) {
  int atMostkDrops = subarrays_atmost_k_drops(arr,k);
  int atMostkMinusOneDrops = (k==0) ? 0 : subarrays_atmost_k_drops(arr,k-1);
  int exactlyKDrops = atMostkDrops - atMostkMinusOneDrops;
  int n = arr.size();
  int total_subarrays = n*(n+1)/2;
  int atLeastkDrops = total_subarrays - atMostkMinusOneDrops;
  return vector<int>({atMostkDrops,exactlyKDrops,atLeastkDrops});
}

// To execute C++, please define "int main()"
int main() {
  vector<int> arr {1,2,3}; int k=1;
  for(auto& val: count_subarrays_with_drops(arr,k)) cout<<val<<" ";
  cout<<"\n";
  arr = {3,2,1}; k=1;
  for(auto& val: count_subarrays_with_drops(arr,k)) cout<<val<<" ";
  cout<<"\n";
  arr = {5,4,3,2,1}; k=2;
  for(auto& val: count_subarrays_with_drops(arr,k)) cout<<val<<" ";
  cout<<"\n";
  return 0;
}

// # Count Subarrays With Drops

// Given an array, `arr`, of integers and a number `k`, count how many subarrays have:

// 1. at most `k` drops
// 2. exactly `k` drops
// 3. at least `k` drops

// A _drop_ is a sequence of two consecutive numbers where the first is larger than the second.

// Return an array with the three values.

// Example 1: arr = [1, 2, 3], k = 1
// Output: [6, 0, 0]
// - The array has 6 subarrays: [1], [2], [3], [1, 2], [2, 3], and [1, 2, 3].
// - At most k drops:  6. The array has no drops, so every subarray has 0 drops.
// - Exactly k drops:  0. The array has no drops.
// - At least k drops: 0. The array has no drops.

// Example 2: arr = [3, 2, 1], k = 1
// Output: [5, 2, 3]
// - The array has 6 subarrays: [3], [2], [1], [3, 2], [2, 1], and [3, 2, 1].
// - At most k drops:  5. [3, 2] and [2, 1] have 1 drop and [3], [2], and [1] have 0 drops.
// - Exactly k drops:  2. [3, 2] and [2, 1] have exactly 1 drop.
// - At least k drops: 3. [3, 2] and [2, 1] have 1 drop and [3, 2, 1] has 2 drops.

// Example 3: arr = [5, 4, 3, 2, 1], k = 2
// Output: [12, 3, 6]
// - The array has 5 + 4 + 3 + 2 + 1 = 15 subarrays.
// - At most k drops: 12. All the subarrays with 1, 2, or 3, elements.
// - Exactly k drops:  3. All the subarrays with 3 elements: [5, 4, 3], [4, 3, 2], and [3, 2, 1].
// - At least k drops: 6. All the subarrays with 3, 4, or 5 elements.

// Constraints:

// - `0 <= arr.length <= 10^5`
// - `-10^9 <= arr[i] <= 10^9`
// - `0 <= k <= 10^5`
