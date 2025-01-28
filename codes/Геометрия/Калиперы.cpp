// Диаметр выпуклого многоугольника
int calipers(vector<vctr> &pts) {
  int n = pts.size();
  int a = 0, b = 0;
  for (int i = 1; i < n; ++i) {
    auto &v = pts[i];
    if (tie(v.y, v.x) < tie(pts[a].y, pts[a].x))
      a = i;
    if (tie(v.y, v.x) > tie(pts[b].y, pts[b].x))
      b = i;
  }
  int aa = (a + 1) % n, bb = (b + 1) % n;
  int dist2 = 0;
  for (int i = 0; i < n; ++i) {
    while (sign((pts[aa] - pts[a]) * (pts[bb] - pts[b])) > 0)
      b = bb, bb = (b + 1) % n;
    dist2 = max(dist2, (pts[a] - pts[b]).dist2());
    a = aa, aa = (a + 1) % n;
  }
  return dist2;
}
