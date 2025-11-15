struct TwoSat {
  int n;
  vector<vector<int>> g, rg;
  vector<int> comp, topsort;
  vector<char> used;

  TwoSat(int n) : n(n) {
    g.resize(2 * n);
    rg.resize(2 * n);
    comp.assign(2 * n, -1);
    topsort.reserve(2 * n);
    used.assign(2 * n, 0);
  }

  int neg(int v) {
    return 2 * n - 1 - v;
  }

  void add(int v, int u) {
    g[v].pb(u);
    rg[u].pb(v);
  }

  void add_OR(int v, int u) { // v | u
    add(neg(v), u), add(neg(u), v);
  }

  void add_IMPL(int v, int u) { // v -> u
    add_OR(neg(v), u);
  }

  void dfs1(int v) {
    used[v] = 1;
    for (auto u: g[v]) {
      if (!used[u])
        dfs1(u);
    }
    topsort.push_back(v);
  }

  void dfs2(int v, int col) {
    comp[v] = col;
    for (auto u: rg[v]) {
      if (comp[u] == -1)
        dfs2(u, col);
    }
  }

  void SCC() {
    for (int v = 0; v < 2 * n; ++v) {
      if (!used[v])
        dfs1(v);
    }
    reverse(all(topsort));
    int cc = 0;
    for (int i = 0; i < 2 * n; ++i) {
      if (comp[topsort[i]] == -1)
        dfs2(topsort[i], cc++);
    }
  }

  vector<char> solution() {
    assert(n > 0); // returns {} if ans exists AND not
    SCC();
    vector<char> ans(n);
    for (int v = 0; v < n; ++v) {
      if (comp[v] == comp[neg(v)])
        return {}; // no solution
      ans[v] = comp[v] > comp[neg(v)];
    }
    return ans;
  }
};
