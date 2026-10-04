/**
 * @file multimap.cc
 * @brief Multimap (int -> list of strings) implemented with separate chaining
 *
 * A multimap allows several values per key. Each distinct key is stored once
 * as (key, vector<string>) in bucket h(key, cap), where h is the
 * multiplicative (Knuth) hash floor(cap * frac(key * C)), C = (sqrt(5)-1)/2.
 * Adding a value to an existing key appends to that key's value list.
 *
 * Key Concepts:
 * - Two counters with different meanings:
 *     _size       = number of key-value pairs (what size() must return)
 *     resize_size = number of distinct keys (what actually occupies buckets)
 * - Load factor uses resize_size / cap, since bucket length depends on the
 *   number of distinct keys, not on how many values each key has
 * - Grow (x2) when load factor > 1; shrink (/2) when < 0.25 and cap > 10
 * - remove(k) drops the whole (key, list) entry and subtracts the list
 *   length from _size, using swap-with-last + pop_back inside the bucket
 *
 * @warning h() strips the fractional part with static_cast<int>, which
 *          truncates toward zero. For a negative key the "fraction" is
 *          negative, so h() returns a negative bucket index (out of bounds).
 *          Only non-negative keys are safe.
 *
 * Time Complexity (u = distinct keys, n = key-value pairs, cap = buckets):
 *   - contains:  O(1) average, O(u) worst case
 *   - get:       O(1) average to locate + O(v) to copy the v values returned
 *   - add:       O(1) amortized average; O(u + n + cap) when a resize happens
 *                (resize copies every value list)
 *   - remove:    O(1) average to locate (the moved entry is O(1));
 *                O(u + n + cap) when a resize happens
 *
 * Space Complexity: O(n + u + cap)
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/**
 * @brief Multiplicative hash: map key to a bucket index in [0, m)
 *
 * @param key The key to hash (must be non-negative, see file @warning)
 * @param m   Number of buckets
 * @return    floor(m * frac(key * C)), C = golden-ratio conjugate
 *
 * Time:  O(1)
 * Space: O(1)
 */
int h(int key, int m) {
  double C = 0.6180339887;
  double x = key * C;
  x -= static_cast<int>(x);                        // keep fractional part
  x *= m;                                          // scale to [0, m)
  return static_cast<int>(x);
}

/// Multimap from int keys to lists of string values using separate chaining.
class MultiMap {
  int (*h)(int,int);                               ///< hash function (key, cap) -> bin
  int _cap;                                        ///< number of buckets
  int _size;                                       ///< number of key-value pairs
  int resize_size;                                 ///< number of distinct keys (drives load factor)
  vector<vector<pair<int,vector<string>>>> buckets;   ///< buckets[bin] = chain of (key, values)
  void resize_map(int new_cap);
  public:
  MultiMap(int (*h)(int,int), int cap=10);
  bool contains(int k);
  vector<string> get(int k);
  void add(int k, string v);
  void remove(int k);
  /// @brief Number of key-value pairs (copies counted). Time O(1), Space O(1)
  int size() {return _size;}
};

/**
 * @brief Construct an empty multimap
 *
 * @param h   Hash function (key, cap) -> bucket index
 * @param cap Initial number of buckets (default 10)
 *
 * Time:  O(cap)
 * Space: O(cap)
 */
MultiMap::MultiMap(int (*h)(int,int), int cap): h(h), _cap(cap), _size(0),
    resize_size(0) {
  buckets.resize(_cap);
}

/**
 * @brief Rehash every (key, values) entry into a table with new_cap buckets
 *
 * @param new_cap New number of buckets
 *
 * Time:  O(u + n + new_cap) (each value list is copied)
 * Space: O(u + n + new_cap) for the temporary table
 */
//Time O(u + n + new_cap)
//Space O(u + n + new_cap)
void MultiMap::resize_map(int new_cap) {
  vector<vector<pair<int,vector<string>>>> temp(new_cap);
  _cap = new_cap;
  for (auto& bucket:buckets) {
    for (auto& [key,val]: bucket) {
      int bin = h(key, _cap);                      // bin in the new table
      temp[bin].push_back({key,val});
    }
  }
  buckets = move(temp);
}

/**
 * @brief Return whether at least one pair has key k
 *
 * @param k Key to look up
 * @return  true if k is present
 *
 * Time:  O(1) average, O(u) worst case
 * Space: O(1)
 */
