pair<int, int> tangents_from_point(vector<vctr> &p, vctr &a) {
  int n = p.size();
  int logn = 31 - __builtin_clz(n);
  auto findWithSign = [&](int sgn) {
    int i = 0;
    for (int k = logn; k >= 0; --k) {
      int i1 = (i - (1 << k) + n) % n;
      int i2 = (i + (1 << k)) % n;
      if (sign((p[i1] - a) * (p[i] - a)) == sgn)
        i = i1;
      if (sign((p[i2] - a) * (p[i] - a)) == sgn)
        i = i2;
    }
    return i;
  };
  return {findWithSign(1), findWithSign(-1)};
}

