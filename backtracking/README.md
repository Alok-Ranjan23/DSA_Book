# Backtracking

Systematic exploration of solution spaces using the **Choose → Explore → Unchoose** pattern.

---

## Overview

Backtracking builds solutions incrementally, abandoning a branch ("backtracking") as soon as it determines the branch cannot lead to a valid or optimal solution. It is a refined form of brute-force that prunes the search space.

| File | Problem | Pattern | Time |
|------|---------|---------|------|
| `subset_enumeration.cc` | Generate all subsets (power set) | Include/Exclude | O(2^n * n) |
| `permutation_enumeration.cc` | Generate all permutations | Swap-based | O(n! * n) |
| `tobe_nottobe.cc` | All sentence variations (include/exclude words) | Include/Exclude | O(2^n * n) |
| `thesaurusly.cc` | Replace words with synonyms — all combos | Branching on choices | O(k^m * n) |
| `count_unique_sum_zero.cc` | Count unique submultisets with sum zero | Grouped choices | O(∏(count_i + 1)) |
| `ikea_shopping.cc` | Maximize style ratings within budget (0/1 Knapsack) | Include/Exclude + Pruning | O(2^n) |
| `white_hat_hacker.cc` | Brute-force password cracking | Permutation + Early exit | O(P(26, k)) |
| `jumping_numbers.cc` | All jumping numbers less than n | Digit-by-digit construction | O(k * log n) |
| `max_path_sum.cc` | Max-sum path (down/right only) | Grid DFS | O(2^(R+C)) |
| `four_dir_max_path_sum.cc` | Max-sum path (4-directional) | Grid DFS + Visited | O(4^(R*C)) |
| `escape_with_all_clues.cc` | Shortest path collecting all clues | Grid DFS + Pruning | O(4^(R*C)) |

---

## The Backtracking Template

```
function backtrack(state):
    if goal_reached(state):
        record solution
        return

    for each choice in available_choices(state):
        if is_valid(choice):
            make_choice(choice)        // CHOOSE
            backtrack(new_state)        // EXPLORE
            undo_choice(choice)         // UNCHOOSE
```

---

## Key Patterns

### 1. Include / Exclude (Subset Pattern)
Each element is either included or excluded — binary decision tree.

```
                    []
           /                  \
        [x]                   []
       /    \              /      \
    [x,y]   [x]          [y]      []
```
Used in: `subset_enumeration`, `tobe_nottobe`, `ikea_shopping`, `count_unique_sum_zero`

### 2. Swap-Based (Permutation Pattern)
Fix one element at each position by swapping, then permute the rest.

```
[A, B, C] at index 0:
  Fix A → permute [B, C]
  Fix B → permute [A, C]
  Fix C → permute [A, B]
```
Used in: `permutation_enumeration`, `white_hat_hacker`

### 3. Grid Exploration (Path Pattern)
Move through a grid in allowed directions, tracking visited cells to avoid cycles.

```
From cell (r, c):
  Try UP, DOWN, LEFT, RIGHT
  Mark visited before recursing
  Unmark visited after returning
```
Used in: `max_path_sum`, `four_dir_max_path_sum`, `escape_with_all_clues`

### 4. Branching on Choices
At each step, branch into a variable number of options (e.g., synonyms, digits).

Used in: `thesaurusly`, `jumping_numbers`

---

## Pruning Techniques

| Technique | Description | Used In |
|-----------|-------------|---------|
| Constraint check | Skip choices that violate constraints (budget, bounds) | `ikea_shopping`, grid problems |
| Visited array | Prevent revisiting cells in grid paths | `four_dir_max_path_sum`, `escape_with_all_clues` |
| Best-so-far bound | Abandon path if it can't beat current best | `escape_with_all_clues` |
| Early termination | Stop all recursion once solution is found | `white_hat_hacker` |
| Grouping duplicates | Group identical elements to avoid duplicate subsets | `count_unique_sum_zero` |

---

## Backtracking vs Other Approaches

| Aspect | Backtracking | Dynamic Programming | BFS |
|--------|-------------|-------------------|-----|
| Strategy | Explore all, prune bad branches | Optimal substructure + memoization | Level-by-level exploration |
| Finds | All solutions / best solution | Optimal value | Shortest path (unweighted) |
| Space | O(depth) recursion stack | O(state space) table | O(state space) queue |
| Best for | Small search spaces, all solutions | Overlapping subproblems | Shortest path guaranteed |

---

## Problems To Solve

| # | Problem | Pattern | Difficulty |
|---|---------|---------|------------|
| 1 | N-Queens | Constraint satisfaction | Medium |
| 2 | Sudoku Solver | Constraint satisfaction | Hard |
| 3 | Word Search in Grid | Grid DFS | Medium |
| 4 | Combination Sum | Include/Exclude with repeats | Medium |
| 5 | Letter Combinations of Phone Number | Branching on choices | Medium |
| 6 | Generate Parentheses | Constraint-based generation | Medium |
| 7 | Palindrome Partitioning | Substring branching | Medium |
| 8 | Rat in a Maze | Grid DFS + Visited | Medium |
| 9 | Knight's Tour | Grid DFS + Visited | Hard |
| 10 | Graph Coloring | Constraint satisfaction | Hard |

---

## Build & Run

```bash
make                          # Build all programs
make subset_enumeration       # Build specific
make clean                    # Remove all binaries
./subset_enumeration          # Run
```
