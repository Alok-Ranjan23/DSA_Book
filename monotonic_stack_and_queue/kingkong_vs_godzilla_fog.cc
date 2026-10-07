/**
 * @file kingkong_vs_godzilla_fog.cc
 * @brief King Kong vs Godzilla with limited visibility of k buildings
 *
 * Same as the base problem, but each monster can only see k buildings ahead.
 * King Kong spares street[i] iff a strictly taller building exists in
 * (i, i+k]; Godzilla spares it iff a strictly shorter building exists in
 * [i-k, i). The monotonic-stack NGE / PSE passes are extended with one extra
 * pop condition: discard indices that are more than k positions away.
 *
 * Key Concepts:
 * - NGE / PSE with a monotonic stack (see kingkong_vs_godzilla.cc)
 * - Distance pruning: in the right-to-left NGE scan the stack top is the
 *   CLOSEST remaining index, and indices deeper in the stack are farther.
 *   So if the top is > k away, every index in the stack is too. As i keeps
 *   moving left, distances only grow, so a pruned index can never become
 *   visible again -- popping it permanently is safe. PSE is the mirror image.
 * - The nearest strictly taller element is the FIRST taller one; if it is
 *   beyond k, no taller element is within k. Hence "nearest greater, then
 *   check distance" is equivalent to "any greater within k".
 *
 * Time Complexity: O(n)
 *   - The extra distance condition only adds pops; each index is still pushed
 *     once and popped at most once per pass, so both passes are O(n) total.
 *
 * Space Complexity: O(n)
 *   - Two index arrays, a stack of up to n indices, and the boolean output.
 */
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

/**
 * @brief Nearest strictly taller element to the right, within k positions
 *
 * @param tiles Heights
 * @param k     Visibility (1 <= k <= n)
 * @return      res[i] = nearest j in (i, i+k] with tiles[j] > tiles[i],
 *              or n if none
 *
 * Algorithm:
 * 1. Iterate i from n-1 down to 0.
 * 2. Pop while the top is not taller (tiles[top] <= tiles[i]) OR is too far
 *    away (top - i > k).
 * 3. A remaining top is the answer; push i.
 *
 * Time:  O(n) -- each index pushed once, popped at most once
 * Space: O(n) -- stack + result
 */
//Time O(n)   (each index pushed/popped at most once)
//Space O(n)  (stack + result)
vector<int> next_greater_elements(vector<int>& tiles, int k) {
  int n = tiles.size();
  vector<int> res(n,n);                            // n = "nothing taller within k"
  stack<int> st;
  for(int i=n-1;i>=0;--i) {
    // not taller, or hidden by the fog (more than k away)
    while(!st.empty() && (tiles[st.top()]<=tiles[i] || st.top()-i>k)) st.pop();
    if(!st.empty()) res[i] = st.top();
    st.push(i);
  }
  return res;
}

/**
 * @brief Nearest strictly shorter element to the left, within k positions
 *
 * @param tiles Heights
 * @param k     Visibility (1 <= k <= n)
 * @return      res[i] = nearest j in [i-k, i) with tiles[j] < tiles[i],
 *              or -1 if none
 *
 * Algorithm: mirror of next_greater_elements -- scan left-to-right, pop while
 * tiles[top] >= tiles[i] OR i - top > k.
 *
 * Time:  O(n) -- each index pushed once, popped at most once
 * Space: O(n) -- stack + result
 */
//Time O(n)   (each index pushed/popped at most once)
//Space O(n)  (stack + result)
vector<int> previous_smaller_elements(vector<int>& tiles, int k) {
  int n = tiles.size();
  vector<int> res(n,-1);                           // -1 = "nothing shorter within k"
  stack<int> st;
  for(int i=0;i<n;++i) {
    // not shorter, or hidden by the fog (more than k away)
    while(!st.empty() && (tiles[st.top()]>=tiles[i] || i-st.top()>k)) st.pop();
    if(!st.empty()) res[i] = st.top();
    st.push(i);
  }
  return res;
}

/**
 * @brief Return which buildings survive both monsters in the fog
 *
 * @param street Building heights from left to right (non-empty)
 * @param k      Number of buildings each monster can see ahead
 * @return       res[i] == true iff street[i] is spared by both
 *
 * Time:  O(n) -- two O(n) stack passes plus one O(n) combine loop
 * Space: O(n) -- two index arrays and the boolean result
 */
