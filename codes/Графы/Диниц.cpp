const int LOG = 29; // масштабирование, =0 если не нужно
struct Edge { int u, f, c, r; };

struct Dinic {
  vector<vector<Edge>> graph;
  vector<char> vis;
  vector<int> inds, dist, Q;
  int ql, qr, S, T, BIT;
  Dinic(int n) : graph(n), vis(n), inds(n), dist(n), Q(n) {}

  bool bfs() {
    memset(vis.data(), 0, vis.size());
    ql = 0, qr = 0;
    dist[S] = 0, vis[S] = true;
    Q[qr++] = S;
    while (ql < qr) {
      int v = Q[ql++];
      for (auto &e : graph[v]) {
        int u = e.u;
        if (vis[u] || e.c - e.f < BIT)
          continue;
        vis[u] = true;
        dist[u] = dist[v] + 1;
        Q[qr++] = u;
        if (u == T) return true;
      }
    }
    return false;
  }

  int dfs(int v, int maxF) {
    if (v == T) return maxF;
    int ans = 0;
    for (int &i = inds[v]; i < graph[v].size(); ++i) {
      auto &e = graph[v][i];
      auto cc = min(maxF - ans, e.c - e.f);
      if (dist[e.u] <= dist[v] || !vis[e.u] || inds[e.u] == graph[e.u].size() || cc < BIT)
        continue;
      auto f = dfs(e.u, cc);
      if (f != 0) {
        e.f += f, ans += f;
        graph[e.u][e.r].f -= f;
      }
      // иногда быстрее один иф, иногда другой
      if (maxF - ans < 1) break;
      // if (maxF - ans < BIT) break;
    }
    return ans;
  }

  void run(int s, int t) {
    S = s, T = t;
    assert(S != T);
    for (BIT = (1ll << LOG); BIT > 0; BIT >>= 1) {
      while (bfs()) {
        memset(inds.data(), 0, inds.size() * sizeof(int));
        for (auto &e : graph[S]) {
          if (inds[e.u] == graph[e.u].size() || e.c - e.f < BIT)
            continue;
          int f = dfs(e.u, e.c - e.f);
          e.f += f, graph[e.u][e.r].f -= f;
        }
      }
    }
  }

  void addedge(int v, int u, int c) {
    graph[v].push_back({u, 0, c, (int)graph[u].size()});
    // если не ориентированно, то обратная capacity = c
    graph[u].push_back({v, 0, 0, (int)graph[v].size() - 1});
  }
};

void use_example() {
  Dinic dinic(n);
  for (int i = 0; i < m; ++i) {
    int v, u, c;
    cin >> v >> u >> c;
    v--, u--;
    dinic.addedge(v, u, c);
  }
  dinic.run(s, t);

  ll maxflow = 0;
  for (auto &e : dinic.graph[s])
    maxflow += e.f;

  vector<int> cut;
  for (int i = 0; i < m; i++) {
    auto &e = edges[i];
    if (dinic.vis[e.v] != dinic.vis[e.u])
      cut.push_back(i);
  }
}
