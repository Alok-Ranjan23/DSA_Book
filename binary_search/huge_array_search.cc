/**
 * @file huge_array_search.cc
 * @brief Binary Search in an unbounded/infinite sorted array
 * 
 * This file implements a search algorithm for a sorted array where the
 * length is unknown and potentially very large (won't fit in memory).
 * Access is only through an API that returns -1 for out-of-bounds indices.
 * 
 * Key Concepts:
 * - Exponential search to find upper bound
 * - Binary search within the found range
 * - Handling unknown array boundaries
 * - Two-phase approach: bound finding + searching
 * 
 * Time Complexity: O(log n) where n is the position of target
 *   - Phase 1 (Bound finding): O(log n) - doubles until past target
 *   - Phase 2 (Binary search): O(log n) - standard binary search
 * Space Complexity: O(1) - only uses constant extra space
 * 
 * Algorithm Pattern: Exponential Search + Binary Search
 */

#include <iostream>
#include <vector>
using namespace std;

/*============================================================================
 * HUGE ARRAY CLASS (Simulates API)
 *============================================================================*/

/**
 * @class HugeArray
 * @brief Simulates a huge array with limited API access
 * 
 * In real scenarios, this would be a remote API or database query.
 * fetch(i) returns -1 for out-of-bounds access (no length API available).
 */
class HugeArray {
private:
    std::vector<int> data;
public:
    HugeArray(std::vector<int> input) : data(input) {}
    
    /**
     * @brief Fetches element at index i
     * @param i Index to fetch (0-based)
     * @return Element at index i, or -1 if out of bounds
     */
    int fetch(long long i) {
        if (i < 0 || i >= static_cast<long long>(data.size())) return -1;
        return data[i];
    }
};

/*============================================================================
 * EXPONENTIAL + BINARY SEARCH IMPLEMENTATION
 *============================================================================*/

/**
 * @brief Searches for target in a huge array with unknown length
 * @param obj HugeArray object providing fetch() API
 * @param target The value to search for
 * @return Index of target if found, -1 otherwise
 * 
 * Algorithm:
 * Phase 1 - Exponential Search (Find bounds):
 *   1. Start with range [0, 1]
 *   2. Double the right bound until arr[r] >= target or out of bounds
 *   3. If r goes out of bounds, binary search to find actual array end
 * 
 * Phase 2 - Binary Search:
 *   4. Standard binary search in range [l, r]
 *   5. Return leftmost occurrence if duplicates exist
 * 
 * Why exponential doubling?
 * - If target is at position n, we find bounds in O(log n) steps
 * - Each doubling: 1 -> 2 -> 4 -> 8 -> ... -> n takes log(n) steps
 * 
 * Visual Example (arr = [1,3,5,7,9], target = 7):
 *   r: 1 -> 2 -> 4 (arr[4]=9 >= 7, stop)
 *   Binary search in [2, 4] -> find 7 at index 3
 */
long long hb_search(HugeArray obj, int target) {
  long long r = 1;
  long long l = 0;
  
  // Early returns for trivial cases
  if(obj.fetch(l) == target) return l;
  if(obj.fetch(r) == target) return r;
  
  // Phase 1: Exponential search to find upper bound
  // Double r until we find a value >= target or go out of bounds
  while(obj.fetch(r) != -1 && obj.fetch(r) < target) {
    l = r;
    r *= 2;
  }
  
  // Handle case where r went out of bounds
  // Binary search to find the actual last valid index
  if(obj.fetch(r) == -1) {
    long long lo = l, hi = r;
    while(hi - lo > 1) {
      long long m = lo + (hi - lo) / 2;
      if(obj.fetch(m) == -1) hi = m;
      else lo = m;
    }
    r = lo;  // r now points to last valid index
  }
  
  // Phase 2: Binary search within [l, r]
  long long ans = -1;
  while(l <= r) {
    long long m = l + (r - l) / 2;
    if(obj.fetch(m) == target) {
      ans = m;
      r = m - 1;          // Continue searching left for first occurrence
    } else if(obj.fetch(m) > target) {
      r = m - 1;          // Target in left half
    } else {
      l = m + 1;          // Target in right half
    }
  }
  
  return ans;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Example 1: Target exists in middle
  HugeArray obj = HugeArray(vector<int>{1, 3, 5, 7, 9});
  int target = 5;
  long long index = hb_search(obj, target);
  if(index == -1) {
    cout << "The target " << target << " is not in the array.\n";
  } else {
    cout << "The target " << target << " is at index " << index << ".\n";
  }

  // Example 2: Target smaller than all elements
  obj = HugeArray(vector<int>{2, 4, 6, 8, 10});
  target = 1;
  index = hb_search(obj, target);
  if(index == -1) {
    cout << "The target " << target << " is not in the array.\n";
  } else {
    cout << "The target " << target << " is at index " << index << ".\n";
  }

  // Example 3: Target larger than all elements
  obj = HugeArray(vector<int>{1, 3, 5, 7, 9});
  target = 10;
  index = hb_search(obj, target);
  if(index == -1) {
    cout << "The target " << target << " is not in the array.\n";
  } else {
    cout << "The target " << target << " is at index " << index << ".\n";
  }

  // Example 4: Target at end, r doubles past array bounds
  // This test case previously failed before the bug fix
  obj = HugeArray(vector<int>{1, 3, 5, 7});
  target = 7;
  index = hb_search(obj, target);
  if(index == -1) {
    cout << "The target " << target << " is not in the array.\n";
  } else {
    cout << "The target " << target << " is at index " << index << ".\n";
  }

  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT
 *============================================================================
 * 
 * # Search in Huge Array
 * 
 * We are trying to search for a target integer, `target`, in a sorted array 
 * of positive integers (duplicates allowed) that is too big to fit into 
 * memory. We can only access the array through an API, `fetch(i)`, which 
 * returns the value at index `i` if `i` is within bounds or `-1` otherwise.
 * 
 * Using as few calls to the API as possible, return the index of the 
 * `target`, or `-1` if it does not exist. If the `target` appears multiple 
 * times, return any of the indices.
 * 
 * There is no API to get the array's length.
 * 
 * Note: The array is 0-indexed and all elements in the array are positive.
 * 
 * Example 1: arr = [1, 3, 5, 7, 9], target = 5
 * Output: 2. The target 5 is at index 2.
 * 
 * Example 2: arr = [2, 4, 6, 8, 10], target = 1
 * Output: -1. The target 1 is not in the array.
 * 
 * Example 3: arr = [1, 3, 5, 7, 9], target = 10
 * Output: -1. The target 10 is not in the array.
 * 
 * Constraints:
 * - The array is sorted in ascending order
 * - The array may contain duplicates
 * - All numbers in the array are positive
 * - target is positive
 * - The length of the array is at most 10^9
 * 
 *============================================================================*/
