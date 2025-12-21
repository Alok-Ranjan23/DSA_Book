/**
 * @file dynamic_arrays2.cc
 * @brief Extended Dynamic Array implementation with additional operations
 * 
 * This file builds upon the basic dynamic array (from dynamic_arrays1.cc) and
 * adds extra operations: pop(i), contains(x), insert(i, x), and remove(x).
 * 
 * Key Concepts:
 * - Element shifting for insertions and deletions at arbitrary indices
 * - Linear search for contains() and remove() operations
 * - Automatic resizing (grow/shrink) maintained from base implementation
 * 
 * Time Complexities:
 * - append():   Amortized O(1), worst case O(n) when resizing
 * - get():      O(1)
 * - set():      O(1)
 * - size():     O(1)
 * - pop_back(): Amortized O(1), worst case O(n) when shrinking
 * - pop(i):     O(n) - requires shifting elements
 * - contains(): O(n) - linear search
 * - insert():   O(n) - requires shifting elements
 * - remove():   O(n) - linear search + shifting
 * 
 * Space Complexity: O(n) where n is the number of elements
 */

#include <iostream>
#include <cassert>
using namespace std;

/**
 * @class DynamicArray
 * @brief A resizable array with extended operations for insertion/deletion
 * 
 * Extends the basic dynamic array with:
 * - Arbitrary index removal (pop)
 * - Element searching (contains)
 * - Arbitrary index insertion (insert)
 * - Value-based removal (remove)
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
     */
    void pop_back();
    
    /**
     * @brief Removes and returns element at specified index
     * @param i Index of element to remove
     * @return The removed element
     * @throws std::out_of_range if index is invalid
     * 
     * Time Complexity: O(n) - shifts all elements after index left by one
     */
    int pop(int i);
    
    /**
     * @brief Checks if element exists in the array
     * @param x Element to search for
     * @return true if found, false otherwise
     * 
     * Time Complexity: O(n) - linear search
     */
    bool contains(int x);
    
    /**
     * @brief Inserts element at specified index
     * @param i Index where element should be inserted
     * @param x Element to insert
     * @throws std::out_of_range if index is invalid (i < 0 or i > size)
     * 
     * Time Complexity: O(n) - shifts all elements at/after index right by one
     */
    void insert(int i, int x);
    
    /**
     * @brief Removes first occurrence of specified element
     * @param x Element to remove
     * @return Index where element was found, or -1 if not found
     * 
     * Time Complexity: O(n) - linear search + potential shifting
     */
    int remove(int x);
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
  int* temp = new int[newCap];
  for(int i=0;i<size_;++i) temp[i] = arr_[i];
  delete [] arr_;
  arr_ = temp;
  cap_ = newCap; 
}

/**
 * append() - Add element to end
 * 
 * Strategy: Add element first, then check if resize needed.
 * If array is full after adding, DOUBLE the capacity.
 * Doubling ensures amortized O(1) time complexity.
 */