//Time O(1) average
//Space O(1)
bool MultiMap::contains(int k) {
  int bin = h(k,_cap);
  for(auto& [key, _]:buckets[bin]) {
    if(k==key) return true;
  }
  return false;
}

/**
 * @brief Return all values associated with key k
 *
 * @param k Key to look up
 * @return  Copy of k's value list, or an empty list if k is absent
 *
 * Time:  O(1) average to locate + O(v) to copy v values
 * Space: O(v) for the returned list
 */
//Time O(1) average + O(v)
//Space O(v)
vector<string> MultiMap::get(int k) {
  int bin = h(k,_cap);
  for(auto& [key,val_list]:buckets[bin]) {
    if(key==k) return val_list;
  }
  return {};
}

/**
 * @brief Add the pair (k, v), even if k already exists
 *
 * @param k Key
 * @param v Value
 *
 * Algorithm:
 * 1. If k exists, append v to its value list; _size += 1.
 * 2. Otherwise push a new entry (k, {v}); _size += 1 and resize_size += 1,
 *    then double the table if resize_size / cap exceeds 1.
 *
 * Time:  O(1) amortized average; O(u + n + cap) when a resize happens
 * Space: O(1) amortized
 */
//Time O(1) amortized average
//Space O(1) amortized
void MultiMap::add(int k, string v) {
  int bin = h(k,_cap);
  if(contains(k)) {                                // existing key: append value
    int n = buckets[bin].size();
    for(int i=0;i<n;++i) {
      if(buckets[bin][i].first==k) {
        buckets[bin][i].second.push_back(v);
        _size+=1;
        break;
      }
    }
  } else {                                         // new key
    buckets[bin].push_back({k,{v}});
    _size+=1;
    resize_size+=1;
    double load_factor = static_cast<double>(resize_size) / _cap;
    if(load_factor > 1) resize_map(_cap*2);        // grow
  }
}

/**
 * @brief Remove every pair whose key is k
 *
 * @param k Key to remove
 *
 * Algorithm:
 * 1. Scan k's bucket for the entry; if absent, nothing is removed.
 * 2. Subtract the entry's value count from _size and 1 from resize_size,
 *    move the bucket's last entry into its slot, and pop_back.
 * 3. Halve the table if resize_size / cap drops below 0.25 and cap > 10.
 *
 * Time:  O(1) average; O(u + n + cap) when a resize happens
 * Space: O(1)
 */
//Time O(1) average
//Space O(1)
void MultiMap::remove(int k) {
  int bin = h(k,_cap);
  int index = -1;
  int n = buckets[bin].size();
  for(int i=0;i<n;++i) {
    if(buckets[bin][i].first == k) {
      index = i;
      break;
    }
  }
  if(index!=-1) {
    resize_size-=1;
    _size-=buckets[bin][index].second.size();     // drop all of k's values
    buckets[bin][index] = move(buckets[bin][n-1]); // swap-with-last (moved, not copied)
    buckets[bin].pop_back();
  }
  double load_factor = static_cast<double>(resize_size) / _cap;
  if(load_factor < 0.25 && _cap > 10) resize_map(_cap/2);   // shrink
}

// To execute C++, please define "int main()"
int main() {
  MultiMap umap(h);
  cout<<boolalpha;cout<<umap.contains(1)<<"\n";
  umap.add(1,"one");
  for(auto& val: umap.get(1)) { cout<<val<<" ";}cout<<"\n"; 
  umap.add(1,"alok");
  for(auto& val: umap.get(1)) { cout<<val<<" ";}cout<<"\n";
  cout<<boolalpha;cout<<umap.contains(1)<<"\n";
  umap.add(2,"two");
  cout<<boolalpha;cout<<umap.contains(2)<<"\n";
  umap.remove(2);
  cout<<boolalpha;cout<<umap.contains(2)<<"\n";
  return 0;
}

// # Multimap

// A multimap is a map that allows multiple key-value pairs with the same key. Implement a multimap data structure with the following API:

// - `add(k, v)`: adds key `k` with value `v` to the multimap, even if key `k` is already found
// - `remove(k)`: removes all key-value pairs with `k` as the key
// - `contains(k)`: returns whether the multimap contains any key-value pair with `k` as the key
// - `get(k)`: returns all values associated to key `k` in a list. If there is none, returns an empty list
// - `size()`: returns the number of key-value pairs in the multimap

// Constraints:

// - If your language is typed, you can either implement a multimap for integers, or make it generic.
// - The multimap will contain at most `10^6` key-value pairs.
