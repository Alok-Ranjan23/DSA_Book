/**
 * @file heap_implementation.cc
 * @brief Complete Heap (Priority Queue) implementation from scratch
 * 
 * This file implements a generic Heap class that can function as either
 * a min-heap or max-heap based on a priority comparator string.
 * 
 * Key Concepts:
 * - Binary heap represented as an array (complete binary tree)
 * - Parent of node at index i: (i-1)/2
 * - Left child of node at index i: 2*i + 1
 * - Right child of node at index i: 2*i + 2
 * - Heapify: Maintaining the heap property after modifications
 * - Build heap: Converting an arbitrary array into a heap in O(n) time
 * 
 * Time Complexities:
 * - Constructor (heapify): O(n) - building heap from array
 * - size():              O(1)
 * - top():               O(1) - access root element
 * - push():              O(log n) - bubble up
 * - pop():               O(log n) - heapify down
 * 
 * Space Complexity: O(n) where n is the number of elements
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @class Heap
 * @brief A flexible priority queue supporting both min-heap and max-heap
 * 
 * The heap can be configured as:
 * - Min-heap (priority_ = "<"): smallest element has highest priority
 * - Max-heap (priority_ = ">"): largest element has highest priority
 */
class Heap {
  vector<int> arr_;     // Underlying array storing heap elements
  string priority_;     // Comparator: "<" for min-heap, ">" for max-heap
  
  /**
   * @brief Restores min-heap property starting from given index (sift down)
   * @param index Starting index for heapification
   * 
   * Recursively swaps with smaller child until heap property is satisfied.
   */
  void minheapify(int);
  
  /**
   * @brief Restores max-heap property starting from given index (sift down)
   * @param index Starting index for heapification
   * 
   * Recursively swaps with larger child until heap property is satisfied.
   */
  void maxheapify(int);
  
  /**
   * @brief Calculates parent index of a given node
   * @param index Child node index
   * @return Index of parent node
   */
  int parent(int);
  
  public:
  /**
   * @brief Constructor - creates a heap with given priority and optional elements
   * @param priority Comparator string: "<" for min-heap, ">" for max-heap
   * @param arr Initial elements to heapify (can be empty)
   * 
   * Time Complexity: O(n) - uses Floyd's heap construction algorithm
   * Starting from last non-leaf node and working backwards ensures O(n).
   */
  Heap(string priority, vector<int>& arr);
  
  /**
   * @brief Returns the number of elements in the heap
   * @return Number of elements
   */
  size_t size();
  
  /**
   * @brief Returns the highest-priority element without removing it
   * @return Root element, or -1 if heap is empty
   */
  int top();
  
  /**
   * @brief Adds a new element to the heap
   * @param elem Element to insert
   * 
   * Time Complexity: O(log n) - bubbles up from leaf to restore heap property
   */
  void push(int elem);
  
  /**
   * @brief Removes and returns the highest-priority element
   * @return Root element, or -1 if heap is empty
   * 
   * Time Complexity: O(log n) - replaces root with last element and heapifies down
   */
  int pop();
  
  /**
   * @brief Prints all heap elements (for debugging)
   */
  void print();
};

/*============================================================================
 * IMPLEMENTATION SECTION
 *============================================================================*/

/**
 * parent() - Calculate parent index
 * 
 * Formula: For node at index i, parent is at (i-1)/2
 * Example: Node at index 5 has parent at (5-1)/2 = 2
 */
int Heap::parent(int index) {
  return (index-1)/2;
}

/**
 * Constructor: Build heap from array
 * 
 * Algorithm (Floyd's Heap Construction):
 * 1. Copy input array
 * 2. Start from the last non-leaf node (n/2 - 1)
 * 3. Heapify each node moving towards root
 * 
 * Why start from n/2 - 1?
 * - Leaves (indices n/2 to n-1) are already valid heaps of size 1
 * - Only internal nodes need heapification
 * 
 * Time Complexity: O(n) - NOT O(n log n)!
 * - Nodes near bottom have small subtrees (O(1) heapify)
 * - Only root has full height (O(log n) heapify)
 * - Summing over all nodes gives O(n)
 */
Heap::Heap(string priority, vector<int>&arr) : arr_{arr},priority_{priority} {
  int n = arr_.size();
  if(priority_=="<") {
    for(int i=n/2-1;i>=0;--i) {
      minheapify(i);
    }
  }
  else if(priority_==">") {
    for(int i=n/2-1;i>=0;--i) {
      maxheapify(i);
    }
  }
}

/**
 * size() - Return element count
 */
size_t Heap::size() { return arr_.size();}

/**
 * top() - Peek at highest-priority element
 * 
 * The root (index 0) always contains the highest-priority element.
 */
int Heap::top() { if(arr_.size()==0)return -1; return arr_[0];}

/**
 * minheapify() - Restore min-heap property (sift down)
 * 
 * Algorithm:
 * 1. Compare node with both children
 * 2. Find the smallest among node and its children
 * 3. If node is not smallest, swap with smallest child
 * 4. Recursively heapify the affected subtree
 * 
 * Time Complexity: O(log n) - at most height of tree comparisons
 */
