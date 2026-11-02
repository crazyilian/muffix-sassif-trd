// convex CCW, no 3 collinear, any start, size >= 3
bool is_point_in_poly(vctr p, const vector<vctr> &a,
                      bool strict = 0) {
  int n = a.size(), l=1, r=n-1;
  auto s = [&](int i, int j) {
    return sign((a[j] - a[i]) * (p - a[i]));
  };
  if (s(0, 1) < strict || s(0, n-1) > -strict) return false;
  while (r-l>1) {
    int m = (l+r)/2;
    (s(0, m) >= 0 ? l : r) = m;
  }
  return s(l, l+1) >= strict;
}
