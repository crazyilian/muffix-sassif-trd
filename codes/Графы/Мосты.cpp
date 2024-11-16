// graph[v][i] = {u, edge_i}
void dfs(int v, int pi = -1) {
  vis[v] = 1;
  up[v] = tin[v] = timer++;
  for (auto [u, ei] : g[v]) {
    if (!vis[u]) {
      dfs(u, v);
      up[v] = min(up[v], up[u]);
    } else if (ei != pi)
      up[v] = min(up[v], tin[u]);
    if (up[u] > tin[v]) {
      bridges.emplace_back(v, u);
      is_bridge[ei] = 1;
    }
  }
}
