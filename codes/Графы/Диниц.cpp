// flow_t: capacity of one edge, total flow is ll
// undirected edges: flow_t must fit 2c
using flow_t = int;
const int LOG = 29; // масштабирование, =0 если не нужно
struct Edge { int u, r; flow_t f, c; };

struct Dinic {
  vector<vector<Edge>> graph;
  vector<char> vis;
  vector<int> inds, dist, Q;
  int ql, qr, S, T;
  flow_t BIT; // 2^LOG must fit flow_t
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

  flow_t dfs(int v, flow_t maxF) {
    if (v == T) return maxF;
    flow_t ans = 0;
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
          flow_t f = dfs(e.u, e.c - e.f);
          e.f += f, graph[e.u][e.r].f -= f;
        }
      }
    }
  }

  int addedge(int v, int u, flow_t c) { // index in graph[v]
    int i = graph[v].size();
    graph[v].push_back({u, (int)graph[u].size(), 0, c});
    // если не ориентированно, то обратная capacity = c
    graph[u].push_back({v, i, 0, 0});
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
  for (auto &e : dinic.graph[s])
    maxflow += e.f;

  vector<int> cut;
  for (int i = 0; i < m; i++) {
    auto &e = edges[i];
    if (dinic.vis[e.v] && !dinic.vis[e.u])
      cut.push_back(i);
  }
}
