// need_all: also points on edges
vector<vctr> convex_hull(vector<vctr> p, bool need_all = 0) {
  sort(all(p), [](const vctr &a, const vctr &b) {
    return tie(a.y, a.x) < tie(b.y, b.x);
  });
  p.erase(unique(all(p)), end(p)); // must have
  int n = p.size(), k = 0;
  if (n <= 2) return p;
  auto bad = [&](vctr a, vctr b, vctr c) { // pop b?
    return sign((b - a) * (c - b)) < !need_all;
  };
  vector<vctr> ch(2 * n);
  for (int i = 0; i < n; ch[k++] = p[i++])
    while (k >= 2 && bad(ch[k-2], ch[k-1], p[i])) --k;
  for (int i = n - 2, t = k + 1; i >= 0; ch[k++] = p[i--])
    while (k >= t && bad(ch[k-2], ch[k-1], p[i])) --k;
  ch.resize(k - 1);
// If hull is seg and need_all: p[0] p[1] .. p[n-1] .. p[1].
// If need only one entry in this case: ch.resize(min(k-1, n));
  return ch;
}
