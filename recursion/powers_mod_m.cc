/**
 * @file powers_mod_m.cc
 * @brief Compute a^p mod m efficiently using binary exponentiation
 * 
 * Computes large powers under modulo without overflow by applying
 * modulo at each step and using the fast exponentiation technique.
 * 
 * Key Concepts:
 * - Binary exponentiation (exponentiation by squaring)
 * - Modular arithmetic property: (a * b) % m = ((a % m) * (b % m)) % m
 * - Reduces O(p) multiplications to O(log p) multiplications
 * 
 * Time Complexity: O(log p) - power is halved at each recursive step
 * Space Complexity: O(log p) - recursion stack depth
 * 
 * Mathematical basis:
 * - a^0 = 1
 * - If p is even:  a^p = (a^2)^(p/2)
 * - If p is odd:   a^p = a * (a^2)^((p-1)/2)
 */

#include <iostream>
using namespace std;

/**
 * @brief Computes (a^p) % m using binary exponentiation
 * @param a Base value (1 < a ≤ 10^9)
 * @param p Exponent (0 ≤ p ≤ 10^9)
 * @param m Modulus (1 < m ≤ 10^9)
 * @return (a^p) % m
 * 
 * Algorithm:
 * 1. Base case: a^0 = 1
 * 2. If p is even: a^p = (a^2)^(p/2), apply mod at each step
 * 3. If p is odd:  a^p = a * (a^2)^((p-1)/2), apply mod at each step
 * 
 * The key insight is that we square 'a' and halve 'p' at each step,
 * reducing the problem size logarithmically.
 */
long powermodm(long a, long p, long m) {
  if(p==0) return 1;
  if(p%2==0) {
    return powermodm((a*a)%m,p/2,m)%m;
  }
  return (a*(powermodm((a*a)%m,(p-1)/2,m)%m))%m;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  cout<<powermodm(2,5,100)<<"\n";
  cout<<powermodm(2,5,30)<<"\n";
  cout<<powermodm(123456789,987654321,1000000007)<<"\n";
  cout<<powermodm(3,1,5)<<"\n";
  cout<<powermodm(5,3,7)<<"\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Powers Mod M
 * 
 * Given three integers `a > 1`, `p ≥ 0`, and `m > 1`, compute `a^p % m` 
 * while avoiding storing intermediate values much larger than `m`.
 * 
 * The basic recurrence relation for powers is:
 * - `a^0 = 1`
 * - For `p > 0`, `a^p = a * a^(p-1)`
 * 
 * When it comes to the modulo operation, we can apply it at each step 
 * without affecting the result:
 * - `a^0 % m = 1`
 * - For `p > 0`, `a^p % m = (a * (a^(p-1) % m)) % m`
 * 
 * Example 1: a = 2, p = 5, m = 100
 * Output: 32
 * 
 * Example 2: a = 2, p = 5, m = 30
 * Output: 2
 * 
 * Example 3: a = 123456789, p = 987654321, m = 1000000007
 * Output: 652541198
 * 
 * Example 4: a = 3, p = 1, m = 5
 * Output: 3
 * 
 * Example 5: a = 5, p = 3, m = 7
 * Output: 6
 * 
 * Constraints:
 * - `1 < a ≤ 10^9`
 * - `0 ≤ p ≤ 10^9`
 * - `1 < m ≤ 10^9`
 * 
 *============================================================================*/
