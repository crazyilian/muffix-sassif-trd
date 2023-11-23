vector<int> LCIS(vector<int> a, vector<int> b) { // 1-indexation ({0, a_1, ..., a_n}, {0, b_1, ..., b_m})
  int n = (int) a.size() - 1, m = (int) b.size() - 1;
  vector<int> dp(m + 1), dp2(m + 1), par(m + 1);
  for (int i = 1; i <= n; i++) {
    int best = 0, best_idx = 0;
    for (int j = 1; j <= m; j++) {
      dp2[j] = dp[j];
      if (a[i] == b[j]) {
        dp2[j] = max(dp2[j], best + 1);
        par[j] = best_idx;
      }
      if (a[i] > b[j] && best < dp[j]) {
        best = dp[j];
        best_idx = j;
      }
    }
    swap(dp, dp2);
  }
  int pj = 0;
  for (int j = 1; j <= m; j++) {
    if (dp[pj] < dp[j]) {
      pj = j;
    }
  }
  vector<int> ans; // exact values
  while (pj > 0) {
    ans.push_back(b[pj]);
    pj = par[pj];
  }
  reverse(ans.begin(), ans.end());
  return ans;
}
