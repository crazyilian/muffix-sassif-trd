// mod: a[i][j] in [0, mod), mod^2 <= 2^63 (mod < 3e9).
//   % не на каждом шаге, а когда элемент дорос до 2^63.
using T = ull; // dbl: =dbl
T inv(T x) { return binpow(x, mod-2); } // dbl: return 1/x
T md(T x) { return x % mod; } // dbl: return x
T neg(T x) { return md(mod - x); } // dbl: return -x
char sign(T x) { return (x>EPS)-(x<-EPS);} // mod: EPS=0
ull abs(ull x) { return x; } // ._.

vector<vector<T>> gauss(vector<vector<T>> a) {
  int n = a.size(), m = a[0].size();
  // T det = 1;
  for (int col = 0, row = 0; col < m && row < n; ++col) {
    int sel = row; // max |a| is for dbl precision
    for (int i = row; i < n; ++i) {
      a[i][col] = md(a[i][col]);
      if (abs(a[i][col]) > abs(a[sel][col]))
        sel = i;
    }
    if (!sign(a[sel][col])) continue;
    swap(a[sel], a[row]);
    // if (sel != row) det = neg(det);
    for (auto &x : a[row]) x = md(x);
    T iv = inv(a[row][col]);
    ull acc = 0; // dbl: remove it
    for (int i = 0; i < n; ++i) { // i=row+1: ступенчатый вид, x1.5 speed. Хватает для sle, rank, det, проверки "вектор в span строк"
      T val = neg(md(md(a[i][col]) * iv));
      if (i == row || !sign(val)) continue;
      for (int j = col; j < m; ++j) {
        a[i][j] += val * a[row][j];
        acc |= a[i][j]; // dbl: remove it
      }
    }
    ++row;
    if (acc >> 63) // dbl: remove it
      for(auto &r:a) for(auto &x:r) x=md(x);
  }
  for(auto &r:a) for(auto &x:r) x=md(x);
  // for (int i = 0; i < n; ++i) det = md(det * a[i][i]);
  return a;
}

pair<int,vector<T>> sle(vector<vector<T>> a, vector<T> b) {
  int n = a.size(), m = a[0].size();
  assert(n == b.size());
  for (int i = 0; i < n; ++i) a[i].pb(b[i]);
  a = gauss(a);
  vector<T> x(m, 0);
  for (int i = n - 1; i >= 0; --i) {
    int l = 0;
    while (l < m && !sign(a[i][l])) ++l;
    if (l == m && sign(a[i][m]))
      return {-1, {}};
    if (l == m) continue;
    T val = a[i][m];
    for (int j = m - 1; j > l; --j)
      val = md(val + neg(a[i][j]) * x[j]);
    x[l] = md(val * inv(a[i][l]));
  }
  return {1, x};
}

vector<bitset<N>> gauss_bit(vector<bitset<N>> a, int m) {
  int n = a.size();
  for (int col = 0, row = 0; col < m && row < n; ++col) {
    for (int i = row; i < n; ++i)
      if (a[i][col]) {
        swap(a[i], a[row]);
        break;
      }
    if (!a[row][col]) continue;
    for (int i = 0; i < n; ++i) // i=row+1: ступенчатый вид, x2.5 speed
      if (i != row && a[i][col]) a[i] ^= a[row];
    ++row;
  }
  return a;
}
