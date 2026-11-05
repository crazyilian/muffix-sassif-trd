// $\max c^Tx: Ax \leq b, x \geq 0, A \in \mathbb{R}^{m \times n}$ ($x$ is output only)
// Returns -inf if infeasible, +inf if unbounded ($x$ is any feasible then).
// Phase 1 (finds a feasible $x$) is skipped automatically if $b\geq 0$, since then $x = 0$ is feasible. Faster.
// $O(nm)$ per pivot; usually $\approx n+m$ pivots, $2^n$ worst case.
// eps is absolute: fine for $|A|, |c| \leq 10^6$
// dbl = double is ~7x faster than long double
dbl simplex(vector<vector<dbl>> A, vector<dbl> b,
            vector<dbl> c, vector<dbl> &x) {
  const dbl eps = 1e-8, inf = 1 / .0;
  int m = b.size(), n = c.size();
  vector<int> B(m), N(n+1);
  iota(all(B), n), iota(all(N), 0), N[n] = -1, x.assign(n, 0);
  A.pb(c), b.pb(0);
  vector D(m+2, vector<dbl>(n+2));
  for (int i = 0; i <= m; ++i)
    copy(all(A[i]), D[i].begin()), D[i][n+1] = b[i];
  auto pivot = [&](int r, int s) {
    dbl *a = D[r].data(), t = 1 / exchange(a[s], 1);
    for (int j = 0; j <= n+1; ++j) a[j] *= t;
    for (int i = 0; i < m+2; ++i)
      if (dbl k = D[i][s]; i != r && abs(k) > eps) {
        D[i][s] = 0;
        for (int j = 0; j <= n+1; ++j) D[i][j] -= a[j] * k;
      }
    swap(B[r], N[s]);
  };
  auto run = [&](int x) {
    int deg = 0, r, s;
    auto p = [&](int j) {
      return pair(deg > n+m ? D[x][j] > eps : D[x][j], -N[j]);
    };
    auto q = [&](int i) {
      return pair(D[i][n+1] / D[i][s], B[i]);
    };
    while (1) {
      r = -1, s = 0;
      for (int j = 1; j <= n; ++j)
        if (p(j) > p(s)) s = j;
      if (D[x][s] <= eps) return 1;
      for (int i = 0; i < m; ++i)
        if (D[i][s] > eps && (r < 0 || q(i) < q(r))) r = i;
      if (r < 0) return 0;
      deg = D[r][n+1] < eps ? deg + 1 : 0;
      pivot(r, s);
    }
  };
  int r = min_element(all(b)) - b.begin();
  if (D[r][n+1] < -eps) { // can remove this block if $b\geq 0$
    for (auto &d : D) d[n] = -1;
    pivot(r, n), run(m+1);
    if (D[m+1][n+1] > eps) return -inf;
    for (int i = 0, s = 0; i < m; ++i)
      if (B[i] < 0) {
        for (int j = 1; j <= n; ++j)
          if (abs(D[i][j]) > abs(D[i][s])) s = j;
        pivot(i, s);
      }
    for (auto &d : D) d[find(all(N), -1) - N.begin()] = 0;
  }
  bool ok = run(m);
  for (int i = 0; i < m; ++i)
    if (B[i] < n) x[B[i]] = D[i][n+1];
  return ok ? -D[m][n+1] : inf;
}

// same, but x[j] < 0 is allowed if neg[j]:
// x[j] = y[j] - y[n] for them, all y >= 0
dbl simplex_neg(vector<vector<dbl>> A, vector<dbl> b,
    vector<dbl> c, vector<char> neg, vector<dbl> &x) {
  int n = c.size();
  A.pb(c);
  for (auto &r : A) {
    r.pb(0);
    for (int j = 0; j < n; ++j)
      if (neg[j]) r[n] -= r[j];
  }
  c = A.back(), A.pop_back();
  dbl res = simplex(A, b, c, x);
  for (int j = 0; j < n; ++j)
    if (neg[j]) x[j] -= x[n];
  x.pop_back();
  return res;
}
