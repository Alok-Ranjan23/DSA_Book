/**
 * @file hash_set_class.cc
 * @brief Hash set of ints implemented with separate chaining
 *
 * The table is a vector of buckets; each bucket is a vector of ints. An
 * element x lives in bucket h(x, cap), where h is the multiplicative (Knuth)
 * hash floor(cap * frac(x * C)) with C = (sqrt(5) - 1) / 2. Colliding elements
 * share a bucket and are found by a linear scan of that bucket.
 *
 * Key Concepts:
 * - Separate chaining: buckets[bin] holds every element hashing to bin
 * - Load factor = size / cap. Grow (x2) when it exceeds 1, shrink (/2) when it
 *   drops below 0.25 (never below the initial capacity of 10)
 * - Resizing rehashes every element because bin = h(x, cap) depends on cap
 * - Removal swaps the target with the last element of its bucket and pops
 *
 * @warning h() strips the fractional part with static_cast<int>, which
 *          truncates toward zero. For a negative element the "fraction" is
 *          negative, so h() returns a negative bucket index (out of bounds).
 *          Only non-negative elements are safe.
 *
 * Time Complexity (n = number of elements, cap = number of buckets):
 *   - contains:     O(1) average, O(n) worst case (all in one bucket)
 *   - add / remove: O(1) amortized average; a call that triggers a resize
 *                   costs O(n + cap)
 *   - size:         O(1)
 *
 * Space Complexity: O(n + cap)
 *   - cap stays within a constant factor of n due to the grow/shrink rules.
 */
#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Multiplicative hash: map val to a bucket index in [0, m)
 *
 * @param val The value to hash (must be non-negative, see file @warning)
 * @param m   Number of buckets
 * @return    floor(m * frac(val * C)), C = golden-ratio conjugate
 *
 * Time:  O(1)
 * Space: O(1)
 */
int h(int val, int m) {
  double C = 0.6180339887;
  double x = val * C;
  x -= static_cast<int>(x);                        // keep fractional part
  x*=m;                                            // scale to [0, m)
  return static_cast<int>(x); 
}

/// Hash set of ints using separate chaining.
class HashSet {
  int (*h)(int,int);                               ///< hash function (x, cap) -> bin
  int _cap;                                        ///< number of buckets
  int _size;                                       ///< number of elements stored
  vector<vector<int>> buckets;                     ///< buckets[bin] = chain of elements
  void resize_set(int new_cap_);
  public:
  HashSet(int (*h)(int,int), int cap=10);
  bool contains(int x);
  void add(int x);
  void remove(int x);
  /// @brief Number of elements in the set. Time O(1), Space O(1)
  int size() {return _size;}
};

/**
 * @brief Rehash every element into a new table with new_cap_ buckets
 *
 * @param new_cap_ New number of buckets
 *
 * _cap is updated first so h(elem, _cap) computes bins for the new table.
 *
 * Time:  O(n + new_cap_)
 * Space: O(n + new_cap_) for the temporary table
 */
//Time O(n + new_cap_)
//Space O(n + new_cap_)
void HashSet::resize_set(int new_cap_) {
  vector<vector<int>> temp(new_cap_);
  _cap = new_cap_;
  for (const auto& bucket : buckets) {
    for (int elem : bucket) {
        int hash = h(elem,_cap);                   // bin in the new table
        temp[hash].push_back(elem);
      }
    }
    buckets = std::move(temp);
}
   

/**
 * @brief Construct an empty set
 *
 * @param h   Hash function (x, cap) -> bucket index
 * @param cap Initial number of buckets (default 10)
 *
 * Time:  O(cap)
 * Space: O(cap)
 */
HashSet::HashSet(int(*h)(int,int),int cap):h(h), _cap(cap),_size(0) {
  buckets.resize(_cap);
}

/**
 * @brief Return whether x is in the set
 *
 * @param x Element to look up
 * @return  true if x is present
 *
 * Time:  O(1) average, O(n) worst case
 * Space: O(1)
 */
//Time O(1) average
//Space O(1)
bool HashSet::contains(int x) {
  int bin = h(x,_cap);
  for(auto val: buckets[bin]) {
    if(x==val) return true;
  }
  return false;
}

/**
 * @brief Add x to the set; do nothing if it is already present
 *
 * @param x Element to add
 *
 * Algorithm:
 * 1. Return if x already exists.
 * 2. Append x to its bucket, increment size, and double the table if the
 *    load factor exceeds 1.
 *
 * Time:  O(1) amortized average; O(n + cap) when a resize happens
 * Space: O(1) amortized
 */
//Time O(1) amortized average
//Space O(1) amortized
void HashSet::add(int x) {
  if(contains(x)) return;
  int bin = h(x,_cap);
  buckets[bin].push_back(x);
  _size+=1;
  //resize if needed.
  double loadFactor = static_cast<double>(_size) / _cap;
  if (loadFactor > 1) {
    resize_set(_cap * 2);                          // grow
  }
}

/**
 * @brief Remove x from the set if present
 *
 * @param x Element to remove
 *
 * Algorithm:
 * 1. Return if x is absent.
 * 2. Find x's index in its bucket, overwrite it with the bucket's last
 *    element, and pop_back (O(1) delete).
 * 3. Halve the table if the load factor drops below 0.25 and cap > 10.
 *
 * Time:  O(1) amortized average; O(n + cap) when a resize happens
 * Space: O(1) amortized
 */
//Time O(1) amortized average
//Space O(1) amortized
void HashSet::remove(int x) {
  if(!contains(x)) return ;
  int bin = h(x,_cap);
  int index = -1;
  int n = buckets[bin].size();
  for(int i=0;i<n;++i) {
    if(buckets[bin][i] == x) {
      index = i; break;
    }
  }
  if(index!=-1) {
    buckets[bin][index] = buckets[bin][buckets[bin].size()-1];   // swap-with-last
    buckets[bin].pop_back();
    _size-=1;
  }
  double loadFactor = static_cast<double>(_size) / _cap;
  if (loadFactor < 0.25 && _cap > 10) {
    resize_set(_cap / 2);                          // shrink
  }
}

// To execute C++, please define "int main()"
int main() {
  HashSet s(h);
  cout<<boolalpha;cout<<s.contains(1)<<"\n";
  s.add(1);
  s.add(3);
  s.add(5);
  s.add(7);
  cout<<boolalpha;cout<<s.contains(3)<<"\n";
  s.remove(5);
  cout<<boolalpha;cout<<s.contains(5)<<"\n";
  return 0;
}

// # Hash Set Class

// Implement a hash set data structure with the following API:

// - `add(x)`: if `x` is not in the set, add `x` to the set. If `x` is already in the set, do nothing.
// - `remove(x)`: if `x` is in the set, remove it from the set.
// - `contains(x)`: return whether the element `x` is in the set.
// - `size()`: return the number of elements in the set.

// Constraints:

// - If your language is typed, you can either implement a hash set for integers, or make it generic.
// - The set will contain at most `10^6` elements.
