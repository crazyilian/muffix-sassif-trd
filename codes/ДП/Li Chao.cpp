// MAXIMUM
struct Line {
  int k, b;

  int f(int x) {
    return k * x + b;
  }
};

struct ST {
  vector<Line> st;

  ST(int n) {
    Line ln = {0LL, -INF};
    st.resize(4 * n, ln);
  }

  void upd(int i, int l, int r, Line ln) {
    int child = 1;
    Line ln1 = ln;
    int m = (l + r) / 2;
    if (ln.f(m) > st[i].f(m)) {
      if (ln.k < st[i].k) {
        child = 2;
      }
      ln1 = st[i];
      st[i] = ln;
    } else {
      if (st[i].k < ln.k) {
        child = 2;
      }
    }
    if (l + 1 < r) {
      if (child == 1) {
        upd(i * 2 + 1, l, m, ln1);
      } else {
        upd(i * 2 + 2, m, r, ln1);
      }
    }
  }

  int res(int i, int l, int r, int x) {
    if (l + 1 == r) {
      return st[i].f(x);
    }
    int m = (l + r) / 2;
    int val = st[i].f(x);
    if (x < m) {
      val = max(val, res(i * 2 + 1, l, m, x));
    } else {
      val = max(val, res(i * 2 + 2, m, r, x));
    }
    return val;
  }
};
