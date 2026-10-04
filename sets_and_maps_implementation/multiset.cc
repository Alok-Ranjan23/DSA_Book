/**
 * @file multiset.cc
 * @brief Multiset of ints implemented with separate chaining and counts
 *
 * Instead of storing every copy, each distinct element is stored once as
 * (element, count) in bucket h(x, cap), where h is the multiplicative (Knuth)
 * hash floor(cap * frac(x * C)), C = (sqrt(5) - 1) / 2. Adding a copy bumps
 * the count; removing a copy decrements it and deletes the entry at zero.
 *
 * Key Concepts:
 * - (element, count) pairs: k copies of x cost O(1) space, not O(k)
 * - Two counters with different meanings:
 *     _size     = total copies (what size() must return)
 *     _num_keys = distinct elements (what actually occupies buckets)
 * - Load factor uses _num_keys / cap. Grow (x2) when > 1; shrink (/2) when
 *   < 0.25 and cap > 10. Resizing only happens when a key is created or
 *   deleted, never when just a count changes
 * - h() uses floor() so the fractional part is always in [0, 1); negative
 *   elements therefore hash to a valid bucket
 *
 * Time Complexity (u = distinct elements, cap = number of buckets):
 *   - contains:     O(1) average, O(u) worst case
 *   - add / remove: O(1) amortized average; a call that triggers a resize
 *                   costs O(u + cap)
 *   - size:         O(1)
 *
 * Space Complexity: O(u + cap) (independent of how many copies are stored)
 */
#include <cmath>
#include <ios>
#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Multiplicative hash: map val to a bucket index in [0, m)
 *
 * @param val The value to hash (negative values are fine)
 * @param m   Number of buckets
 * @return    floor(m * frac(val * C)), C = golden-ratio conjugate
 *
 * Time:  O(1)
 * Space: O(1)
 */
int h(int val, int m) {
  double C = 0.6180339887;
  double x = val * C;
  x -= floor(x);                                   // fractional part in [0, 1), also for negatives
  x*=m;                                            // scale to [0, m)
  return static_cast<int>(x); 
}

/// Multiset of ints storing (element, count) pairs with separate chaining.
class MultiSet {
  int (*h)(int,int);                               ///< hash function (x, cap) -> bin
  int _cap;                                        ///< number of buckets
  int _size;                                       ///< total copies stored
  int _num_keys;                                   ///< distinct elements (drives load factor)
  vector<vector<pair<int, int>>> buckets;          ///< buckets[bin] = chain of (element, count)
  void resize_set(int new_cap_);
  public:
  MultiSet(int (*h)(int,int), int cap=10);
  bool contains(int x);
  void add(int x);
  void remove(int x);
  /// @brief Number of elements including copies. Time O(1), Space O(1)
  int size() {return _size;}
};

/**
 * @brief Rehash every (element, count) entry into a table with new_cap_ buckets
 *
 * @param new_cap_ New number of buckets
 *
 * Time:  O(u + new_cap_)
 * Space: O(u + new_cap_) for the temporary table
 */
//Time O(u + new_cap_)
//Space O(u + new_cap_)
void MultiSet::resize_set(int new_cap_) {
  vector<vector<pair<int,int>>> temp(new_cap_);
  _cap = new_cap_;
  for (const auto& bucket : buckets) {
    for (auto& [elem,count] : bucket) {
        int hash = h(elem,_cap);                   // bin in the new table
        temp[hash].push_back({elem,count});
      }
    }
    buckets = std::move(temp);
}

/**
 * @brief Construct an empty multiset
 *
 * @param h   Hash function (x, cap) -> bucket index
 * @param cap Initial number of buckets (default 10)
 *
 * Time:  O(cap)
 * Space: O(cap)
 */
MultiSet::MultiSet(int(*h)(int,int),int cap):h(h), _cap(cap),_size(0),
    _num_keys(0) {
  buckets.resize(_cap);
}

