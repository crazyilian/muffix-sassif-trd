struct line {
  ll k, b;
  i128 eval(ll x) { return (i128)k * x + b; }
};

// check if b is redudant, exact
bool redundant(line a, line b, line c) {
  return (a.b - b.b) * (i128)(c.k - b.k)
      >= (b.b - c.b) * (i128)(b.k - a.k);
}
// floating point alternative
dbl inter(line a, line b) { return (a.b-b.b)/(dbl)(b.k-a.k); }
bool redundant(line a, line b, line c) { return inter(a, b)>=inter(b, c); }

// |k|, |b| <= 1e18; query answer must fit long long
struct ConvexHull {
  // for min: k decreasing (non-increasing)
  // for max: k increasing (non-decreasing)
  vector<line> st;

  void add(line a) {
    if (!st.empty() && st.back().k == a.k) {
      if (st.back().b < a.b) st.pop_back(); // for max
    //if (st.back().b > a.b) st.pop_back(); // for min
      else return;
    }
    while (st.size() > 1 && redundant(st[st.size()-2], st.back(), a))
      st.pop_back();
    st.pb(a);
  }

  ll get_val(ll x) {
    if (st.empty()) return -INF; // +INF for min
    int l = -1, r = ssize(s) - 1;
    while (r - l > 1) {
      int m = (l + r) / 2;
      if (st[m].eval(x) < st[m + 1].eval(x)) l = m; // > for min
      else r = m;
    }
    return st[r].eval(x);
  }
};
