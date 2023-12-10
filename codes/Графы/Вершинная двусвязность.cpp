struct edge {
  int u, ind;

  bool operator<(const edge &other) const {
    return u < other.u;
  }
};

vector<int> stack_;

void paint(int v, int pr = -1) {
  used[v] = pr;
  up[v] = tin[v] = ++timer;
  for (auto e: g[v]) {
    if (e.u == pr) {
      continue;
    }
    if (!used[e.u]) {
      stack_.push_back(e.ind);
      paint(e.u, v);
      if (up[e.u] >= tin[v]) {
        ++mx_col;
        while (true) {
          int cur_edge = stack_.back();
          col[cur_edge] = mx_col;
          stack_.pop_back();
          if (cur_edge == e.ind) {
            break;
          }
        }
      }
      up[v] = min(up[v], up[e.u]);
    } else if (tin[e.u] < tin[v]) {
      stack_.push_back(e.ind);
      up[v] = min(up[v], tin[e.u]);
    } else if (up[v] > tin[e.u]) {
      up[v] = up[e.u];
    }
  }
}

signed main() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    g[u].push_back({v, i});
    g[v].push_back({u, i});
  }
  for (int v = 1; v <= n; ++v) {
    sort(all(g[v]));
  }
  for (int v = 1; v <= n; ++v) {
    if (!used[v]) {
      paint(v);
    }
  }
  for (int v = 1; v <= n; ++v) {
    int len = g[v].size();
    for (int i = 1; i < len; ++i) {
      if (col[g[v][i].ind] == 0) {
        col[g[v][i].ind] = col[g[v][i - 1].ind];
      }
    }
  }
}
