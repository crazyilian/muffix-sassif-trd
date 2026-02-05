struct LRFlow {
  Dinic dinic;
  int S, T; // исток и сток
  int Sx, Tx; // вспомогательные вершины, любые неиспользуемые индексы
  vector<ll> dem;

  LRFlow(int n, int S, int T, int Sx, int Tx) : S(S), T(T), Sx(Sx), Tx(Tx), dinic(n), dem(n) {}

  void addedge(int v, int u, int mincap, int maxcap, int i) {
    // i - any number, can be used for flow restoring. Just store it inside Edge.
    dinic.addedge(v, u, maxcap - mincap, i);
    dem[v] -= mincap;
    dem[u] += mincap;
  }

  // edge.real_flow = edge.flow + edge.mincap
  // returns true if found flow is feasible
  // size of flow is sum flows+mincaps from S
  bool run() {
    dinic.addedge(T, S, INF, -1); // INF >= sum maxcap-mincap
    ll totaldem = 0;
    for (int v = 0; v < dem.size(); ++v) {
      if (dem[v] > 0) {
        totaldem += dem[v];
        // here capacity could be long long (sum of v's mincaps)
        dinic.addedge(Sx, v, dem[v], -1);
      } else if (dem[v] < 0)
        dinic.addedge(v, Tx, -dem[v], -1);
    }
    dinic.run(Sx, Tx);
    ll flow = 0;
    for (auto &e : dinic.graph[Sx]) flow += e.f;
    if (flow != totaldem) return false;
    // return true; // if want ONLY feasibility
    for (int v = 0; v < dem.size(); ++v) {
      if (dem[v]) dinic.graph[v].pop_back();
    }
    dinic.graph[Sx].clear();
    dinic.graph[Tx].clear();
    dinic.graph[S].pop_back();
    dinic.graph[T].pop_back();
    // dinic.run(S, T); // if we want max lr-flow (not any lr-flow)
    return true;
  }
};
