const double PI = acosl(-1);
const int LOG = 20, MAXN = 1 << LOG;

//using comp = complex<double>;
struct comp {
  double x, y; // long double is ~3x slower
  comp() : x(0), y(0) {}
  comp(double x, double y) : x(x), y(y) {}
  comp(int x) : x(x), y(0) {}
  comp operator+(const comp &o) const { return {x + o.x, y + o.y}; }
  comp operator-(const comp &o) const { return {x - o.x, y - o.y}; }
  comp operator*(const comp &o) const { return {x * o.x - y * o.y, x * o.y + y * o.x}; }
  comp operator/(const int k) const { return {x / k, y / k}; }
  comp conj() const { return {x, -y}; }
};

comp OMEGA[MAXN + 10];
int tail[MAXN + 10];
bool fftinit = false;

int gettail(int x, int lg) { return tail[x] >> (LOG - lg); }

// OMEGA[k + j] = $e^{i \pi j / k}$ (j < k): level k in a row
void precalc() {
  for (int k = 1; k < MAXN; k *= 2) {
    for (int j = 0; j < k; ++j) {
      double x = PI * j / k;
      OMEGA[k + j] = {cos(x), sin(x)};
    }
  }
  tail[0] = 0;
  for (int i = 1; i < MAXN; ++i)
    tail[i] = (tail[i/2]/2) | ((i & 1) << (LOG - 1));
}

void fft(vector<comp> &A, int lg) {
  if (!fftinit) precalc(), fftinit = 1;
  int n = A.size();
  for (int i = 0; i < n; ++i)
    if (int j = gettail(i, lg); i < j)
      swap(A[i], A[j]);
  for (int k = 1; k < n; k *= 2)
    for (int i = 0; i < n; i += 2 * k)
      for (int j = 0; j < k; ++j) {
        auto v = A[i + j];
        auto u = A[i + j + k] * OMEGA[k + j];
        A[i + j] = v + u;
        A[i + j + k] = v - u;
      }
}

// optional: x1.7 vs 2 fft; bad precision if |A| >> |B|
void fft2(vector<comp> &A, vector<comp> &B, int lg) {
  int n = A.size();
  vector<comp> C(n);
  for (int i = 0; i < n; ++i) {
    C[i].x = A[i].x;
    C[i].y = B[i].x;
  }
  fft(C, lg);
  for (int i = 0; i < n; ++i) {
    int j = -i & (n - 1);
    A[i] = (C[i] + C[j].conj()) / 2;
    B[i] = (C[i] - C[j].conj()) / 2 * comp(0, -1);
  }
}

void invfft(vector<comp> &A, int lg) {
  int n = 1 << lg;
  fft(A, lg);
  for (auto &el : A) el = el / n;
  reverse(A.begin() + 1, A.end());
}

vector<int> mul(vector<int> &a, vector<int> &b) {
  if (a.empty() || b.empty()) return {};
  int lg = 32-__builtin_clz(max<int>(1,a.size()+b.size()-2));
  int n = 1 << lg;
  vector<comp> A(n, 0), B(n, 0);
  for (int i = 0; i < a.size(); ++i)
    A[i] = a[i];
  for (int i = 0; i < b.size(); ++i)
    B[i] = b[i];
  fft(A, lg), fft(B, lg); // fft2(A, B, lg);
  for (int i = 0; i < n; ++i)
    A[i] = A[i] * B[i];
  invfft(A, lg);
  vector<int> c(n);
  for (int i = 0; i < n; ++i)
    c[i] = round(A[i].x);
  while (!c.empty() && c.back() == 0)
    c.pop_back();
  return c;
}
