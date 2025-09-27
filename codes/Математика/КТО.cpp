// ans % p_i = a_i
vector<vector<int>> r(k, vector<int>(k));
for (int i = 0; i < k; ++i)
  for (int j = 0; j < k; ++j)
    if (i != j)
      r[i][j] = binpow(p[i] % p[j], p[j] - 2, p[j]); // [phi(p[j]) - 1] для не простого модуля
vector<int> x(k);
for (int i = 0; i < k; ++i) {
  x[i] = a[i];
  for (int j = 0; j < i; ++j) {
    x[i] = r[j][i] * (x[i] - x[j]);
    x[i] = x[i] % p[i];
    if (x[i] < 0) x[i] += p[i];
  }
}
int ans = 0;
for (int i = 0; i < k; ++i) {
  int val = x[i];
  for (int j = 0; j < i; ++j) val *= p[j];
  ans += val;
}
