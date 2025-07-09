// half plane: ax+by+c > 0
// bounding box MUST have
vector<int> intersection_half_planes_inds(const vector<line> &ls) {
  int n = (int)ls.size();
  vector<int> lsi(n);
  iota(lsi.begin(), lsi.end(), 0);
  sort(lsi.begin(), lsi.end(), [&](int i, int j) {
    vctr aa(ls[i].a, ls[i].b);
    vctr bb(ls[j].a, ls[j].b);
    bool pla = is2plane(aa);
    bool plb = is2plane(bb);
    if (pla != plb)
      return pla < plb;
    return aa * bb > 0;
  });

  vector<line> st;
  vector<int> inds;
  for (int ii = 0; ii < 2 * n; ++ii) {
    int i = lsi[ii % n];
    if (st.empty()) {
      st.push_back(ls[i]);
      inds.push_back(i);
      continue;
    }
    vctr p = intersection(ls[i], st.back());
    bool pp = isparallel(ls[i], st.back());
    bool bad = false;
    while (st.size() >= 2) {
      if (!pp && sign(st[st.size() - 2].get(p)) >= 0)
        break;
      else if (pp && sign(st.back().get(ls[i].anyPoint())) <= 0) {
        bad = true;
        break;
      }
      st.pop_back();
      inds.pop_back();
      p = intersection(ls[i], st.back());
      pp = isparallel(ls[i], st.back());
    }
    if (!bad) {
      st.push_back(ls[i]);
      inds.push_back(i);
    }
  }
  vector<int> cnt(n, 0);
  for (int i : inds)
    cnt[i]++;
  vector<int> good;
  for (int i : inds) {
    if (cnt[i]-- == 2)
      good.push_back(i);
  }
  return good;
}

vector<vctr> intersection_half_planes(vector<line> &ls) {
  vector<int> inter = intersection_half_planes_inds(ls);
  int n = inter.size();
  vector<vctr> pts;
  for (int i = 0; i < n; ++i) {
    int j = (i + 1) % n;
    vctr P = intersection(ls[inter[i]], ls[inter[j]]);
    if (pts.empty() || sign(pts.back().x - P.x) != 0
         || sign(pts.back().y - P.y) != 0)
      pts.push_back(P);
  }
  // pts против часовой стрелки, но pts[0] != minvctr
  return pts;
}

