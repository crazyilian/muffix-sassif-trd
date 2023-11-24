long long mult(long long a, long long b, long long mod) {
  return (__int128)a * b % mod;
}

long long f(long long x, long long c, long long mod) {
  return (mult(x, x, mod) + c) % mod;
}

long long rho(long long n, long long x0=2, long long c=1) {
  long long x = x0;
  long long y = x0;
  long long g = 1;
  while (g == 1) {
    x = f(x, c, n);
    y = f(y, c, n);
    y = f(y, c, n);
    g = gcd(abs(x - y), n);
  }
  return g;
}

mt19937_64 rnd(time(nullptr));

void factor(int n, vector<int> &pr) {
  if (n == 4) {
    factor(2, pr);
    factor(2, pr);
    return;
  }
  if (n == 1) {
    return;
  }
  if (is_prime(n)) {
    pr.push_back(n);
    return;
  }
  int d = rho(n, abs((int) rnd()) % (n - 2) + 2, abs((int) rnd()) % 3 + 1);
  factor(n / d, pr);
  factor(d, pr);
}
