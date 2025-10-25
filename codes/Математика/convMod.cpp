vector<ll> convMod(const vector<ll> &a, const vector<ll> &b) {
  if (a.empty() || b.empty()) return {};
  vector <ll> res((int) a.size() + (int) b.size() - 1);
  int lg = 32 - __builtin_clz((int) res.size()), n = 1 << lg, cut = (int) (sqrt(MOD));
  vector <comp> L(n), R(n), outs(n), outl(n);
  for (int i = 0; i < a.size(); i++) L[i] = comp((int) a[i] / cut, (int) a[i] % cut);
  for (int i = 0; i < b.size(); i++) R[i] = comp((int) b[i] / cut, (int) b[i] % cut);
  fft(L, lg), fft(R, lg);
  for (int i = 0; i < n; i++) {
    int j = -i & (n - 1);
    outl[j] = (L[i] + L[j].conj()) * R[i] / (2.0 * n);
    outs[j] = (L[i] - L[j].conj()) * R[i] / (2.0 * n) * comp(0, 1) * -1;
  }
  fft(outl, lg), fft(outs, lg);
  for (int i = 0; i < res.size(); i++) {
    ll av = (ll)((outl[i]).x + .5), cv = (ll)((outs[i]).y + .5);
    ll bv = (ll)((outl[i]).y + .5) + (ll)((outs[i]).x + .5);
    res[i] = ((av % MOD * cut + bv) % MOD * cut + cv) % MOD;
  }
  return res;
}
