// convex CCW, no 3 collinear, any start, size >= 3
bool is_point_in_convex_poly(vctr a, const vector<vctr> &p,
                             bool strict = 0) {
  int n = p.size(), l=1, r=n-1;
  auto s = [&](int i, int j) {
    return sign((p[j] - p[i]) * (a - p[i]));
  };
  if (s(0, 1) < strict || s(0, n-1) > -strict) return false;
  while (r-l>1) {
    int m = (l+r)/2;
    (s(0, m) >= 0 ? l : r) = m;
  }
  return s(l, l+1) >= strict;
}

// p: any simple polygon, any orientation. O(n)
bool is_point_in_any_poly(vctr a, const vector<vctr> &p,
                          bool strict = 0) {
  int n = p.size(), cnt = 0;
  for (int i = 0, j = n - 1; i < n; j = i++) {
    vctr u = p[j] - a, v = p[i] - a;
    if (!sign(u * v) && sign(u % v) <= 0) return !strict;
    cnt ^= ((0 < u.y) - (0 < v.y)) * sign(u * v) > 0;
  }
  return cnt;
}
