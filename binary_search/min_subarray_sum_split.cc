/**
 * @file min_subarray_sum_split.cc
 * @brief Binary Search on Answer - Minimize largest subarray sum when splitting
 * 
 * This file implements the classic "Split Array Largest Sum" problem using
 * binary search on the answer. Given an array, split it into k subarrays
 * such that the maximum sum among all subarrays is minimized.
 * 
 * Key Concepts:
 * - Binary search on answer space (possible sum values)
 * - Greedy validation: can we split into <= k parts with max sum <= mid?
 * - Monotonic property: larger allowed sum -> fewer subarrays needed
 * - Similar to "Capacity to Ship Packages", "Painter's Partition"
 * 
 * Time Complexity: O(n * log(sum - max))
 *   - Binary search: O(log(sum - max)) iterations
 *   - Validation: O(n) per iteration
 * Space Complexity: O(1)
 * 
 * Algorithm Pattern: Binary Search on Answer + Greedy Validation
 * 
 * Search space: [max(arr), sum(arr)]
 *   - Lower bound: largest element (each subarray must fit largest element)
 *   - Upper bound: total sum (entire array as one subarray)
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

/*============================================================================
 * VALIDATION FUNCTION
 *============================================================================*/

/**
 * @brief Checks if array can be split into <= k subarrays with max sum <= mid
 * @param arr The array to split
 * @param mid Maximum allowed sum for any subarray
 * @param k Maximum number of subarrays allowed
 * @return true if splitting is possible with given constraints
 * 
 * Greedy Algorithm:
 * 1. Start with first subarray
 * 2. Add elements to current subarray while sum <= mid
 * 3. When adding next element would exceed mid, start new subarray
 * 4. Count total subarrays needed
 * 5. Return true if count <= k
 * 
 * Why greedy works:
 * - We're checking feasibility, not finding optimal split
 * - Making each subarray as large as possible (up to mid) minimizes count
 * - If greedy needs > k subarrays, no valid split exists for this mid
 * 
 * Example: arr = [10, 5, 8, 9, 11], mid = 17, k = 3
 *   Subarray 1: [10, 5] sum=15 <= 17
 *   Subarray 2: [8, 9] sum=17 <= 17
 *   Subarray 3: [11] sum=11 <= 17
 *   Count = 3 <= k, valid!
 */
bool isValid(vector<int>& arr, long long mid, int k) {
  long long subarray_sum = 0;
  int subarray_count = 1;                   // Start with 1 subarray
  int n = arr.size();
  
  for(int i = 0; i < n; ++i) {
    subarray_sum += arr[i];
    
    if(subarray_sum > mid) {                // Current subarray would exceed limit
      subarray_count += 1;                  // Start new subarray
      subarray_sum = arr[i];                // New subarray starts with current element
    }
  }
  
  return subarray_count <= k;
}

/*============================================================================
 * BINARY SEARCH ON ANSWER
 *============================================================================*/

/**
 * @brief Finds minimum possible value of maximum subarray sum when split into k parts
 * @param arr Array to split
 * @param k Number of subarrays to create
 * @return Minimum achievable maximum subarray sum
 * 
 * Algorithm:
 * Binary search on the answer (maximum allowed subarray sum):
 * 
 * 1. Search range: [max(arr), sum(arr)]
 *    - Lower: largest element must fit in some subarray
 *    - Upper: entire array as single subarray (if k >= 1)
 * 
 * 2. For each candidate 'mid':
 *    - If isValid(mid, k): mid might be answer, try smaller (r = mid)
 *    - If not valid: need larger max sum (l = mid + 1)
 * 
 * 3. Return the converged answer
 * 
 * Visual for arr = [10, 5, 8, 9, 11], k = 3:
 *   Search: [11, 43]  (max=11, sum=43)
 *   mid=27: can split into 2 parts -> try smaller
 *   mid=19: can split into 3 parts -> try smaller
 *   mid=15: need 4 parts > 3 -> try larger
 *   mid=17: can split into 3 parts -> try smaller
 *   mid=16: need 4 parts > 3 -> try larger
 *   Answer: 17 with split [10,5], [8,9], [11]
 */
long long min_subarray_sum_split(vector<int>& arr, int k) {
  int n = arr.size();
  
  // Edge case: single element array
  if(n == 1) {
    if(k == 1) return arr[0];
    else return -1;                         // Can't split 1 element into k > 1 parts
  }
  
  // Binary search bounds
  long long l = *max_element(arr.begin(), arr.end());   // Minimum possible max sum
  long long r = accumulate(arr.begin(), arr.end(), 0LL); // Maximum possible max sum
  
  while(l < r) {
    long long mid = l + (r - l) / 2;
    
    if(isValid(arr, mid, k)) {
      r = mid;                              // mid works, try smaller
    } else {
      l = mid + 1;                          // mid too small, need larger
    }
  }
  
  return r;                                 // l == r == minimum valid answer
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Example 1: Split into [10,5], [8,9], [11] with max sum = 17
  vector<int> arr{10, 5, 8, 9, 11};
  int k = 3;
  cout << min_subarray_sum_split(arr, k) << "\n";  // Output: 17
  
  // Example 2: Split into [10,10,10], [10,10] with max sum = 30
  arr = {10, 10, 10, 10, 10};
  k = 2;
  cout << min_subarray_sum_split(arr, k) << "\n";  // Output: 30
  
  // Example 3: Each element is its own subarray
  arr = {1, 2, 3};
  k = 3;
  cout << min_subarray_sum_split(arr, k) << "\n";  // Output: 3
  
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT
 *============================================================================
 * 
 * # Min Subarray Sum Split
 * 
 * Given a non-empty array with `n` positive integers, `arr`, and a number 
 * `k` with `1 <= k <= n`, the goal is to split `arr` into `k` non-empty 
 * subarrays so that the largest sum across all subarrays is minimized. 
 * Return the largest sum across all `k` subarrays after making it as 
 * small as possible. Each subarray must contain at least one value.
 * 
 * Example 1: arr = [10, 5, 8, 9, 11], k = 3
 * Output: 17. There are six ways of splitting the array into three 
 * subarrays. The optimal split is: [10, 5], [8, 9], and [11]. The 
 * largest sum among the three subarrays is 17.
 * 
 * Example 2: arr = [10, 10, 10, 10, 10], k = 2
 * Output: 30. The optimal split is [10, 10, 10] and [10, 10].
 * 
 * Example 3: arr = [1, 2, 3], k = 3
 * Output: 3. Each element becomes its own subarray.
 * 
 * Constraints:
 * - 1 <= n <= 10^6
 * - 1 <= arr[i] <= 10^4
 * - 1 <= k <= n
 * 
 *============================================================================*/
