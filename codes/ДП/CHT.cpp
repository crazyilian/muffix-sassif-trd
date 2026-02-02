#define bback(x) x[size(x)-2]
struct line {
  int k, b;
  int eval(int x) { return k * x + b; }
};
struct part { line a; dbl x; };

dbl intersection(line a, line b) {
  return (a.b - b.b) / (dbl)(b.k - a.k);
}

struct ConvexHull {
  // for min: k decreasing (non-increasing)
  // for max: k increasing (non-decreasing)
  vector<part> st;

  void add(line a) {
    if (!st.empty() && st.back().a.k == a.k) {
      if (st.back().a.b < a.b) st.pop_back(); // for max
    //if (st.back().a.b > a.b) st.pop_back(); // for min
      else return;
    }
    while (st.size() > 1 &&
           intersection(bback(st).a, a) <= bback(st).x)
      st.pop_back();
    if (!st.empty())
      st.back().x = intersection(st.back().a, a);
    st.push_back({a, INFINITY}); // C++ define
  }

  int get_val(int x) {
    if (st.empty()) {
      return -INF; // min possible value, for max
     //return INF; // max possible value, for min
    }
    int l = -1, r = ssize(st) - 1;
    while (r - l > 1) {
      int m = (l + r) / 2;
      if (st[m].x < x) l = m;
      else r = m;
    }
    return st[r].a.eval(x);
  }
};

