/**
 * @file heap_sort.cc
 * @brief Heap Sort implementation using Min-Heap (Descending Order)
 * 
 * This file implements heap sort using a min-heap, which produces output
 * in descending order. The implementation encapsulates heap operations
 * within a class for clean organization.
 * 
 * Key Concepts:
 * - Min-heap: Parent is always smaller than or equal to children
 * - Heap sort works by repeatedly extracting the min element
 * - In-place sorting by swapping root with last unsorted element
 * - After each extraction, heap size decreases by 1
 * 
 * Algorithm Steps:
 * 1. Build a min-heap from the input array - O(n)
 * 2. Repeatedly swap root (min) with last element
 * 3. Reduce heap size and heapify the root
 * 4. Result: Array sorted in DESCENDING order (largest to smallest)
 * 
 * Time Complexities:
 * - Build Heap:  O(n) - Floyd's algorithm
 * - sort():      O(n log n) - n extractions, each O(log n)
 * - push():      O(log n) - bubble up
 * - pop():       O(log n) - heapify down
 * - top():       O(1)
 * 
 * Space Complexity: O(1) auxiliary - sorting is done in-place
 * 
 * Note: For ASCENDING order, use a max-heap instead (see heap_sort2.cc)
 */

// Min-Heap Descending Order

#include <iostream>
#include <vector>

using namespace std;

/**
 * @class Heap
 * @brief Min-heap implementation with sorting capability
 * 
 * This heap maintains the min-heap property where parent <= children.
 * The sort() method produces a descending order result because
 * minimum elements are moved to the end first.
 */
class Heap {
  vector<int> arr_;   // Underlying array storing heap elements

  /**
   * @brief Calculates parent index of a given node
   * @param i Child node index
   * @return Index of parent node: (i-1)/2
   */
  int parent(int i) { return (i - 1) / 2; }
  
  /**
   * @brief Restores min-heap property starting from given index
   * @param i Starting index for heapification
   * @param n Heap size (elements beyond n are sorted/excluded)
   * 
   * This is the bounded version of heapify used during sorting.
   * Parameter n limits the heap boundary, excluding sorted elements.
   * 
   * Time Complexity: O(log n)
   */
  void minheapify(int i, int n) {
    int smallest = i;
    int left  = 2 * i + 1;
    int right = 2 * i + 2;
    if (left  < n && arr_[left]  < arr_[smallest]) smallest = left;
    if (right < n && arr_[right] < arr_[smallest]) smallest = right;
    if (smallest == i) return;
    swap(arr_[i], arr_[smallest]);
    minheapify(smallest,n);
  }

public:
  /**
   * @brief Constructor - builds a min-heap from the given array
   * @param a Reference to input array
   * 
   * Uses Floyd's heap construction algorithm starting from
   * last non-leaf node (n/2 - 1) and working up to root.
   * 
   * Time Complexity: O(n)
   */
  Heap(vector<int>& a) : arr_(a) {
    int n = arr_.size();
    for (int i = n / 2 - 1; i >= 0; --i)
      minheapify(i,n);
  }

  /**
   * @brief Returns the number of elements in the heap
   * @return Number of elements
   */
  size_t size() const { return arr_.size(); }

  /**
   * @brief Returns the minimum element without removing it
   * @return Root element (minimum), or -1 if empty
   */
  int top() const {
    if (arr_.empty()) return -1;   // sentinel for empty
    return arr_[0];
  }

  /**
   * @brief Inserts a new element into the heap
   * @param x Element to insert
   * 
   * Algorithm (Bubble Up):
   * 1. Add element at the end
   * 2. Compare with parent, swap if smaller
   * 3. Repeat until heap property is satisfied
   * 
   * Time Complexity: O(log n)
   */
  void push(int x) {
    arr_.push_back(x);
    int i = (int)arr_.size() - 1;
    while (i != 0 && arr_[parent(i)] > arr_[i]) {
      swap(arr_[i], arr_[parent(i)]);
      i = parent(i);
    }
  }

  /**
   * @brief Removes and returns the minimum element
   * @return Root element (minimum), or -1 if empty
   * 
   * Algorithm:
   * 1. Store root value
   * 2. Move last element to root
   * 3. Remove last position
   * 4. Heapify from root
   * 
   * Time Complexity: O(log n)
   */
  int pop() {
    if (arr_.empty()) return -1;
    int root = arr_[0];
    arr_[0] = arr_.back();
    arr_.pop_back();
    int n = arr_.size();
    if (!arr_.empty()) minheapify(0,n);
    return root;
  }

  /**
   * @brief Sorts the array in DESCENDING order using heap sort
   * 
   * Algorithm:
   * 1. For i from n-1 down to 1:
   *    a. Swap arr[0] (min) with arr[i]
   *    b. Heapify arr[0..i-1] to restore min-heap
   * 
   * Why descending? With min-heap, smallest elements are moved to
   * the end first. When all elements are processed, the array
   * is sorted from largest to smallest.
   * 
   * Example: [1, 4, 2, 6, 8, 3] (heapified)
   * After sort: [8, 6, 4, 3, 2, 1] (descending)
   * 
   * Time Complexity: O(n log n)
   * Space Complexity: O(1) - in-place
   */
  // 1 4 2 6 8 3 
  void sort() {
    int n = arr_.size();
    for(int i=n-1;i>=1;--i) {
     swap(arr_[i],arr_[0]); 
     minheapify(0,i);
    }
  }

  /**
   * @brief Prints all elements in the array (for debugging)
   */
  void print() const {
    for (int v : arr_) cout << v << ' ';
    cout << '\n';
  }
};

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
    vector<int> arr{4, 8, 2, 6, 1};
    Heap h(arr);
    h.print();          // heapified array
    h.push(3);
    h.print();
    h.sort();
    h.print();
}
