pair<Node *, Node *> split(Node *t, int x) {
  if (!t)
    return {nullptr, nullptr};
  if (x <= t->x) {
    auto [l, r] = split(t->l, x);
    t->l = r;
    pull(t);
    return {l, t};
  } else {
    auto [l, r] = split(t->r, x);
    t->r = l;
    pull(t);
    return {t, r};
  }
}

Node *merge(Node *l, Node *r) {
  if (!l)
    return r;
  if (!r)
    return l;
  if (l->y < r->y) {
    l->r = merge(l->r, r);
    pull(l);
    return l;
  } else {
    r->l = merge(l, r->l);
    pull(r);
    return r;
  }
}

void insert(Node *&root, int val) {
  Node *new_v = new Node(val);
  auto [l, r] = split(root, val);
  root = merge(merge(l, new_v), r);
}

void erase(Node *&root, int val) {
  auto [lm, r] = split(root, val + 1);
  auto [l, m] = split(lm, val);
  root = merge(l, r);
}

int sum(Node *v) {
  return v ? v->sm : 0;
}

// query [l, r)
int query(Node *&root, int ql, int qr) {
  auto [lm, r] = split(root, qr);
  auto [l, m] = split(lm, ql);
  int res = sum(m);
  root = merge(merge(l, m), r);
  return res;
}
