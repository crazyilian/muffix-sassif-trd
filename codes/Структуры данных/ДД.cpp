pair<Node *, Node *> split(Node *now, ll x) {
    if (!now) {
        return {nullptr, nullptr};
    }
    if (now->x <= x) {
        auto ans = split(now->r, x);
        now->r = ans.first;
        update_sum(now);
        return {now, ans.second};
    }
    auto ans = split(now->l, x);
    now->l = ans.second;
    update_sum(now);
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
        update_sum(l);
        return l;
    }
    auto ans = merge(l, r->l);
    r->l = ans;
    update_sum(r);
    return r;
}

Node *insert(Node *root, ll val) {
    Node *new_v = new Node(val);
    auto ans = split(root, val);
    return merge(merge(ans.first, new_v), ans.second);
}

Node *del(Node *root, ll val) {
    auto ans = split(root, val);
    auto ans1 = split(ans.first, val - 1);
    return merge(ans1.first, ans.second);
}

ll get_sum(Node *root, ll l, ll r) {
    if (!root) {
        return 0;
    }
    auto ans = split(root, l - 1);
    auto ans2 = split(ans.second, r);
    if (!ans2.first) {
        merge(merge(ans.first, ans2.first), ans2.second);
        return 0;
    }
    ll res = ans2.first->sum_;
    merge(merge(ans.first, ans2.first), ans2.second);
    return res;
}

