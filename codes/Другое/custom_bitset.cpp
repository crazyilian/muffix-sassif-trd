// __builtin_ctz = Count Trailing Zeroes
// __builtin_clz = Count Leading Zeroes
// both are UB in gcc when pass 0
struct custom_bitset {
  vector<uint64_t> bits;
  int b, n;

  custom_bitset(int bb = 0) { init(bb); }
  void init(int bb) {
    b = bb, n = (b + 63) / 64;
    bits.assign(n, 0);
  }
  void clear() { b = n = 0, bits.clear(); }
  void reset() { bits.assign(n, 0); }
  void _clean() {
    // Reset all bits after `b`.
    if (b % 64)
      bits.back() &= (1LLU << (b % 64)) - 1;
  }
  bool get(int i) const {
    return bits[i / 64] >> (i % 64) & 1;
  }
  void set(int i, bool value) {
    // assert(0 <= i && i < b);
    bits[i / 64] &= ~(1LLU << (i % 64));
    bits[i / 64] |= uint64_t(value) << (i % 64);
  }

  // Simulates `bs1 |= bs2 << s;`
  // `|=` can be replaced with `^=`, `&=`, `=`
  void or_shift_left(int s){return or_shift_left(*this,s);}
  void or_shift_left(const custom_bitset &o, int s) {
    // assert(s >= 0);
    int d = s/64, r = s%64;
    if (r == 0) {
      for (int i = n-1; i >= d; --i)
        bits[i] |= o.bits[i-d];
    } else {
      for (int i = n-1; i >= d+1; --i)
        bits[i] |= o.bits[i-d-1]>>(64-r) | o.bits[i-d]<<r;
      if (d < n)
        bits[d] |= o.bits[0]<<r;
    }
    // if `&=`, `=`
    //fill(bits.begin(), bits.begin() + min(d, n), 0);
    _clean();
  }

  // Simulates `bs1 |= bs2 >> s;`
  // `|=` can be replaced with `^=`, `&=`, `=`
  void or_shift_right(int s){return or_shift_right(*this,s);}
  void or_shift_right(const custom_bitset &o, int s) {
    // assert(s >= 0);
    int d = s/64, r = s%64;
    if (r == 0) {
      for (int i = d; i < n; ++i)
        bits[i-d] |= o.bits[i];
    } else {
      for (int i = 0; i < n-d-1; ++i)
        bits[i] |= o.bits[i+d+1]<<(64-r) | o.bits[i+d]>>r;
      if (d < n)
        bits[n-d-1] |= o.bits[n-1]>>r;
    }
    // if `&=`, `=`
    //fill(bits.end() - min(d, n), bits.end(), 0);
    _clean();
  }

  // find min j, that j >= i and bs[j] = 1;
  int find_next(int i) {
    i = max(i,0);
    if (i >= b) return b;
    int d = i/64, r = i%64;
    auto x = bits[d]>>r;
    if (x != 0)
      return i + __builtin_ctzll(x);
    for (auto k = d+1; k < n; ++k) {
      if (bits[k] != 0)
        return 64*k + __builtin_ctzll(bits[k]);
    }
    return b;
  }

  // `|=` can be replaced with `&=`, `^=`
  custom_bitset &operator|=(const custom_bitset &other){
    // assert(b == other.b);
    for (int i = 0; i < n; i++)
      bits[i] |= other.bits[i];
    return *this;
  }
};
