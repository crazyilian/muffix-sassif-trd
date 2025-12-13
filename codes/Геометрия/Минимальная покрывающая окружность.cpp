circle MinDisk2(vector<vctr> &p, vctr A, vctr B, int sz) {
  circle w(A, B);
  for (int i = 0; i < sz; ++i) {
    if (w.isin(p[i])) continue;
    w = circle(A, B, p[i]);
  }
  return w;
}
circle MinDisk1(vector<vctr> &p, vctr A, int sz) {
  shuffle(p.begin(), p.begin() + sz, rnd);
  circle w(A, p[0]);
  for (int i = 1; i < sz; ++i) {
    if (w.isin(p[i])) continue;
    w = MinDisk2(p, A, p[i], i);
  }
  return w;
}
circle MinDisk(vector<vctr> &p) {
  int sz = p.size();
  if (sz == 1) return circle(p[0], 0);
  shuffle(p.begin(), p.end(), rnd);
  circle w(p[0], p[1]);
  for (int i = 2; i < sz; ++i) {
    if (w.isin(p[i])) continue;
    w = MinDisk1(p, p[i], i);
  }
  return w;
}

