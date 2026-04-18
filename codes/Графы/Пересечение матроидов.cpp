template<typename T, typename A, typename B>
vector<T> matroid_intersection(const std::vector<T> &ground_set, const A &matroid1, const B &matroid2) {
  // у B должны быть методы add_extra, independed_without
  // у T должно быть поле w
  // ищет минимальный по весу среди максимальных по размеру
  int n = ground_set.size();
  vector<char> in_set(n), inm1(n), inm2(n);
  vector<pair<ll, int>> dist(n);
  vector<char> inQ(n);
  vector<int> par(n), left, right;
  while (true) {
    // чтобы искать просто минимальный по весу,
    // здесь нужно прорелаксировать ответ
    A m1 = matroid1;
    B m2 = matroid2;
    left.clear();
    right.clear();
    for (int i = 0; i < n; i++)
      if (in_set[i]) {
        m1.add(ground_set[i]);
        m2.add(ground_set[i]);
        left.push_back(i);
      } else {
        right.push_back(i);
      }
    fill(all(inm1), 0);
    fill(all(inm2), 0);
    // bool found = false; // unweighted
    for (int i: right) {
      inm1[i] = m1.independed_with(ground_set[i]);
      inm2[i] = m2.independed_with(ground_set[i]);
      // if (inm1[i] && inm2[i]) { // unweighted
        // in_set[i] = 1;
        // found = true;
        // break;
      // }
    }
    // if (found) continue; // unweighted
    fill(all(dist), pair{INF, INF});
    fill(all(par), -1);
    fill(all(inQ), 0);
    deque<int> que;
    for (int i: right)
      if (inm1[i]) {
        dist[i] = {ground_set[i].w, 0};
        que.push_back(i);
        inQ[i] = 1;
      }
    while (!que.empty()) {
      // if (found) break; // unweighted
      int v = que.front();
      auto [smw, cnte] = dist[v];
      que.pop_front();
      inQ[v] = 0;
      if (in_set[v]) {
        A m = matroid1;
        for (int i: left) if (i != v) m.add(ground_set[i]);
        for (int u: right) {
          auto newdist = pair{smw + ground_set[u].w, cnte + 1};
          if (dist[u] > newdist && m.independed_with(ground_set[u])) {
            par[u] = v;
            dist[u] = newdist;
            // if (inm2[u]) found = true; // unweighted
            if (!inQ[u]) {
              que.push_back(u);
              inQ[u] = 1;
        }}}
      } else {
        B m = m2;
        m.add_extra(ground_set[v]);
        for (auto u: left) {
          auto newdist = pair{smw - ground_set[u].w, cnte + 1};
          if (dist[u] > newdist && m.independed_without(ground_set[u])) {
            par[u] = v;
            dist[u] = newdist;
            if (!inQ[u]) {
              que.push_back(u);
              inQ[u] = 1;
      }}}}
    }
    int bestv = -1;
    for (int v : right) {
      if (inm2[v] && dist[v].first != INF) {
        if (bestv == -1 || dist[bestv] > dist[v]) {
          bestv = v;
    }}}
    if (bestv == -1) break;
    for (; bestv != -1; bestv = par[bestv]) in_set[bestv] ^= 1;
  }
  vector<T> res;
  for (int i = 0; i < n; i++) if (in_set[i]) res.push_back(ground_set[i]);
  return res;
}
