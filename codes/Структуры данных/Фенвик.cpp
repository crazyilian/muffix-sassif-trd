// Нумерация с 0

struct FenwickTree {
  int n;
  vector<vector<vector<int>>> ft;

  FenwickTree(int n) : n(n) {
    ft.resize(n + 1, vector<vector<int>>(n + 1, vector<int>(n + 1)));
  }

  // a[x][y][z] += d
  void upd(int x, int y, int z, int d) {
    x++, y++, z++;
    for (int x1 = x; x1 <= n; x1 += x1 & -x1) {
      for (int y1 = y; y1 <= n; y1 += y1 & -y1) {
        for (int z1 = z; z1 <= n; z1 += z1 & -z1) {
          ft[x1][y1][z1] += d;
        }
      }
    }
  }

  // sum a[0..x)[0..y)[0..z)
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

  // sum a[x1..x2)[y1..y2)[z1..x2)
  int sum_3d(int x1, int x2, int y1, int y2, int z1, int z2) {
    int ans = rsq(x2, y2, z2);
    ans -= rsq(x1, y2, z2) + rsq(x2, y1, z2) + rsq(x2, y2, z1);
    ans += rsq(x1, y1, z2) + rsq(x1, y2, z1) + rsq(x2, y1, z1);
    ans -= rsq(x1, y1, z1);
    return ans;
  }
};
