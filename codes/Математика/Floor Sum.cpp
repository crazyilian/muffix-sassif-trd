int floor_sum(int n, int d, int m, int a) {
  // sum_{i=0}^{n-1} floor((a + i*m)/d), only non-negative integers!
  int ans = 0;
  ans += (n * (n - 1) / 2) * (m / d);
  m %= d;
  ans += n * (a / d);
  a %= d;
  int l = m * n + a;
  if (l >= d)
    ans += floor_sum(l / d, m, d, l % d);
  return ans;
}
