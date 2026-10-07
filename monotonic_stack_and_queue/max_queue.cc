/**
 * @file max_queue.cc
 * @brief FIFO queue that also reports its maximum in amortized O(1)
 *
 * A plain std::queue stores the elements in order. Alongside it, a monotonic
 * deque `dq` stores the "max candidates": values in non-increasing order from
 * front to back. The front of dq is always the current maximum.
 *
 * Key Concepts:
 * - On push(val), every candidate smaller than val is removed from dq's back:
 *   val was pushed later, so it will outlive them and is larger, meaning
 *   they can never be the max again
 * - Equal values are KEPT (pop only on strictly smaller), so duplicates of
 *   the maximum are tracked individually
 * - On pop(), the front element leaves the queue; if it equals dq.front(),
 *   that candidate is removed too. Comparing by value is safe because equal
 *   values are kept as separate entries, in queue order
 *
 * Time Complexity:
 *   - push:  amortized O(1) -- each value enters dq once and leaves at most
 *            once, so total back-pops over any sequence of m pushes is <= m
 *   - pop / peek / max / size: O(1)
 *
 * Space Complexity: O(n)
 *   - The queue holds n elements; dq holds at most n candidates (e.g. a
 *     non-increasing input keeps every value).
 */
#include <iostream>
#include <queue>
#include <deque>
using namespace std;

/// Queue of ints supporting push, pop, peek, max and size.
class MaxQueue {
  queue<int>q{};                                   ///< elements in FIFO order
  deque<int>dq{};                                  ///< max candidates, non-increasing; front = max
  int _size{0};                                    ///< number of elements in the queue
  public:
  void push(int val);
  int pop();
  int peek();
  int max();
  /// @brief Number of elements in the queue. Time O(1), Space O(1)
  int size() {return _size;}
};

/**
 * @brief Add val to the back of the queue
 *
 * @param val Value to insert
 *
 * Algorithm: push to q; pop every strictly smaller value from dq's back
 * (it can never be the maximum again); push val to dq.
 *
 * Time:  amortized O(1) -- each value is popped from dq at most once overall
 * Space: O(1) extra per call
 */
//Time O(1) amortized
//Space O(1)
void MaxQueue::push(int val) {
  q.push(val);
  _size+=1;
  while(!dq.empty() and dq.back()<val) dq.pop_back();   // drop dominated candidates
  dq.push_back(val);
}

/**
 * @brief Remove and return the front element (queue must be non-empty)
 *
 * @return The removed value
 *
 * If the removed value is the current max candidate, drop it from dq too.
 *
 * Time:  O(1)
 * Space: O(1)
 */
//Time O(1)
//Space O(1)
int MaxQueue::pop() {
  int val = peek();
  q.pop();
  _size-=1;
  if(val==dq.front()) dq.pop_front();             // leaving element was the max
  return val;
}

/**
 * @brief Return the front element without removing it (queue must be non-empty)
 *
 * Time:  O(1)
 * Space: O(1)
 */
//Time O(1)
//Space O(1)
int MaxQueue::peek() {
  return q.front();
}

/**
 * @brief Return the maximum element in the queue (queue must be non-empty)
 *
 * Time:  O(1)
 * Space: O(1)
 */
//Time O(1)
//Space O(1)
int MaxQueue::max() {
  return dq.front();
}

// To execute C++, please define "int main()"
int main() {
  MaxQueue q = MaxQueue();            // []
  q.push(10);                         // [10]
  q.push(30);                         // [10, 30]
  q.push(20);                         // [10, 30, 20]
  cout<<q.max()<<"\n"; // Returns 30  // [10, 30, 20]
  cout<<q.pop()<<"\n"; // Returns 10  // [30, 20]
  cout<<q.max()<<"\n"; // Returns 30  // [30, 20]
  cout<<q.pop()<<"\n"; // Returns 30  // [20]
  cout<<q.max()<<"\n"; // Returns 20  // [20]
  q.push(50);                         // [20, 50]
  q.push(30);                         // [20, 50, 30]
  q.push(20);                         // [20, 50, 30, 20]
  q.push(10);                         // [20, 50, 30, 20, 10]
  cout<<q.max()<<"\n"; // Returns 50  // [20, 50, 30, 20, 10]
  q.push(50);                         // [20, 50, 30, 20, 10, 50]
  cout<<q.max()<<"\n"; // Returns 50  // [20, 50, 30, 20, 10, 50]
  cout<<q.pop()<<"\n"; // Returns 20  // [50, 30, 20, 10, 50]
  cout<<q.pop()<<"\n"; // Returns 50  // [30, 20, 10, 50]
  cout<<q.max()<<"\n"; // Returns 50  // [30, 20, 10, 50] 
  return 0;
}

// # Max Queue

// Implement a special queue data structure that behaves like a normal queue but also supports a `max()` operation.
// This operation returns the maximum of the elements in the queue without modifying the queue.

// In total, the operations are:

// - `push(val)`: Add an element to the back of the queue
// - `pop()`: Remove and return the element at the front of the queue
// - `peek()`: Return the element at the front of the queue
// - `max()`: Return the maximum element currently in the queue
// - `size()`: Return the number of elements in the queue

// Constraints:

// - All the operations should take constant time (amortized constant time is fine).
// - You can use your language's built-in queue and deque data structures (or assume you have them available, if your language doesn't provide them).
// - For simplicity, you can assume that `pop()`, `peek()`, and `max()` are never called on an empty queue.
// - You can assume that the queue will only contain integers.

// Example:

// MaxQueue operations        Current queue
// q = MaxQueue()             []
// q.push(10)                 [10]
// q.push(30)                 [10, 30]
// q.push(20)                 [10, 30, 20]
// q.max() // Returns 30.     [10, 30, 20]
// q.pop() // Returns 10.     [30, 20]
// q.max() // Returns 30.     [30, 20]
// q.pop() // Returns 30.     [20]
// q.max() // Returns 20.     [20]
// q.push(50)                 [20, 50]
// q.push(30)                 [20, 50, 30]
// q.push(20)                 [20, 50, 30, 20]
// q.push(10)                 [20, 50, 30, 20, 10]
// q.max() // Returns 50.     [20, 50, 30, 20, 10]
// q.push(50)                 [20, 50, 30, 20, 10, 50]
// q.max() // Returns 50.     [20, 50, 30, 20, 10, 50]
// q.pop() // Returns 20.     [50, 30, 20, 10, 50]
// q.pop() // Returns 50.     [30, 20, 10, 50]
// q.max() // Returns 50.     [30, 20, 10, 50]
