```python
def fixed_length_window(arr, k):
  initialize:
  - l and r to 0 (empty window)
  - data structures to track window info
  - cur_best to 0
  while we can grow the window (r < len(arr))
    grow the window (update data structures and increase r)
    if the window has the correct length (r - l == k)
      update cur_best if needed
      shrink the window (update data structures and increase l)
  return cur_best
```
