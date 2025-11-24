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

  // returns size of lr-flow (-1 if not exists)
  // edge.real_flow = edge.flow + edge.mincap
  ll run() {
    dinic.addedge(T, S, INF, -1); // INF >= sum maxcap-mincap
    ll totaldem = 0;
    for (int v = 0; v < dem.size(); ++v) {
      if (dem[v] > 0) {
        totaldem += dem[v];
        // here capacity could potentially be long long (sum of v's mincaps)
        dinic.addedge(Sx, v, dem[v], -1);
      } else if (dem[v] < 0)
        dinic.addedge(v, Tx, -dem[v], -1);
    }
    dinic.run(Sx, Tx);
    ll flow = 0;
    for (auto &e : dinic.graph[Sx]) flow += e.f;
    if (flow != totaldem) return -1;
    for (int v = 0; v < dem.size(); ++v) {
      if (dem[v]) dinic.graph[v].pop_back();
    }
    dinic.graph[Sx].clear();
    dinic.graph[Tx].clear();
    dinic.graph[S].pop_back();
    dinic.graph[T].pop_back();
    // dinic.run(S, T); // if we want max lr-flow (not any lr-flow)
    for (auto &e : dinic.graph[S]) flow += e.f;
    return flow;
  }
};
