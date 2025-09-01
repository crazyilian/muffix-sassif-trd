// insert $(key,val)$, erase $key$, $\max(val)$ for $key\in[l,r)$, $val$+= for $key\in[l,r)$
struct Node {
  int l, r;
  int x, y;
  int val, mx, mod;

  // value of empty set
  Node() : val(-INF), mx(-INF) {
    l = r = 0, mod = 0;
  }
  Node(int x, int val) : x(x), val(val), mx(val) {
    l = r = 0, mod = 0, y = rnd();
  }
};

Node nds[MAX];
int ndsz = 1; // nds[0] means empty

void push(int t) {
  if (!t || nds[t].mod == 0) return;
  nds[t].val += nds[t].mod;
  nds[t].mx += nds[t].mod;
  if (nds[t].l) nds[nds[t].l].mod += nds[t].mod;
  if (nds[t].r) nds[nds[t].r].mod += nds[t].mod;
  nds[t].mod = 0;
}

int getmx(int t) {
  push(t); // delete if sure (faster)
  return nds[t].mx;
}

void pull(int t) {
  if (!t) return;
  push(t), push(nds[t].l), push(nds[t].r); // must have
  nds[t].mx = max(nds[t].val, max(getmx(nds[t].l), getmx(nds[t].r)));
}

pair<int, int> split(int t, int x) {
  if (!t) return {0, 0};
  push(t);
  if (x <= nds[t].x) {
    auto [l, r] = split(nds[t].l, x);
    nds[t].l = r;
    pull(t);
    return {l, t};
  } else {
    auto [l, r] = split(nds[t].r, x);
    nds[t].r = l;
    pull(t);
    return {t, r};
  }
}

int merge(int l, int r) {
  push(l), push(r);
  if (!l) return r;
  if (!r) return l;
  if (nds[l].y < nds[r].y) {
    nds[l].r = merge(nds[l].r, r);
    pull(l);
    return l;
  } else {
    nds[r].l = merge(l, nds[r].l);
    pull(r);
    return r;
  }
}

void insert(int &root, int x, int val) {
  nds[ndsz++] = Node(x, val);
  auto [l, r] = split(root, x);
  root = merge(merge(l, ndsz - 1), r);
}

// erase all equal to x
void erase(int &root, int x) {
  auto [lm, r] = split(root, x + 1);
  auto [l, m] = split(lm, x);
  root = merge(l, r);
}

// query [l, r)
int query(int &root, int ql, int qr) {
  auto [lm, r] = split(root, qr);
  auto [l, m] = split(lm, ql);
  int res = getmx(m);
  root = merge(merge(l, m), r);
  return res;
}

// update [l, r)
void update(int &root, int ql, int qr, int qx) {
  auto [lm, r] = split(root, qr);
  auto [l, m] = split(lm, ql);
  if (m) nds[m].mod += qx;
  root = merge(merge(l, m), r);
}

