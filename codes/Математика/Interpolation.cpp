// for double: ll -> dbl, no %MOD, inv(x) = 1/x;
// for precision pick $x_k = c \cdot \cos \frac{k \pi}{n-1}$.
// x distinct, $P(x_i) = y_i$, $P(X) = \sum \text{res}_i X^i$
// $O(n^2)$. Mod: x, y, $\text{res} \in (-\text{MOD}, \text{MOD})$
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

// $\deg P < n$ задан значениями $y_i = P(i)$, $0 \le i < n$
// Возвращает $P(X)$ за $O(n)$. $0 < n \le$ MOD, $X \in (-\text{MOD}, \text{MOD})$
// dbl: нужно $(n-1)!$ в типе: $n \le 171$ (long double: 1755)
// Если $y_i = P(x_0 + ih)$: передать $X \to (X - x_0) / h$
ll lagrange(const vector<ll> &y, ll X) {
  int n = y.size();
  // fi[i] = $1 / i!$. Maybe precomputed?
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