void DynamicArray::append(int x) {
  arr_[size_] = x;
  ++size_;
  if(size_==cap_) {
    resize(cap_*2);
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
 * Shrinks array if utilization drops below 25% (and capacity > 10).
 */
void DynamicArray::pop_back() {
  if(size_==0) return;
  size_--;
  if(cap_>10 && (static_cast<double>(size_)/cap_)<0.25) {
    resize(cap_/2);
  }
}

/**
 * pop(index) - Remove element at arbitrary index
 * 
 * Algorithm:
 * 1. Validate index bounds
 * 2. Store value to return
 * 3. Shift all elements after index LEFT by one position
 *    [a, b, c, d, e] pop(2) -> [a, b, d, e, _]
 * 4. Decrement size
 * 5. Shrink if needed (same logic as pop_back)
 * 
 * Time Complexity: O(n) due to shifting
 * - Best case: O(1) when removing last element
 * - Worst case: O(n) when removing first element
 */
int DynamicArray::pop(int index) {
  if (index < 0 || index >= size_) {
    throw std::out_of_range("Index out of bounds");
  }
  int val = arr_[index];
  for(int i=index;i<size_-1;++i) {
    arr_[i] = arr_[i+1];
  }
  size_--;
  if(cap_>10 && (static_cast<double>(size_)/cap_)<0.25) {
    resize(cap_/2);
  }
  return val;
}

/**
 * contains() - Search for element existence
 * 
 * Algorithm: Simple linear search through all elements
 * 
 * Time Complexity: O(n)
 * - Best case: O(1) if element is at index 0
 * - Worst case: O(n) if element is not present or at last index
 * 
 * Note: Could be O(log n) if array was sorted (binary search),
 * but we don't maintain sorted order.
 */
bool DynamicArray::contains(int x) {
  bool found = false;
  for(int i=0;i<size_;++i) {
    if(arr_[i]==x){
      found=true;
      break;
    }
  }
  return found;
}

/**
 * insert() - Insert element at arbitrary index
 * 
 * Algorithm:
 * 1. Validate index bounds (note: i == size is valid - append at end)
 * 2. Resize if needed BEFORE shifting
 * 3. Shift all elements at/after index RIGHT by one position
 *    [a, b, c, d] insert(1, x) -> [a, x, b, c, d]
 * 4. Increment size
 * 5. Place new element at index
 * 
 * Time Complexity: O(n) due to shifting
 * - Best case: O(1) when inserting at end (like append)
 * - Worst case: O(n) when inserting at beginning
 * 
 * Note: Shifting happens from RIGHT to LEFT to avoid overwriting
 */
void DynamicArray::insert(int index, int x) {
  if (index < 0 || index > size_) {
    throw std::out_of_range("Index out of bounds");
  }
  if(size_+1==cap_) {
    resize(cap_*2);
  }
  for(int i=size_;i>index;--i) {
    arr_[i] = arr_[i-1];
  }
  size_++;
  arr_[index] = x;
  return;
}

/**
 * remove() - Remove first occurrence of value
 * 
 * Algorithm:
 * 1. Linear search to find first index of element
 * 2. If not found, return -1
 * 3. If found, use pop(index) to remove it
 * 4. Return the index where element was found
 * 
 * Time Complexity: O(n)
 * - Search: O(n)
 * - Removal (pop): O(n)
 * - Total: O(n) + O(n) = O(n)
 * 
 * Note: Only removes FIRST occurrence. If duplicates exist,
 * they remain in the array.
 */
int DynamicArray::remove(int x) {
  int index = -1;
  for(int i=0;i<size_;++i) {
    if(arr_[i]==x) {
      index=i;
      break;
    }
  }
  if(index==-1) return index;
  pop(index);
  return index;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
// Example 1: Testing pop(i) - remove at specific index
  DynamicArray d1 = DynamicArray();
  d1.append(1);
  d1.append(2);
  d1.append(3);
  cout<<d1.pop(1)<<"\n"; // returns 2
  cout<<d1.get(1)<<"\n"; // returns 3
  cout<<d1.size()<<"\n"; // returns 2

// Example 2: Testing contains() - element existence check
  DynamicArray d2 = DynamicArray();
  d2.append(1);
  d2.append(2);
  cout<<boolalpha;
  cout<<d2.contains(1)<<"\n"; // returns True
  cout<<d2.contains(3)<<"\n"; // returns False

// Example 3: Testing insert() - insert at specific index
  DynamicArray d3 = DynamicArray();
  d3.append(1);
  d3.append(2);
  d3.insert(1, 3); // array becomes [1,3,2]
  cout<<d3.get(1)<<"\n"; // returns 3

// Example 4: Testing remove() - remove by value
  DynamicArray d4 = DynamicArray();
  d4.append(1);
  d4.append(2);
  d4.append(2);
  cout<<d4.remove(2)<<"\n"; // returns 1 (first index where 2 appears)
  cout<<d4.get(1)<<"\n"; // returns 2 (the second 2 shifted left)
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Extra Dynamic Array Operations
 * 
 * In this problem, we are building off of an existing dynamic array data 
 * structure, which already has append, pop_back, set, get, and size methods, 
 * and adding additional methods.
 * 
 * Add the following methods:
 * 
 * 1. pop(i): Removes the element at index i. Every element after that index 
 *    should be shifted left by one index so that there are no gaps remaining 
 *    in the fixed-size array. Returns the element removed.
 * 
 * 2. contains(x): Takes an element and returns whether the element appears 
 *    in the array.
 * 
 * 3. insert(i, x): Takes an index and an element and adds the element at that 
 *    index, shifting right any preexisting elements at index i or greater.
 * 
 * 4. remove(x): Takes in an element and removes the first instance of that 
 *    element in the array. Returns the index that the element was at or -1 
 *    if the element was not found.
 * 
 * Constraints:
 * - If you are coding in a strongly typed language, you can either assume 
 *   all elements are integers, or define a generic dynamic array type.
 * - All operations should work with arrays of up to 10^6 elements
 * 
 *============================================================================*/
