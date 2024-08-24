// Быстрое взятие по НЕ константному модулю (~1.5 раза быстрее)
struct FastMod {
  ull mod, wtf;
  FastMod(ull mod) : mod(mod), wtf((__uint128_t(1) << 64) / mod) {}
  ull reduce(ull a) const {
    ull q = ((__uint128_t)wtf * a) >> 64;
    ull r = a - q * mod;
    return r >= mod ? r - mod : r;
  }
}; // Usage:
// FastMod F(m);
// ull x_mod_m = F.reduce(x);

