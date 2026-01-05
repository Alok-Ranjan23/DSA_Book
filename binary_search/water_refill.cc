/**
 * @file water_refill.cc
 * @brief Binary Search without Division - Water container problem
 * 
 * This file implements binary search to find how many times a smaller
 * container can be poured into a larger one without overflow, with the
 * constraint that division operation is not allowed.
 * 
 * Key Concepts:
 * - Binary search using only bit shifts (>>1) for division by 2
 * - Exponential search to find upper bound
 * - Mathematical constraint: b * times <= a
 * - Demonstrates binary search can work without standard division
 * 
 * Time Complexity: O(log(a/b))
 *   - Exponential phase: O(log(a/b)) doublings
 *   - Binary search phase: O(log(a/b)) iterations
 * Space Complexity: O(1)
 * 
 * Algorithm Pattern: Exponential Search + Binary Search (Division-free)
 * 
 * This is essentially computing floor(a/b) without using division!
 */

#include <iostream>
using namespace std;

/*============================================================================
 * WATER REFILLING - DIVISION-FREE BINARY SEARCH
 *============================================================================*/

/**
 * @brief Counts how many times container b can be poured into container a
 * @param a Capacity of the larger container (gallons)
 * @param b Capacity of the smaller container (gallons)
 * @return Maximum number of times b can be poured without overflow
 * 
 * Algorithm:
 * Phase 1 - Exponential Search (find upper bound):
 *   Start with times = 1, double until b * times > a
 *   This gives us a range [l, r] where answer lies
 * 
 * Phase 2 - Binary Search (find exact answer):
 *   Binary search in [l, r] for largest times where b * times <= a
 *   Use >>1 instead of /2 (constraint: no division allowed)
 * 
 * Why exponential search?
 *   - We don't know the upper bound initially
 *   - Doubling finds it in O(log n) steps
 *   - After doubling, l is valid (b*l <= a), r is invalid (b*r > a)
 * 
 * Example: a = 18, b = 5
 *   Phase 1: l=1 (5*1=5<=18), l=2 (5*2=10<=18), l=4 (5*4=20>18) STOP
 *            So l=2, r=4
 *   Phase 2: Binary search [2, 4]
 *            mid=3: 5*3=15<=18 ✓, l=3
 *            r-l=1, return l=3
 * 
 * Note: Using long long to prevent overflow in multiplication b*times
 */
int water_refilling(int a, int b) {
  /**
   * Validation function: checks if pouring 'times' containers is safe
   * Uses long long cast to prevent overflow in multiplication
   */
  auto isValid = [=](long long times) {
    return (long long)b * times <= a;
  };
  
  // Phase 1: Exponential search to find bounds
  long long l = 1;                          // Start with 1 (always valid since a > b)
  while(isValid(l * 2)) {                   // Keep doubling while valid
    l *= 2;
  }
  long long r = l * 2;                      // r is first invalid point
  
  // Phase 2: Binary search for exact transition point
  // Find largest l where isValid(l) is true
  while(r - l > 1) {
    long long mid = (l + r) >> 1;           // Division by 2 using right shift
    if(isValid(mid)) {
      l = mid;                              // mid is valid, search higher
    } else {
      r = mid;                              // mid is invalid, search lower
    }
  }
  
  return l;                                 // l is the largest valid count
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Example 1: 5 gallons poured 3 times = 15 gallons (18-15=3 remaining)
  int a = 18, b = 5;
  cout << water_refilling(a, b) << "\n";    // Output: 3
  
  // Example 2: 2 gallons poured 5 times = 10 gallons (exactly full)
  a = 10; b = 2;
  cout << water_refilling(a, b) << "\n";    // Output: 5
  
  // Example 3: 3 gallons poured 3 times = 9 gallons (10-9=1 remaining)
  a = 10; b = 3;
  cout << water_refilling(a, b) << "\n";    // Output: 3
  
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT
 *============================================================================
 * 
 * # Water Refilling
 * 
 * You have an empty container with a capacity of `a` gallons of water 
 * and another container with a capacity of `b` gallons. Return how many 
 * times you can pour the second container full of water into the first 
 * one without overflowing. Assume that `a > b`.
 * 
 * **Constraint:** You are not allowed to use the division operation, 
 * but you can still divide by powers of two with the right-shift 
 * operator, `>>`. Recall that `x >> 1` is the same as `x // 2`.
 * 
 * Example 1: a = 18, b = 5
 * Output: 3. After pouring 5 gallons three times, the first container 
 * will be at 15, and 5 more gallons would make it overflow.
 * 
 * Example 2: a = 10, b = 2
 * Output: 5
 * 
 * Example 3: a = 10, b = 3
 * Output: 3
 * 
 * Constraints:
 * - 1 <= b < a <= 10^9
 * - Division operation is not allowed (only right-shift for powers of 2)
 * 
 *============================================================================*/
