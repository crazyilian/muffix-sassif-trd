// f(x) = (a*x+b) mod m in [0,m); ll = __int128.
// S = {0} U {x > 0 : f(x) < min_{0 <= j < x} f(j)}.
// {X,DX}: S = {0} U {X[i] + t*DX[i] : 0 <= i < DX.size(),
//   1 <= t <= (X[i+1]-X[i])/DX[i]}; X[0] = 0; O(log m).
pair<vector<ll>, vector<ll>> min_of_linear_segments(ll a, ll b, ll m) {
  a = (a % m + m) % m, b = (b % m + m) % m;
  ll g = __gcd(a, m);
  ll A = a / g, M = m / g, y = b / g;
  ll q = 1, s = 1, dl = M - A, dr = A, x = 0;
  vector<ll> X = {0}, DX;
  while (y) {
    ll k = dr / dl;
    dr %= dl;
    if (!dr) --k, dr = dl;
    s += k * q;
    while (true) {
      k = max<ll>(0, (dl - y + dr - 1) / dr);
      if (dl - k * dr <= 0) break;
      dl -= k * dr;
      q += k * s;
      k = y / dl;
      y -= k * dl, x += q * k;
      X.pb(x), DX.pb(q);
    }
    k = dl / dr;
    dl -= k * dr;
    q += k * s;
  }
  return {X, DX};
}
pair<vector<ll>, vector<ll>> max_of_linear_segments(ll a, ll b, ll m) {
  return min_of_linear_segments(-a, m - 1 - b, m);
}
// min {x >= 0 : l <= f(x) <= r}; -1, если множество пусто.
// 0 <= l <= r < m; O(log m).
ll min_rem(ll a, ll b, ll m, ll l, ll r) {
  if (l > r) return -1;
  ll len = r - l + 1;
  b = ((b - l) % m + m) % m;
  if (b < len) return 0;
  auto [X, DX] = min_of_linear_segments(a, b, m);
  for (ll i = 0; i < DX.size(); ++i) {
    ll y2 = ((a * X[i + 1] + b) % m + m) % m;
    if (y2 >= len) continue;
    ll y1 = ((a * X[i] + b) % m + m) % m;
    ll d = (y1 - y2) / ((X[i + 1] - X[i]) / DX[i]);
    return X[i] + ((y1 - len) / d + 1) * DX[i];
  }
  return -1;
}
// {x,y}: y = min_{0 <= i < n} f(i), x = min i: f(i) = y.
// n > 0; O(log m).
pair<ll, ll> min_mod(ll n, ll a, ll b, ll m) {
  a = (a % m + m) % m, b = (b % m + m) % m;
  auto [X, DX] = min_of_linear_segments(a, b, m);
  ll x = 0;
  for (ll i = 0; i < DX.size() && X[i] < n; ++i)
    x = X[i] + (min(X[i + 1], n - 1) - X[i]) / DX[i] * DX[i];
  return {x, (a * x + b) % m};
}
// {x,y}: y = max_{0 <= i < n} f(i), x = min i: f(i) = y.
// n > 0; O(log m).
pair<ll, ll> max_mod(ll n, ll a, ll b, ll m) {
  auto [x, y] = min_mod(n, -a, m - 1 - b, m);
  return {x, m - 1 - y};
}
// {x,y}: y = min_{L <= i < R} f(i), x = min i: f(i) = y.
// L < R; O(log m).
pair<ll, ll> min_of_linear(ll L, ll R, ll a, ll b, ll m) {
  auto [x, y] = min_mod(min(R - L, m), a, a * L + b, m);
  return {L + x, y};
}
// sum_{0 <= x < n} floor((a*x+b)/m); O(log m).
ll floor_sum(ll n, ll a, ll b, ll m) {
  ll ans = 0;
  while (n) {
    ll q = a / m - (a % m < 0);
    a -= q * m;
    ans += n * (n - 1) / 2 * q;
    q = b / m - (b % m < 0);
    b -= q * m;
    ans += n * q;
    ll y = a * n + b;
    if (y < m) break;
    n = y / m, b = y % m;
    swap(a, m);
  }
  return ans;
}
// sum_{L <= x < R} floor((a*x+b)/m); O(log m).
ll floor_sum_of_linear(ll L, ll R, ll a, ll b, ll m) {
  return floor_sum(R - L, a, a * L + b, m);
}
// |{x : 0 <= x < n, l <= f(x) <= r}|.
// 0 <= l <= r < m; l > r -> 0; O(log m).
ll count_mod(ll n, ll a, ll b, ll m, ll l, ll r) {
  if (l > r) return 0;
  a = (a % m + m) % m, b = (b % m + m) % m;
  return floor_sum(n, a, b - l, m) -
         floor_sum(n, a, b - r - 1, m);
}
// sum_{0 <= x < n} f(x); O(log m).
ll sum_mod(ll n, ll a, ll b, ll m) {
  a = (a % m + m) % m, b = (b % m + m) % m;
  return n * (n - 1) / 2 * a + n * b -
         m * floor_sum(n, a, b, m);
}
