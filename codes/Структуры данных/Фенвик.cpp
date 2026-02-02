// Нумерация с 0
struct Fenwick {
  int n;
  vector<int> f;
  Fenwick(int n) : n(n), f(n+1) {}
 
  // a[i] += x
  void add(int i, int x) {
    for (++i; i <= n; i += i & -i) f[i] += x;
  }
 
  // sum a[0..i)
  int get(int i) {
    int ans = 0;
    for (; i > 0; i -= i & -i) ans += f[i];
    return ans;
  }
 
  // a[..] > 0; find max k: sum a[0..k) <= x
  int max_not_more(int x) {
    int cur = 0;
    for (int i = 20; i >= 0; --i) {
      int len = 1 << i;
      if (cur + len <= n && f[cur + len] <= x) {
        cur += len;
        x -= f[cur];
      }
    }
    return cur;
  }
};

// sum a[x1..x2)[y1..y2)[z1..x2)
int sum_3d(int x1, int x2, int y1, int y2, int z1, int z2) {
  int ans = get(x2, y2, z2);
  ans -= get(x1, y2, z2) + get(x2, y1, z2) + get(x2, y2, z1);
  ans += get(x1, y1, z2) + get(x1, y2, z1) + get(x2, y1, z1);
  ans -= get(x1, y1, z1);
  return ans;
}

// a[l..r) += x
void update(int l, int r, int x) {
  T1.add(l, x);
  T1.add(r, -x);
  T2.add(l, -x * l);
  T2.add(r, x * r);
}
// sum a[0..i)
int get(int i) {
  return T1.get(i) * i + T2.get(i);
}

