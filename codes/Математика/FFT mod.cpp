const int MOD = 998244353; // $7 \cdot 17 \cdot 2^{23} + 1$
const int GEN = 3;
//const int MOD = 7340033; // $7 \cdot 2^{20} + 1$
//const int GEN = 5;
//const int MOD = 469762049; // $7 \cdot  2^{26} + 1$
//const int GEN = 30;

const int LOG = 20;
const int MAXN = 1 << LOG;
int tail[MAXN + 1];
int OMEGA[MAXN + 1];

int binpow(int x, int p) {
  int res = 1;
  while (p > 0) {
    if (p & 1)
      res = res * 1ll * x % MOD;
    x = x * 1ll * x % MOD;
    p >>= 1;
  }
  return res;
}

int omega(int n, int k) {
  return OMEGA[MAXN / n * k];
}

int gettail(int x, int lg) {
  return tail[x] >> (LOG - lg);
}

void calcomega() {
  long long one = binpow(GEN, (MOD - 1) / MAXN);
  OMEGA[0] = 1;
  for (int i = 1; i < MAXN; ++i) {
    OMEGA[i] = OMEGA[i - 1] * one % MOD;
  }
}

void calctail() {
  int n = MAXN;
  for (int x = 0; x < n; ++x) {
    int res = 0;
    for (int i = 0; i < LOG; ++i) {
      res += ((x >> i) & 1) << (LOG - i - 1);
    }
    tail[x] = res;
  }
}

// Without precalc, tail[], OMEGA[]
//
//long long omega(int n, int k) {
//    return binpow(GEN, (MOD - 1) / n * k);
//}
//
//int gettail(int x, int lg) {
//    int res = 0;
//    for (int i = 0; i < lg; ++i)
//        res += ((x >> i) & 1) << (lg - i - 1);
//    return res;
//}

void fft(vector<int> &A, int lg) {
  int n = 1 << lg;
  for (int i = 0; i < n; ++i) {
    int j = gettail(i, lg);
    if (i < j)
      swap(A[i], A[j]);
  }
  for (int len = 2; len <= n; len *= 2) {
    for (int i = 0; i < n; i += len) {
      for (int j = 0; j < len / 2; ++j) {
        auto v = A[i + j];
        auto u = A[i + j + len / 2] * 1ll * omega(len, j) % MOD;
        A[i + j] = (v + u) % MOD;
        A[i + j + len / 2] = (v - u + MOD) % MOD;
      }
    }
  }
}

int inverse(int x) {
  return binpow(x, MOD - 2);
}

void invfft(vector<int> &A, int lg) {
  int n = 1 << lg;
  fft(A, lg);
  for (auto &el : A)
    el = el * 1ll * inverse(n % MOD) % MOD;
  reverse(A.begin() + 1, A.end());
}

vector<int> mul(vector<int> A, vector<int> B) {
  int lg = 32 - __builtin_clz(A.size() + B.size() - 1);
  int n = 1 << lg;
  A.resize(n, 0);
  B.resize(n, 0);
  fft(A, lg);
  fft(B, lg);
  for (int i = 0; i < n; ++i)
    A[i] = A[i] * 1ll * B[i] % MOD;
  invfft(A, lg);
  return A;
}

signed main() {
  calctail(); // НЕ ЗАБЫТЬ
  calcomega(); // НЕ ЗАБЫТЬ
  int n, m;
  cin >> n >> m;
  vector<int> A(n), B(m);
  for (int &el : A)
    cin >> el;
  for (int &el : B)
    cin >> el;
  auto C = mul(A, B);
  for (auto el : C)
    cout << el << ' ';
}

