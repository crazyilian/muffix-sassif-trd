struct SparseTable {
  vector<vector<int>> st;
  vector<int> max2;

  SparseTable(vector<int> &a) {
    int n = a.size();
    st.push_back(a);
    for (int i = 1; (1 << i) <= n; i++) {
      st.emplace_back(n - (1 << i) + 1);
      for (int p = 0; p < st[i].size(); p++) {
        st[i][p] = min(st[i - 1][p], st[i - 1][p + (1 << (i - 1))]);
      }
      st.push_back(st[i - 1]);
      for (int p = 0; p + (1 << (i - 1)) <= n; ++p) {
        st[i][p] = min(st[i - 1][p], st[i - 1][p + (1 << (i - 1))]);
      }
    }
    // max2[i] = i ? (32 - __builtin_clz(i - 1)) : 0
    max2.resize(n + 1);
    max2[0] = -1;
    max2[1] = 0;
    for (int i = 2; i <= n; i++)
      max2[i] = max2[i / 2] + 1;
  }

  // min a[l..r)
  int rmq(int l, int r) {
    int i = max2[r - l];
    return min(st[i][l], st[i][r - (1 << i)]);
  }
};
