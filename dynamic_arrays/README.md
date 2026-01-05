# Dynamic Arrays

Implementation of a resizable array (vector) data structure from scratch.

---

## Overview

Dynamic arrays automatically grow and shrink based on the number of elements stored, unlike fixed-size arrays.

| File | Description | Key Operations |
|------|-------------|----------------|
| `dynamic_arrays1.cc` | Basic dynamic array | append, get, set, size, pop_back |
| `dynamic_arrays2.cc` | Extended operations | + pop(i), contains, insert, remove |

---

## API Reference

### Basic Operations (dynamic_arrays1.cc)

| Method | Description | Time | Space |
|--------|-------------|------|-------|
| `append(x)` | Add element to end | Amortized O(1) | O(n) on resize |
| `get(i)` | Get element at index | O(1) | O(1) |
| `set(i, x)` | Update element at index | O(1) | O(1) |
| `size()` | Return element count | O(1) | O(1) |
| `pop_back()` | Remove last element | Amortized O(1) | O(n) on shrink |

### Extended Operations (dynamic_arrays2.cc)

| Method | Description | Time | Space |
|--------|-------------|------|-------|
| `pop(i)` | Remove element at index i | O(n) | O(1) |
| `contains(x)` | Check if element exists | O(n) | O(1) |
| `insert(i, x)` | Insert element at index i | O(n) | O(1) |
| `remove(x)` | Remove first occurrence of x | O(n) | O(1) |

---

## Key Concepts

### Amortized O(1) Append

```
Strategy: Double capacity when full

Capacity:  1 → 2 → 4 → 8 → 16 → ...

After n insertions causing k resizes:
  Total copies ≈ 1 + 2 + 4 + ... + n ≈ 2n
  Amortized cost = 2n / n = O(1)
```

### Shrinking Strategy

```
Shrink when utilization < 25% (not 50%)

Why 25%? Prevents "thrashing":
  - At 50% threshold: grow at n, shrink at n/2, grow at n...
  - At 25% threshold: grow at n, shrink at n/4 (stable)
```

### Shifting for Insert/Remove

```
Insert at index 2:        Remove at index 2:
[a, b, c, d, _]          [a, b, c, d, e]
      ↓                        ↓
[a, b, _, c, d]          [a, b, d, e, _]
      ↓
[a, b, X, c, d]

Shift RIGHT (end→index)   Shift LEFT (index→end)
```

---

## Memory Layout

```
DynamicArray object:
┌──────────┬──────────┬──────────┐
│  cap_    │  arr_    │  size_   │
│   10     │    *──────────┐     │
│          │          │    3     │
└──────────┴──────────┴────│─────┘
                           ↓
Heap:        ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
             │ 1 │ 2 │ 3 │ ? │ ? │ ? │ ? │ ? │ ? │ ? │
             └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
               0   1   2   3   4   5   6   7   8   9
                         ↑
                    size_ = 3 (logical end)
                                              cap_ = 10 (physical end)
```

---

## Build & Run

```bash
make                    # Build all programs
make dynamic_arrays1    # Build specific
make clean              # Remove all binaries
./dynamic_arrays1       # Run
```

