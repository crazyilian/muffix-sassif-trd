const int LOG = 29; // масштабирование, =0 если не нужно
struct Edge { int u, f, c, r; };

struct Dinic {
  vector<Edge> graph[MAXN];
  // разные битсеты, чтобы легко найти разрез
  bitset<MAXN> vis, visf;
  int dist[MAXN], Q[MAXN];
  int ql, qr, S, T, BIT;
  Dinic() {}

  bool bfs() {
    vis.reset();
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
        // удаление ифа может ускорить,
        // но скорее сильно замедлит
        if (u == T) return true;
      }
    }
    return vis[T];
  }

  int dfs(int v, int minC) {
    if (v == T) return minC;
    visf[v] = true;
    int ans = 0;
    for (auto &e : graph[v]) {
      auto cc = min(minC - ans, e.c - e.f);
      // удалить второе условие, если один битсет
      if (dist[e.u] <= dist[v] || !vis[e.u] || visf[e.u] || cc < BIT)
        continue;
      auto f = dfs(e.u, cc);
      if (f != 0) {
        e.f += f, ans += f;
        graph[e.u][e.r].f -= f;
      }
    }
    return ans;
  }

  void run(int s, int t) {
    S = s, T = t;
    for (BIT = (1ll << LOG); BIT > 0; BIT >>= 1) {
      while (bfs()) {
        visf.reset();
        dfs(S, MAXC);
      }
    }
  }

  void addedge(int v, int u, int c) {
    graph[v].push_back({u, 0, c, (int)graph[u].size()});
    // если ориентированно, то обратная capacity = 0
    graph[u].push_back({v, 0, c, (int)graph[v].size() - 1});
  }
};

void use_example() {
  Dinic dinic;
  for (int i = 0; i < m; ++i) {
    int v, u, c;
    cin >> v >> u >> c;
    v--, u--;
    dinic.addedge(v, u, c);
  }
  dinic.run(s, t);

  long long maxflow = 0;
  for (auto &e : dinic.graph[s])
    maxflow += e.f;

  vector<int> cut;
  for (int i = 0; i < m; i++) {
    auto &e = edges[i];
    if (dinic.vis[e.v] != dinic.vis[e.u])
      cut.push_back(i);
  }
}
