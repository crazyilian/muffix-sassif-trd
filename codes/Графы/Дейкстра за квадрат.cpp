// 0-based
pair<vector<int>, vector<int>> dijkstra(int start, int n) {
  vector<int> dist(n, INF);
  vector<int> pred(n, -1);
  vector<int> used(n);
  dist[start] = 0;
  for (int _ = 0; _ < n; ++_) {
    int v = -1;
    for (int i = 0; i < n; ++i) {
      if (!used[i])
        if (v == -1 || dist[v] > dist[i])
          v = i;
    }
    if (v == -1) break;
    for (auto [u, w] : g[v]) {
      if (dist[u] > w + dist[v]) {
        dist[u] = w + dist[v];
        pred[u] = v;
      }
    }
    used[v] = 1;
  }
  return {dist, pred};
}
