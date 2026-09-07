// strict LIS, returns indices
vector<int> calc_lis(const vector<int> &a) {
  vector<int> dp, ind, par(a.size());
  dp.reserve(a.size()), ind.reserve(a.size());
  for (int i = 0; i < a.size(); ++i) {
    // upper_bound for non-strict LIS
    int len = lower_bound(all(dp), a[i]) - dp.begin();
    par[i] = len ? ind[len - 1] : -1;
    if (len == dp.size()) {
      dp.pb(a[i]);
      ind.pb(i);
    } else {
      dp[len] = a[i];
      ind[len] = i;
    }
  }
  int len = dp.size();
  vector<int> ans(len);
  if (len==0) return ans;
  for (int i = len-1, j=ind.back(); i>=0; j=par[j], --i)
    ans[i] = j;
  return ans;
}
