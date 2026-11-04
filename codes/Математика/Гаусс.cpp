// for modular: dbl -> ll, EPS=0
char sign(dbl x) { return (x>EPS) - (x<-EPS); }

// for double: ll -> dbl, no %mod, inv(x) = 1/x
vector<vector<ll>> gauss(vector<vector<ll>> &a) {
  int n = a.size();
  int m = a[0].size();
//  ll det = 1;
  for (int col = 0, row = 0; col < m && row < n; ++col) {
    int sel = row; // max |a| is for dbl precision
    for (int i = row; i < n; ++i) {
      if (abs(a[i][col]) > abs(a[sel][col])) sel = i;
    }
    if (!sign(a[sel][col])) continue;
    swap(a[sel], a[row]);
//    if (sel != row) det *= -1;
    ll iv = inv(a[row][col]);
    for (int i = 0; i < n; ++i) {
      if (i != row && sign(a[i][col])) {
        ll val = a[i][col] * iv % mod;
        for (int j = col; j < m; ++j) {
          a[i][j] -= val * a[row][j];
          a[i][j] %= mod;
        }
      }
    }
    ++row;
  }
//  for (int i = 0; i < n; ++i) det = (det * a[i][i]) % mod;
//  det = (det % mod + mod) % mod;
// result in (-mod, mod)
  return a;
}

pair<int,vector<ll>> sle(vector<vector<ll>> a, vector<ll> b) {
  int n = a.size();
  int m = a[0].size();
  assert(n == b.size());
  for (int i = 0; i < n; ++i) {
    a[i].push_back(b[i]);
  }
  a = gauss(a);
  vector<ll> x(m, 0);
  for (int i = n - 1; i >= 0; --i) {
    int leftmost = m;
    for (int j = 0; j < m; ++j) {
      if (sign(a[i][j])) {
        leftmost = j;
        break;
      }
    }
    if (leftmost == m && sign(a[i].back())) return {-1, {}};
    if (leftmost == m) continue;
    ll val = a[i].back();
    for (int j = m - 1; j > leftmost; --j) {
      val -= a[i][j] * x[j];
      val %= mod;
    }
    x[leftmost] = (val * inv(a[i][leftmost]) % mod + mod) % mod;
  }
  return {1, x};
}

vector<bitset<N>> gauss_bit(vector<bitset<N>> a, int m) {
  int n = a.size();
  for (int col = 0, row = 0; col < m && row < n; ++col) {
    for (int i = row; i < n; ++i) {
      if (a[i][col]) {
        swap(a[i], a[row]);
        break;
      }
    }
    if (!a[row][col]) continue;
    for (int i = 0; i < n; ++i)
      if (i != row && a[i][col]) a[i] ^= a[row];
    ++row;
  }
  return a;
}
