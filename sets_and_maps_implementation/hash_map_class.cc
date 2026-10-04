/**
 * @file hash_map_class.cc
 * @brief Hash map (int -> string) implemented with separate chaining
 *
 * The table is a vector of buckets; each bucket is a vector of (key, value)
 * pairs. A key is placed in bucket h(key, cap), where h is the multiplicative
 * (Knuth) hash floor(cap * frac(key * C)) with C = (sqrt(5) - 1) / 2. Keys that
 * collide simply share a bucket and are found by a linear scan of that bucket.
 *
 * Key Concepts:
 * - Separate chaining: buckets[bin] holds every pair whose key hashes to bin
 * - Load factor = size / cap. Grow (x2) when it exceeds 1 so buckets stay
 *   O(1) long on average; shrink (/2) when it drops below 0.25 (never below
 *   the initial capacity of 10) so memory stays O(size)
 * - Resizing rehashes every pair, because bin = h(key, cap) depends on cap
 * - Removal swaps the target with the last pair in its bucket and pops, so it
 *   is O(1) once found (order inside a bucket does not matter)
 *
 * @warning h() strips the fractional part with static_cast<int>, which
 *          truncates toward zero. For a negative key the "fraction" is
 *          negative, so h() returns a negative bucket index (out of bounds).
 *          Only non-negative keys are safe.
 *
 * Time Complexity (n = number of keys, cap = number of buckets):
 *   - contains / get:  O(1) average, O(n) worst case (all keys in one bucket)
 *   - add / remove:    O(1) amortized average; a single call that triggers a
 *                      resize costs O(n + cap)
 *   - keys / values:   O(n + cap) (every bucket is visited)
 *
 * Space Complexity: O(n + cap)
 *   - Every pair is stored once; cap stays within a constant factor of n
 *     because of the grow/shrink thresholds.
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

/// Hash map from int keys to string values using separate chaining.
class HashMap {
  int (*h)(int,int);                               ///< hash function (key, cap) -> bin
  int _cap;                                        ///< number of buckets
  int _size;                                       ///< number of keys stored
  vector<vector<pair<int,string>>> buckets;        ///< buckets[bin] = chain of (key, value)
  void resize_map(int new_cap);
  public:
  HashMap(int (*h)(int,int), int cap=10);
  bool contains(int k);
  string get(int k);
  void add(int k, string v);
  void remove(int k);
  /// @brief Number of keys in the map. Time O(1), Space O(1)
  int size() {return _size;}
  vector<int> keys();
  vector<string> values();
};

/**
 * @brief Construct an empty map
 *
 * @param h   Hash function (key, cap) -> bucket index
 * @param cap Initial number of buckets (default 10)
 *
 * Time:  O(cap)
 * Space: O(cap)
 */
HashMap::HashMap(int (*h)(int,int), int cap): h(h), _cap(cap), _size(0) {
  buckets.resize(_cap);
}

/**
 * @brief Rehash every pair into a new table with new_cap buckets
 *
 * @param new_cap New number of buckets
 *
 * _cap is updated first so that h(key, _cap) computes bins for the new table.
 *
 * Time:  O(n + new_cap)
 * Space: O(n + new_cap) for the temporary table
 */
