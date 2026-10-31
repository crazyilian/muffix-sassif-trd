// a[i] in [0, MOD), MOD <~ 1e9, n + m <= 2^20 (precision)
vector<ll> convMod(const vector<ll> &a, const vector<ll> &b) {
  if (a.empty() || b.empty()) return {};
  vector <ll> res((int) a.size() + (int) b.size() - 1);
  int lg = 32 - __builtin_clz((int) res.size()), n = 1 << lg, cut = (int) (sqrt(MOD));
  vector <comp> L(n), R(n), outs(n), outl(n);
  // x = h * cut + l, |h|, |l| <~ cut / 2: 4x less fft error
  auto sp = [&](ll x) {
    if (x > MOD / 2) x -= MOD;
    ll h = rint((double)x / cut);
    return comp(h, x - h * cut);
  };
  for (int i = 0; i < a.size(); i++) L[i] = sp(a[i]);
  for (int i = 0; i < b.size(); i++) R[i] = sp(b[i]);
  fft(L, lg), fft(R, lg);
  for (int i = 0; i < n; i++) {
    int j = -i & (n - 1);
    outl[j] = (L[i] + L[j].conj()) * R[i] / (2.0 * n);
    outs[j] = (L[i] - L[j].conj()) * R[i] / (2.0 * n) * comp(0, 1) * -1;
  }
  fft(outl, lg), fft(outs, lg);
  for (int i = 0; i < res.size(); i++) {
    ll av = rint(outl[i].x), cv = rint(outs[i].y);
    ll bv = rint(outl[i].y) + rint(outs[i].x);
    res[i] = ((av % MOD * cut + bv) % MOD * cut + cv) % MOD;
    res[i] += res[i] < 0 ? MOD : 0;
  }
  return res;
}
