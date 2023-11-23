vector<int> lis(vector<int> a) { // 0-indexation ({a_0, ..., a_{n-1}})
  int n = (int) a.size();
  vector<int> dp(n + 1, INF), ind(n + 1), par(n + 1); // INF > all a[i] required
  ind[0] = -INF;
  dp[0] = -INF;
  for (int i = 0; i < n; i++) {
    int l = upper_bound(dp.begin(), dp.end(), a[i]) - dp.begin();
    if (dp[l - 1] < a[i] && a[i] < dp[l]) {
      dp[l] = a[i];
      ind[l] = i;
      par[i] = ind[l - 1];
    }
  }
  vector<int> ans; // exact values
  for (int l = n; l >= 0; l--) {
    if (dp[l] < INF) {
      int pi = ind[l];
      ans.resize(l);
      for (int i = 0; i < l; i++) {
        ans[i] = a[pi]; // =pi if need indices
        pi = par[pi];
      }
      reverse(ans.begin(), ans.end());
      return ans;
    }
  }
  return {};
}
