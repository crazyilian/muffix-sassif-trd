// __builtin_ctz = Count Trailing Zeroes
// __builtin_clz = Count Leading Zeroes
// both are UB in gcc when pass 0
struct custom_bitset {
  vector<uint64_t> bits;
  int b, n;

  custom_bitset(int _b = 0) {
    init(_b);
  }
  void init(int _b) {
    b = _b, n = (b + 63) / 64;
    bits.assign(n, 0);
  }
  void clear() {
    b = n = 0;
    bits.clear();
  }
  void reset() {
    bits.assign(n, 0);
  }
  void _clean() {
    // Reset all bits after `b`.
    if (b != 64 * n)
      bits.back() &= (1LLU << (b - 64 * (n - 1))) - 1;
  }
  bool get(int i) const {
    return bits[i / 64] >> (i % 64) & 1;
  }
  void set(int i, bool value) {
    // assert(0 <= i && i < b);
    bits[i / 64] &= ~(1LLU << (i % 64));
    bits[i / 64] |= uint64_t(value) << (i % 64);
  }

  // Simulates `bs |= bs << shift;`
  // `|=` can be replaced with `^=`, `&=`, `=`
  void or_shift_left(int shift) {
    int div = shift / 64, mod = shift % 64;
    if (mod == 0) {
      for (int i = n - 1; i >= div; i--)
        bits[i] |= bits[i - div];
    } else {
      for (int i = n - 1; i >= div + 1; i--)
        bits[i] |= bits[i - (div + 1)] >> (64 - mod) | bits[i - div] << mod;
      if (div < n)
        bits[div] |= bits[0] << mod;
    }
    // if `&=`, `=`
    //fill(bits.begin(), bits.begin() + min(div, n), 0);
    _clean();
  }

  // Simulates `bs |= bs >> shift;`
  // `|=` can be replaced with `^=`, `&=`, `=`
  void or_shift_right(int shift) {
    int div = shift / 64, mod = shift % 64;
    if (mod == 0) {
      for (int i = div; i < n; i++)
        bits[i - div] |= bits[i];
    } else {
      for (int i = 0; i < n - (div + 1); i++)
        bits[i] |= bits[i + (div + 1)] << (64 - mod) | bits[i + div] >> mod;
      if (div < n)
        bits[n - div - 1] |= bits[n - 1] >> mod;
    }
    // if `&=`, `=`
    //fill(bits.end() - min(div, n), bits.end(), 0);
    _clean();
  }

  // find min j, that j >= i and bs[j] = 1;
  int find_next(int i) {
    if (i >= b) return b;
    int div = i / 64, mod = i % 64;
    auto x = bits[div] >> mod;
    if (x != 0)
      return i + __builtin_ctzll(x);
    for (auto k = div + 1; k < n; ++k) {
      if (bits[k] != 0)
        return 64 * k + __builtin_ctzll(bits[k]);
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
