const int MAXN = 50500;
const int INF = (int) 1e15;
const int L = 20;
vector<int> g[MAXN];
int sz[MAXN];
int depth[MAXN];

vector<vector<int>> up(MAXN, vector<int>(L + 1));

void dfs(int v, int p) {
  up[v][0] = p;
  for (int i = 1; i <= L; i++) {
    up[v][i] = up[up[v][i - 1]][i - 1];
  }
  for (int u : g[v]) {
    if (u != p) {
      dfs(u, v);
    }
  }
}

int lca(int u, int v) {
  if (u == v) {
    return u;
  }
  int du = depth[u], dv = depth[v];
  if (du < dv) {
    swap(du, dv);
    swap(u, v);
  }
  for (int i = L; i >= 0; i--) {
    if (du - (int) pow(2, i) >= dv) {
      u = up[u][i];
      du -= (int) pow(2, i);
    }
  }
  if (u == v) {
    return u;
  }
  for (int i = L; i >= 0; i--) {
    if (up[u][i] != up[v][i]) {
      u = up[u][i];
      v = up[v][i];
    }
  }
  return up[u][0];
}

void dfs1(int v, int p) {
  sz[v] = 1;
  for (int u : g[v]) {
    if (u != p) {
      dfs1(u, v);
      sz[v] += sz[u];
    }
  }
}

int cnt = 0;
int nn[MAXN];
int pred[MAXN];
int rup[MAXN];

void dfs2(int v, int p, int root, int dep = 0) {
  depth[v] = dep;
  nn[v] = cnt++;
  pred[v] = p;
  rup[v] = root;
  int mx = 0;
  int vert = -1;
  for (int u : g[v]) {
    if (u != p) {
      if (mx < sz[u]) {
        mx = sz[u];
        vert = u;
      }
    }
  }
  if (vert != -1) {
    dfs2(vert, v, root, dep + 1);
  }
  for (int u : g[v]) {
    if (u != p && u != vert) {
      dfs2(u, v, u, dep + 1);
    }
  }
}

ST st({});
int n;

int mx_path_up(int u, int v) {
  if (depth[u] < depth[v]) {
    swap(u, v);
  }
  int res = -INF;
  while (true) {
    int root = rup[u];
    if (depth[root] <= depth[v]) {
      res = max(res, st.rmq(0, 0, n, nn[v], nn[u] + 1));
      break;
    }
    res = max(res, st.rmq(0, 0, n, nn[root], nn[u] + 1));
    u = pred[rup[u]];
  }
  return res;
}

int mx_path(int u, int v) {
  int vert = lca(u, v);
  return max(mx_path_up(u, vert), mx_path_up(v, vert));
}

void change(int u, int qd) {
  st.update(0, 0, n, nn[u], qd);
}

signed main() {
  cin >> n;
  vector<int> hs(n);
  for (auto &x : hs) {
    cin >> x;
  }
  for (int i = 0; i < n - 1; i++) {
    cin >> u1 >> v1;
    g[u1].push_back(v1);
    g[v1].push_back(u1);
  }
  dfs1(1, -1);
  dfs(1, 1);
  dfs2(1, -1, 1);
  vector<int> nhs(n);
  for (int i = 1; i <= n; i++) {
    nhs[nn[i]] = hs[i - 1];
  }
  st = *new ST(nhs);
  char op;
  int q;
  cin >> q;
  while (q--) {
    cin >> op >> v1 >> u1;
    if (op == '?') {
      cout << mx_path(u1, v1) << endl;
    } else {
      change(v1, u1);
    }
  }
}
