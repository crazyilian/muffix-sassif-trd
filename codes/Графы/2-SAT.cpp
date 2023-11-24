for (int i = 1; i <= n; ++i) {
  not_v[i] = i + n;
  not_v[i + n] = i;
}
for (int i = 0; i < m; ++i) {
  cin >> u >> v;
  g[not_v[v]].push_back(u);
  g[not_v[u]].push_back(v);
  rg[u].push_back(not_v[v]);
  rg[v].push_back(not_v[u]);
}
// делаем КСС, получаем comp
for (int v = 1; v <= n; ++v) {
  if (comp[v] == comp[not_v[v]]) {
    cout << "UNSATISFIABLE\n";
    return 0;
  }
}
for (int v = 1; v <= n; ++v)
  cout << (comp[v] > comp[not_v[v]] ? v : not_v[v]);
