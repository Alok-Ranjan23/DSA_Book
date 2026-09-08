```python
    def minimum_window(arr):
        initialize:
        - l and r to 0 (empty window)
        - data structures to track window info
        - cur_best to infinity
        while true
            if the window must grow to become valid
                if the window cannot grow (r == len(arr))
                    break
                grow the window (update data structures and increase r)
            else
                update cur_best if needed
                shrink the window (update data structures and increase l)
        return cur_best
```
