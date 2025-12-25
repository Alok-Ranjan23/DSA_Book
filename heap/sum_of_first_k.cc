/**
 * @file sum_of_first_k.cc
 * @brief Sum of First K Prime Powers using K-Way Merge with Min-Heap
 * 
 * This file implements a function that finds the sum of the first k numbers
 * that are positive powers of given distinct primes.
 * 
 * Key Concepts:
 * - K-Way Merge: Each prime generates an infinite sorted sequence of powers
 * - Min-Heap: Efficiently extracts the smallest power across all sequences
 * - Lazy Generation: Only compute next power when current one is consumed
 * 
 * Algorithm:
 * 1. Initialize min-heap with p^1 for each prime p
 * 2. Pop the smallest power, add to sum
 * 3. Push the next power of that same prime (current * base)
 * 4. Repeat until we've summed k powers
 * 
 * Why no duplicates?
 * - Powers of distinct primes are always distinct
 * - Fundamental Theorem of Arithmetic: unique prime factorization
 * - So 2^a ≠ 3^b for any positive integers a, b
 * 
 * Time Complexity: O(k log m) where m = number of primes
 *   - Each of k iterations: one pop O(log m) + one push O(log m)
 * 
 * Space Complexity: O(m) - heap stores exactly one entry per prime
 */

#include <functional>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const long long MOD = 1e9 + 7;

/*============================================================================
 * FUNCTION IMPLEMENTATION
 *============================================================================*/

/**
 * @brief Computes sum of first k prime powers
 * @param primes Vector of distinct prime numbers
 * @param k Number of prime powers to sum
 * @return Sum of first k prime powers, modulo 10^9+7
 * 
 * Heap Structure: {current_power, base_prime}
 * - Uses min-heap to always extract smallest power
 * - base_prime used to compute next power: current * base
 * 
 * Time Complexity: O(k log m)
 */
long long sum_first_k(vector<int>& primes, int k) {
  // Edge case: k <= 0 means sum nothing
  if (k <= 0) return 0;
  
  // Min-heap: {current_power, base_prime}
  // Using long long to prevent overflow (primes^power can exceed int)
  priority_queue<pair<long long, int>,
                 vector<pair<long long, int>>,
                 greater<pair<long long, int>>> pq;
  
  // Step 1: Initialize heap with p^1 for each prime
  for (auto& x : primes) {
    pq.push({x, x});
  }
  
  long long sum_primes = 0;
  int counter = 0;
  
  // Step 2-4: Extract min, add to sum, push next power
  while (!pq.empty()) {
    auto p = pq.top();
    auto power = p.first;
    auto base = p.second;
    pq.pop();
    
    // Add current power to sum (with modulo)
    sum_primes = (sum_primes + power % MOD) % MOD;
    counter++;
    
    // Done if we've summed k powers
    if (counter == k) return sum_primes;
    
    // Push next power of same prime (if within bounds)
    // Limit to 10^18 to prevent overflow in multiplication
    long long next_power = power * base;
    if (next_power <= 1e18) {
      pq.push({next_power, base});
    }
  }
  
  return sum_primes;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  // Test 1: primes = [2], k = 1
  // Powers of 2: 2, 4, 8, 16, ...
  // First 1: 2 -> Sum = 2
  vector<int> primes {2};
  int k = 1;
  cout << sum_first_k(primes, k) << "\n";  // Expected: 2
  
  // Test 2: primes = [5], k = 3
  // Powers of 5: 5, 25, 125, 625, ...
  // First 3: 5 + 25 + 125 = 155
  primes = {5};
  k = 3;
  cout << sum_first_k(primes, k) << "\n";  // Expected: 155
  
  // Test 3: primes = [2, 3], k = 7
  // Powers of 2: 2, 4, 8, 16, 32, ...
  // Powers of 3: 3, 9, 27, 81, ...
  // Merged:      2, 3, 4, 8, 9, 16, 27, ...
  // First 7: 2 + 3 + 4 + 8 + 9 + 16 + 27 = 69
  primes = {2, 3};
  k = 7;
  cout << sum_first_k(primes, k) << "\n";  // Expected: 69
  
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Sum Of First K Prime Powers
 * 
 * Given a non-empty array, `primes`, of **distinct prime** numbers, and a 
 * positive number `k`, return the sum of the first `k` numbers that are a 
 * positive power of a number in `primes`.
 * 
 * If the answer is larger than `10^9+7`, return it modulo `10^9+7`.
 * 
 * Example 1: primes = [2], k = 1
 * Output: 2
 * The first positive power of 2 is 2^1 = 2.
 * 
 * Example 2: primes = [5], k = 3
 * Output: 155
 * The first 3 positive powers of 5 are 5, 25, and 125.
 * 
 * Example 3: primes = [2, 3], k = 7
 * Output: 69
 * The first 7 numbers that are a positive power of 2 or 3 are:
 * 2, 3, 4, 8, 9, 16, and 27.
 * 
 * Constraints:
 * - `1 <= primes.length <= 10^4`
 * - Each element in `primes` is a distinct prime number
 * - `0 <= k <= 10^6`
 * 
 *============================================================================*/
