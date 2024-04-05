vector<int> build_suff_arr(string s) {
  int MAX = max((int) s.size() + 10, (int) 256);
  s.push_back('#');
  int n = s.size();
  vector<int> suf(n), c(n);
  vector<int> cnt(MAX);
  for (int i = 0; i < n; i++) {
    cnt[s[i] - '#']++;
  }
  vector<int> pos(MAX);
  for (int i = 1; i < MAX; i++) {
    pos[i] = pos[i - 1] + cnt[i - 1];
  }
  for (int i = 0; i < n; i++) {
    suf[pos[s[i] - '#']++] = i;
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
    if (cls == n - 1) {
      break;
    }
  }
  suf.erase(suf.begin());
  return suf;
}

vector<int> kasai(string s, vector<int> sa) {
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
