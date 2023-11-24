void dfs1(int v, vector<int> &topsort) {
  used[v] = 1;
  for (auto u : g[v]) {
    if (!used[u]) {
      dfs1(u, topsort);
    }
  }
  topsort.push_back(v);
}

void dfs2(int v, int col) {
  comp[v] = col;
  for (auto u : rg[v]) {
    if (!comp[u]) {
      dfs2(u, col);
    }
  }
}

signed main() {
  vector<int> topsort;
  for (int v = 1; v <= n; ++v)
    if (!used[v])
      dfs1(v, topsort);
  reverse(all(topsort));
  for (int j = 1; j <= n; ++j)
    if (!comp[topsort[j - 1]])
      dfs2(topsort[j - 1], j);
}
