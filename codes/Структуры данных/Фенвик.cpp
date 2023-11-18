// Нумерация с 1

struct Fenwick_tree {
    vector<vector<vector<int>>> ft;

    Fenwick_tree(int n) {
        ft.resize(n + 1, vector<vector<int>>(n + 1, vector<int>(n + 1)));
    }

    void upd(int x, int y, int z, int d) {
        for (int x1 = x; x1 < ft.size(); x1 += x1 & -x1) {
            for (int y1 = y; y1 < ft[x1].size(); y1 += y1 & -y1) {
                for (int z1 = z; z1 < ft[x1][y1].size(); z1 += z1 & -z1) {
                    ft[x1][y1][z1] += d;
                }
            }
        }
    }

    int rsq(int x, int y, int z) {
        int ans = 0;
        for (int x1 = x; x1 > 0; x1 -= x1 & -x1) {
            for (int y1 = y; y1 > 0; y1 -= y1 & -y1) {
                for (int z1 = z; z1 > 0; z1 -= z1 & -z1) {
                    ans += ft[x1][y1][z1];
                }
            }
        }
        return ans;
    }

    int sum_3d(int x1, int x2, int y1, int y2, int z1, int z2) {
        int ans = rsq(x2, y2, z1 - 1) + rsq(x1 - 1, y2, z2) - rsq(x1 - 1, y2, z1 - 1);
        ans += rsq(x2, y1 - 1, z2);
        ans -= rsq(x2, y1 - 1, z1 - 1) + rsq(x1 - 1, y1 - 1, z2) - rsq(x1 - 1, y1 - 1, z1 - 1);
        return rsq(x2, y2, z2) - ans;
    }
};