/**
 * @brief Return whether at least one copy of x is present
 *
 * @param x Element to look up
 * @return  true if x's count is >= 1
 *
 * Time:  O(1) average, O(u) worst case
 * Space: O(1)
 */
//Time O(1) average
//Space O(1)
bool MultiSet::contains(int x) {
  int bin = h(x,_cap);
  for(auto& [val,_]: buckets[bin]) {
    if(x==val) return true;
  }
  return false;
}

/**
 * @brief Add one copy of x
 *
 * @param x Element to add
 *
 * Algorithm:
 * 1. _size += 1 (every add is one more copy).
 * 2. If x already has an entry, increment its count in place and return.
 * 3. Otherwise push (x, 1), _num_keys += 1, and double the table if
 *    _num_keys / cap exceeds 1.
 *
 * Time:  O(1) amortized average; O(u + cap) when a resize happens
 * Space: O(1) amortized
 */
//Time O(1) amortized average
//Space O(1) amortized
void MultiSet::add(int x) {
  int bin = h(x,_cap);
  _size+=1;
  for(auto& [val,count]: buckets[bin]) {
    if(val==x) {
      count+=1;                                    // existing element: one more copy
      return;
    }
  }
  buckets[bin].push_back({x,1});                   // new element
  _num_keys+=1;
  //resize if needed.
  double loadFactor = static_cast<double>(_num_keys) / _cap;
  if (loadFactor > 1) {
    resize_set(_cap * 2);                          // grow
  }
}

/**
 * @brief Remove one copy of x if present
 *
 * @param x Element to remove
 *
 * Algorithm:
 * 1. Find x's entry in its bucket; return if absent.
 * 2. _size -= 1. If count > 1, decrement it in place and return.
 * 3. Otherwise (last copy) delete the entry via swap-with-last + pop_back,
 *    _num_keys -= 1, and halve the table if _num_keys / cap < 0.25 and
 *    cap > 10.
 *
 * Time:  O(1) amortized average; O(u + cap) when a resize happens
 * Space: O(1) amortized
 */
//Time O(1) amortized average
//Space O(1) amortized
void MultiSet::remove(int x) {
  int bin = h(x,_cap);
  int index = -1;
  int n = buckets[bin].size();
  for(int i=0;i<n;++i) {
    if(buckets[bin][i].first == x) {
      index = i; break;
    }
  }
  if(index==-1) return;                            // x not present
  _size-=1;
  if(buckets[bin][index].second > 1) {
    buckets[bin][index].second-=1;                 // still has copies left
    return;
  }
  buckets[bin][index] = buckets[bin][n-1];         // last copy: swap-with-last delete
  buckets[bin].pop_back();
  _num_keys-=1;
  double loadFactor = static_cast<double>(_num_keys) / _cap;
  if (loadFactor < 0.25 && _cap > 10) {
    resize_set(_cap / 2);                          // shrink
  }
}

// To execute C++, please define "int main()"
int main() {
  MultiSet ms(h);
  cout<<boolalpha;cout<<ms.contains(2)<<"\n";
  ms.add(1);
  ms.add(2);
  ms.add(2);
  ms.add(2);
  ms.add(5);
  ms.add(6);
  cout<<boolalpha;cout<<ms.contains(2)<<"\n";
  ms.remove(2);
  cout<<boolalpha;cout<<ms.contains(2)<<"\n";
  ms.remove(2);
  cout<<boolalpha;cout<<ms.contains(2)<<"\n";
  ms.remove(2);
  cout<<boolalpha;cout<<ms.contains(2)<<"\n";
  return 0;
}

// # Multiset

// A multiset is a set that allows multiple copies of the same element. Implement a multiset data structure with the following API:

// - `add(x)`: adds a 'copy' of x to the multiset
// - `remove(x)`: removes a 'copy' of x from the multiset
// - `contains(x)`: returns whether x is in the multiset (at least one copy)
// - `size()`: returns the number of elements in the multiset (including copies)

// Constraints:

// - If your language is typed, you can either implement a multiset for integers, or make it generic.
// - The multiset will contain at most `10^6` elements.
