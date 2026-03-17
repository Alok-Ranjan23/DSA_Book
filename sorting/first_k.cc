/**
 * @file first_k.cc
 * @brief Find the K Smallest Elements — Multiple Approaches
 * 
 * This file implements four different approaches to find the k smallest
 * elements from an array of unique integers:
 * 
 * 1. QuickSelect (Randomized)     — O(n) average, O(n^2) worst
 * 2. Max-Heap with size-k window  — O(n log k)
 * 3. Max-Heap (insert all, pop)   — O(n log k)
 * 4. Min-Heap (insert all, pop k) — O(n log n)
 * 5. Sorting                       — O(n log n)
 * 
 * Key Concepts:
 * - QuickSelect: Partition-based selection (like quicksort but only recurses
 *   into one side). Randomized pivot avoids worst-case on average.
 * - Max-Heap of size k: Maintains a "window" of k smallest seen so far.
 *   Any element larger than the heap top cannot be in the k smallest.
 * - Trade-off: QuickSelect is fastest on average but has poor worst-case.
 *   Heap approaches have guaranteed O(n log k) but larger constant factors.
 * 
 * Algorithm (QuickSelect):
 * 1. Pick a random pivot
 * 2. Partition into smaller[], equal[], larger[]
 * 3. If k <= |smaller|, recurse into smaller
 * 4. If k <= |smaller| + |equal|, pivot is the answer
 * 5. Else recurse into larger with k' = k - |smaller| - |equal|
 * 6. After finding kth value, collect all elements <= kth value
 * 
 * Algorithm (Max-Heap of size k):
 * 1. Insert first k elements into a max-heap
 * 2. For each remaining element: if smaller than heap top, replace top
 * 3. Heap always contains the k smallest elements seen so far
 * 
 * Time Complexities:
 * - find_k (QuickSelect):      O(n) average, O(n^2) worst
 * - find_k_max_heap:           O(n log k) - optimal for k << n
 * - find_k_max_heap2:          O(n log k) - variant with lazy size control
 * - find_k_min_heap:           O(n log n) - builds full heap
 * - find_k_sorting:            O(n log n)
 * 
 * Space Complexity: O(n) for QuickSelect partitions, O(k) for heap approaches
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <random>
using namespace std;

/*============================================================================
 * APPROACH 1: QuickSelect (Randomized) — O(n) average
 *============================================================================*/

/**
 * @brief Finds the k-th smallest value using randomized QuickSelect
 * @param arr Array of unique integers
 * @param k Position to find (1-indexed: k=1 means smallest)
 * @return The k-th smallest value
 * 
 * Three-way partition (Dutch National Flag variant):
 * - smaller[]: elements < pivot
 * - equal[]:   elements == pivot
 * - larger[]:  elements > pivot
 * 
 * Recurse into only one partition based on sizes.
 * Random pivot gives O(n) expected time (each level reduces by ~half).
 * 
 * Time Complexity: O(n) average, O(n^2) worst case
 */
int quickselect(std::vector<int>& arr, int k) {
  size_t n = arr.size();
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<size_t> dis(0, n-1);
  int pivot = arr[dis(gen)];
  
  vector<int> smaller,equal,larger;
  for(auto&x: arr) {
    if(x<pivot) smaller.push_back(x);
    else if(x==pivot) equal.push_back(x);
    else larger.push_back(x);
  }
  int S = smaller.size();
  int E = equal.size();

  if (k <= S) {
    return quickselect(smaller, k);
  } else if (k <= S + E) {
    return equal[0];
  }
  return quickselect(larger, k - S - E);
}

/**
 * @brief Returns k smallest elements using QuickSelect
 * @param arr Array of unique integers
 * @param k Number of smallest elements to return
 * @return Vector of k smallest elements (unordered)
 * 
 * Uses quickselect to find the k-th smallest value, then collects
 * all elements <= that value in a single pass.
 * 
 * Time Complexity: O(n) average
 */
vector<int> find_k(vector<int>& arr,int k) {
  int kthVal = quickselect(arr, k);
  std::vector<int> result;
  for (int x : arr) {
    if (x <= kthVal) {
      result.push_back(x);
    }
  }
  return result;
}

/*============================================================================
 * APPROACH 2: Max-Heap with lazy size control — O(n log k)
 *============================================================================*/

