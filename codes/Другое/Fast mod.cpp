// Быстрое взятие по НЕ константному модулю (в 2-4 раза быстрее)
struct FastMod {
  ull b, m;
  FastMod(ull b) : b(b), m(-1ULL / b) {}
  ull mod(ull a) const {
      ull r = a - (ull)((__uint128_t(m) * a) >> 64) * b;
      return r;  // r in [0, 2b) // $\approx$ x3.5 speed
      return r >= b ? r - b : r; // $\approx$ x3 speed
  }
}; // Usage:
// FastMod F(m);
// ull x_mod_m = F.mod(x);
