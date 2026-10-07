# Monotonic Stack and Queue

A collection of problems solved with **monotonic stacks** (next/previous greater/smaller element) and **monotonic deques** (sliding-window max/min), turning O(n²) or O(n·k) brute force into a single O(n) pass.

---

## 1. Next / Previous Greater or Smaller Element (Monotonic Stack)

For every index, find the nearest element on one side that is strictly greater or smaller.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `next_greater_elements.cc` | First index to the right with a strictly greater value | Right-to-left stack, pop `<=` | O(n) | O(n) |
| `kingkong_vs_godzilla.cc` | Buildings with a taller one to the right AND a shorter one to the left | NGE (sentinel `n`) + PSE (sentinel `-1`) | O(n) | O(n) |
| `kingkong_vs_godzilla_fog.cc` | Same, but only buildings at most `k` away are visible | NGE / PSE + pop indices more than `k` away | O(n) | O(n) |

---

## 2. Span Between Smaller Elements (Monotonic Stack)

Use the nearest smaller element on both sides to find how far each element can extend.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `largest_rectangle.cc` | Largest all-blue rectangle in a histogram mosaic | `tiles[i] * (NSE[i] - PSE[i] - 1)`, `long long` area | O(n) | O(n) |

---

## 3. Fixed-Size Sliding Window (Monotonic Deque)

Window of exactly `k` elements; deque fronts give the window max/min in O(1).

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `sliding_window_max.cc` | Max of every window of size `k` | Non-increasing deque, evict `l` from the front | O(n) | O(k) |
| `largest_temp_change.cc` | Largest `max - min` over every `k`-day window | Max deque + min deque | O(n) | O(k) |

---

## 4. Variable-Size Sliding Window (Monotonic Deque)

Grow the window while a condition holds, otherwise shrink from the left.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `longest_stable_period.cc` | Longest subarray with `max - min <= t` | Check before mutating deques; grow or shrink | O(n) | O(n) |

---

## 5. Data Structure Design

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `max_queue.cc` | Queue with O(1) `max()` | `queue` + non-increasing deque of candidates | O(1) amortized/op | O(n) |

---

## Monotonic Stack Recipe

All four variants share one template. Only the **scan direction**, the **pop comparison**, and the **sentinel** change. The stack stores **indices**, so the answer can be an index and values are read as `arr[stack.top]`.

### NGE: Next Greater Element
First index `j > i` with `arr[j] > arr[i]`. Used in `next_greater_elements.cc` (sentinel `-1`) and `kingkong_vs_godzilla*.cc` (sentinel `n`).

```
next_greater(arr)                       # scan RIGHT -> LEFT
  n = len(arr)
  res = [n] * n                         # n = "no greater element to the right"
  stack = []                            # values strictly decreasing bottom -> top
  for i from n-1 down to 0:
    while stack and arr[stack.top] <= arr[i]:   # not strictly greater -> useless
      stack.pop()
    if stack: res[i] = stack.top        # nearest strictly greater on the right
    stack.push(i)
  return res
```

### NSE: Next Smaller Element
First index `j > i` with `arr[j] < arr[i]`. Used in `largest_rectangle.cc`.

```
next_smaller(arr)                       # scan RIGHT -> LEFT
  n = len(arr)
  res = [n] * n                         # n = "no smaller element to the right"
  stack = []                            # values strictly increasing bottom -> top
  for i from n-1 down to 0:
    while stack and arr[stack.top] >= arr[i]:   # not strictly smaller -> useless
      stack.pop()
    if stack: res[i] = stack.top        # nearest strictly smaller on the right
    stack.push(i)
  return res
```

### PGE: Previous Greater Element
Last index `j < i` with `arr[j] > arr[i]`.

```
previous_greater(arr)                   # scan LEFT -> RIGHT
  n = len(arr)
  res = [-1] * n                        # -1 = "no greater element to the left"
  stack = []                            # values strictly decreasing bottom -> top
  for i from 0 to n-1:
    while stack and arr[stack.top] <= arr[i]:   # not strictly greater -> useless
      stack.pop()
    if stack: res[i] = stack.top        # nearest strictly greater on the left
    stack.push(i)
  return res
```

