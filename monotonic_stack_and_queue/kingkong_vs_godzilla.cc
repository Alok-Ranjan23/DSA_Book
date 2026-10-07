/**
 * @file kingkong_vs_godzilla.cc
 * @brief Find buildings spared by both King Kong and Godzilla
 *
 * King Kong spares street[i] only if some building to its RIGHT is strictly
 * taller; Godzilla spares street[i] only if some building to its LEFT is
 * strictly shorter. Both questions are "does a next-greater / previous-smaller
 * element exist?", which a monotonic stack answers for every index in one pass.
 *
 * Key Concepts:
 * - Next Greater Element (NGE): scan right-to-left keeping a stack of indices
 *   whose heights strictly decrease from bottom to top -- pop every index
 *   with height <= current; whatever remains on top is the nearest taller one
 * - Previous Smaller Element (PSE): scan left-to-right, pop every index with
 *   height >= current; the remaining top is the nearest strictly shorter one
 * - Sentinels: NGE uses n and PSE uses -1 for "no such element", so a building
 *   is spared iff NGE[i] != n AND PSE[i] != -1
 *
 * Time Complexity: O(n)
 *   - Each helper pushes every index exactly once and pops it at most once,
 *     so the total work of all inner while-loops is O(n) (amortized O(1) per
 *     index). The final combining loop is O(n).
 *
 * Space Complexity: O(n)
 *   - Two result arrays of size n, one stack of up to n indices, and the
 *     output vector<bool> of size n.
 */
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

/**
 * @brief For each index, the index of the nearest strictly taller element to
 *        its right
 *
 * @param tiles Heights
 * @return      res[i] = smallest j > i with tiles[j] > tiles[i], or n if none
 *
 * Algorithm:
 * 1. Iterate i from n-1 down to 0.
 * 2. Pop indices whose height is <= tiles[i]; they can never be the "next
 *    greater" of i or of anything further left (i blocks them and is at
 *    least as tall).
 * 3. If the stack is non-empty its top is the answer; then push i.
 *
 * Time:  O(n) -- every index is pushed once and popped at most once
 * Space: O(n) -- the stack and the result array
 */
//Time O(n)   (each index pushed/popped at most once)
//Space O(n)  (stack + result)
vector<int> next_greater_elements(vector<int>& tiles) {
  int n = tiles.size();
  vector<int> res(n,n);                            // n = "no taller building to the right"
  stack<int> st;
  for(int i=n-1;i>=0;--i) {
    while(!st.empty() && tiles[st.top()]<=tiles[i]) st.pop();
    if(!st.empty()) res[i] = st.top();
    st.push(i);
  }
  return res;
}

/**
 * @brief For each index, the index of the nearest strictly shorter element to
 *        its left
 *
 * @param tiles Heights
 * @return      res[i] = largest j < i with tiles[j] < tiles[i], or -1 if none
 *
 * Algorithm: mirror of next_greater_elements -- scan left-to-right and pop
 * indices whose height is >= tiles[i].
 *
 * Time:  O(n) -- every index is pushed once and popped at most once
 * Space: O(n) -- the stack and the result array
 */
//Time O(n)   (each index pushed/popped at most once)
//Space O(n)  (stack + result)
vector<int> previous_smaller_elements(vector<int>& tiles) {
  int n = tiles.size();
  vector<int> res(n,-1);                           // -1 = "no shorter building to the left"
  stack<int> st;
  for(int i=0;i<n;++i) {
    while(!st.empty() && tiles[st.top()]>=tiles[i]) st.pop();
    if(!st.empty()) res[i] = st.top();
    st.push(i);
  }
  return res;
}

/**
 * @brief Return which buildings survive both monsters
 *
 * @param street Building heights from left to right (non-empty)
 * @return       res[i] == true iff street[i] is spared by both
 *
 * Algorithm:
 * 1. kingkong = NGE of street (taller building to the right exists?).
 * 2. godzilla = PSE of street (shorter building to the left exists?).
 * 3. res[i] = (kingkong[i] != n) && (godzilla[i] != -1).
 *
 * Time:  O(n) -- two O(n) stack passes plus one O(n) combine loop
 * Space: O(n) -- two index arrays and the boolean result
 */
//Time O(n)
//Space O(n)
vector<bool> safe_buildings(vector<int>& street) {
  int n = street.size();
  vector<int> kingkong = next_greater_elements(street);
  vector<int> godzilla = previous_smaller_elements(street);
  vector<bool> res(n,false);
  for(int i=0;i<n;++i) {
    res[i] = ((kingkong[i]!=n) && (godzilla[i]!=-1));   // spared by both
  }
  return res;
}

// To execute C++, please define "int main()"
int main() {
  vector<int> street {10, 20, 30, 15, 5};
  cout<<boolalpha;
  for(bool state: safe_buildings(street)) {cout<<state<<" ";} cout<<"\n";
  street = {10, 20, 30, 40, 50};
  for(bool state: safe_buildings(street)) {cout<<state<<" ";} cout<<"\n";
  street = {50, 40, 30, 20, 10};
  for(bool state: safe_buildings(street)) {cout<<state<<" ";} cout<<"\n";
  street = {1, 10, 5, 20};
  for(bool state: safe_buildings(street)) {cout<<state<<" ";} cout<<"\n";
  return 0;
}

// # King Kong Vs Godzilla

// King Kong and Godzilla are rampaging a city. You're given a non-empty array of positive integers, `street`, representing the heights of buildings in a street from left to right.

// - King Kong starts at the beginning of the street and prefers to smash tall buildings. King Kong will only spare a building `street[i]` if there is a **taller building to the right**.
// - Godzilla starts at the end of the street and prefers crushing small buildings. Godzilla will only spare a building `street[i]` if there is a **shorter building to the left**.

// Return a boolean array of length `n`, where `n` is the length of `street`, indicating which buildings were spared by both King Kong and Godzilla. Index `i` should be true if `street[i]` was spared.

// Example 1: street = [10, 20, 30, 15, 5]
// Output: [False, True, False, False, False]
// King Kong spares 10 and 20 because, for each of those, there is a taller building to the right.
// Godzilla spares 15, 30 and 20 because, for each of those, there is a shorter building to the left.
// The only building spared by both is 20.

// Example 2: street = [10, 20, 30, 40, 50]
// Output: [False, True, True, True, False]
// Godzilla destroys the first building and King King destroys the last.

// Example 3: street = [50, 40, 30, 20, 10]
// Output: [False, False, False, False, False]
// King Kong destroys all buildings, and so does Godzilla.

// Example 4: street = [1, 10, 5, 20]
// Output: [False, True, True, False]

// Constraints:

// - The length of street is at most 10^5
// - Each element in street is a positive integer less than 10^3
