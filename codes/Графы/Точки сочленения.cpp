void dfs(int v, int p = -1) {
  vis[v] = 1;
  up[v] = tin[v] = timer++;
  bool is_artic = false;
  int child = 0;
  for (auto u : g[v]) {
    if (!vis[u]) {
      child++;
      dfs(u, v);
      up[v] = min(up[v], up[u]);
      is_artic |= p != -1 && up[u] >= tin[v];
    } else
      up[v] = min(up[v], tin[u]);
  }
  is_artic |= p == -1 && child >= 2;
  if (is_artic)
    articulation_points.insert(v);
}
