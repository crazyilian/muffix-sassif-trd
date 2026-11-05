int par[MAXN], sizes[MAXN], pathup[MAXN];
int tin[MAXN], tout[MAXN], timer;

int dfs1_hld(int v, int p) {
  par[v] = p;
  int sz = 1;
  for (int i = 0; i < g[v].size(); ++i) {
    int u = g[v][i];
    if (u == p) {
      swap(g[v][i--], g[v].back());
      g[v].pop_back();
    } else sz += dfs1_hld(u, v);
  }
  return sizes[v] = sz;
}

void dfs2_hld(int v, int up) {
  tin[v] = timer++, pathup[v] = up;
  for (int i = 1; i < g[v].size(); ++i)
    if (sizes[g[v][i]] > sizes[g[v][0]])
      swap(g[v][i], g[v][0]);
  for (int u : g[v])
    dfs2_hld(u, u == g[v][0] ? up : u);
  tout[v] = timer;
}

bool is_ancestor(int v, int p) {
  return tin[p] <= tin[v] && tout[v] <= tout[p];
}

// get_hld полностью аналогичный
void update_hld(int v, int u, int ARG) {
  for (int _ = 0; _ < 2; ++_) {
    while (!is_ancestor(u, pathup[v])) {
      int vup = pathup[v];
      ST.update(0, 0, timer, tin[vup], tin[v] + 1, ARG);
      v = par[vup];
    }
    swap(v, u);
  }
  if (tin[v] > tin[u]) swap(v, u);
  // v = lca
  ST.update(0, 0, timer, tin[v], tin[u] + 1, ARG);
}

signed main() {
  dfs1_hld(0, -1);
  dfs2_hld(0, 0);
  ST.build();
  // your code here
}
