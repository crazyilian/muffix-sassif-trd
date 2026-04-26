// n=1e6, a<1e18, B=2^12, iters=5, time=17ms
// n=1e7, a<1e18, B=2^12, iters=5, time=190ms
// n=1e8, a<1e18, B=2^12, iters=5, time=1.9s
// n=1e6, a<1e9, B=2^10, iters=3, time=10ms
// n=1e7, a<1e9, B=2^10, iters=3, time=120ms
// n=1e8, a<1e9, B=2^10, iters=3, time=1.2s
void radix_sort(vector<ll> &a) {
  // оптимальный $B \approx 2^{10} - 2^{12}$, не обязательно степень 2
  // $0 \leq a < B^{iters}$
  // далее можно уменьшить $B$ сохраняя такой же $iters$
  const signed B = 1 << 12;
  static signed c[B + 1];
  vector<ll> b(a.size());
#define PASS(key) { \
  memset(c, 0, sizeof c); \
  for (auto x : a) ++c[(key)+1]; \
  for (signed i = 1; i <= B; ++i) { c[i]+=c[i-1]; } \
  for (auto x : a) b[c[key]++] = x; \
  swap(a,b); \
}
  PASS(x%B);
  PASS(x/B%B);
  PASS(x/B/B%B);
  PASS(x/B/B/B%B);
  PASS(x/B/B/B/B);
#undef PASS
}

