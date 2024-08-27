vector<int> mu(n + 1);
mu[1] = 1;
for (int x = 1; x <= n; x++) {
  for (int y = x + x; y <= n; y += x) mu[y] -= mu[x];
}
