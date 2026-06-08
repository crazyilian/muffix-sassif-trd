// Half plane: ax+by+c >= 0. Bounding box MUST HAVE.
vector<int> calc_hpi_inds(const vector<line> &ls) {
  int n = ls.size(), m=0, l=0, r=0;
  vector<int> q(n);
  vector<char> h(n);
  iota(q.begin(), q.end(), 0);
  auto cr = [&](int i, int j) {
    return ls[i].a * ls[j].b - ls[i].b * ls[j].a;
  };
  auto on = [&](int i, int j) {
    return sign(ls[i].get(ls[j].anyPoint()));
  };
  for (int i = 0; i < n; ++i)
    h[i] = sign(ls[i].b)<0||(!sign(ls[i].b)&&sign(ls[i].a)<0);
  sort(q.begin(), q.end(), [&](int i, int j) { // 70% of time
    return h[i] != h[j] ? h[i] < h[j] : cr(i, j) > 0;
  });
  for (int i : q) {
    if (!m || sign(cr(q[m-1], i))) q[m++] = i;
    else if (on(q[m-1], i) >= 0) q[m-1] = i;
  }

  auto bad = [&](int i, int j, int k) {
    if (!sign(cr(i, j))) return false;
    int s = sign(ls[k].get(intersection(ls[i], ls[j])));
    int t = sign(cr(i, k));
    return s<0 || (!s&&t&&sign(cr(i,j))==t&&sign(cr(j,k))==t);
  };
  for (int t = 0; t < m; ++t) {
    int i = q[t];
    while (r-l>1 && bad(q[r-2], q[r-1], i)) --r;
    while (r-l>1 && bad(q[l+1], q[l], i)) ++l;
    if (l<r && !sign(cr(q[r-1], i)) && on(q[r-1], i) < 0)
      return {};
    q[r++] = i;
  }
  while (r-l > 2 && bad(q[r-2], q[r-1], q[l])) --r;
  while (r-l > 2 && bad(q[l+1], q[l], q[r-1])) ++l;
  if (r-l < 3) return {};
  return {q.begin() + l, q.begin() + r};
}

vector<vctr> half_plane_intersection(const vector<line> &ls) {
  vector<int> inds = calc_hpi_inds(ls);
  int n = inds.size();
  vector<vctr> pts;
  pts.reserve(n);
  for (int i = 0; i < n; ++i) {
    vctr P = intersection(ls[inds[i]], ls[inds[(i+1) % n]]);
    if (pts.empty() || !(pts.back() == P)) pts.pb(P);
  }
  if (pts.size() > 1 && pts[0] == pts.back()) pts.pop_back();
// "empty"->{}, "point"->{P}, "segment"->{A,B}, else CCW.
// `inds` have no lines with 0 length, except for "segment"
// (4 lines), and "point" (3 lines, or 4 if 2 and 2 parallel)
  return pts;
}

