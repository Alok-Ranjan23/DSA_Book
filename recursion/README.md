# Recursion

A collection of recursion problems demonstrating various patterns and techniques.

---

## 1. Divide and Conquer

Problems that split the input into smaller parts, solve recursively, and combine results.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `laminal_arrays.cc` | Find max sum laminal subarray | Divide array into halves, track max | O(n) | O(log n) |
| `powers_mod_m.cc` | Compute a^p mod m efficiently | Binary exponentiation (squaring) | O(log p) | O(log p) |

---

## 2. Tree / Nested Structure Traversal

Problems involving recursive data structures like trees or nested arrays.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `nested_array_sum.cc` | Sum all integers in nested array | Recursive tree traversal | O(n) | O(d) |

---

## 3. Mutual Recursion

Problems where multiple functions call each other recursively.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `lego_castle.cc` | Count blocks for n-story castle | Two functions with interdependent recurrences | O(n) | O(n) |

---

## 4. String Expansion / Transformation

Problems that recursively process and expand strings.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `robot_instructions.cc` | Expand robot movement instructions | Recursive string building with branching | O(2^k · n) | O(2^k · n) |

---

## Recursion Recipe

The core pattern for solving recursive problems:

```
recursive_solution(problem)
  1. Define base case(s):
     - What's the simplest input? Return directly.
     - Handle edge cases (empty, single element, etc.)

  2. Define recursive case:
     - Break problem into smaller subproblem(s)
     - Make recursive call(s) on subproblem(s)
     - Combine results to solve original problem

  3. Trust the recursion:
     - Assume recursive calls return correct results
     - Focus only on current level's logic
```

**Key insight:** Every recursive function needs at least one base case that doesn't make a recursive call, otherwise you get infinite recursion.

---

## Common Recursion Patterns

```
Linear Recursion (single call):
  f(n) = base_case           if n == 0
       = combine(n, f(n-1))  otherwise

Binary Recursion (two calls):
  f(n) = base_case                    if n is small
       = combine(f(left), f(right))   otherwise

Tail Recursion (optimizable):
  f(n, acc) = acc                     if n == 0
            = f(n-1, update(acc))     otherwise

Mutual Recursion:
  f(n) = ... g(n-1) ...
  g(n) = ... f(n-1) ...
```

---

## Complexity Analysis Tips

```
Recurrence                          Time Complexity
─────────────────────────────────────────────────────
T(n) = T(n-1) + O(1)                O(n)
T(n) = T(n-1) + O(n)                O(n²)
T(n) = T(n/2) + O(1)                O(log n)
T(n) = T(n/2) + O(n)                O(n)
T(n) = 2·T(n/2) + O(1)              O(n)
T(n) = 2·T(n/2) + O(n)              O(n log n)
T(n) = 2·T(n-1) + O(1)              O(2^n)
```

---

## Build & Run

```bash
make              # Build all programs
make <program>    # Build specific (e.g., make laminal_arrays)
make clean        # Remove all binaries
./<program>       # Run (e.g., ./laminal_arrays)
```

