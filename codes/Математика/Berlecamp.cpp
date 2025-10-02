int getkfps(vector<ll> p, vector<ll> q, ll k) {
    // assert(q[0] != 0);
    while (k) {
        auto f = q;
        for (int i = 1; i < (int) f.size(); i += 2) {
            f[i] = (MOD - f[i] % MOD) % MOD;
        }
        auto p2 = convMod(p, f);
        auto q2 = convMod(q, f);
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

// a - initials values of sequence, s - result of berlekamp on a
int kth_term(vector<ll> &a, vector<ll> s, ll k) {
    int d = ssize(s) - 1;
    s[0] = MOD - 1;
    while (s.back() == 0) {
        s.pop_back();
    }
    for (auto &el: s) {
        el = (MOD - el % MOD) % MOD;
    }
    vector<ll> p(d);
    copy(a.begin(), a.begin() + d, p.begin());
    p = convMod(p, s);
    p.resize(d);
    return getkfps(p, s, k);
}

vector<ll> berlekamp_massey(vector<ll> a) {
    // given a[0]...a[n], returns sequence s[1]..s[k] s.t a[i] = a[i-1] \cdot s[1] + \ldots + a[i-k] \cdot s[k]
    vector<ll> ls, s;
    int lf = 0, d = 0;
    for (int i = 0; i < a.size(); ++i) {
        ll t = 0;
        for (int j = 0; j < s.size(); ++j) {
            t = (t + 1ll * a[i - j - 1] * s[j]) % MOD;
        }
        if ((t - a[i]) % MOD == 0)continue;
        if (s.empty()) {
            s.resize(i + 1);
            lf = i;
            d = (t - a[i]) % MOD;
            continue;
        }
        ll k = -(a[i] - t) * inverse(d) % MOD;
        vector<ll> c(i - lf - 1);
        c.push_back(k);
        for (auto &j: ls)
            c.push_back(-j * k % MOD);
        if (c.size() < s.size())
            c.resize(s.size());
        for (int j = 0; j < s.size(); ++j) {
            c[j] = (c[j] + s[j]) % MOD;
        }
        if (i - lf + (int) ls.size() >= (int) s.size()) {
            tie(ls, lf, d) = make_tuple(s, i, (t - a[i]) % MOD);
        }
        s = c;
    }
    s.insert(s.begin(), 0); // fictive s[0] = 0
    for (auto &i: s)
        i = (i % MOD + MOD) % MOD;
    return s;
}
