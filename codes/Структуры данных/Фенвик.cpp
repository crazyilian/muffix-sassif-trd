// Нумерация с 0
struct Fenwick {
  int n;
  vector<int> f;
  Fenwick(int n) : n(n), f(n+1) {}

  void build(const vector<int> &a) { // O(n)
    assert(ssize(a) == n);
    f.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
      f[i] += a[i-1];
      int j = i + (i & -i);
      if (j <= n) f[j] += f[i];
    }
  }

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

  // n > 0, a[..] >= 0,   pref[i] = a[0] + ... + a[i]
  // lower_bound по pref: min i, что pref[i] >= x (либо n)
  int lower_bound(int x) {
    int i = 0;
    for (int b = 31 - __builtin_clz(n); b >= 0; --b) {
      int d = 1 << b;
      if (i + d <= n && f[i + d] < x) {
        i += d;
        x -= f[i];
      }
    }
    return i;
  }
};

// sum a[x1..x2)[y1..y2)[z1..z2)
int sum_3d(int x1,int x2,int y1,int y2,int z1,int z2) {
  int ans = get(x2, y2, z2);
  ans -= get(x1,y2,z2) + get(x2,y1,z2) + get(x2,y2,z1);
  ans += get(x1,y1,z2) + get(x1,y2,z1) + get(x2,y1,z1);
  ans -= get(x1,y1,z1);
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
