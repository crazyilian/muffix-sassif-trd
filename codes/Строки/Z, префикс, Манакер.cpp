vector<int> z_func(const string &s) {
  int n = s.size();
  vector<int> z(n, 0);
  z[0] = n;
  int l = 0, r = 0;
  for (int i = 1; i < n; i++) {
    if (i < r) z[i] = min(z[i-l], r-i);
    while (i+z[i] < n && s[z[i]] == s[i+z[i]]) z[i]++;
    if (i+z[i] > r) l = i, r = i+z[i];
  }
  return z;
}

vector<int> prefix_func(const string &s) {
  int n = s.size(), a = 0;
  vector<int> pref(n, 0);
  for (int i = 1; i < n; i++) {
    while (a > 0 && s[a] != s[i]) a = pref[a-1];
    pref[i] = a += s[i] == s[a];
  }
  return pref;
}

// d[0][i] even center (i,i+1). d[1][i] odd center (i)
array<vector<int>, 2> manacher(const string &s) {
  int n = s.size();
  array<vector<int>, 2> d;
  for (int z = 0; z <= 1; ++z) {
    d[z].resize(n - z);
    int l = 0, r = -1;
    for (int i = z; i < n; ++i) {
      int k = i > r ? 1-z : min(d[z][l+r-i], r-i+z);
      while(i-k-z>=0 && i+k<n && s[i-k-z]==s[i+k]) ++k;
      d[z][i-z] = k--;
      if (i+k > r) l = i-k-z, r = i+k;
    }
  }
  swap(d[0], d[1]);
  return d;
}

