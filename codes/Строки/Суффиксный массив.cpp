vector<int> build_suff_arr(string s) {
    s.push_back('$');
    int n = s.size();
    vector<int> suf(n), c(n);
    vector<int> cnt(MAX);
    for (int i = 0; i < n; i++) {
        cnt[s[i] - '$']++;
    }
    vector<int> pos(MAX);
    for (int i = 1; i < MAX; i++) {
        pos[i] = pos[i - 1] + cnt[i - 1];
    }
    for (int i = 0; i < n; i++) {
        suf[pos[s[i] - '$']++] = i;
    }
    int cls = -1;
    for (int i = 0; i < n; i++) {
        if (i == 0 || s[suf[i]] != s[suf[i - 1]]) {
            cls++;
        }
        c[suf[i]] = cls;
    }
    for (int L = 1; L < n; L *= 2) {
        fill(cnt.begin(), cnt.end(), 0);
        for (int i = 0; i < n; i++) {
            cnt[c[i]]++;
        }
        pos[0] = 0;
        for (int i = 1; i < n; i++) {
            pos[i] = pos[i - 1] + cnt[i - 1];
        }
        for (int i = 0; i < n; i++) {
            suf[i] = (suf[i] - L + n) % n;
        }
        vector<int> new_suf(n), new_c(n);
        for (int i = 0; i < n; i++) {
            int where = pos[c[suf[i]]];
            new_suf[where] = suf[i];
            pos[c[suf[i]]]++;
        }
        cls = -1;
        for (int i = 0; i < n; i++) {
            if (i == 0) {
                cls++;
                new_c[new_suf[i]] = cls;
                continue;
            }
            pair<int, int> prev = {c[new_suf[i - 1]], c[(new_suf[i - 1] + L) % n]};
            pair<int, int> now = {c[new_suf[i]], c[(new_suf[i] + L) % n]};
            if (prev != now) {
                cls++;
            }
            new_c[new_suf[i]] = cls;
        }
        swap(c, new_c);
        swap(suf, new_suf);
    }
    vector<int> res;
    for (int i = 1; i < n; i++) {
        res.push_back(suf[i]);
    }
    return res;
}

vector<int> lcp_neighboring(string &s, vector<int> &suf) {
    int n = s.size();
    vector<int> lcp(n), where(n);
    for (int i = 0; i < n; i++) {
        where[suf[i]] = i;
    }
    int k = 0;
    for (int j = 0; j < n; j++) {
        int pos = where[j];
        if (pos == n - 1) {
            k = 0;
            lcp[pos] = 0;
        } else {
            k = max(0LL, k - 1);
            while (s[j + k] == s[suf[pos + 1] + k]) {
                k++;
                if (j + k >= n || suf[pos + 1] + k >= n) {
                    break;
                }
            }
            lcp[pos] = k;
        }
    }
    return lcp;
}

int sol(int k, string s) {
    int n = s.size();
    vector<int> suf = build_suff_arr(s);
    vector<int> lcp = lcp_neighboring(s, suf);
    vector<int> where(n);
    for (int i = 0; i < n; i++) {
        where[suf[i]] = i;
    }
    Sparse_Table st(lcp);
    int ans = 0;
    for (int i = 0; i < n - k; i++) {
        ans += st.rmq(where[i], where[i + k]);
    }
    return ans;
}

