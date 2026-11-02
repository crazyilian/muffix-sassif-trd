ull path_mul(ull a, ull b) {
  ull r = 0;
  for (; b; b >>= 1, a = (a << 1) ^ (a >> 63) * 27)
    r ^= a * (b & 1);
  return r;
}

// Возвращает {число рёбер, первая вершина после s}; {-1,-1}, если не найдено; O(2^k (n+m) ans)
pair<int, int> find_path_through_specified(int n, vector<pair<int, int>> edges, int s, int t, vector<int> need) {
  vector<int> bit(n);
  int k = 0;
  for (auto v : need) {
    if (v == s || v == t || bit[v]) continue;
    bit[v] = 1 << k++;
  }
  int masks = 1 << k;
  struct Edge { int v, u; ull w; };
  vector<Edge> es;
  vector<int> from, to;
  for (auto [v, u] : edges) {
    if ((v == s && u == t) || (v == t && u == s)) {
      if (k == 0) return {1, t};
      continue;
    }
    if (v == s || u == s) from.push_back(v ^ u ^ s);
    if (v == t || u == t) to.push_back(v ^ u ^ t);
    if (v != s && v != t && u != s && u != t) {
      ull w = rnd();
      es.push_back({v, u, w});
      es.push_back({u, v, w});
    }
  }
  int m = es.size();
  vector<vector<ull>> dp(masks, vector<ull>(n));
  vector<vector<ull>> dp_e(masks, vector<ull>(m));
  for (auto v : to) dp[bit[v]][v] = rnd();
  for (int len = 1; len < n; ++len) {
    if (s != t || len >= 2) {
      for (auto v : from) {
        if (dp[masks - 1][v]) return {len + 1, v};
      }
    }
    if (len + 1 == n) break;
    vector<vector<ull>> ndp(masks, vector<ull>(n));
    vector<vector<ull>> ndp_e(masks, vector<ull>(m));
    for (int mask = 0; mask < masks; ++mask) {
      for (int id = 0; id < m; ++id) {
        auto [v, u, w] = es[id];
        if (bit[u] && (mask & bit[u])) continue;
        int nmask = mask | bit[u];
        ull x = dp[mask][v] ^ dp_e[mask][id ^ 1];
        if (!x) continue;
        x = path_mul(x, w);
        ndp[nmask][u] ^= x;
        ndp_e[nmask][id] ^= x;
      }
    }
    swap(dp, ndp);
    swap(dp_e, ndp_e);
  }
  return {-1, -1};
}
