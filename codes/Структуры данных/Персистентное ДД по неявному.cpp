mt19937 rnd(228);

struct Node;
int size(Node *);
int sum(Node *);

struct Node {
  Node *l, *r;
  int val, sz, sm;

  Node(int val) : val(val), sz(1), sm(val) {
    l = r = nullptr;
  }
  Node(int val, Node *l, Node *r) : val(val), l(l), r(r) {
    sz = 1 + size(l) + size(r);
    sm = val + sum(l) + sum(r);
  }
};

int size(Node *v) {
  return v ? v->sz : 0;
}

int sum(Node *v) {
  return v ? v->sm : 0;
}

pair<Node *, Node *> split(Node *t, int x) {
  if (!t)
    return {nullptr, nullptr};
  int lsz = size(t->l);
  if (lsz >= x) {
    auto [l, r] = split(t->l, x);
    auto v = new Node(t->val, r, t->r);
    return {l, v};
  } else {
    auto [l, r] = split(t->r, x - lsz - 1);
    auto v = new Node(t->val, t->l, l);
    return {v, r};
  }
}

bool chooseleft(int lsz, int rsz) {
  return rnd() % (lsz + rsz) < lsz;
}

Node *merge(Node *l, Node *r) {
  if (!l)
    return r;
  if (!r)
    return l;
  if (chooseleft(l->sz, r->sz)) {
    auto rr = merge(l->r, r);
    auto v = new Node(l->val, l->l, rr);
    return v;
  } else {
    auto ll = merge(l, r->l);
    auto v = new Node(r->val, ll, r->r);
    return v;
  }
}

Node *insert(Node *root, int pos, int val) {
  Node *new_v = new Node(val);
  auto [l, r] = split(root, pos);
  return merge(merge(l, new_v), r);
}

Node *erase(Node *root, int pos) {
  auto [lm, r] = split(root, pos + 1);
  auto [l, m] = split(lm, pos);
  return merge(l, r);
}

// query [l, r)
pair<int, Node *> query(Node *root, int ql, int qr) {
  auto [lm, r] = split(root, qr);
  auto [l, m] = split(lm, ql);
  int res = sum(m);
  auto new_root = merge(merge(l, m), r);
  return {res, new_root};
}

