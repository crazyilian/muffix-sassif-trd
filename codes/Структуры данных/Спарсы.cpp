struct Sparse_Table {
    vector<vector<int>> st;
    vector<int> max2;

    Sparse_Table(vector<int> &a) {
        int n = a.size();
        st.emplace_back();
        for (int i = 0; i < n; i++) {
            st[0].push_back(a[i]);
        }
        for (int i = 1; (1 << i) <= n; i++) {
            st.emplace_back();
            for (int p = 0; p + (1 << i) <= n; p++) {
                st[i].push_back(min(st[i - 1][p], st[i - 1][p + (1 << (i - 1))]));
            }
        }
        max2.resize(n + 1);
        max2[1] = 0;
        for (int i = 2; i <= n; i++) {
            max2[i] = max2[i / 2] + 1;
        }
    }

    int rmq(int l, int r) {
        r++;
        int i = max2[r - l];
        return min(st[i][l], st[i][r - (1 << i)]);
    }
};

