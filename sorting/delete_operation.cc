/**
 * @file delete_operation.cc
 * @brief Process Delete Operations on an Array using Pre-sorted Index Mapping
 * 
 * This file implements a function that processes a sequence of delete operations
 * on an array. Operations can either delete by index or delete the smallest
 * remaining element.
 * 
 * Key Concepts:
 * - Indirect Sorting: Sort indices by their values (not the values themselves)
 *   to precompute the order for "delete smallest" operations
 * - Stable Sort: Preserves original index order for equal values, ensuring
 *   tie-breaking by smaller index
 * - Exclusion Set: O(1) lookup to check if an index has been deleted
 * - Lazy Pointer (smallIdx): Tracks the next smallest un-deleted element
 *   in the pre-sorted order, avoiding re-scanning
 * 
 * Algorithm:
 * 1. Create include_index = [0, 1, ..., n-1]
 * 2. Stable-sort include_index by nums[i] ascending
 *    → include_index[0] is the index of the smallest element,
 *      include_index[1] is the next smallest, etc.
 * 3. For each operation:
 *    a. If op >= 0: mark index op as excluded (deleted)
 *    b. If op == -1: advance smallIdx past excluded indices,
 *       then mark include_index[smallIdx] as excluded
 * 4. Collect all non-excluded elements in original order
 * 
 * Why stable_sort?
 * - When two elements have equal values, the one with the smaller
 *   original index should be deleted first (per problem spec).
 * - Stable sort preserves the original index order for equal values.
 * 
 * Time Complexity: O(n log n) for the sort + O(n + m) for processing operations
 *   where m = number of operations
 * Space Complexity: O(n) for the index array and exclusion set
 */

#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

/*============================================================================
 * FUNCTION IMPLEMENTATION
 *============================================================================*/

/**
 * @brief Processes delete operations and returns the remaining elements
 * @param nums Original array of integers
 * @param op Array of operations: >= 0 means delete by index, -1 means delete smallest
 * @return Vector of remaining elements in their original order
 * 
 * Data Structures:
 * - include_index: Indices [0..n-1] sorted by nums value (ascending)
 *   Used to quickly find the next smallest un-deleted element.
 * - exclude: Set of deleted indices for O(1) membership checks
 * - smallIdx: Pointer into include_index tracking the next candidate
 *   for "delete smallest" operations. Only advances forward.
 * 
 * Time Complexity: O(n log n + m), where m = op.size()
 *   - Sorting indices: O(n log n)
 *   - Processing ops: O(n + m) amortized (smallIdx only moves forward)
 *   - Building result: O(n)
 */
vector<int> delete_op(vector<int>& nums,vector<int>& op) {
  vector<int> include_index;
  unordered_set<int> exclude;
  
  int n = nums.size();
  for(int i=0;i<n;++i) include_index.push_back(i);
  
  stable_sort(include_index.begin(), include_index.end(), [&nums](const int& i, const int& j)
   {return nums[i]<nums[j];});
  
  int smallIdx = 0;
  for(auto& o: op) {
    if(o>=0 && o<n) exclude.insert(o);
    else {
      while(smallIdx<n && exclude.count(include_index[smallIdx])) {
        smallIdx++;
      } 
      if(smallIdx<n) {
        exclude.insert(include_index[smallIdx]);
        smallIdx++;
      }
    }
  }

  std::vector<int> res;
  for (int i = 0; i < n; i++) {
    if (!exclude.count(i)) {
      res.push_back(nums[i]);
    }
  }
  return res;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Test 1: Mixed operations — expected: [50]
  // Delete index 2 (70), delete smallest (20), delete index 4 (80), delete smallest (30)
  vector<int> nums {50,30,70,20,80};
  vector<int> op {2,-1,4,-1};
  for (auto&x : delete_op(nums,op)) cout<<x<<" ";
  cout<<"\n";

  // Test 2: No operations — expected: [1, 2, 3]
  nums = {1,2,3};
  op = {};
  for (auto&x : delete_op(nums,op)) cout<<x<<" ";
  cout<<"\n";

  // Test 3: Delete all via smallest — expected: []
  nums = {1,2,3};
  op = {-1,-1,-1};
  for (auto&x : delete_op(nums,op)) cout<<x<<" ";
  cout<<"\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Delete Operations
 * 
 * You're given an array of n integers, nums, and another array of at most n
 * integers, operations, where each integer represents an operation:
 * 
 * - If the operation number is k >= 0, delete the number at index k in the
 *   original array if it has not been deleted yet. Otherwise, do nothing.
 * - If the operation number is -1, delete the smallest number in nums that
 *   has not been deleted yet, breaking ties by smaller index.
 * 
 * Return the state of nums after applying all the operations.
 * 
 * Constraints:
 * - 1 <= n <= 10^5
 * - Each element in nums is between -10^9 and 10^9
 * - operations.length <= n
 * - Each element in operations is between -1 and n-1
 * 
 *============================================================================*/
