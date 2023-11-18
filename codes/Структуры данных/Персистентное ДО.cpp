struct ST {
    vector<Node *> roots;
    int n;

    ST(vector<int> &a) {
        start = a;
        n = a.size();
        roots.push_back(nullptr);
        build(roots[0], 0, n);
    }

    void update(Node *&now, Node *old, int l, int r, int pos, int qd) {
        if (l + 1 == r) {
            now = new_node(qd);
            return;
        }
        now = new_node();
        int m = (l + r) / 2;
        if (pos < m) {
            now->r = old->r;
            update(now->l, old->l, l, m, pos, qd);
        } else {
            now->l = old->l;
            update(now->r, old->r, m, r, pos, qd);
        }
        now->sm = now->l->sm + now->r->sm;
    }
};

