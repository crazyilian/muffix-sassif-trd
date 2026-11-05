int size(int), sum(int);

struct Node {
  int l, r, val, sz, sm;
  Node() : l(0), r(0), val(0), sz(0), sm(0) {}
  Node(int val, int l, int r) : val(val), l(l), r(r) {
    sz = 1 + size(l) + size(r);
    sm = val + sum(l) + sum(r);
  }
};

Node nds[MAX];
int ndsz = 1;

int size(int t) { return nds[t].sz; }
int sum(int t) { return nds[t].sm; }

int newNode(int val, int l, int r) {
  nds[ndsz++] = Node(val, l, r);
  return ndsz - 1;
}

pair<int, int> split(int t, int x) {
  if (!t) return {0, 0};
  int szl = size(nds[t].l);
  if (szl >= x) {
    auto [l, r] = split(nds[t].l, x);
    return {l, newNode(nds[t].val, r, nds[t].r)};
  } else {
    auto [l, r] = split(nds[t].r, x - szl - 1);
    return {newNode(nds[t].val, nds[t].l, l), r};
  }
}

bool chooseleft(int szl, int szr) {
  return rnd() % (szl + szr) < szl;
}

int merge(int l, int r) {
  if (!l) return r;
  if (!r) return l;
  if (chooseleft(nds[l].sz, nds[r].sz)) {
    int nr = merge(nds[l].r, r);
    return newNode(nds[l].val, nds[l].l, nr);
  } else {
    int nl = merge(l, nds[r].l);
    return newNode(nds[r].val, nl, nds[r].r);
  }
}

int insert(int root, int pos, int val) {
  int new_v = newNode(val, 0, 0);
  auto [l, r] = split(root, pos);
  return merge(merge(l, new_v), r);
}

int erase(int root, int pos) {
  auto [lm, r] = split(root, pos + 1);
  auto [l, m] = split(lm, pos);
  return merge(l, r);
}

// query [ql, qr), no new nodes
int get(int t, int ql, int qr) {
  if (!t || qr <= 0 || size(t) <= ql) return 0;
  if (ql <= 0 && size(t) <= qr) return sum(t);
  int lsz = size(nds[t].l);
  return get(nds[t].l, ql, qr)
       + (ql <= lsz && lsz < qr ? nds[t].val : 0)
       + get(nds[t].r, ql-lsz-1, qr-lsz-1);
}
