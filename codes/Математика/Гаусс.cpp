vector<vector<int>> gauss(vector<vector<int>> &a) {
  int n = a.size();
  int m = a[0].size();
//  int det = 1;
  for (int col = 0, row = 0; col < m && row < n; ++col) {
    for (int i = row; i < n; ++i) {
      if (a[i][col]) {
        swap(a[i], a[row]);
        if (i != row) {
//          det *= -1;
        }
        break;
      }
    }
    if (!a[row][col])
      continue;
    for (int i = 0; i < n; ++i) {
      if (i != row && a[i][col]) {
        int val = a[i][col] * inv(a[row][col]) % mod;
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

pair<int, vector<int>> sle(vector<vector<int>> a, vector<int> b) {
  int n = a.size();
  int m = a[0].size();
  assert(n == b.size());
  for (int i = 0; i < n; ++i) {
    a[i].push_back(b[i]);
  }
  a = gauss(a);
  vector<int> x(m, 0);
  for (int i = n - 1; i >= 0; --i) {
    int leftmost = m;
    for (int j = 0; j < m; ++j) {
      if (a[i][j] != 0) {
        leftmost = j;
        break;
      }
    }
    if (leftmost == m && a[i].back() != 0) return {-1, {}};
    if (leftmost == m) continue;
    int val = a[i].back();
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
    if (!a[row][col])
      continue;
    for (int i = 0; i < n; ++i)
      if (i != row && a[i][col])
        a[i] ^= a[row];
    ++row;
  }
  return a;
}
