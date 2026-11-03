// p convex (CCW or CW), no 3 collinear, a outside.
// {right, left} tangents looking from a to p
pair<int, int> tangents_from_point(vctr &a, vector<vctr> &p) {
  int n = p.size();
  int logn = 31 - __builtin_clz(n);
  auto findWithSign = [&](int sgn) {
    int i = 0;
    for (int k = logn; k >= 0; --k) {
      int i1 = (i - (1 << k) + n) % n;
      int i2 = (i + (1 << k)) % n;
      if (sign((p[i1] - a) * (p[i] - a)) == sgn) i = i1;
      if (sign((p[i2] - a) * (p[i] - a)) == sgn) i = i2;
    }
    return i;
  };
  return {findWithSign(1), findWithSign(-1)};
}

// p convex, no 3 collinear. Point with max (sgn=1) or
// min (sgn=-1) signed distance to line
int tangent_parallel_line(const vector<vctr> &p, line l, int sgn) {
  l *= sgn;
  int n = p.size();
  int i = 0;
  int logn = 31 - __builtin_clz(n);
  for (int k = logn; k >= 0; --k) {
    int i1 = (i - (1 << k) + n) % n;
    int i2 = (i + (1 << k)) % n;
    if (l.get(p[i1]) > l.get(p[i])) i = i1;
    if (l.get(p[i2]) > l.get(p[i])) i = i2;
  }
  return i;
}
