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

poly mul(poly &P, poly &Q) {
  poly R(P.n + Q.n);
  for (int i = 0; i <= P.n; i++) {
    for (int j = 0; j <= Q.n; j++) {
      R.a[i + j] = (R.a[i + j] + P.a[i] * Q.a[j]) % MOD;
    }
  }
  return R;
}

poly multiply_many(vector<poly> a) {
  if (a.empty()) return poly((vector<ll>){1ll});
  if (a.size() == 1) return a[0];
  vector<poly> b;
  int n = a.size();
  for (int i = n / 2; i < n; i++) {
    b.push_back(a[i]);
  }
  a.resize(n / 2);
  poly P = multiply_many(a), Q = multiply_many(b);
  return mul(P, Q);
}

poly divide(poly &res, int c) {
  poly ans(res.n - 1);
  ll val = 0;
  for (int i = res.n; i >= 1; i--) {
    val = (val * c + res.a[i]) % MOD;
    ans.a[i - 1] = val;
  }
  return ans;
}

poly interpolate(int deg, vector<int> x, vector<int> y) {
  assert(x.size() >= deg + 1 && y.size() >= deg + 1);
  x.resize(deg + 1), y.resize(deg + 1);
  vector<poly> fm;
  for (int j = 0; j <= deg; j++) {
    fm.push_back(poly({(MOD - x[j]) % MOD, 1}));
  }
  poly res = multiply_many(fm);
  poly ans(deg);
  for (int i = 0; i <= deg; i++) {
    ll denom = 1;
    for (int j = 0; j <= deg; j++) {
      if (j != i) {
        denom = denom * ((x[i] - x[j] + MOD) % MOD) % MOD;
      }
    }
    poly res_divided = divide(res, x[i]);
    denom = inv(denom);
    denom = denom * y[i] % MOD;
    for (int j = 0; j <= deg; j++) {
      ll el = res_divided.a[j];
      el = (el * denom) % MOD;
      ans.a[j] = (ans.a[j] + el) % MOD;
    }
  }
  return ans;
}
