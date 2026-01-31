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
      if (i+k>r) l=i-k-z, r=i+k;
    }
  }
  swap(d[0], d[1]);
  return d;
}
