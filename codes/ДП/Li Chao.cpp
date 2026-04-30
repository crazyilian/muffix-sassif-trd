struct Line {
  ll k, b;
  ll operator()(ll x) const { return k * x + b; }
};

// LiChao for maximum at x
struct LiChao {
  struct Node {
    int l, r;
    Line ln;
  };
  ll L, R;
  int root;
  vector<Node> t;

  LiChao(ll L, ll R, int maxsz=1) : L(L), R(R), root(0) {
    t.reserve(maxsz + 1);
    t.pb({0, 0, {0, -INF}}); // t[0] = empty. +INF for min
  }
  
  int add_on_seg(int v, ll l, ll r, ll ql, ll qr, Line ln) {
    if (qr <= l || r <= ql) { return v; }
    if (ql <= l && r <= qr) { return add(v, l, r, ln); }
    if (!v) { v = t.size(), t.push_back({0, 0, {0, -INF}}); }
    ll m = (l + r) / 2;
    t[v].l = add_on_seg(t[v].l, l, m, ql, qr, ln);
    t[v].r = add_on_seg(t[v].r, m, r, ql, qr, ln);
    return v;
  }
  void add_on_seg(ll ql, ll qr, Line ln) { // [ql,qr)
    root = add_on_seg(root, L, R, ql, qr, ln);
  }

  int add(int v, ll l, ll r, Line ln) {
    if (!v) {
      v = t.size();
      t.push_back({0, 0, ln});
      return v;
    }
    ll m = (l + r) / 2;
    if (ln(m) > t[v].ln(m)) swap(ln, t[v].ln); // "<" for min
    if (r - l == 1 || ln.k == t[v].ln.k) return v;
    if (ln.k < t[v].ln.k) t[v].l = add(t[v].l, l, m, ln); // ">" for min
    else t[v].r = add(t[v].r, m, r, ln);
    return v;
  }
  void add(Line nw) { root = add(root, L, R, nw); }

  ll get(ll x) {
    ll ans = -INF; // +INF for min
    int v = root;
    ll l = L, r = R;
    while (v) {
      ans = max(ans, t[v].ln(x)); // "min" for min
      ll m = (l + r) / 2;
      if (x < m) v = t[v].l, r = m;
      else v = t[v].r, l = m;
    }
    return ans;
  }
};
