int levels[MAXN];
int szs[MAXN];
int cent_par[MAXN];

int calcsizes(int v, int p) {
  int sz = 1;
  for (int u : graph[v]) {
    if (u != p && levels[u] == 0)
      sz += calcsizes(u, v);
  }
  return szs[v] = sz;
}

void centroid(int v, int lvl=1, int p=-1) {
  int sz = calcsizes(v, -1);
  int nxt = v, prv;
  while (nxt != -1) {
    prv = v, v = nxt, nxt = -1;
    for (int u : graph[v]) {
      if (u != prv && levels[u] == 0 && szs[u] * 2 >= sz)
        nxt = u;
    }
  }
  levels[v] = lvl;
  cent_par[v] = p;
  for (int u : graph[v]) {
    if (levels[u] == 0)
      centroid(u, lvl + 1, v);
  }
  // calc smth for centroid v
}
