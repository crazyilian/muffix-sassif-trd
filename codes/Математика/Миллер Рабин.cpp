// assuming '#define int long long' is ON (replace 'int' with 'long long' if not)
// works for all n < 2^64
const int MAGIC[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

int bpow(__int128 a, int x, int mod) {
  a %= mod;
  __int128 ans = 1;
  while (x) {
    if (x % 2) {
      ans *= a;
      ans %= mod;
    }
    a *= a;
    a %= mod;
    x /= 2;
  }
  return (int) ans;
}

bool is_prime(int n) {
  if (n == 1) return false;
  if (n <= 3) return true;
  if (n % 2 == 0 || n % 3 == 0) return false;
  int s = __builtin_ctzll(n - 1), d = n >> s;
  for (auto a : MAGIC) {
    if (a % n == 0) {
      continue;
    }
    int x = bpow(a, d, n);
    for (int _ = 0; _ < s; _++) {
      int y = bpow(x, 2, n);
      if (y == 1 && x != 1 && x != n - 1) {
        return false;
      }
      x = y;
    }
    if (x != 1) {
      return false;
    }
  }
  return true;
}
