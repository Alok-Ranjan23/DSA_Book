/**
 * @file exclusive_product.cc
 * @brief For every index, the product of all other elements, modulo 10^9 + 7
 *
 * Dividing the total product by arr[i] fails: values can be 0, and division
 * does not work with a running modulo. Instead, the product of everything
 * except arr[i] is (product of everything to its left) * (product of
 * everything to its right). Prefix and suffix product arrays give both
 * sides in O(1).
 *
 * Key Concepts:
 * - Prefix products: prefix_product[i] = arr[0] * ... * arr[i] (mod M)
 * - Suffix products: suffix_product[i] = arr[i] * ... * arr[n-1] (mod M)
 * - res[i] = prefix_product[i-1] * suffix_product[i+1]; the two ends use
 *   only one side (res[0] = suffix_product[1], res[n-1] = prefix_product[n-2])
 * - Take the modulo after every multiplication, widening to a 64-bit type
 *   first so the product of two values < M does not overflow
 * - No division, so zeros are handled naturally
 *
 * Time Complexity: O(n)
 *   - Three linear passes (prefix, suffix, result).
 *
 * Space Complexity: O(n)
 *   - The prefix, suffix, and result arrays.
 */
#include <iostream>
#include <vector>
using namespace std;

int const mod = 1000000007;

/**
 * @brief Return res where res[i] = product of arr[j] for all j != i, mod M
 *
 * @param arr Non-negative integers (length n >= 2)
 * @return    Exclusive products modulo 10^9 + 7
 *
 * Algorithm:
 * 1. Build prefix_product left to right and suffix_product right to left.
 * 2. res[0] = suffix_product[1]; res[n-1] = prefix_product[n-2].
 * 3. For 0 < i < n-1: res[i] = prefix_product[i-1] * suffix_product[i+1].
 *
 * Time:  O(n) -- three linear passes
 * Space: O(n) -- prefix + suffix + result
 */
//Time O(n)   (prefix pass + suffix pass + result pass)
//Space O(n)  (prefix + suffix + result arrays)
vector<int> exclusive_product(vector<int>& arr) {
  int n = arr.size();
  vector<int> prefix_product(n);                   // arr[0..i] (mod M)
  prefix_product[0] = arr[0];
  for(int i=1;i<n;++i) {
    prefix_product[i] = (static_cast<long>(prefix_product[i-1])*arr[i])%mod;
  }
  vector<int> suffix_product(n);                   // arr[i..n-1] (mod M)
  suffix_product[n-1] = arr[n-1];
  for(int i=n-2;i>=0;--i) {
    suffix_product[i] = (static_cast<long>(suffix_product[i+1])*arr[i])%mod;
  }
  vector<int> res(n);
  
  if(n>=2) res[0] = suffix_product[1];             // nothing on the left
  res[n-1] = prefix_product[n-2];                  // nothing on the right
  for(int i=1;i<n-1;++i) {
    res[i] = (static_cast<long>(prefix_product[i-1]) *   // left of i
              static_cast<long>(suffix_product[i+1]))%mod; // right of i
  }
  return res;
}

// To execute C++, please define "int main()"
int main() {
  vector<int> arr {1,3,2,1};
  for(auto& val: exclusive_product(arr)) {cout<<val<<" ";}cout<<"\n";
  arr = {0,1,0};
  for(auto& val: exclusive_product(arr)) {cout<<val<<" ";}cout<<"\n";
  return 0;
}

// # Exclusive Product

// Given an array of non-negative integers, `arr`, return an array with the same length where index `i` contains the product of all the elements in `arr` except `arr[i]`. Since the values could be very large, return them modulo `10^9 + 7`.

// Example 1:
// arr = [1, 3, 2, 1]
// Output: [6, 2, 3, 6]

// Example 2:
// arr = [0, 1, 0]
// Output: [0, 0, 0]

// Constraints:

// - For any `i`, `0 ≤ arr[i] ≤ 10000`.
// - `2 ≤ n ≤ 10^6`, where `n` is the length of `arr`.

// Note: the "obvious" solution is to compute the total product and then divide it by each element. However, the total product could be up to `10000^n = 10^4000000`. Even if your language supports arbitrary integers, we don't want to work with numbers that large (at that point, arithmetic operations are not 'constant time' anymore).

// Instead, we should use the fact that, instead of applying modulo at the end, we can apply at each step without affecting the final result. This will keep any products we compute below `10^9 + 7`. However, applying the modulo at each step only works for addition, subtraction, and multiplication, not division. Dividing first and then applying modulo yields different results than applying modulo and then dividing: `(12 / 3) % 5 != (12 % 5) / 3`.

// This means that we need to find a way to solve this problem without using division at the end.
