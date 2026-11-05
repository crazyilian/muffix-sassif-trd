// flow_t: capacity of one edge, total flow is ll
// undirected edges: flow_t must fit 2c
using flow_t = int;
const int LOG = 0; // масштабирование, =0 если не нужно. Обычно =0 в 2-10 раз быстрее.
struct Edge { int u, r; flow_t f, c; };

struct Dinic {
  vector<vector<Edge>> g;
  vector<int> inds, dist, Q; // dist < 0: unreached or dead
  int ql, qr, S, T;
  flow_t BIT; // 2^LOG must fit flow_t
  Dinic(int n) : g(n), inds(n), dist(n), Q(n) {}

  bool bfs() {
    fill(all(dist), -1);
    ql = 0, qr = 0;
    dist[S] = 0, Q[qr++] = S;
    while (ql < qr) {
      int v = Q[ql++];
      for (auto &e : g[v]) {
        int u = e.u;
        if (dist[u] >= 0 || e.c - e.f < BIT)
          continue;
        dist[u] = dist[v] + 1;
        Q[qr++] = u;
        if (u == T) return true;
      }
    }
    return false;
  }

  flow_t dfs(int v, flow_t maxF) {
    if (v == T) return maxF;
    flow_t ans = 0;
    for (int &i = inds[v]; i < g[v].size(); ++i) {
      auto &e = g[v][i];
      auto cc = min(maxF - ans, e.c - e.f);
      // one random access per edge: x1.2
      if (dist[e.u] != dist[v] + 1 || cc < BIT)
        continue;
      auto f = dfs(e.u, cc);
      if (f != 0) {
        e.f += f, ans += f;
        g[e.u][e.r].f -= f;
      }
      // иногда быстрее один иф, иногда другой
      if (maxF - ans < 1) break;
      // if (maxF - ans < BIT) break;
    }
    if (inds[v] == g[v].size()) dist[v] = -1; // dead end
    return ans;
  }

  // repeated runs are NOT independent
  void run(int s, int t) {
    S = s, T = t;
    assert(S != T);
    for (BIT = (1ll << LOG); BIT > 0; BIT >>= 1) {
      while (bfs()) {
        memset(inds.data(), 0, inds.size() * sizeof(int));
        for (auto &e : g[S]) {
          if (dist[e.u] != 1 || e.c - e.f < BIT)
            continue;
          flow_t f = dfs(e.u, e.c - e.f);
          e.f += f, g[e.u][e.r].f -= f;
        }
      }
    }
  }

  int addedge(int v, int u, flow_t c) { // index in g[v]
    int i = g[v].size();
    g[v].pb({u, (int)g[u].size(), 0, c});
    // если не ориентированно, то обратная capacity = c
    g[u].pb({v, i, 0, 0});
    return i;
  }
};

void use_example() {
  Dinic dinic(n);
  for (int i = 0; i < m; ++i) {
    int v, u; flow_t c;
    cin >> v >> u >> c;
    v--, u--;
    dinic.addedge(v, u, c);
  }
  dinic.run(s, t);
  ll maxflow = 0; // may not fit flow_t
  for (auto &e : dinic.g[s]) maxflow += e.f;
  vector<int> cut;
  for (int i = 0; i < m; ++i) {
    auto &e = edges[i];
    if (dinic.dist[e.v] >= 0 && dinic.dist[e.u] < 0)
      cut.pb(i);
  }
}
