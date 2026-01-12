# Stacks and Queues

A collection of stack and queue problems demonstrating various patterns and techniques.

---

## 1. Balanced Brackets

Classic bracket matching problems using stack.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `balanced_partition.cc` | Max balanced substrings | Height tracking | O(n) | O(1) |
| `custom_brackets.cc` | Balance check with custom brackets | Stack + hash map | O(n) | O(n) |
| `longest_balanced_subsequence.cc` | Longest balanced subsequence | Track invalid indices | O(n) | O(n) |

---

## 2. Array Compression

Merge consecutive elements using stack.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `compress_array.cc` | Merge consecutive equal pairs | Cascading stack merge | O(n) | O(n) |
| `compress_array_by_k.cc` | Merge k consecutive equals | Stack with (val, count) pairs | O(n) | O(n) |

---

## 3. Browser Navigation

Simulate browser history with stacks.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `current_url.cc` | Back navigation only | Single stack | O(n) | O(n) |
| `current_url_with_forward.cc` | Back + forward navigation | Two stacks | O(n) | O(n) |

---

## 4. Sliding Window with Queue

Time-based counting with queue.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `viewer_counter_class.cc` | Count viewers in time window | Queue per category + lazy cleanup | O(1)* | O(n) |

*Amortized

---

## Dangling Bracket Recipe

Core pattern for bracket matching:

```
stack = []
for c in s:
  if c is opening bracket:
    stack.push(c)
  else if c is closing bracket:
    if stack.empty() or stack.top() != matching(c):
      return False
    stack.pop()
return stack.empty()
```

---

## Quick Reference

```
Stack (LIFO):               Queue (FIFO):
  push(x)  - add to top       push(x)  - add to back
  pop()    - remove top       pop()    - remove front
  top()    - peek top         front()  - peek front
  empty()  - check empty      empty()  - check empty
  size()   - get count        size()   - get count

Common Patterns:
  - Matching pairs      → Stack (brackets, undo/redo)
  - Monotonic sequence  → Stack (next greater element)
  - Sliding window      → Deque or Queue
  - BFS traversal       → Queue
  - DFS traversal       → Stack (or recursion)
```

---

## Build & Run

```bash
make              # Build all programs
make <program>    # Build specific (e.g., make compress_array)
make clean        # Remove all binaries
./<program>       # Run (e.g., ./compress_array)
```
