// unconnected graph, deleting edges, set<int> g[N];
for (int v = 0; v < n; v++) {
  if (!g[v].empty()) {
    vector<int> ccl;
    vector<int> s = {v};
    while (!s.empty()) {
      int u = s.back();
      if (g[u].empty()) {
        ccl.pb(u);
        s.pop_back();
      } else {
        int u2 = *g[u].begin();
        g[u].erase(u2);
        g[u2].erase(u);
        s.pb(u2);
      }
    }
    // ccl[0] = ccl.back()
    // i.e for graph with edges $(1, 2), (1, 3), (2, 3) \to ccl = [1, 2, 3, 1]$
  }
}
