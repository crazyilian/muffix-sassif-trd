// solve $w \equiv r_i \pmod {c_i}$
// assumes $c_i > 0$ and $\operatorname{lcm}(c_i)$ fits in ll
// return minimum $w \geq 0$ and common modulo
// return {-1, -1} if there is no solution
pair<ll, ll> generalized_crt(const vector<pair<int, int>> &equations) {
  ll r = 0, mod = 1;
  for (auto [ri, ci] : equations) {
    ri %= ci;
    if (ri < 0) ri += ci;
    int reduced_mod = mod % ci;
    auto [p, q] = ext_gcd(reduced_mod, ci);
    int g = (ll)p * reduced_mod + (ll)q * ci;
    ll diff = ri - r;
    if (diff % g != 0) return {-1, -1};
    ll k = (__int128)(diff / g) * p % (ci / g);
    if (k < 0) k += ci / g;
    ll new_mod = mod / g * ci;
    r = (r + (__int128)mod * k) % new_mod;
    mod = new_mod;
  }
  return {r, mod};
}