void Heap::minheapify(int index) {
  int smallest = index;
  int n = arr_.size();
  int left  = 2*smallest+1;
  int right = 2*smallest+2;
  if(left<n && arr_[smallest]> arr_[left])  { smallest = left; }
  if(right<n && arr_[smallest]> arr_[right]) { smallest = right; }
  if(smallest==index) return;
  swap(arr_[smallest],arr_[index]);
  minheapify(smallest);
  return;
}

/**
 * maxheapify() - Restore max-heap property (sift down)
 * 
 * Algorithm:
 * 1. Compare node with both children
 * 2. Find the largest among node and its children
 * 3. If node is not largest, swap with largest child
 * 4. Recursively heapify the affected subtree
 * 
 * Time Complexity: O(log n) - at most height of tree comparisons
 */
void Heap::maxheapify(int index) {
  int largest = index;
  int n = arr_.size();
  int left  = 2*largest+1;
  int right = 2*largest+2;
  if(left<n && arr_[largest] < arr_[left])  { largest = left; }
  if(right<n && arr_[largest] < arr_[right]) { largest = right; }
  if(largest==index) return;
  swap(arr_[largest],arr_[index]);
  maxheapify(largest);
  return;
}

/**
 * push() - Insert new element into heap (bubble up / sift up)
 * 
 * Algorithm:
 * 1. Add element at the end (maintains complete tree property)
 * 2. Compare with parent and swap if heap property violated
 * 3. Repeat until root is reached or heap property is satisfied
 * 
 * Time Complexity: O(log n) - at most height of tree swaps
 */
void Heap::push(int elem) {
  arr_.push_back(elem);
  int n = arr_.size();
  int index = n-1;
  if(priority_=="<") {
    while(index!=0 && arr_[parent(index)]>arr_[index]) {
      swap(arr_[parent(index)],arr_[index]);
      index = parent(index);
    }
  } else if(priority_==">") {
    while(index!=0 && arr_[parent(index)]<arr_[index]) {
      swap(arr_[parent(index)],arr_[index]);
      index = parent(index);
    }
  }
}

/**
 * pop() - Remove and return highest-priority element
 * 
 * Algorithm:
 * 1. Store root value to return
 * 2. Move last element to root (maintains complete tree property)
 * 3. Remove last position
 * 4. Heapify from root to restore heap property
 * 
 * Time Complexity: O(log n) - heapify takes O(log n)
 */
int Heap::pop() {
  int n = arr_.size();
  if(n==0) return -1;
  int elem = arr_[0];
  arr_[0] = arr_[n-1];
  arr_.pop_back();
  (priority_=="<")?minheapify(0):maxheapify(0);
  return elem;
}

/**
 * print() - Display heap contents for debugging
 */
void Heap::print() {
  for(auto& val: arr_) cout<<val<<" ";
  cout<<"\n";
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
 vector<int> arr{};
 Heap h = Heap("<", arr);  
 h.push(4);  // Elements ordered by priority: 4
 h.push(8); // Elements ordered by priority: 4, 8
 h.push(2);  // Elements ordered by priority: 2, 4, 8
 h.push(6);  // Elements ordered by priority: 2, 4, 6, 8
 h.push(1);  // Elements ordered by priority: 1, 2, 4, 6, 8
 cout<<h.pop()<<"\n";    // Returns 1. Elements ordered by priority: 2, 4, 6, 8
 cout<<h.pop()<<"\n";   // Returns 2. Elements ordered by priority: 4, 6, 8
 cout<<h.top()<<"\n";    // Returns 4. Elements ordered by priority: 6, 8
 cout<<h.pop()<<"\n";    // Returns 4. Elements ordered by priority: 8
 cout<<h.top()<<"\n";    // Returns 6. Elements ordered by priority: 8
 cout<<h.pop()<<"\n";    // Returns 6.
 cout<<h.size()<<"\n";   // Returns 1.
 cout<<h.top()<<"\n";    // Returns 8.
 cout<<h.pop()<<"\n";    // Returns 8.
 arr= {1,8,2,4,6};
 Heap h2 = Heap(">",arr);
 cout<<h2.top()<<"\n";     
 cout<<h2.pop()<<"\n";    
 cout<<h2.pop()<<"\n";    
 cout<<h2.pop()<<"\n";    
return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Implement A Heap
 * 
 * Assume your language does not support a heap or priority queue. Implement 
 * a `Heap` class from scratch with:
 * 
 * - A constructor that receives an optional list of elements to be heapified, and
 * - Operations `size()`, `top()`, `push(elem)`, and `pop()`.
 * 
 * Constraints:
 * - The number of elements is at most `10^5`
 * - If your language is typed, you can either make the type of the elements 
 *   be generic, or use integers.
 * - You can either make it a min-heap or make it generic by receiving a 
 *   comparator function, `higher_priority`, in the constructor.
 * 
 * API:
 * - initialize(higher_priority, heap): initializes a heap with the elements
 * - push(elem): adds an element to the priority queue
 * - pop(): removes and returns the highest-priority element
 * - top(): returns the highest-priority element without removing it
 * - size(): returns the number of elements in the priority queue
 * 
 *============================================================================*/
