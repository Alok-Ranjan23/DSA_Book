/**
 * @file all_overbooked_slots.cc
 * @brief Count the slots whose total bookings exceed the capacity after
 *        applying a list of range (bulk) bookings
 *
 * Each bulk booking [l, r, c] adds c to every slot in [l, r]. Applying them
 * one by one is O(n) per booking. Instead, use a difference array: record
 * +c at l and -c at r+1, then a single prefix-sum pass turns the difference
 * array into the actual number of new bookings per slot.
 *
 * Key Concepts:
 * - Difference array: diff[l] += c, diff[r+1] -= c marks where a range
 *   update starts and stops; the prefix sum of diff rebuilds the values
 * - r+1 == n is skipped, since the range runs to the end of the array
 * - Final load of slot i = existing slots[i] + prefix_sum[i]; overbooked
 *   when that is strictly greater than cap
 *
 * Time Complexity: O(n + k)
 *   - O(1) per booking to update diff (k bookings), then one O(n) prefix
 *     pass and one O(n) counting pass. Applying each range directly would
 *     be O(n * k).
 *
 * Space Complexity: O(n)
 *   - The diff and prefix_sum arrays (plus the by-value copy of slots).
 */
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Return the number of slots with more bookings than cap
 *
 * @param bookings Bulk bookings, each [l, r, c] with 0 <= l <= r < n, c > 0
 * @param slots    Existing bookings per slot (length n > 0)
 * @param cap      Maximum bookings allowed per slot
 * @return         Count of slots i with slots[i] + new bookings > cap
 *
 * Algorithm:
 * 1. For every booking, diff[l] += c and (if r+1 < n) diff[r+1] -= c.
 * 2. prefix_sum[i] = diff[0] + ... + diff[i] = new bookings at slot i.
 * 3. Count the i where slots[i] + prefix_sum[i] > cap.
 *
 * Time:  O(n + k) -- O(1) per range update + linear prefix/count passes
 * Space: O(n)     -- diff + prefix_sum
 */
//Time O(n + k)  (O(1) per booking + one prefix pass + one count pass)
//Space O(n)     (diff + prefix_sum)
int overbooked_slots(vector<vector<int>>& bookings, vector<int> slots, int cap) {
  int n = slots.size();
  vector<int>diff(n);                              // difference array of new bookings
  for(auto& booking: bookings) {
    int l = booking[0];
    int r = booking[1];
    int v = booking[2];
    diff[l] += v;                                  // range starts at l
    if(r+1<n) diff[r+1] -= v;                      // range stops after r
  }
  
  vector<int> prefix_sum (n);                      // prefix_sum[i] = new bookings at slot i
  prefix_sum[0] = diff[0];
  for(int i=1;i<n;++i) {
    prefix_sum[i] = prefix_sum[i-1] + diff[i];
  }

  int overbooked = 0;
  for(int i=0;i<n;++i) {
    if(cap < prefix_sum[i] + slots[i]) {           // existing + new > capacity
      overbooked+=1;
    }
  }
  return overbooked;
}

// To execute C++, please define "int main()"
int main() {
  vector<int> slots {0,0,0,0,0,0}; vector<vector<int>> bookings{{0, 3, 4},{2, 5, 1},{4, 4, 3}};int cap=5;
  cout<< overbooked_slots(bookings,slots,cap)<<"\n";
  slots = {1,1,0,0,2,3}; bookings = {{0, 3, 4},{2, 5, 1},{4, 4, 3}};cap=4;
  cout<< overbooked_slots(bookings,slots,cap)<<"\n";  
  return 0;
}


// # All Overbooked Slots

// In a mock interview booking system, there is a list of `n` time slots available to book interviews. We are given:

// - An array, `slots`, of length `n > 0`, where `slots[i]` is the number of bookings already made for slot `i`.
// - An array, `bookings`, of length `k >= 0`, where each element represents a bulk booking for a given range. Each element is an array with 3 integers: `[l, r, c]`, where `[l, r]` is the range of requested slots (both inclusive), and `c` is the number of clients booked for the entire range. We can assume that `0 <= l <= r < n` and `c > 0`.
// - A positive integer, `cap`, representing the maximum number of interviews that can be accommodated at any given slot.

// Return the number of slots that are _overbooked_ (i.e., have more bookings than the capacity allows).

// Example 1:
// slots = [0, 0, 0, 0, 0, 0]
// bookings = [[0, 3, 4], [2, 5, 1], [4, 4, 3]]
// cap = 5

// Output: 0
// The number of bookings at each slot is [4, 4, 5, 5, 4, 1].
// None of them is over the cap.

// Example 2:
// slots = [1, 1, 0, 0, 2, 3]
// bookings = [[0, 3, 4], [2, 5, 1], [4, 4, 3]]
// cap = 4

// Output: 5
// The number of bookings at each slot is [5, 5, 5, 5, 6, 4].

// Constraints:

// - `1 <= slots.length <= 10^5`
// - `0 <= slots[i] <= 10^5`
// - `0 <= bookings.length <= 10^5`
// - `bookings[i].length` is `3`
// - `0 <= bookings[i][0] <= bookings[i][1] < slots.length`
// - `bookings[i][2] > 0`
// - `1 <= cap <= 10^6`
