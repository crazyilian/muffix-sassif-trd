struct LRFlow {
  Dinic dinic;
  int S, T; // исток и сток
  int Sx, Tx; // вспомогательные вершины, любые неиспользуемые индексы

  LRFlow(int S, int T, int Sx, int Tx) : S(S), T(T), Sx(Sx), Tx(Tx) {}

  void addedge(int v, int u, int mincap, int maxcap) {
    // все рёбра ориентированные
    dinic.addedge(v, u, maxcap - mincap);
    dinic.addedge(Sx, u, mincap);
    dinic.addedge(v, Tx, mincap);
  }

  bool inner_check() {
    for (auto edge: dinic.graph[Sx]) {
      if (edge.f != edge.c) {
        return false;
      }
    }
    for (auto edge: dinic.graph[Tx]) {
      auto iedge = dinic.graph[edge.u][edge.r];
      if (iedge.f != iedge.c) {
        return false;
      }
    }
    return true;
  }

  bool only_existence() {
    dinic.addedge(T, S, INF);
    dinic.run(Sx, Tx);
    return inner_check();
  }

  bool with_flows() {
    dinic.run(Sx, Tx);
    dinic.run(Sx, T);
    dinic.run(S, Tx);
    dinic.run(S, T);
    // real (v, u, mincap, maxcap) flow = flow on (v, u, maxcap - mincap) edge + mincap
    return inner_check();
  }
};
