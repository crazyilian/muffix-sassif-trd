// Быстрое взятие по НЕ константному модулю (в 1.5-1.9 раза быстрее)
struct FastMod {
  ull b, m;
  FastMod(ull b) : b(b), m(-1ULL / b) {}
  ull reduce(ull a) const {
      ull r = a - (ull)((__uint128_t(m) * a) >> 64) * b;
      return r;  // r in [0, 2b) // x1.9 speed
      return r >= b ? r - b : r; // x1.5 speed
  }
}; // Usage:
// FastMod F(m);
// ull x_mod_m = F.reduce(x);
