// works for all n < 2^64
const ll MAGIC[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

bool is_prime(ll n) {
  if (n == 1) return false;
  if (n <= 3) return true;
  if (n % 2 == 0 || n % 3 == 0) return false;
  ll s = __builtin_ctzll(n - 1), d = n >> s; // $n-1 = 2^s \cdot d$
  for (auto a : MAGIC) {
    if (a % n == 0) {
      continue;
    }
    ll x = binpow(a, d, n); // a -> __int128 in binpow
    for (int _ = 0; _ < s; _++) {
      ll y = binpow(x, 2, n);  // x -> __int128 in binpow
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
