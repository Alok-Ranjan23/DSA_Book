# Grids and Matrices

A collection of grid/matrix problems commonly seen in coding interviews.

---

## 1. Movement Pattern Problems

Problems involving traversal or piece movement on a grid.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `chess_moves.cc` | Find cells reachable by King/Knight/Queen | Direction vectors | O(n) | O(k) |
| `queen_reach.cc` | Mark all cells attackable by queens | 8-directional extension | O(n²·q) | O(q) |
| `snowprints.cc` | Track fox's closest approach to river | Path following | O(C) | O(1) |
| `spiral_order.cc` | Fill grid in spiral from center | Layer-by-layer fill | O(n²) | O(n²) |

---

## 2. Subgrid Problems

Problems involving rectangular subregions of a grid.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `valid_sudoku.cc` | Check Sudoku board for conflicts | Hash set duplicate check | O(1)* | O(1) |
| `subgrid_max.cc` | Max in subgrid from each cell to bottom-right | DP (reverse traversal) | O(R·C) | O(1) |
| `subgrid_sum.cc` | Sum of subgrid from each cell to bottom-right | DP + inclusion-exclusion | O(R·C) | O(1) |

*Fixed 9×9 board

---

## 3. Matrix Operation Problems

Fundamental matrix transformations.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `matrix_operation.cc` | Transpose, rotate, reflect | In-place swaps | O(n²) | O(1) |

**Rotation Formulas:**
- Clockwise 90° = Transpose + Horizontal Reflection
- Counter-clockwise 90° = Transpose + Vertical Reflection

---

## Quick Reference

```
Direction Vectors (8-directional):
  (-1,-1) (-1,0) (-1,1)
  ( 0,-1)   X    ( 0,1)
  ( 1,-1) ( 1,0) ( 1,1)

Knight Moves (L-shaped):
  {±1,±2}, {±2,±1}
```

---

## Build & Run

```bash
make              # Build all programs
make <program>    # Build specific (e.g., make chess_moves)
make clean        # Remove all binaries
./<program>       # Run (e.g., ./chess_moves)
```

