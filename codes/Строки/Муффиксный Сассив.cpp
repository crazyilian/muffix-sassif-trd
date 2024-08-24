vector<int> build_suff_arr(string &s) {
  // Remove, if you want to sort cyclic shifts
  s += (char) (1);
  int n = s.size();
  vector<int> a(n);
  iota(all(a), 0);
  stable_sort(all(a), [&](int i, int j) {
      return s[i] < s[j];
  });
  vector<int> c(n);
  int cc = 0;
  for (int i = 0; i < n; i++) {
    if (i == 0 || s[a[i]] != s[a[i - 1]])
      c[a[i]] = cc++;
    else
      c[a[i]] = c[a[i - 1]];
  }
  for (int L = 1; L < n; L *= 2) {
    vector<int> cnt(n);
    for (auto i: c) cnt[i]++;
    if (*min_element(all(cnt)) > 0) break;
    vector<int> pref(n);
    for (int i = 1; i < n; i++)
      pref[i] = pref[i - 1] + cnt[i - 1];
    vector<int> na(n);
    for (int i = 0; i < n; i++) {
      int pos = (a[i] - L + n) % n;
      na[pref[c[pos]]++] = pos;
    }
    a = na;
    vector<int> nc(n);
    cc = 0;
    for (int i = 0; i < n; i++) {
      if (i == 0 || c[a[i]] != c[a[i - 1]] ||
          c[(a[i] + L) % n] != c[(a[i - 1] + L) % n])
        nc[a[i]] = cc++;
      else
        nc[a[i]] = nc[a[i - 1]];
    }
    c = nc;
  }
  // Remove, if you want to sort cyclic shifts
  a.erase(a.begin());
  s.pop_back();
  return a;
}

vector<int> kasai(string s, vector<int> sa) {
  // lcp[i] = lcp(sa[i], sa[i + 1])
  int n = s.size(), k = 0;
  vector<int> lcp(n, 0);
  vector<int> rank(n, 0);
  for (int i = 0; i < n; i++) rank[sa[i]] = i;
  for (int i = 0; i < n; i++, k ? k-- : 0) {
    if (rank[i] == n - 1) {
      k = 0;
      continue;
    }
    int j = sa[rank[i] + 1];
    while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
    lcp[rank[i]] = k;
  }
  return lcp;
}
