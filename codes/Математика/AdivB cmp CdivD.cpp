// -1 = less, 0 = equal, 1 = greater
char compare(ll a, ll b, ll c, ll d) {
  if (a / b != c / d) return sign(a / b - c / d);
  a %= b, c %= d;
  if (a == 0) return -sign(c) * sign(d);
  if (c == 0) return sign(a) * sign(b);
  return compare(d, c, b, a) * sign(a) * sign(b) * sign(c) * sign(d);
}
// O(1) cross-multiplicatoin equivalent
char compare(ll a, ll b, ll c, ll d) {
  return sign(a*d-c*b)*sign(b)*sign(d);
}
