#include <iostream>
#include <vector>
using namespace std;

class Heap {
  vector<int> arr_;
  string priority_;
  void minheapify(int);
  void maxheapify(int);
  int parent(int);
  public:
  Heap(string priority, vector<int>& arr);
  size_t size();
  int top();
  void push(int elem);
  int pop();
  void print();
};

int Heap::parent(int index) {
  return (index-1)/2;
}

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

size_t Heap::size() { return arr_.size();}

int Heap::top() { if(arr_.size()==0)return -1; return arr_[0];}

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

int Heap::pop() {
  int n = arr_.size();
  if(n==0) return -1;
  int elem = arr_[0];
  arr_[0] = arr_[n-1];
  arr_.pop_back();
  (priority_=="<")?minheapify(0):maxheapify(0);
  return elem;
}

void Heap::print() {
  for(auto& val: arr_) cout<<val<<" ";
  cout<<"\n";
}

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

// # Implement A Heap

// Assume your language does not support a heap or priority queue. Implement a `Heap` class from scratch with:

// - A constructor that receives an optional list of elements to be heapified, and
// - Operations `size()`, `top()`, `push(elem)`, and `pop()`.

// Constraints:

// - The number of elements is at most `10^5`
// - If your language is typed, you can either make the type of the elements be generic, or use integers.
// - You can either make it a min-heap or make it generic by receiving a comparator function, `higher_priority`, in the constructor.

// This is the API:

// initialize(higher_priority, heap):
//   initializes a heap with the elements in `heap` (if any)
//   sets higher_priority() as the method to compare element priorities
//   higher_priority() should have this signature:
//   higher_priority(x, y):
//       returns true if x has higher priority than y, false otherwise

// push(elem): adds an element to the priority queue.

// pop(): removes and returns the highest-priority element.
// If the heap is empty, return null.

// top(): returns the highest-priority element without removing it.

// size(): returns the number of elements in the priority queue

// Example 1:
// heap = Heap(higher_priority: <)  # Min-heap
// heap.push(4)  # Elements ordered by priority: 4
// heap.push(8)  # Elements ordered by priority: 4, 8
// heap.push(2)  # Elements ordered by priority: 2, 4, 8
// heap.push(6)  # Elements ordered by priority: 2, 4, 6, 8
// heap.push(1)  # Elements ordered by priority: 1, 2, 4, 6, 8
// heap.pop()    # Returns 1. Elements ordered by priority: 2, 4, 6, 8
// heap.pop()    # Returns 2. Elements ordered by priority: 4, 6, 8
// heap.top()    # Returns 6. Elements ordered by priority: 6, 8
// heap.pop()    # Returns 6. Elements ordered by priority: 8
// heap.top()    # Returns 8. Elements ordered by priority: 8
// heap.pop()    # Returns 8.
// heap.size()   # Returns 0.
// heap.top()    # Returns null.
// heap.pop()    # Returns null.

// Example 2:
// heap = Heap(higher_priority: >, heap = [1, 8, 2, 6, 4])  # Max-heap
// heap.top()     # Returns 8. Elements ordered by priority: 8, 6, 4, 2, 1
// heap.pop()     # Returns 8. Elements ordered by priority: 6, 4, 2, 1
// heap.pop()     # Returns 6. Elements ordered by priority: 4, 2, 1
// heap.pop()     # Returns 4. Elements ordered by priority: 2, 1