//Time O(n + new_cap)
//Space O(n + new_cap)
void HashMap::resize_map(int new_cap) {
  vector<vector<pair<int,string>>> temp(new_cap);
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
 * @brief Return whether key k is in the map
 *
 * @param k Key to look up
 * @return  true if k is present
 *
 * Time:  O(1) average, O(n) worst case
 * Space: O(1)
 */
//Time O(1) average
//Space O(1)
bool HashMap::contains(int k) {
  int bin = h(k,_cap);
  for(auto& [key, _]:buckets[bin]) {
    if(k==key) return true;
  }
  return false;
}

/**
 * @brief Return the value stored for key k
 *
 * @param k Key to look up
 * @return  The value, or "" (the "null" value) if k is not in the map
 *
 * Time:  O(1) average, O(n) worst case
 * Space: O(1) (plus the returned string copy)
 */
//Time O(1) average
//Space O(1)
string HashMap::get(int k) {
  int bin = h(k,_cap);
  for(auto& [key,val]:buckets[bin]) {
    if(key==k) return val;
  }
  return "";
}

/**
 * @brief Insert key k with value v, or update v if k already exists
 *
 * @param k Key
 * @param v Value
 *
 * Algorithm:
 * 1. If k exists, find it in its bucket and overwrite the value (size unchanged).
 * 2. Otherwise append (k, v) to its bucket, increment size, and double the
 *    table if the load factor exceeds 1.
 *
 * Time:  O(1) amortized average; O(n + cap) when a resize happens
 * Space: O(1) amortized
 */
//Time O(1) amortized average
//Space O(1) amortized
void HashMap::add(int k, string v) {
  int bin = h(k,_cap);
  if(contains(k)) {                                // update existing key
    int n = buckets[bin].size();
    for(int i=0;i<n;++i) {
      if(buckets[bin][i].first==k) {
        buckets[bin][i].second=v;
        break;
      }
    }
  } else {                                         // new key
    buckets[bin].push_back({k,v});
    _size+=1;
    double load_factor = static_cast<double>(_size) / _cap;
    if(load_factor > 1) resize_map(_cap*2);        // grow
  }
}

/**
 * @brief Remove key k (and its value) if present
 *
 * @param k Key to remove
 *
 * Algorithm:
 * 1. Return if k is absent.
 * 2. Find k's index in its bucket, overwrite it with the bucket's last pair,
 *    and pop_back (O(1) delete, order within a bucket does not matter).
 * 3. Halve the table if the load factor drops below 0.25 and cap > 10.
 *
 * Time:  O(1) amortized average; O(n + cap) when a resize happens
 * Space: O(1) amortized
 */
//Time O(1) amortized average
//Space O(1) amortized
void HashMap::remove(int k) {
  if(!contains(k)) return;
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
    buckets[bin][index] = buckets[bin][n-1];       // swap-with-last delete
    _size-=1;
    buckets[bin].pop_back();

  }
  double load_factor = static_cast<double>(_size) / _cap;
  if(load_factor < 0.25 && _cap > 10) resize_map(_cap/2);   // shrink
}

/**
 * @brief Return all keys in the map (order unspecified)
 *
 * @return Vector of n keys
 *
 * Time:  O(n + cap)
 * Space: O(n) for the result
 */
//Time O(n + cap)
//Space O(n)
vector<int> HashMap::keys() {
  vector<int> res;
  for(auto& bucket: buckets) {
    for(auto& [key,_]: bucket) {
      res.push_back(key);
    }
  }
  return res;
}

/**
 * @brief Return all values in the map (order unspecified, duplicates kept)
 *
 * @return Vector of n values
 *
 * Time:  O(n + cap)
 * Space: O(n) for the result
 */
//Time O(n + cap)
//Space O(n)
vector<string> HashMap::values() {
  vector<string> res;
  for(auto& bucket: buckets) {
    for(auto& [_,val]: bucket) {
      res.push_back(val);
    }
  }
  return res;
}

// To execute C++, please define "int main()"
int main() {
  HashMap umap(h);
  cout<<boolalpha;cout<<umap.contains(1)<<"\n";
  umap.add(1,"one");
  cout<<umap.get(1)<<"\n";
  umap.add(1,"alok");
  cout<<umap.get(1)<<"\n";
  cout<<boolalpha;cout<<umap.contains(1)<<"\n";
  umap.add(2,"two");
  cout<<umap.get(2)<<"\nKeys:   ";
  for(auto& key: umap.keys()) {cout<<key<<" ";}cout<<"\nvalues: ";
  for(auto& val: umap.values()) {cout<<val<<" ";}cout<<"\n";
  cout<<boolalpha;cout<<umap.contains(2)<<"\n";
  umap.remove(2);
  cout<<boolalpha;cout<<umap.contains(2)<<"\n";
  return 0;
}

// # Hash Map Class

// Implement a hash map data structure with the following API:

// - `add(k, v)`: if `k` is not in the map, add key `k` to the map with value `v`. If `k` is already in the map, update its value to `v`.
// - `remove(k)`: if `k` is in the map, remove it from the map
// - `contains(k)`: return whether the key `k` is in the map
// - `get(k)`: return the value for key `k`. If `k` is not in the map, return a null value
// - `size()`: return the number of keys in the map
// - `keys()`: return all keys in the map in a dynamic array. The output order doesn't matter.
// - `values()`: return all values in the map in a dynamic array. The output order doesn't matter. If a value appears more than once, return it as many times as it occurs.

// For each method, provide time and space complexity analysis.

// Constraints:

// - If your language is typed, you can either implement a hash map for integers, or make it generic.
// - The map will contain at most `10^6` key-value pairs.
