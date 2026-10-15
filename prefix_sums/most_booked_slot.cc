/**
 * @file most_booked_slot.cc
 * @brief Index of the slot with the most bookings after applying a list of
 *        range (bulk) bookings; earliest index wins ties
 *
 * Each bulk booking [l, r, c] adds c to every slot in [l, r]. Use a
 * difference array (+c at l, -c at r+1) so each booking costs O(1), then
 * one prefix-sum pass rebuilds the number of new bookings per slot. Add the
 * existing bookings and take the first maximum.
 *
 * Key Concepts:
 * - Difference array + prefix sum for many range-add updates
 * - r+1 == n is skipped, since the range runs to the end of the array
 * - Strict '<' when updating the maximum keeps the EARLIEST index on ties
 * - max_bookings starts at -1 (below any valid count) so index 0 is chosen
 *   even when every slot has 0 bookings
 *
 * Time Complexity: O(n + k)
 *   - O(1) per booking (k bookings), then O(n) prefix pass and O(n) scan.
 *     Applying each range directly would be O(n * k).
 *
 * Space Complexity: O(n)
 *   - The diff and prefix_sum arrays.
 */
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Return the earliest index of the most booked slot
 *
 * @param bookings Bulk bookings, each [l, r, c] with 0 <= l <= r < n, c > 0
 * @param slots    Existing bookings per slot (length n > 0)
 * @return         Smallest i maximising slots[i] + new bookings at i
 *
 * Algorithm:
 * 1. For every booking, diff[l] += c and (if r+1 < n) diff[r+1] -= c.
 * 2. prefix_sum[i] = diff[0] + ... + diff[i] = new bookings at slot i.
 * 3. Scan i = 0..n-1 and keep the first i with the largest
 *    slots[i] + prefix_sum[i].
 *
 * Time:  O(n + k) -- O(1) per range update + linear prefix/scan passes
 * Space: O(n)     -- diff + prefix_sum
 */
//Time O(n + k)  (O(1) per booking + one prefix pass + one scan)
//Space O(n)     (diff + prefix_sum)
int most_booked_slots(vector<vector<int>>& bookings, vector<int>& slots) {
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

  int index = -1;
  int max_bookings = -1;                           // below any real count
  for(int i=0;i<n;++i) {
    if(max_bookings < prefix_sum[i] + slots[i]) {  // strict '<' keeps earliest on ties
      max_bookings = prefix_sum[i] + slots[i];
      index = i;
    }
  }
  return index;
}

// To execute C++, please define "int main()"
int main() {
  vector<int> slots {0,0,0,0,0,0}; vector<vector<int>> bookings{{0, 3, 4},{2, 5, 1},{4, 4, 3}};
  cout<< most_booked_slots(bookings,slots)<<"\n";
  slots = {1,1,0,0,2,3}; bookings = {{0, 3, 4},{2, 5, 1},{4, 4, 3}};
  cout<< most_booked_slots(bookings,slots)<<"\n";  
  return 0;
}

// # Most Booked Slot

// In a mock interview booking system, there is a list of `n` time slots available to book interviews. We are given:

// - An array, `slots`, of length `n > 0`, where `slots[i]` is the number of bookings already made for slot `i`.
// - An array, `bookings`, of length `k >= 0`, where each element represents a bulk booking for a given range. Each element is an array with 3 integers: `[l, r, c]`, where `[l, r]` is the range of requested slots (both inclusive), and `c` is the number of clients booked for the entire range. We can assume that `0 <= l <= r < n` and `c > 0`.

// Determine the most booked slot and return its index. If there is more than one, return the earliest one.

// Example 1:
// slots = [0, 0, 0, 0, 0, 0]
// bookings = [[0, 3, 4], [2, 5, 1], [4, 4, 3]]

// Output: 2
// The final number of bookings at each slot is [4, 4, 5, 5, 4, 1].
// Slots at indices 2 and 3 are the most popular, and 2 is earlier

// Example 2:
// slots = [1, 1, 0, 0, 2, 3]
// bookings = [[0, 3, 4], [2, 5, 1], [4, 4, 3]]

// Output: 4
// Counting the initial bookings, the final number of bookings at
// each slot is [5, 5, 5, 5, 6, 4].

// Constraints:

// - `1 <= slots.length <= 10^5`
// - `0 <= slots[i] <= 10^5`
// - `0 <= bookings.length <= 10^5`
// - `bookings[i].length` is `3`
// - `0 <= bookings[i][0] <= bookings[i][1] < slots.length`
// - `bookings[i][2] > 0`
