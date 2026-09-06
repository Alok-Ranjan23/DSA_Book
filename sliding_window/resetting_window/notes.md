```python
def resetting_window(arr):
initialize:
  - l and r to 0 (empty window)
  - data structures to track window info
  - cur_best to 0
  while we can grow the window (r < len(arr))
    if the window is still valid with one more element
      grow the window (update data structures and increase r)
      update cur_best if needed
    else
      reset window and data structures past the problematic element
  return cur_best
```
