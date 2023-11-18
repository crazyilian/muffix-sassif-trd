pair<Node *, Node *> split(Node *now, int k) {
    if (!now) {
        return {nullptr, nullptr};
    }
    if (size(now->l) + 1 <= k) {
        auto ans = split(now->r, k - 1 - size(now->l));
        now->r = ans.first;
        update_size(now);
        return {now, ans.second};
    }
    auto ans = split(now->l, k);
    now->l = ans.second;
    update_size(now);
    return {ans.first, now};
}

Node *merge(Node *l, Node *r) {
    if (!l) {
        return r;
    }
    if (!r) {
        return l;
    }
    if (l->y <= r->y) {
        auto ans = merge(l->r, r);
        l->r = ans;
        update_size(l);
        return l;
    }
    auto ans = merge(l, r->l);
    r->l = ans;
    update_size(r);
    return r;
}

Node *insert(Node *root, int pos) {
    auto r = split(root, pos);
    Node *nn = new Node(pos);
    root = merge(r.first, nn);
    root = merge(root, r.second);
    return root;
}

Node *to_begin(Node *root, int l, int r) {
    auto a = split(root, l);
    auto b = split(a.second, r - l);
    return merge(b.first, merge(a.first, b.second));
}

