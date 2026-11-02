// g: tree or forest
// par[v] = parent in centroid trees; -1 for roots
// level[root] = 1
struct Centroid {
  const vector<vector<int>> &g;
  vector<int> levels, _szs, par;
  Centroid(const vector<vector<int>> &g) : g(g),
      levels(g.size()), _szs(g.size()), par(g.size()) {
    for (int v = 0; v < g.size(); ++v)
      if (levels[v] == 0) build(v);
  }

  int _calcsizes(int v, int p) {
    int sz = 1;
    for (int u : g[v]) {
      if (u != p && levels[u] == 0)
        sz += _calcsizes(u, v);
    }
    return _szs[v] = sz;
  }

  void build(int v, int lvl = 1, int p = -1) {
    int sz = _calcsizes(v, -1);
    int nxt = v, prv;
    while (nxt != -1) {
      prv = v, v = nxt, nxt = -1;
      for (int u : g[v]) {
        if (u != prv && levels[u] == 0 && _szs[u] * 2 >= sz)
          nxt = u;
      }
    }
    levels[v] = lvl;
    par[v] = p;
    for (int u : g[v]) {
      if (levels[u] == 0)
        build(u, lvl + 1, v);
    }
    // calc smth for centroid v: dfs by levels[u]>=lvl
    // _szs[] are NOT subtree sizes (it's trash)
  }
};
