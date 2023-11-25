vector<int> prefix_func(string s) {
  int n = s.size();
  vector<int> pref(n, 0);
  int ans = 0;
  for (int i = 1; i < n; i++) {
    while (ans > 0 && s[ans] != s[i]) {
      ans = pref[ans - 1];
    }
    if (s[i] == s[ans]) {
      ans++;
    }
    pref[i] = ans;
  }
  return pref;
}
