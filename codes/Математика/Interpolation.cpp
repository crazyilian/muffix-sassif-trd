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
  for (int i = ssize(a)-1; i>= 0; --i) r = (r*x+a[i]) % MOD;
  return r;
}

// deg P < n задан значениями y[i]=P(i), i = 0..n-1
// Возвращает P(X) за O(n). 0 < n <= MOD, X in (-MOD, MOD)
// dbl: нужно (n-1)! в типе: n <= 171 (long double: 1755)
// Если y[i]=P(x0+i*h): передать X -> (X-x0)/h
ll lagrange(const vector<ll> &y, ll X) {
  int n = y.size();
  // fi[i] = 1 / i!. Maybe precomputed?
  vector<ll> suf(n + 1, 1), fi(n);
  ll f = 1, pre = 1, res = 0;
  for (int i = 1; i < n; ++i) f = f * i % MOD;
  fi[n - 1] = inv(f);
  for (int i = n - 1; i > 0; --i) fi[i - 1] = fi[i] * i % MOD;
  for (int i = n; i--; ) suf[i] = suf[i + 1] * (i - X) % MOD;
  for (int i = 0; i < n; ++i) {
    auto t = pre * suf[i + 1] % MOD * fi[i] % MOD;
    res = (res + y[i] * t % MOD * fi[n - 1 - i]) % MOD;
    pre = pre * (X - i) % MOD;
  }
  return res;
}
