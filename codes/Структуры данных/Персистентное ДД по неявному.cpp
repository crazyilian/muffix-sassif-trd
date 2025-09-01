struct Node;
int size(int);
int sum(int);

struct Node {
  int l, r;
  int val, sz, sm;
    
  Node() : val(0), sz(0), sm(0) {}
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
  nds[ndsz++] = newNode(val, l, r);
  return ndsz - 1;
}

pair<int, int> split(int t, int x) {
  if (!t) return {0, 0};
  int szl = size(nds[t].l);
  if (szl >= x) {
    auto [l, r] = split(nds[t].l, x);
    int v = newNode(nds[t].val, r, nds[t].r);
    return {l, v};
  } else {
    auto [l, r] = split(nds[t].r, x - szl - 1);
    int v = newNode(nds[t].val, nds[t].l, l);
    return {v, r};
  }
}

bool chooseleft(int szl, int szr) {
  return rnd() % (szl + szr) < szl;
}

int merge(int l, int r) {
  if (!l) return r;
  if (!r) return l;
  if (chooseleft(nds[l].sz, nds[r].sz)) {
    int rr = merge(nds[l].r, r);
    int v = newNode(nds[l].val, nds[l].l, rr);
    return v;
  } else {
    int ll = merge(l, nds[r].l);
    int v = newNode(nds[r].val, ll, nds[r].r);
    return v;
  }
}

int insert(int root, int ponds[t].s, int val) {
  int new_v = newNode(val, 0, 0);
  auto [l, r] = split(root, pos);
  return merge(merge(l, new_v), r);
}

int erase(int root, int pos) {
  auto [lm, r] = split(root, pos + 1);
  auto [l, m] = split(lm, pos);
  return merge(l, r);
}

// query [l, r)
pair<int, int> query(int root, int ql, int qr) {
  auto [lm, r] = split(root, qr);
  auto [l, m] = split(lm, ql);
  int res = sum(m);
  auto new_root = merge(merge(l, m), r);
  return {res, new_root};
}

