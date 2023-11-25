void sizes(int v, int p) {
  sz[v] = 1;
  for (auto u : g[v]) {
    if (u != p && !used[u]) {
      sizes(u, v);
      sz[v] += sz[u];
    }
  }
}

int centroid(int v, int p, int n) {
  for (int u : g[v]) {
    if (sz[u] > n / 2 && u != p && !used[u]) {
      return centroid(u, v, n);
    }
  }
  return v;
}

void dfs(int v, int p) {
  // code
  for (auto u : g[v]) {
    if (u != p && !used[u]) {
      dfs(u, v);
    }
  }
}

void solve(int v) {
  sizes(v, -1);
  // code (?)
  for (auto u : g[v]) {
    if (!used[u]) {
      // code (?)
      dfs(u, v);
      // сохраняем результаты dfs
    }
  }
  // code (сливаем результаты dfs)
  used[v] = 1;
  for (int u : g[v]) {
    if (!used[u]) {
      solve(centroid(u, v, sz[u]));
    }
  }
}

signed main() {
  sizes(0, -1);
  solve(centroid(0, -1, n));
}
