struct Hashmap {
  using K = int; using V = int; using cK = const K;
  static constexpr K EMP = INT_MIN; // forbidden value
  static constexpr unsigned RND = 1791791791; // random odd
  int lg, m;
  vector<K> kk; vector<V> vv; // K kk[SZ]; V vv[SZ];
  K *k; V *v;

  Hashmap(int n) { // max size
    lg = 32 - __builtin_clz(n) + 2; // <8n, mem-perf tradeoff
    m = (1<<lg)-1;
    kk.assign(m+1, EMP); vv.resize(m+1); // fill(kk,kk+s,EMP);
    k=kk.data(), v=vv.data(); // k=kk,v=vv;
  }
  int h(cK &x) { return unsigned(x)*RND>>(32-lg); }
  int pos(cK &x) {
    int i = h(x);
    while (k[i]!=EMP && k[i]!=x) i=(i+1)&m;
    return i;
  }
  V* getptr(cK &x) { int i = pos(x); return k[i]==x?v+i:0; }
  V &get(cK &x) { return *getptr(x); }
  void set(cK &x, const V &y) { int i=pos(x);k[i]=x;v[i]=y; }
  bool erase(cK &x) {
    int i = pos(x);
    if (k[i]!=x) return 0;
    for (int j=(i+1)&m; k[j]!=EMP; j=(j+1)&m) {
      int r = h(k[j]);
      if (((j-r)&m) > ((i-r)&m))
        swap(k[i],k[j]), swap(v[i],v[j]), i=j;
    }
    return k[i]=EMP, 1;
  }
};

