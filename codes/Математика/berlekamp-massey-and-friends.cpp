int getkfps(vector<ll> p, vector<ll> q, ll k) {
    // assert(q[0] != 0);
    while (k) {
        auto f = q;
        for (int i = 1; i < (int) f.size(); i += 2) {
            f[i] = (MOD - f[i] % MOD) % MOD;
        }
        auto p2 = (vector<ll>) convMod<MOD>(p, f);
        auto q2 = (vector<ll>) convMod<MOD>(q, f);
        p.clear(), q.clear();
        for (int i = k % 2; i < (int) p2.size(); i += 2) {
            p.pb(p2[i]);
        }
        for (int i = 0; i < (int) q2.size(); i += 2) {
            q.pb(q2[i]);
        }
        k >>= 1;
    }
    return (int) ((p[0] * inverse(q[0])) % MOD);
}

// vals - initials values of reccurence, c - result of berlekamp on vals
int getk(vector<ll> &vals, vector<ll> c, ll k) {
    int d = (int) c.size() - 1;
    c[0] = MOD - 1;
    while (c.back() == 0) {
        c.pop_back();
    }
    for (auto &el: c) {
        el = (MOD - el % MOD) % MOD;
    }
    vector<ll> p(d);
    copy(vals.begin(), vals.begin() + d, p.begin());
    p = (vector<ll>) convMod<MOD>(p, c);
    p.resize(d);
    return getkfps(p, c, k);
}

vector<ll> mod_poly_slow(vector<ll> &p, vector<ll> &q) {
    int n = (int) p.size(), m = (int) q.size();
    if (n < m) {
        return p;
    }
    vector<ll> r = p;
    for (int i = n - 1; i >= m - 1; --i) {
        int coef = (r[i] * 1ll * inverse(q[m - 1])) % MOD;
        for (int j = 0; j < m; ++j) {
            r[i - j] = (r[i - j] - coef * 1ll * q[m - 1 - j] % MOD + MOD) % MOD;
        }
    }
    while (!r.empty() && r.back() == 0) {
        r.pop_back();
    }
    return r;
}

int kth_term(vector<ll> &a, vector<ll> s, ll k) {
    // a in 0-index, s in 1-index
    int n = (int) s.size() - 1;
    assert((int) a.size() >= n);
    // a[0]..a[n-1] -- first values
    // a[i] = a[i-1] \cdot s[1] + \ldots + a[i-n] \cdot s[n]
    // find a[k]

    // return getk(a, s, k);

    vector<ll> f(n + 1);
    for (int i = 1; i <= n; i++) {
        f[n - i] = (MOD - s[i]) % MOD;
    }
    f[n] = 1;
    vector<ll> res = {1}, w = {0, 1};
    while (k) {
        if (k % 2) {
            res = (vector<ll>) convMod<MOD>(res, w); // mul
            res = mod_poly_slow(res, f);
        }
        w = (vector<ll>) convMod<MOD>(w, w); // mul
        w = mod_poly_slow(w, f);
        k /= 2;
    }
    int ans = 0;
    for (int i = 0; i < (int) res.size(); i++) {
        ans = (ans + a[i] * 1ll * res[i] % MOD) % MOD;
    }
    return ans;
}

vector<ll> berlekamp_massey(vector<ll> a) {
    // given a[0]...a[n], returns sequence s[1]..s[k] s.t a[i] = a[i-1] \cdot s[1] + \ldots + a[i-k] \cdot s[k]
    vector<ll> ls, cur;
    int lf = 0, d = 0;
    for (int i = 0; i < a.size(); ++i) {
        ll t = 0;
        for (int j = 0; j < cur.size(); ++j) {
            t = (t + 1ll * a[i - j - 1] * cur[j]) % MOD;
        }
        if ((t - a[i]) % MOD == 0)continue;
        if (cur.empty()) {
            cur.resize(i + 1);
            lf = i;
            d = (t - a[i]) % MOD;
            continue;
        }
        ll k = -(a[i] - t) * inverse(d) % MOD;
        vector<ll> c(i - lf - 1);
        c.push_back(k);
        for (auto &j: ls)
            c.push_back(-j * k % MOD);
        if (c.size() < cur.size())
            c.resize(cur.size());
        for (int j = 0; j < cur.size(); ++j) {
            c[j] = (c[j] + cur[j]) % MOD;
        }
        if (i - lf + (int) ls.size() >= (int) cur.size()) {
            tie(ls, lf, d) = make_tuple(cur, i, (t - a[i]) % MOD);
        }
        cur = c;
    }
    cur.insert(cur.begin(), 0); // fictive s[0] = 0
    for (auto &i: cur)
        i = (i % MOD + MOD) % MOD;
    return cur;
}
