// 2^pow > maxcoord
ll gilbertOrder(int x, int y, int pow=21, int rotate=0) {
  int h = 1 << (pow - 1);
  int seg = (x < h ? (y < h ? 0 : 3) : (y < h ? 1 : 2));
  seg = (seg + rotate) & 3;
  static const int rotateDelta[4] = {3, 0, 0, 1};
  int nx = x & (x ^ h), ny = y & (y ^ h);
  int nrot = (rotate + rotateDelta[seg]) & 3;
  ll subSquareSize = 1LL << (2 * pow - 2);
  ll ans = seg * subSquareSize;
  ll add = gilbertOrder(nx, ny, pow - 1, nrot);
  if (seg == 1 || seg == 2) ans += add;
  else ans += (subSquareSize - add - 1);
  return ans;
}
queries.push_back({l, r, i, gilbertOrder(l, r)});
sort(all(queries), [&](query lhs, query rhs) {
    return lhs.ord < rhs.ord;});
