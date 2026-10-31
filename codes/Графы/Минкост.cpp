// flow_t: capacity of one edge, total flow is ll
// cost_t: must fit n * max|w| and the answer
using flow_t = int;
using cost_t = ll;
const cost_t INFw = 1e18;
const flow_t INFf = 2e9;

struct MinCost {
  struct Edge { int v, u; flow_t f, c; cost_t w; };
  vector<Edge> edg; // edg[i ^ 1] is reverse of edg[i]
  vector<vector<int>> graph;
  vector<cost_t> dist, pot;
  vector<int> pre;
  vector<char> inQ;
  int S, T;
  MinCost(int n)
    : graph(n), dist(n), pot(n), pre(n), inQ(n) {}

  flow_t get_flow() {
    int v = T;
    if (pre[v] == -1) return 0;
    flow_t f = INFf;
    do {
      int ei = pre[v];
      Edge &e = edg[ei];
      f = min(f, e.c - e.f);
      if (f == 0) return 0;
      v = e.v;
    } while (v != S);
    v = T;
    do {
      int ei = pre[v];
      edg[ei].f += f;
      edg[ei ^ 1].f -= f;
      v = edg[ei].v;
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
      Q.pop_front();
      inQ[v] = false;
      cost_t d = dist[v];
      for (int ei : graph[v]) {
        Edge &e = edg[ei];
        if (e.f == e.c) continue;
        cost_t w = e.w + pot[v] - pot[e.u];
        if (dist[e.u] <= d + w) continue;
        pre[e.u] = ei;
        dist[e.u] = d + w;
        if (!inQ[e.u]) {
          inQ[e.u] = true;
          Q.pb(e.u);
        }
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
      spfa(); // or dijkstra
    }
    cost_t cost = 0;
    for (int i = 0; i < edg.size(); i += 2)
      cost += edg[i].f * edg[i].w;
    return {flow, cost};
  }

  // returns id: flow on the edge = edg[id].f
  int addedge(int v, int u, flow_t c, cost_t w) {
    // reserve edg to m*2 before adding
    int i = edg.size();
    edg.pb({v, u, 0, c, w});
    edg.pb({u, v, 0, 0, -w});
    graph[v].pb(i);
    graph[u].pb(i + 1);
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
