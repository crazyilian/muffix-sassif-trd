pair<ll, vector<int>> venger(vector<vector<ll>> a) {
// ищет минимальное по стоимости
// работает только при n <= m
// a - массив весов $(n+1) \times (m+1)$
// a[0][..] = a[..][0] = 0
// a[i][j] любые (>0, <0, =0)
// возвращает ans[i] = j если взяли ребро a[i][j]
  int n = ssize(a) - 1;
  int m = ssize(a[0]) - 1;
  vector<ll> u(n + 1), v(m + 1);
  vector<int> p(m + 1), way(m + 1);
  const ll INF = LLONG_MAX;
  for (int i = 1; i <= n; ++i) {
    p[0] = i;
    int y = 0;
    vector<ll> minv(m + 1, INF);
    vector<char> used(m + 1, false);
    do {
      used[y] = true;
      int x = p[y], z;
      ll delta = INF;
      for (int j = 1; j <= m; ++j) {
        if (!used[j]) {
          ll cur = a[x][j] - u[x] - v[j];
          if (cur < minv[j])
            minv[j] = cur, way[j] = y;
          if (minv[j] < delta)
            delta = minv[j], z = j;
        }
      }
      for (int j = 0; j <= m; ++j) {
        if (used[j])
          u[p[j]] += delta, v[j] -= delta;
        else
          minv[j] -= delta;
      }
      y = z;
    } while (p[y] != 0);
    do {
      int z = way[y];
      p[y] = p[z];
      y = z;
    } while (y);
  }
  ll cost = -v[0];
  vector<int> ans(n + 1);
  for (int j = 1; j <= m; ++j)
    ans[p[j]] = j;
  return {cost, ans};
}
