vector<int> venger(vector<vector<int>> arr) {
    int n = (int) arr.size() - 1;
    vector<int> u(n + 1), v(n + 1), p(n + 1), way(n + 1);
    for (int i = 1; i <= n; i++) {
        p[0] = i;
        int ind = 0;
        vector<int> minv(n + 1, INF), used(n + 1);
        do {
            used[ind] = 1;
            int ind2 = p[ind], dlt = INF, ind3 = 0;
            for (int j = 1; j <= n; j++)
                if (!used[j]) {
                    int cur = arr[ind2][j] - u[ind2] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = ind;
                    }
                    if (minv[j] < dlt) {
                        dlt = minv[j], ind3 = j;
                    }
                }
            for (int j = 0; j <= n; j++)
                if (used[j]) {
                    u[p[j]] += dlt;
                    v[j] -= dlt;
                } else {
                    minv[j] -= dlt;
                }
            ind = ind3;
        } while (p[ind] != 0);
        do {
            int ind3 = way[ind];
            p[ind] = p[ind3];
            ind = ind3;
        } while (ind);
    }
    vector<int> ans(n + 1);
    for (int j = 1; j <= n; j++) {
        ans[p[j]] = j;
    }
    return ans;
}