//Time O(n)
//Space O(n)
vector<bool> safe_buildings(vector<int>& street, int k) {
  int n = street.size();
  vector<int> kingkong = next_greater_elements(street,k);
  vector<int> godzilla = previous_smaller_elements(street,k);
  vector<bool> res(n,false);
  for(int i=0;i<n;++i) {
    res[i] = ((kingkong[i]!=n) && (godzilla[i]!=-1));   // spared by both
  }
  return res;
}

// To execute C++, please define "int main()"
int main() {
  vector<int> street {10, 20, 30, 15, 5};int k {2};
  cout<<boolalpha;
  for(bool state: safe_buildings(street,k)) {cout<<state<<" ";} cout<<"\n";
  street = {10, 20, 30, 40, 50};k=3;
  for(bool state: safe_buildings(street,k)) {cout<<state<<" ";} cout<<"\n";
  street = {50, 40, 30, 20, 10};k=3;
  for(bool state: safe_buildings(street,k)) {cout<<state<<" ";} cout<<"\n";
  street = {1, 10, 5, 20};k=2;
  for(bool state: safe_buildings(street,k)) {cout<<state<<" ";} cout<<"\n";
  street = {1, 10, 5, 20};k=1;
  for(bool state: safe_buildings(street,k)) {cout<<state<<" ";} cout<<"\n";
  return 0;
}

// # King Kong Vs Godzilla In The Fog

// King Kong and Godzilla are rampaging a city. You're given a non-empty array of positive integers, `street`, representing the heights of buildings in a street from left to right. It is foggy, so King Kong and Godzilla can only see the next `k` buildings in front of them.

// - King Kong starts at the beginning of the street and prefers to smash tall buildings. King Kong will only spare a building `street[i]` if there is a **taller building to the right at most `k` buildings away**.
// - Godzilla starts at the end of the street and prefers crushing small buildings. Godzilla will only spare a building `street[i]` if there is a **shorter building to the left at most `k` buildings away**.

// Return a boolean array of length `n`, where `n` is the length of `street`, indicating which buildings were spared by both King Kong and Godzilla. Index `i` should be true if `street[i]` was spared.

// Example 1: street = [10, 20, 30, 15, 5], k = 2
// Output: [False, True, False, False, False]

// King Kong does the following:
// 1. King Kong starts at building 10 and can see the next 2 buildings: 20 and 30.
// It spares it since it sees a taller building (20).
// 2. King Kong moves to building 20 and can see the next 2 buildings: 30 and 15.
// It spares 20 since it sees a taller building (30).
// 3. King Kong moves to building 30. It can see the next 2 buildings: 15 and 5.
// It destroys 30 since it is taller than the other buildings it sees.
// 4. King Kong moves to building 15. It can see the next building: 5.
// It destroys 15 since it is taller than the other buildings it sees.
// 5. King Kong moves to building 5. There are no more buildings to see.
// It destroys 5 since it is the last building.

// Godzilla does the following:
// 1. Godzilla starts at building 5 and can see the next 2 buildings: 15 and 30.
// It destroys 5 since it sees a taller building (15).
// 2. Godzilla moves to building 15 and can see the next 2 buildings: 30 and 20.
// It destroys 15 since it sees a taller building (30).
// 3. Godzilla moves to building 30. It can see the next 2 buildings: 20 and 10.
// It spares 30 since it sees a shorter building (20).
// 4. Godzilla moves to building 20. It can see the next building: 10.
// It spares 20 since it sees a shorter building (10).
// 5. Godzilla moves to building 10. There are no more buildings to see.
// It destroys 10 since it is the last building.

// The only building spared by both is 20.

// Example 2: street = [10, 20, 30, 40, 50], k = 3
// Output: [False, True, True, True, False]
// Godzilla destroys the first building and King King destroys the last.

// Example 3: street = [50, 40, 30, 20, 10], k = 3
// Output: [False, False, False, False, False]
// King Kong destroys all buildings, and so does Godzilla.

// Example 4: street = [1, 10, 5, 20], k = 2
// Output: [False, True, True, False]

// Example 5: street = [1, 10, 5, 20], k = 1
// Output: [False, False, False, False]
// Building (10) has a taller building (20) to the right, but it is hidden by the fog.

// Constraints:

// - The length of street is at most 10^5
// - Each element in street is a positive integer less than 10^3
// - 1 ≤ k ≤ len(street)