### PSE: Previous Smaller Element
Last index `j < i` with `arr[j] < arr[i]`. Used in `kingkong_vs_godzilla*.cc` and `largest_rectangle.cc`.

```
previous_smaller(arr)                   # scan LEFT -> RIGHT
  n = len(arr)
  res = [-1] * n                        # -1 = "no smaller element to the left"
  stack = []                            # values strictly increasing bottom -> top
  for i from 0 to n-1:
    while stack and arr[stack.top] >= arr[i]:   # not strictly smaller -> useless
      stack.pop()
    if stack: res[i] = stack.top        # nearest strictly smaller on the left
    stack.push(i)
  return res
```

### Example: `arr = [5, 3, 10, 8, 8, 10]`

| Index | 0 | 1 | 2 | 3 | 4 | 5 |
|-------|---|---|---|---|---|---|
| `arr` | 5 | 3 | 10 | 8 | 8 | 10 |
| NGE   | 2 | 2 | 6 | 5 | 5 | 6 |
| NSE   | 1 | 6 | 3 | 6 | 6 | 6 |
| PGE   | -1 | 0 | -1 | 2 | 2 | -1 |
| PSE   | -1 | -1 | 1 | 1 | 1 | 4 |

Here `n = 6` is the right sentinel and `-1` is the left sentinel. The two 8s (indices 3, 4) are equal, so neither counts as greater or smaller than the other.

### Summary

| Want | Scan direction | Pop while `arr[top] ? arr[i]` | Stack values (bottom → top) | Sentinel |
|------|----------------|-------------------------------|-----------------------------|----------|
| **NGE**: next strictly greater | right → left | `<=` | strictly decreasing | `n` (or `-1`) |
| **NSE**: next strictly smaller | right → left | `>=` | strictly increasing | `n` |
| **PGE**: previous strictly greater | left → right | `<=` | strictly decreasing | `-1` |
| **PSE**: previous strictly smaller | left → right | `>=` | strictly increasing | `-1` |

**Mnemonic:**
- **Next** scans right to left and **Previous** scans left to right, so the answer side has already been processed.
- **Greater** pops `<=` and **Smaller** pops `>=`, which removes everything that isn't a strict answer.
- Change the comparison to `<` or `>` for "greater or equal" / "smaller or equal" (non-strict) versions.

**Key insight:** an element popped by `i` is "dominated": `i` is closer and at least as good, so it can never be the answer for `i` or for anything further along. Each index is pushed once and popped at most once, so every variant costs **O(n) time and O(n) space**.

---

## Monotonic Deque Recipe

```
sliding_max(arr, k)                     # window [l, r)
  dq = []                               # indices, values non-increasing
  l = 0
  for r in 0..n-1:
    while dq and arr[dq.back] < arr[r]: dq.pop_back()   # dominated
    dq.push_back(r)
    if r - l + 1 == k:
      record arr[dq.front]              # window max
      if dq.front == l: dq.pop_front()  # l leaves the window
      l += 1
```

**Key insight:** the deque holds only indices inside the window, ordered by index *and* by value, so the front is the window max (use `>` for a min deque). For a variable-size window, check the condition **before** changing the deques, then either grow (push `r`) or shrink (evict `l`).

---

## Quick Reference

```
Need nearest greater/smaller to one side        -> monotonic stack
Need how far an element extends (span/width)    -> NSE + PSE, width = NSE - PSE - 1
Need max/min of every fixed-size window         -> monotonic deque, size k
Need longest/shortest window with max-min bound -> two deques + grow/shrink
Need a queue with O(1) max                      -> queue + candidate deque
Pop on <= / >= for STRICT answers; pop on < / > to keep equal values
```

---

## Build & Run

```bash
make              # Build all programs
make <program>    # Build specific (e.g., make largest_rectangle)
make clean        # Remove all binaries
./<program>       # Run (e.g., ./largest_rectangle)
```
