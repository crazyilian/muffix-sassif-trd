struct poly {
  int n = 0;
  vector<ll> a = {0};
  poly() = default;
  poly(vector<ll> a) : a(a), n((int)a.size()-1) {}
  poly(int n) : n(n), a(n+1, 0) {}

  ll evaluate(int x) {
    ll val = 0, y = 1;
    for (int i = 0; i <= n; i++) {
      val = (val + a[i] * y) % MOD;
      y = (y * x) % MOD;
    }
    return val;
  }
};

poly interpolate(int deg, vector<int> x, vector<int> y) {
  assert(x.size() >= deg + 1 && y.size() >= deg + 1);
  int n = deg + 1;
  vector<ll> xs(n), c(n), cur(n);
  for (int i = 0; i < n; i++) {
    xs[i] = (x[i] % MOD + MOD) % MOD;
    c[i] = (y[i] % MOD + MOD) % MOD;
  }
  for (int k = 0; k + 1 < n; k++) {
    for (int i = k + 1; i < n; i++) {
      c[i] = (c[i] - c[k] + MOD) * inv((xs[i] - xs[k] + MOD) % MOD)ы % MOD;
    }
  }
  poly res(deg);
  cur[0] = 1;
  for (int k = 0; k < n; k++) {
    for (int i = 0; i <= k; i++) {
      res.a[i] = (res.a[i] + c[k] * cur[i]) % MOD;
    }
    if (k + 1 == n) break;
    for (int i = k + 1; i >= 0; i--) {
      cur[i] = ((i ? cur[i - 1] : 0) + (i <= k ? MOD - cur[i] * xs[k] % MOD : 0)) % MOD;
    }
  }
  return res;
}
