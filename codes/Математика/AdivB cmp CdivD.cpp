// a/b vs c/d: -1 = less, 0 = equal, 1 = greater
// O(1) cross-multiplication
char compare(ll a, ll b, ll c, ll d) {
  i128 l = (i128)a * d, r = (i128)c * b;
  return ((l>r) - (l<r)) * sign(b) * sign(d);
}
// O(log), only a,b,c,d must fit into type
char compare(i128 a, i128 b, i128 c, i128 d) {
  if (a/b != c/d) return a/b < c/d ? -1 : 1;
  a %= b, c %= d;
  if (a == 0) return -sign(c) * sign(d);
  if (c == 0) return sign(a) * sign(b);
  return compare(d,c,b,a)*sign(a)*sign(b)*sign(c)*sign(d);
}
