// A, B convex (CCW or CW, independently), no 3 collinear,
// no common points.                      O(log n log m).
// Returns (looking from A[i] to B[j]):
// {left, left}, {left, right}, {right, left}, {right, right}
vector<pair<int, int>> tangents_polys(vector<vctr> &A,
                                      vector<vctr> &B) {
  int n = A.size(), logn = 31 - __builtin_clz(n);
  vector<pair<int, int>> res;
  for (int sa : {1, -1}) for (int sb : {1, -1}) {
    auto t = [&](int i) {
      auto [r, l] = tangents_from_point(A[i], B);
      return sb > 0 ? r : l;
    };
    auto d = [&](int i) { return B[t(i)] - A[i]; };
    int i = 0;
    for (int k = logn; k >= 0; --k) {
      int i1 = (i - (1 << k) + n) % n;
      int i2 = (i + (1 << k)) % n;
      if (sign(d(i) * d(i1)) == sa) i = i1;
      if (sign(d(i) * d(i2)) == sa) i = i2;
    }
    res.pb({i, t(i)});
  }
  return res;
}
