// left: v ? v->l : nullptr (same for right)
// sum: v ? v->sm : 0

// v can be nullptr. returns new root of subtree
Node *update(Node *v, int l, int r, int qi, int qx) {
  if (qi < l || r <= qi)
    return v;
  if (l + 1 == r)
    return new Node(qx);
  int m = (l + r) / 2;
  Node *u = new Node();
  u->l = update(left(v), l, m, qi, qx);
  u->r = update(right(v), m, r, qi, qx);
  u->sm = sum(u->l) + sum(u->r);
  return u;
}

int get(Node *v, int l, int r, int ql, int qr) {
  if (!v || qr <= l || r <= ql)
    return 0;
  if (ql <= l && r <= qr)
    return v->sm;
  int m = (l + r) / 2;
  auto a = get(v->l, l, m, ql, qr);
  auto b = get(v->r, m, r, ql, qr);
  return a + b;
}