/**
 * @brief Returns k smallest using a max-heap that stays at size k
 * @param arr Input array
 * @param k Number of smallest elements to return
 * @return Vector of k smallest elements
 * 
 * Inserts every element, but pops whenever size exceeds k.
 * The max-heap ensures the largest element is always evicted first,
 * so the remaining k elements are the smallest.
 * 
 * Time Complexity: O(n log k) - each push/pop is O(log k)
 */
vector<int> find_k_max_heap2(vector<int>& arr,int k) {
  priority_queue<int> pq;
  int n = arr.size();
  for(int i=0;i<n;++i) {
    pq.push(arr[i]);
    if(pq.size()>static_cast<size_t>(k)) pq.pop();
  }
  vector<int> res;
  while(!pq.empty()) {
    res.push_back(pq.top());pq.pop();
  }
  return res;
}

/*============================================================================
 * APPROACH 3: Max-Heap with early rejection — O(n log k)
 *============================================================================*/

/**
 * @brief Returns k smallest using a max-heap with eager comparison
 * @param arr Input array
 * @param k Number of smallest elements to return
 * @return Vector of k smallest elements
 * 
 * Optimized variant: initializes heap with first k elements, then only
 * inserts an element if it's smaller than the current max (heap top).
 * Saves unnecessary push+pop cycles for elements larger than all k smallest.
 * 
 * Time Complexity: O(n log k) - but often faster in practice due to skips
 */
vector<int> find_k_max_heap(vector<int>& arr,int k) {
  if(k==0) return {};
  priority_queue<int> pq {arr.begin(),arr.begin()+k};
  int n = arr.size();
  for(int i=k;i<n;++i) {
    if(arr[i]<pq.top()) {
      pq.pop();pq.push(arr[i]);
    }
  }
  vector<int> res;
  while(!pq.empty()) {
    res.push_back(pq.top());pq.pop();
  }
  return res;
}

/*============================================================================
 * APPROACH 4: Min-Heap (full heapify) — O(n log n)
 *============================================================================*/

/**
 * @brief Returns k smallest using a min-heap built from the entire array
 * @param arr Input array
 * @param k Number of smallest elements to return
 * @return Vector of k smallest elements (in ascending order)
 * 
 * Builds a min-heap with all n elements, then extracts k times.
 * Simple but less efficient than max-heap approach when k << n.
 * 
 * Time Complexity: O(n log n) for heap construction + O(k log n) for extraction
 */
vector<int> find_k_min_heap(vector<int>& arr,int k) {
  priority_queue<int,vector<int>,greater<int>> pq {arr.begin(),arr.end()};
  vector<int> res;
  while(!pq.empty() && k--) {
    res.push_back(pq.top());pq.pop();
  }
  return res;
}

/*============================================================================
 * APPROACH 5: Sorting — O(n log n)
 *============================================================================*/

/**
 * @brief Returns k smallest by sorting the entire array
 * @param arr Input array (modified: sorted in-place)
 * @param k Number of smallest elements to return
 * @return Vector of k smallest elements (in ascending order)
 * 
 * Simplest approach: sort then take the first k elements.
 * Modifies the input array.
 * 
 * Time Complexity: O(n log n)
 */
vector<int> find_k_sorting(vector<int>& arr,int k) {
  sort(arr.begin(),arr.end());
  return vector<int>(arr.begin(),arr.begin()+k);
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Test 1: k=5 from 12 elements — expected k smallest: {2, 3, 4, 5, 8}
  vector<int> arr {15, 4, 13, 8, 10, 5, 2, 20, 3, 9, 11, 27};int k=5;
  for(auto&x: find_k(arr,k))cout<<x<<" ";
  cout<<"\n";

  // Test 2: k=1 — expected: {1}
  arr = {5,3,1,4,2};k=1;
  for(auto&x: find_k(arr,k))cout<<x<<" ";
  cout<<"\n";

  // Test 3: k=4 — expected: {1, 2, 3, 4}
  arr = {5,3,1,4,2};k=4;
  for(auto&x: find_k(arr,k))cout<<x<<" ";
  cout<<"\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # First K
 * 
 * Given an array of n unique integers, arr, return the k smallest numbers,
 * in any order.
 * 
 * Constraints:
 * - 0 <= k <= n <= 10^5
 * - All elements in arr are unique
 * - Each element in arr is between -10^9 and 10^9
 * 
 *============================================================================*/
