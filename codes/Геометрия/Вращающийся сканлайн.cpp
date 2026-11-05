// Прямая проходит через каждую пару точек, её направление $d$ вращается против часовой от $(1,0)$ до $(-1,0)$ (если full_rotation то до $(1,0)$). ord - точки по знаковому расстоянию до прямой, pos[ord[k]] = k. Точки различны, 3+ точки на одной прямой разрешены. $O(n^2 \log n)$.
void sweep_pairs(vector<vctr> p, bool full_rotation=false) {
  sort(all(p), [](const vctr &a, const vctr &b) {
    return tie(a.y, a.x) < tie(b.y, b.x);
  });
  int n = p.size();
  vector<ar(2)> ev; ev.reserve(n*(n-1)/2);
  for (int i = 0; i < n; ++i)
    for (int j = i+1; j < n; ++j) ev.pb({i,j});
  sort(all(ev), [&](ar(2) a, ar(2) b) {
    vctr u = p[a[1]] - p[a[0]];
    auto c = u * (p[b[1]] - p[b[0]]);
    if (sign(c)) return c > 0;
    c = u * (p[b[0]] - p[a[0]]);
    return sign(c) ? c > 0 : a < b;
  });
  vector<int> ord(n), pos(n);
  iota(all(ord), 0), iota(all(pos), 0);
  for (int t=0, rem=0, l, r; t <= full_rotation; ++t) {
    // прямые одного направления: если t==0, то сначала правые
    for (auto [i, j] : ev) {
      if (t) swap(i, j); // d in [pi, 2pi)
      vctr d = p[j] - p[i]; // pos[i]+1 == pos[j].
      auto on = [&](int k) { return !sign(d*(p[k]-p[i])); };
      if (!rem--) { // this if-block can be removed
        // first vctr pair of a new line
        l = pos[i], r = pos[j];
        while (l > 0 && on(ord[l-1])) --l;
        while (r < n-1 && on(ord[r+1])) ++r;
        rem = (r-l+1)*(r-l)/2-1;
        // ord[l..r] - points of the line in order of d.
        // unique line code here
      }
      // ord sorted by d*p[k] $\iff$ by signed dist to line: ord[0..l) - right of i->j, ord(r..n) - left.
      // Ties: right of i->j in order of $-d$, left in order of $d$ (t==1: vice versa).
      // unique vctr pair code here
      swap(ord[pos[i]], ord[pos[j]]);
      swap(pos[i], pos[j]);
      // !rem => line done, ord[l..r] reversed
    }
  }
}
