// for double: ll -> dbl, no % MOD, inv(x) = 1/x;
// for precision pick x[k] = c*cos(k/(n-1)*pi)
// x distinct, P(x[i]) = y[i], P(X) = sum res[i] X^i
// O(n^2). Mod: x, y, res in (-MOD, MOD)
vector<ll> interpolate(vector<ll> x, vector<ll> y) {
  int n = x.size();
  vector<ll> res(n), temp(n), d(n);
  for (int k = 0; k + 1 < n; ++k) {
    ll p = 1;
    for (int i = k + 1; i < n; ++i)
      d[i] = p, p = p * (x[i] - x[k]) % MOD;
    p = inv(p);
    for (int i = n - 1; i > k; --i) {
      y[i] = (y[i] - y[k]) * (d[i] * p % MOD) % MOD;
      p = p * (x[i] - x[k]) % MOD;
    }
  }
  ll last = 0; temp[0] = 1;
  for (int k = 0; k < n; ++k)
    for (int i = 0; i < min(n, k + 2); ++i) {
      res[i] = (res[i] + y[k] * temp[i]) % MOD;
      swap(last, temp[i]);
      temp[i] = (temp[i] - last * x[k]) % MOD;
    }
  return res;
}

ll eval(const vector<ll> &a, ll x) {
  ll r = 0;
  for (int i = a.size(); i>= 0; --i) r = (r*x+a[i]) % MOD;
  return r;
}
