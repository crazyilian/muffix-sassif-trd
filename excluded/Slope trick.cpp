// Дан массив $a_n$. Сделать минимальное кол-во $\pm 1$, чтобы $a_n$ стал неубывающим.

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  int ans = 0;
  multiset<int> now;
  for (int i = 0; i < n; i++) {
    now.insert(a[i]);
    ans += (*now.rbegin() - a[i]);
    now.erase(now.find(*now.rbegin()));
    now.insert(a[i]);
  }
  cout << ans << '\n';
}
