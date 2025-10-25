ll min25_sieve(ll n) {
  // given n, calculate prefix sums of some multiplicative function f
  // at all points of type floor(n/k) in O(n^{3/4}/log(n)), n up to 1e11 is ok
  // in particular you can find f(1) + ... + f(n)
  // also, calculation can be done for primes only, i.e prefix sum of f(i)*I{i is prime}
  // to do that, do not run last stage of algorithm

  vector<ll> v;
  v.reserve((int) sqrt(n) * 2 + 7);
  ll sq = 0;
  {
    ll k = 1;
    while (k * k <= n) {
      v.push_back(k);
      ++k;
    }
    --k;
    sq = k;
    if (k * k == n)--k;
    while (k >= 1) {
      v.push_back(n / k);
      --k;
    }
  }
  auto geti = [&](ll x) {
    // returns i, such that v[i] = x
    if (x <= sq) return x - 1;
    return (int) v.size() - (n / x);
  };
  // OP1: f(ab) = f(a)f(b) for coprime a, b; f(p) = p^T; f(p^k) can be calculated in O(1); we denote f(p^k) = g(p, k) (p is prime) for all k
  // OP2: f also can be any fully multiplicative function, f(ab) = f(a)f(b) for all a,b; you need to calc pref sum of f fast, so only prime case is useful

  auto g = [&](ll p, int k) {
    if (k == 1) {
      return p - 1; // polynomial, for primes-only can be any fully multiplicative function
    }
    return p + k; // any function, g(p^k)
  };

  auto f = [&](ll x) {
    return g(x, 1);
  };

  auto pref = [&](ll x) {
    // return sum_{i=1..x} g(i, 1), i.e 1^T + 2^T + ... + x^T
    return x * (x + 1) / 2;
  };

  vector<ll> s0(v.size()), s1(v.size()); // for all degrees separately
  for (int i = 0; i < (int) v.size(); i++) {
    s0[i] = v[i] % M;
    s1[i] = (((v[i] % M) * ((v[i] + 1) % M) % M) * (((M + 1) / 2) % M)) % M; // pref for g(p,1), degrees separately
    // s[i] = pref(v[i]) - 1  for primes
  }

  vector<ll> used_primes;
  used_primes.reserve((int) sqrt(n) + 7);
  for (ll p = 2; p * p <= n; ++p) {
    if (s0[p - 1] == s0[p - 2]) continue;
    // p is prime
    used_primes.push_back(p);
    for (int i = (int) v.size() - 1; i >= 0; --i) {
      if (v[i] < p * p) break; // very important, dont remove!
      s0[i] += M - ((s0[geti(v[i] / p)] + M - s0[p - 2]) % M * (1)) % M; // p^0
      s0[i] %= M;
      s1[i] += M - ((s1[geti(v[i] / p)] + M - s1[p - 2]) % M * (p)) % M; // p^1
      s1[i] %= M;
      // s[i] += M - ((s[geti(v[i] / p)] + M - s[p-2]) % M * f(p)) % M;
    }
  }

  // PRIMES ONLY calculation is done
  // desired answer for v[i] is in s[i]
  // in particular \sum_{i=1}^n f(i)*I{i is prime} is in s.back()
  // now last stage for default calculation

  vector<ll> s(v.size());
  for (int i = 0; i < v.size(); i++) {
    s[i] = (M - s0[i] % M + s1[i]) % M; // combine polynomial by degrees with needed coeffs
  }

  vector<ll> r = s;

  for (int ui = (int) used_primes.size() - 1; ui >= 0; --ui) { // ui >= 1, sum for odd numbers only
    ll p = used_primes[ui];
    for (int i = (int) v.size() - 1; i >= 0; --i) {
      if (v[i] < p * p) break; // very important, dont remove!
      for (ll c = 1, pc = p; pc * p <= v[i]; c++, pc *= p) { // pc = p^c
        r[i] += g(p, c + 1) % M + ((g(p, c) % M) * ((M + r[geti(v[i] / pc)] - s[geti(p)]) % M)) % M;
        r[i] %= M;
      }
    }
  }

  // done, answer for v[i] is r[i]+1 (f(1)=1)
  // in particular \sum_{i=2}^n f(i) is in r.back()
  // therefore \sum_{i=1}^n f(i) is r.back() + 1
  return r.back() + 1 - g(1, 1); // since f(1)=1 for real, not g(1,1): 1 is not prime
}
