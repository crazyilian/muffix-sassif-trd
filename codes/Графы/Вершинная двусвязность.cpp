vector<pair<int, int>> graph[MAX_V];
bitset<MAX_V> vis;
int st[MAX_E], col[MAX_E], tin[MAX_V], up[MAX_V];
int sti = 0, cc = 0, tt = 0;

void dfs(int v, int pei) {
  vis[v] = true;
  int upv = tin[v] = tt++;
  for (auto [u, ei] : graph[v]) {
    if (ei == pei) continue;
    if (!vis[u]) {
      int pt = sti;
      st[sti++] = ei;
      dfs(u, ei);
      upv = min(upv, up[u]);
      if (up[u] >= tin[v]) {
        while (sti > pt)
          col[st[--sti]] = cc;
        cc++;
      }
    } else if (tin[u] <= tin[v]) {
      st[sti++] = ei;
      upv = min(upv, tin[u]);
    }
  }
  up[v] = upv;
}

// graph[v].emplace_back(u, i);
// graph[u].emplace_back(v, i);
fill(col, col + m, -1);
for (int v = 0; v < n; ++v) {
  if (!vis[v])
    dfs(v, -1);
}
// col[i] - цвет i-го ребра
// cc - итоговое кол-во компонент
