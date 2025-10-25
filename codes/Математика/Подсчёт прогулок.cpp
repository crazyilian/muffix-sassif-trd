int count_walks_1(int b1, int b2, int p, int q) {
  // counting walks from (0, 0) to (p, q)
  // each turn x += 1 or y += 1
  // without touching y = x + b1 and y = x + b2
  // b1 < 0 < b2 must hold
  // O((p + q) / (b2 - b1))
  if (min(p, q) < 0) return 0;
  ll ans = C(p, p + q);
  ar(2) F = {p, q}, S = {p, q};
  int cf = mod - 1;
  while (true) {
    F[1] -= b1;
    swap(F[0], F[1]);
    F[1] += b1;
    S[1] -= b2;
    swap(S[0], S[1]);
    S[1] += b2;
    swap(F, S);
    int wf = C(F[0], F[0] + F[1]);
    int ws = C(S[0], S[0] + S[1]);
    ans += (cf * (ll) ((wf + ws) % mod)) % mod;
    if (wf == 0 && ws == 0) break;
    cf = mod - cf;
  }
  ans %= mod;
  return (int) ans;
}

int count_walks_2(int b1, int b2, int p, int q) {
  // counting walks from (0, 0) to (p, q)
  // each turn x += 1 and (y -= 1 or y += 1)
  // without touching y = b1 and y = b2
  // b1 < 0 < b2 must hold
  // O(p / (b2 - b1))
  if (abs(p) % 2 != abs(q) % 2) return 0;
  int p0 = (p - q) / 2, q0 = (p + q) / 2;
  return count_walks_1(b1, b2, p0, q0);
}
