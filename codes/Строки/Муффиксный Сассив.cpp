template<class T> // works for string and vector
vector<int> build_suff_arr(T s) {
  { // values compression. comment if already 0 < s[i] < ~1e6
    vector<int> id(size(s));
    iota(all(id), 0);
    sort(all(id), [&](int i, int j) { return s[i]<s[j]; });
    auto v = s;
    for (int i=0, r=0; i < ssize(s); i++)
      v[id[i]] = r += !i || s[id[i]] != s[id[i-1]];
    s = v;
  }
  s.pb(0); // remove if cyclic shifts
  int n = s.size(), m = *max_element(all(s)) + 2;
  vector<int> sa(n), rk(n), t(n), c(max(n,m));
  for (auto x : s) c[x+1]++;
  partial_sum(all(c), begin(c));
  for (int i=0; i<n; i++) rk[i] = c[s[i]];
  for (int i=0; i<n; i++) sa[c[s[i]]++] = i;
  // rk[i] = start of i's class in sa
  for (int k=1, g=0; k<n && g<n; k*=2) {
    iota(all(c), 0);
    for (int i : sa) {
      int j = i>=k ? i-k : i-k+n;
      t[c[rk[j]]++] = j;
    }
    swap(sa,t), g=0;
    for (int i=0, pr=-1, pq=-1, st=0; i<n; i++) {
      int b=sa[i], j = b+k<n ? b+k : b+k-n;
      int r=rk[b], q=rk[j];
      if (r!=pr || q!=pq) st=i, g++;
      t[b]=st, pr=r, pq=q;
    }
    swap(rk,t);
  }
  sa.erase(sa.begin()); // remove if cyclic shifts
  return sa;
}

// lcp[i] = lcp(sa[i], sa[i + 1]), size = n-1
template<class T>
vector<int> kasai(const T &s, const vector<int> &sa) {
  int n = s.size(), k=0;
  vector<int> rk(n), lcp(n-!!n);
  for (int i=0; i<n; i++) rk[sa[i]] = i;
  for (int i=0; i<n; i++, k-=k>0) {
    if (rk[i] == n-1) continue;
    int j = sa[rk[i]+1];
    while (max(i,j)+k < n && s[i+k]==s[j+k]) k++;
    lcp[rk[i]] = k;
  }
  return lcp;
}
