// p is prime
// -1 if no solution
// $x=\text{sqrt}(a, p) \implies x^2=a$ and $(-x)^2=a$
// $O(\log n)$ if $p \equiv 3 \mod 4$ else $O(\log^2 n)$
// should be changed if const p
ll sqrt(ll a, ll p) {
  a %= p;
  if (a < 0) a += p;
  if (a == 0) return 0;
  if (binpow(a, (p - 1) / 2, p) != 1)
    return -1; // no solution
  if (p % 4 == 3) return binpow(a, (p + 1) / 4, p);
  ll s = p - 1, n = 2;
  int r = 0, m;
  while (s % 2 == 0) ++r, s /= 2;
  while (binpow(n, (p - 1) / 2, p) != p - 1) ++n;
  ll x = binpow(a, (s + 1) / 2, p);
  ll b = binpow(a, s, p), g = binpow(n, s, p);
  for (;; r = m) {
    ll t = b;
    for (m = 0; m < r && t != 1; ++m) t = t * t % p;
    if (m == 0) return x;
    ll gs = binpow(g, 1LL << (r - m - 1), p);
    g = gs * gs % p;
    x = x * gs % p;
    b = b * g % p;
  }
}

