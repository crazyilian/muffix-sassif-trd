void dfs1(int v, vector<char> &used, vector<int> &topsort) {
  used[v] = 1;
  for (auto u : g[v]) {
    if (!used[u])
      dfs1(u, used, topsort);
  }
  topsort.push_back(v);
}

void dfs2(int v, int col, vector<int> &comp) {
  comp[v] = col;
  for (auto u : rg[v]) {
    if (comp[u] == -1)
      dfs2(u, col, comp);
  }
}

signed main() {
  vector<int> topsort;
  topsort.reserve(n);
  vector<char> used(n, 0);
  for (int v = 0; v < n; ++v) {
    if (!used[v])
      dfs1(v, used, topsort);
  }
  reverse(all(topsort));
  int cc = 0;
  vector<int> comp(n, -1);
  for (int i = 0; i < n; ++i) {
    if (comp[topsort[i]] == -1)
      dfs2(topsort[i], cc++, comp);
  }
}
