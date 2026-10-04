/**
 * @file hash_set_class_extension.cc
 * @brief Hash set of ints (separate chaining) extended with elements, union
 *        and intersection
 *
 * Same core as hash_set_class.cc: a vector of buckets, each a vector of ints,
 * with element x stored in bucket h(x, cap) using the multiplicative (Knuth)
 * hash floor(cap * frac(x * C)), C = (sqrt(5) - 1) / 2. On top of add /
 * remove / contains / size, it exposes elements(), union_set() and
 * intersection_set(), each of which builds a brand-new set.
 *
 * Key Concepts:
 * - Separate chaining with load-factor-driven resizing (grow x2 when > 1,
 *   shrink /2 when < 0.25 and cap > 10)
 * - Union: add every element of both sets into a fresh set; add() already
 *   ignores duplicates, so shared elements appear once
 * - Intersection: iterate over this set and keep only elements that s
 *   contains (O(1) average membership test)
 *
 * @warning h() strips the fractional part with static_cast<int>, which
 *          truncates toward zero. For a negative element the "fraction" is
 *          negative, so h() returns a negative bucket index (out of bounds).
 *          Only non-negative elements are safe.
 *
 * Time Complexity (n = |this|, m = |s|, cap = number of buckets):
 *   - contains:          O(1) average, O(n) worst case
 *   - add / remove:      O(1) amortized average
 *   - elements:          O(n + cap)
 *   - union_set:         O(n + m + cap_this + cap_s) average
 *   - intersection_set:  O(n + cap_this) average
 *
 * Space Complexity: O(n + cap) for the set itself; union/intersection
 *   allocate a new set of O(n + m) / O(min(n, m)) elements.
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
  const double C = 0.6180339887;
  double x = val * C;
  x -= static_cast<int>(x);                        // keep fractional part
  x *= m;                                          // scale to [0, m)
  return static_cast<int>(x);
}

/// Hash set of ints with set-algebra extensions (elements, union, intersection).
class HashSetExt {
  int (*h)(int,int);                               ///< hash function (x, cap) -> bin
  int _cap;                                        ///< number of buckets
  int _size;                                       ///< number of elements stored
  vector<vector<int>> buckets;                     ///< buckets[bin] = chain of elements
  void resize_set(int new_cap);
  public:
  HashSetExt(int (*h)(int,int), int _cap=10);
  bool contains(int x) const;
  void add(int x);
  void remove(int x);
  /// @brief Number of elements in the set. Time O(1), Space O(1)
  int size() { return _size;}
  vector<int> elements() const;
  HashSetExt union_set(const HashSetExt& s);
  HashSetExt intersection_set(const HashSetExt& s);
};

/**
 * @brief Rehash every element into a new table with new_cap buckets
 *
 * @param new_cap New number of buckets
 *
 * Time:  O(n + new_cap)
 * Space: O(n + new_cap) for the temporary table
 */
//Time O(n + new_cap)
//Space O(n + new_cap)
void HashSetExt::resize_set(int new_cap) {
  vector<vector<int>> temp(new_cap);
  _cap = new_cap;
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
HashSetExt::HashSetExt(int(*h)(int,int),int cap):h(h), _cap(cap),_size(0) {
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
bool HashSetExt::contains(int x) const{
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
 * Time:  O(1) amortized average; O(n + cap) when a resize happens
 * Space: O(1) amortized
 */
//Time O(1) amortized average
//Space O(1) amortized
void HashSetExt::add(int x) {
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
 * Uses swap-with-last + pop_back inside the bucket, then halves the table if
 * the load factor drops below 0.25 and cap > 10.
 *
 * Time:  O(1) amortized average; O(n + cap) when a resize happens
 * Space: O(1) amortized
 */
//Time O(1) amortized average
//Space O(1) amortized
void HashSetExt::remove(int x) {
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

/**
 * @brief Return all elements of the set (order unspecified)
 *
 * @return Vector of n elements
 *
 * Time:  O(n + cap)
 * Space: O(n) for the result
 */
//Time O(n + cap)
//Space O(n)
vector<int> HashSetExt::elements() const {
  vector<int> res;
  for(auto& bucket: buckets) {
    for(auto& val: bucket) {
      res.push_back(val);
    }
  }
  return res;
}

/**
 * @brief Return a new set with every element in this set or in s
 *
 * @param s The other set
 * @return  this ∪ s
 *
 * Algorithm:
 * 1. Create an empty result set with the same hash function.
 * 2. Add all elements of this set, then all elements of s; add() skips
 *    duplicates, so common elements are stored once.
 *
 * Time:  O(n + m + cap_this + cap_s) average
 * Space: O(n + m)
 */
//Time O(n + m) average
//Space O(n + m)
HashSetExt HashSetExt::union_set(const HashSetExt& s) {
  HashSetExt res(h);
  vector<int> ele1 = elements();
  for(auto& val: ele1) {
    res.add(val);
  }
  vector<int> ele2 = s.elements();
  for(auto& val: ele2) {
    res.add(val);                                  // duplicates ignored by add()
  }
  return res;
}

/**
 * @brief Return a new set with only the elements present in both sets
 *
 * @param s The other set
 * @return  this ∩ s
 *
 * Algorithm: for each element of this set, keep it if s.contains() it.
 *
 * Time:  O(n + cap_this) average
 * Space: O(n) for the element list + O(min(n, m)) for the result
 */
//Time O(n) average
//Space O(n)
HashSetExt HashSetExt::intersection_set(const HashSetExt& s) {
  HashSetExt res(h);
  vector<int> ele1 = elements();
  for(auto& val: ele1) {
    if(s.contains(val)) res.add(val);              // O(1) average lookup in s
  }
  return res;
}

// To execute C++, please define "int main()"
int main() {
  HashSetExt s1(h);
  cout<<boolalpha;cout<<s1.contains(1)<<"\n";
  s1.add(1);
  s1.add(3);
  s1.add(5);
  s1.add(7);
  cout<<boolalpha;cout<<s1.contains(3)<<"\n";
  s1.remove(5);
  cout<<boolalpha;cout<<s1.contains(5)<<"\n";

  HashSetExt s2(h);
  cout<<boolalpha;cout<<s2.contains(1)<<"\n";
  s2.add(2);
  s2.add(4);
  s2.add(6);
  s2.add(8);
  cout<<boolalpha;cout<<s2.contains(8)<<"\n";
  s2.remove(8);
  cout<<boolalpha;cout<<s2.contains(8)<<"\n";
  HashSetExt s = s2.union_set(s1);
  for(auto& val: s.elements()) cout<<val<<" ";
  cout<<"\n";
  return 0;
}

// # Hash Set Class Extensions

// Implement a hash set data structure with the following API:

// - `add(x)`: if `x` is not in the set, add `x` to the set
// - `remove(x)`: if `x` is in the set, remove it from the set
// - `contains(x)`: return whether element `x` is in the set
// - `size()`: return the number of elements in the set

// Then extend it with these additional methods:

// - `elements()`: return all elements in the set in a dynamic array
// - `union(s)`: return a new set containing all elements in either this set or set `s`
// - `intersection(s)`: return a new set containing only elements present in this set and set `s`

// For each method, provide time and space complexity analysis.

// Constraints:

// - If your language is typed, you can either implement a hash set for integers, or make it generic.
// - The set will contain at most `10^6` elements.
