# DFS using stack

```
dfsVisit(g, s):
  time += 1
  s.color = GRAY
  s.discoveredTime = time
  stack = emptyStack()

  # Put start vertex as well as the iterator of its adjacency
  # list to stack
  stack.push( ( s, g.adj(s).begin() ) )

  while stack is not empty:
    u = stack.top().first
    iter = stack.top().second
    end = g.adj(u).end()

    if iter is not end:
      v = *iter
      if v.color is WHITE:
        time += 1
        v.color = GRAY
        v.discoveredTime = time
        v.prev = u
        stack.push( ( v, g.adj(v).begin() ) )
        report (u, v) as TREE edge

      # v is not WHITE
      else:
        ++iter
        if v.color is GRAY:
          report (u, v) as BACK edge
        else:
          if u.discoveredTime < v.discoveredTime:
            report (u, v) as FORWARD edge
          else:
            report (u, v) as CROSS edge

    # iterator reached the end
    else:
      time += 1
      u.color = BLACK
      u.finishedTime = time
      stack.pop()

      # Advance iterator at top since we just finished exploring a
      # vertex that was WHITE
      if stack is not empty:
        ++stack.top().second

dfs(g):
  for each u in g.vertices():
    u.color = WHITE
    u.prev = NULL

  time = 0
  for each u in g.vertices():
    if u.color is WHITE:
      dfsVisit(g, u)
```
