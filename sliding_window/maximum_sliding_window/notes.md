```python
def maximum_window(arr):
  initialize:
  - l and r to 0 (empty window)
  - data structures to track window info
  - cur_best to 0
  while we can grow the window (r < len(arr))
    if the window would still be valid with one more element
      grow the window (update data structures and increase r)
      update cur_best if needed
    else if the window is empty
      advance both l and r
    else
      shrink the window (update data structures and increase l)
  return cur_best
```

## When do we need the `l == r` (empty window) guard?

The `else if the window is empty` branch (lines 11-12 above) prevents `l` from
overtaking `r`, which would cause out-of-bounds access.

**Rule**: Look at the `can_grow` condition when the window is empty
(all counters reset to 0). Ask: _"Can `can_grow` still be `false`?"_

| Situation | `l == r` guard needed? | Why |
|-----------|------------------------|-----|
| Every element can satisfy `can_grow` when the window is empty (counter = 0) | **No** — `l` can never catch `r` | Shrinking always frees a resource, so `can_grow` becomes `true` before `l` reaches `r`. |
| Some elements can **never** satisfy `can_grow`, regardless of window state | **Yes** — `l` will overtake `r` | No amount of shrinking helps; the element is fundamentally un-fixable and must be skipped. |

### Examples

**No guard needed** — boost is +20 (any day can be made good):
```cpp
// can_grow is false only when boost_sales >= k.
// Empty window → boost_sales = 0 < k (k >= 1) → can_grow = true. Always.
bool can_grow = projected_sales[r] >= 10 || boost_sales < k;
```

**Guard needed** — boost is only +5 (some days can never be made good):
```cpp
// sales = 4 → 4+5 = 9 < 10 → can_grow = false even with boost_days = 0.
bool can_grow = projected_sales[r] >= 10 || (boost_days < k && projected_sales[r]+5 >= 10);
```
