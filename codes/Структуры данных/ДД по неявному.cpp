// потому что nds[0].sz == 0 и sz не изменяется в push
int size(int t) { return nds[t].sz; }

pair<int, int> split(int t, int k) {
  if (!t) return {0, 0};
  push(t);
  int szl = size(nds[t].l);
  if (k <= szl) {
    auto [l, r] = split(nds[t].l, k);
    nds[t].l = r;
    pull(t);
    return {l, t};
  } else {
    auto [l, r] = split(nds[t].r, k - szl - 1);
    nds[t].r = l;
    pull(t);
    return {t, r};
  }
}

// всё остальное ровно как в обычном ДД
// не забыть обновлять sz в pull 
// инициализация sz=0 в Node() и sz=1 в Node(...)


