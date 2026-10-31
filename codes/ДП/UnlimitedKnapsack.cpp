void unlimited_knapsack(int n, int T, vector<int> &v) {
  // O(n^2 log n + T)
  // v[1..n], v[i] --- best value of a single item with weight=i (-inf for non-existent)
  vector<int> items;
  for (int i = 1; i <= n; i++)
    if (v[i] > -inf) items.pb(i);
  sort(all(items), [&](int i, int j) {
    return v[i] * j > v[j] * i;
  });
  v.resize(T + 1, -inf);
  v[0] = 0;
  for (int i = 2; i <= T; i++) {
    int tick = 0;
    for (auto j: items) {
      if (i > j) {
        v[i] = max(v[i], v[j] + v[i - j]);
      }
      if (tick * i > 3 * n * n) break; // apparently 2 works as well, but proved bound is 3
      tick++;
    }
  }
  // v[i] --- best total value of items with total weight=i
  // weight i is unreachable if `v[i] < -inf/2` (not `== -inf`)
}
