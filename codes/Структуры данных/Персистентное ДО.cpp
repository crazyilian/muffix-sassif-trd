Node nds[MAX];
int ndsz = 1;
// nds[0] is default (empty) value

int sum(int v) { return nds[v].sm; }

// returns new root of subtree
int update(int v, int l, int r, int qi, int qx) {
  if (qi < l || r <= qi) return v;
  if (l + 1 == r) {
    nds[ndsz++] = Node(qx);
    return ndsz - 1;
  }
  int m = (l + r) / 2;
  int u = ndsz++;
  nds[u].l = update(nds[v].l, l, m, qi, qx);
  nds[u].r = update(nds[v].r, m, r, qi, qx);
  nds[u].sm = sum(nds[u].l) + sum(nds[u].r);
  return u;
}

int get(int v, int l, int r, int ql, int qr) {
  if (!v || qr <= l || r <= ql) return 0;
  if (ql <= l && r <= qr) return nds[v].sm;
  int m = (l + r) / 2;
  auto a = get(nds[v].l, l, m, ql, qr);
  auto b = get(nds[v].r, m, r, ql, qr);
  return a + b;
}

