// Sum multiplicative f over [1..n], O(n^{3/4}/log n).
// Need f(p) = polynomial in p. Change D, POLY, sum_power(), f_prime_power().
// Default: f(n) = n, f(p) = p, f(p^e) = p^e.
// Prime count: D=0, POLY={1}, build(n), answer = prime_poly(n).
// phi: POLY={-1,1}, f_prime_power=pe-prev.
// f_prime_power may be arbitrary O(1), but e=1 must match POLY.

// ll mul(ll a, ll b);

struct Min25 {
  // f(p) = sum POLY[d] * p^d. Add degrees if needed.
  static const int D = 1;
  const vector<ll> POLY = {0, 1}; // id: p

  ll n, sq;
  vector<ll> val;
  vector<int> id_small, id_large;
  vector<vector<ll>> g; // g[d][i] = sum_{p<=val[i]} p^d
  vector<ll> primes;
  bool built = false;

  int id(ll x) {
    return x <= sq ? id_small[x] : id_large[n / x];
  }

  ll sum_power(int d, ll x) {
    x %= mod;
    if (d == 0) return x;
    if (d == 1) return mul(x, x + 1) * ((mod + 1) / 2) % mod;
    // Add interpolation here for larger D.
    assert(false);
  }

  ll prime_poly_at_index(int i) {
    ll res = 0;
    for (int d = 0; d <= D; ++d)
      res = (res + mul(POLY[d], g[d][i])) % mod;
    return res;
  }

  ll prime_poly(ll x) {
    if (x < 2) return 0;
    return prime_poly_at_index(id(x));
  }

  // Value f(p^e). Args are (p, e, p^e mod mod, p^{e-1} mod mod).
  ll f_prime_power(ll p, int e, ll pe, ll prev) {
    return pe;
  }

  void build(ll _n) {
    if (built) return;
    built = true;
    n = _n;
    val.clear();
    primes.clear();
    sq = sqrtl(n);
    while ((sq + 1) * (sq + 1) <= n) ++sq;
    while (sq * sq > n) --sq;
    id_small.assign(sq + 1, -1);
    id_large.assign(sq + 1, -1);

    for (ll l = 1, r; l <= n; l = r + 1) {
      ll x = n / l;
      r = n / x;
      int i = val.size();
      val.push_back(x);
      if (x <= sq) id_small[x] = i;
      else id_large[n / x] = i;
    }

    g.assign(D + 1, vector<ll>(val.size()));
    for (int d = 0; d <= D; ++d)
      for (int i = 0; i < (int)val.size(); ++i)
        g[d][i] = (sum_power(d, val[i]) - 1 + mod) % mod;

    for (ll p = 2; p <= sq; ++p) {
      if (g[0][id(p)] == g[0][id(p - 1)]) continue;
      primes.push_back(p);
      vector<ll> ppow(D + 1, 1);
      for (int d = 1; d <= D; ++d) ppow[d] = mul(ppow[d - 1], p);
      for (int i = 0; i < (int)val.size() && val[i] >= p * p; ++i) {
        int ip = id(val[i] / p);
        int before_p = id(p - 1);
        for (int d = 0; d <= D; ++d) {
          ll sub = mul(g[d][ip] - g[d][before_p], ppow[d]);
          g[d][i] = (g[d][i] - sub + mod) % mod;
        }
      }
    }
  }

  // Sum of f(x), x <= limit, all prime divisors of x are >= primes[pos].
  ll dfs(ll limit, int pos) {
    ll last = pos ? primes[pos - 1] : 1;
    if (limit < 2 || pos >= (int)primes.size()) {
      ll res = (prime_poly(limit) - prime_poly(last)) % mod;
      if (res < 0) res += mod;
      return res;
    }
    ll res = (prime_poly(limit) - prime_poly(last)) % mod;
    if (res < 0) res += mod;
    for (int i = pos; i < (int)primes.size(); ++i) {
      ll p = primes[i];
      if ((__int128)p * p > limit) break;
      ll pe_int = p, pe_mod = p % mod, prev_mod = 1;
      for (int e = 1; (__int128)pe_int * p <= limit; ++e) {
        ll nxt_mod = mul(pe_mod, p);
        ll cur = f_prime_power(p, e, pe_mod, prev_mod);
        ll nxt = f_prime_power(p, e + 1, nxt_mod, pe_mod);
        res = (res + mul(cur, dfs(limit / pe_int, i + 1)) + nxt) % mod;
        prev_mod = pe_mod;
        pe_mod = nxt_mod;
        pe_int *= p;
      }
    }
    return res;
  }

  ll solve(ll _n) {
    if (_n <= 0) return 0;
    build(_n); // After build(n), prime_poly(n) is sum f(p) over primes p <= n.
    return (1 + dfs(n, 0)) % mod; // f(1) = 1
  }
};
