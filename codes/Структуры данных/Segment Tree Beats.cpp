// min=, sum
struct ST {
  vector<int> st, mx, mx_cnt, sec_mx;

  ST(int n) {
    st.resize(n * 4, 0);
    mx.resize(n * 4, 0);
    mx_cnt.resize(n * 4, 0);
    sec_mx.resize(n * 4, 0);
    build(0, 0, n);
  }

  void upd_from_children(int v) {
    st[v] = st[v * 2 + 1] + st[v * 2 + 2];
    mx[v] = max(mx[v * 2 + 1], mx[v * 2 + 2]);
    mx_cnt[v] = 0;
    sec_mx[v] = max(sec_mx[v * 2 + 1], sec_mx[v * 2 + 2]);
    if (mx[v * 2 + 1] == mx[v]) {
      mx_cnt[v] += mx_cnt[v * 2 + 1];
    } else {
      sec_mx[v] = max(sec_mx[v], mx[v * 2 + 1]);
    }
    if (mx[v * 2 + 2] == mx[v]) {
      mx_cnt[v] += mx_cnt[v * 2 + 2];
    } else {
      sec_mx[v] = max(sec_mx[v], mx[v * 2 + 2]);
    }
  }

  void build(int i, int l, int r) {
    if (l + 1 == r) {
      st[i] = mx[i] = 0;
      mx_cnt[i] = 1;
      sec_mx[i] = -INF;
      return;
    }
    int m = (r + l) / 2;
    build(i * 2 + 1, l, m);
    build(i * 2 + 2, m, r);
    upd_from_children(i);
  }

  void push_min_eq(int v, int val) {
    if (mx[v] > val) {
      st[v] -= (mx[v] - val) * mx_cnt[v];
      mx[v] = val;
    }
  }

  void push(int i) {
    push_min_eq(i * 2 + 1, mx[i]);
    push_min_eq(i * 2 + 2, mx[i]);
  }

  void update(int i, int l, int r, int ql, int qr, int val) {
    if (mx[i] <= val) {
      return;
    }
    if (ql == l && qr == r && sec_mx[i] < val) {
      push_min_eq(i, val);
      return;
    }
    push(i);
    int m = (r + l) / 2;
    if (qr <= m) {
      update(i * 2 + 1, l, m, ql, qr, val);
    } else if (ql >= m) {
      update(i * 2 + 2, m, r, ql, qr, val);
    } else {
      update(i * 2 + 1, l, m, ql, m, val);
      update(i * 2 + 2, m, r, m, qr, val);
    }
    upd_from_children(i);
  }

  int sum(int i, int l, int r, int ql, int qr) {
    if (l == ql && r == qr) {
      return st[i];
    }
    push(i);
    int m = (r + l) / 2;
    if (qr <= m) {
      return sum(i * 2 + 1, l, m, ql, qr);
    }
    if (ql >= m) {
      return sum(i * 2 + 2, m, r, ql, qr);
    }
    return sum(i * 2 + 1, l, m, ql, m) + sum(i * 2 + 2, m, r, m, qr);
  }
};
