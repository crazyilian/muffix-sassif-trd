// кратные рёбра можно, петли нельзя
void cactus_dfs(int v, int pei, vector<vector<int>> &c2vs, vector<int> &e2c, vector<vector<pair<int, int>>> &g, vector<char> &used, vector<pair<int, int>> &st) {
  st.pb({v, pei});
  used[v] = 1;
  for (auto [u, ei] : g[v]) {
    if (ei == pei || e2c[ei] != -1)
        continue;
    if (used[u]) {
      int с = c2vs.size();
      c2vs.emplace_back();
      for (int j = st.size()-1; st[j].first != u; --j) {
        c2vs[с].pb(st[j].first);
        e2c[st[j].second] = с;
      }
      c2vs[с].pb(u);
      e2c[ei] = с;
      continue;
    }
    cactus_dfs(u, ei, c2vs, e2c, g, used, st);
  }
  st.pop_back();
}

signed main() {
  // g[v][i] = {u, ei}, граф
  // e2c[ei] = номер цикла ребра ei (либо -1)
  // c2vs[c] = список вершин цикла c (в порядке обхода)
  vector<int> e2c(m, -1); 
  vector<vector<int>> c2vs;
  c2vs.reserve(m - n + 1); // m - n + #комп.связ.
  {
    vector<char> used(n, 0);
    vector<pair<int, int>> st;
    st.reserve(n);
    for (int v = 0; v < n; ++v) {
      if (!used[v])
        cactus_dfs(v, -1, c2vs, e2c, g, used, st);
    }
  }
  // создание дерева по кактусу
  vector<vector<int>> ngraph(n + c2vs.size());
  for (int v = 0; v < n; ++v) {
    for (auto [u, ei] : g[v]) {
      if (e2c[ei] == -1)
        ngraph[v].pb(u);
    }
  }
  for (int c = 0; c < c2vs.size(); ++c) {
    for (int v : c2vs[c]) {
      ngraph[n + c].pb(v);
      ngraph[v].pb(n + c);
    }
  }
}
