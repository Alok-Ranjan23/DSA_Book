/**
 * @file dynamic_arrays1.cc
 * @brief Implementation of a Dynamic Array (Vector) data structure from scratch
 * 
 * This file implements a dynamic array that automatically resizes when needed.
 * Unlike fixed-size arrays, dynamic arrays can grow and shrink based on the
 * number of elements stored.
 * 
 * Key Concepts:
 * - Amortized O(1) append operation using doubling strategy
 * - Automatic shrinking when utilization falls below 25%
 * - Manual memory management with new/delete
 * 
 * Time Complexities:
 * - append(): Amortized O(1), worst case O(n) when resizing
 * - get():    O(1)
 * - set():    O(1)
 * - size():   O(1)
 * - pop_back(): Amortized O(1), worst case O(n) when shrinking
 * 
 * Space Complexity: O(n) where n is the number of elements
 */

#include <iostream>
using namespace std;

/**
 * @class DynamicArray
 * @brief A resizable array implementation that grows/shrinks automatically
 * 
 * The array doubles in capacity when full and halves when less than 25% utilized.
 * This ensures amortized O(1) time for append and pop_back operations.
 */
class DynamicArray {
  private:
    int cap_;    // Current capacity (total allocated space)
    int* arr_;   // Pointer to the underlying fixed-size array
    int size_;   // Current number of elements stored
    
    /**
     * @brief Resizes the internal array to a new capacity
     * @param newCap The new capacity for the array
     * 
     * Time Complexity: O(n) - must copy all existing elements
     * Space Complexity: O(n) - temporary array needed during resize
     */
    void resize(int newCap);
    
  public:
    /**
     * @brief Constructor - creates a dynamic array with initial capacity
     * @param size Initial capacity (default: 10)
     */
    DynamicArray(int size=10);
    
    /**
     * @brief Destructor - frees the allocated memory
     */
    ~DynamicArray();
    
    /**
     * @brief Adds an element to the end of the array
     * @param x The element to add
     */
    void append(int x);
    
    /**
     * @brief Retrieves element at given index
     * @param i Index of the element (0-based)
     * @return The element at index i
     * @throws std::out_of_range if index is invalid
     */
    int get(int i);
    
    /**
     * @brief Updates element at given index
     * @param i Index of the element to update (0-based)
     * @param x New value to set
     * @throws std::out_of_range if index is invalid
     */
    void set(int i, int x);
    
    /**
     * @brief Returns the current number of elements
     * @return Number of elements in the array
     */
    size_t size();
    
    /**
     * @brief Removes the last element from the array
     * 
     * If the array becomes less than 25% full (and capacity > 10),
     * the capacity is halved to save memory.
     */
    void pop_back();
};

/*============================================================================
 * IMPLEMENTATION SECTION
 *============================================================================*/

/**
 * Constructor: Initialize with given capacity, empty array
 * Uses member initializer list for efficiency
 */
DynamicArray::DynamicArray(int size):cap_(size), arr_(new int[cap_]),size_(0) {};

/**
 * Destructor: Clean up dynamically allocated memory
 * IMPORTANT: Use delete[] for arrays, not delete
 */
DynamicArray::~DynamicArray() {delete [] arr_;}

/**
 * resize() - Core operation for dynamic sizing
 * 
 * Algorithm:
 * 1. Allocate new array with new capacity
 * 2. Copy all existing elements to new array
 * 3. Delete old array
 * 4. Point to new array and update capacity
 */
void DynamicArray::resize(int newCap) {
  int* temp = new int[newCap];              // Step 1: Allocate new memory
  for(int i=0;i<size_;++i) temp[i] = arr_[i]; // Step 2: Copy elements
  delete [] arr_;                            // Step 3: Free old memory
  arr_ = temp;                               // Step 4a: Update pointer
  cap_ = newCap;                             // Step 4b: Update capacity
}

/**
 * append() - Add element to end
 * 
 * Strategy: Add element first, then check if resize needed.
 * If array is full after adding, DOUBLE the capacity.
 * Doubling ensures amortized O(1) time complexity.
 * 
 * Why doubling works:
 * - After n insertions causing resize, we've done ~2n copy operations total
 * - Amortized cost per insertion = 2n/n = O(1)
 */
void DynamicArray::append(int x) {
  arr_[size_] = x;     // Place element at next available position
  ++size_;             // Increment count
  if(size_==cap_) {    // If array is now full...
    resize(cap_*2);    // ...double the capacity
  }
}

/**
 * get() - Random access by index
 * 
 * Bounds checking ensures we don't access uninitialized memory.
 * Returns element at index i in O(1) time - direct array access.
 */
int DynamicArray::get(int i) {
  if (i < 0 || i >= size_) {
    throw std::out_of_range("Index out of bounds");
  }
  return arr_[i];
}

/**
 * set() - Update element at index
 * 
 * Similar to get(), with bounds checking for safety.
 * O(1) time complexity.
 */
void DynamicArray::set(int i, int x) {
 if (i < 0 || i >= size_) {
  throw std::out_of_range("Index out of bounds");
 }
 arr_[i] = x;
}

/**
 * size() - Return current element count
 * 
 * Note: Returns size_t (unsigned) for compatibility with standard containers.
 */
size_t DynamicArray::size() {
  return static_cast<size_t>(size_);
}

/**
 * pop_back() - Remove last element
 * 
 * Strategy: 
 * 1. Simply decrement size (element still exists but is "invisible")
 * 2. If utilization drops below 25% AND capacity > minimum (10),
 *    shrink array by half to save memory
 * 
 * The 25% threshold prevents "thrashing" (repeated grow/shrink cycles)
 * that would occur with a 50% threshold.
 */
void DynamicArray::pop_back() {
  if(size_==0) return;  // Nothing to remove from empty array
  size_--;              // Logically remove last element
  
  // Shrink if less than 25% utilized (but keep minimum capacity of 10)
  if(cap_>10 && (static_cast<double>(size_)/cap_)<0.25) {
    resize(cap_/2);
  }
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Example 1: Basic append and get operations
  DynamicArray d1 = DynamicArray();
  d1.append(1);
  d1.append(2);
  cout<<d1.get(0)<<"\n"; // returns 1
  cout<<d1.get(1)<<"\n"; // returns 2
  cout<<d1.size()<<"\n"; // returns 2
  
  // Example 2: Testing set operation
  DynamicArray d2 = DynamicArray();
  d2.append(1);
  d2.set(0,10);          // Update first element from 1 to 10
  cout<<d2.get(0)<<"\n"; // returns 10
  
  // Example 3: Testing pop_back operation
  DynamicArray d3 = DynamicArray();
  d3.append(1);
  d3.append(2);
  d3.pop_back();         // Remove the '2'
  cout<<d3.size()<<"\n"; // returns 1
  cout<<d3.get(0)<<"\n"; // returns 1
  
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Implement Dynamic Array
 * 
 * Assume your programming language only supports fixed-size arrays. 
 * Implement a dynamic array data structure that supports the following:
 * 
 * Dynamic Array API:
 * - append(x): adds element x to the end of the array
 * - get(i): returns the element at index i
 * - set(i, x): updates the preexisting element at index i to be x
 * - size(): returns the number of elements in the array
 * - pop_back(): removes the last element
 * 
 * You should only declare arrays of a fixed size and not use built-in 
 * append() methods or equivalent.
 * 
 * Constraints:
 * - All elements are integers (for simplicity)
 * - All operations should work with arrays of up to 10^6 elements
 * 
 *============================================================================*/
