// flow_t: capacity of one edge, total flow is ll
// cost_t: must fit n * max|w| and the answer
using flow_t = int;
using cost_t = ll;
const cost_t INFw = 1e18;
const flow_t INFf = 2e9;

struct MinCost {
  struct Edge { int u, r; flow_t f, c; cost_t w; };
  vector<vector<Edge>> g; // g[e.u][e.r] is reverse of e
  vector<cost_t> dist, pot;
  vector<int> pre;
  vector<char> inQ;
  int S, T;
  MinCost(int n) : g(n), dist(n), pot(n), pre(n), inQ(n) {}

  flow_t get_flow() {
    int v = T;
    if (pre[v] == -1) return 0;
    flow_t f = INFf;
    do { // g[v][pre[v]]: reverse of the path edge into v
      Edge &r = g[v][pre[v]], &e = g[r.u][r.r];
      f = min(f, e.c - e.f);
      if (f == 0) return 0;
      v = r.u;
    } while (v != S);
    v = T;
    do {
      Edge &r = g[v][pre[v]], &e = g[r.u][r.r];
      e.f += f, r.f -= f;
      v = r.u;
    } while (v != S);
    return f;
  }

  void spfa() {
    fill(all(dist), INFw);
    fill(all(pre), -1);
    dist[S] = 0;
    deque<int> Q = {S};
    inQ[S] = true;
    while (!Q.empty()) {
      int v = Q.front();
      Q.pop_front(), inQ[v] = false;
      cost_t d = dist[v];
      for (Edge &e : g[v]) {
        if (e.f == e.c) continue;
        cost_t w = e.w + pot[v] - pot[e.u];
        if (dist[e.u] <= d + w) continue;
        pre[e.u] = e.r, dist[e.u] = d + w;
        if (!inQ[e.u])
          inQ[e.u] = true, Q.pb(e.u);
      }
    }
    for (int i = 0; i < dist.size(); ++i)
      if (dist[i] < INFw) // else pot overflows
        pot[i] += dist[i];
  }

  // returns {flow, cost}
  // repeated runs are NOT independent
  pair<ll, cost_t> run(int s, int t) {
    S = s, T = t;
    spfa(); // pot[i] = 0 // or ford_bellman
    ll flow = 0;
    while (true) {
      flow_t ff = get_flow();
      if (ff == 0) break;
      flow += ff;
      spfa(); // or dijkstra - x1.5 speed when big costs
    }
    cost_t cost = 0;
    for (auto &es : g)
      for (auto &e : es)
        if (e.f > 0) cost += e.f * e.w;
    return {flow, cost};
  }

  // returns id: flow on the edge = g[v][id].f
  int addedge(int v, int u, flow_t c, cost_t w) {
    int i = g[v].size();
    g[v].pb({u, (int)g[u].size(), 0, c, w});
    g[u].pb({v, i, 0, 0, -w});
    return i;
  }
};

void use_example() {
  MinCost mc(n);
  for (int i = 0; i < m; ++i) {
    int v, u; flow_t c; cost_t w;
    cin >> v >> u >> c >> w;
    v--, u--;
    mc.addedge(v, u, c, w);
  }
  auto [flow, cost] = mc.run(s, t);
}
