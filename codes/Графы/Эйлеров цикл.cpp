// Эйлеров путь/цикл в компоненте связности s. Возвращает индексы рёбер. Если пути/цикла нет, то алгос найдёт фигню.
// Если неориентированный граф, то edges[ei] и edges[ei ^ 1] - обратные друг к другу рёбра.
// edges[g[v][i]] = {v, u}
vector<int> eulerpath1(int s, vector<vector<int>> &g, vector<pair<int, int>> &edges, vector<char> &used, vector<int> &start) {
  vector<pair<int, int>> st = {{-1, s}};
  vector<int> res;
  while (!st.empty()) {
    auto [ei, v] = st.back();
    while (start[v] < g[v].size() && used[g[v][start[v]]])
      start[v]++;
    if (start[v] == g[v].size()) {
      if (ei != -1) res.pb(ei);
      st.pop_back();
    } else {
      int ej = g[v][start[v]++];
      used[ej] = true;
      used[ej ^ 1] = true; // Удалить если ориент. граф
      st.emplace_back(ej, edges[ej].second);
    }
  }
  reverse(all(res));
  return res;
}

vector<char> used(edges.size(), false);
vector<int> start(g.size(), 0);
for (int v = 0; v < g.size(); ++v) {
  // Если ориентированный граф, второе условие заменить на cnt_in[v] >= cnt_out[v]
  if (start[v] == g[v].size() || g[v].size() % 2 == 0)
    continue;
  auto path = eulerpath1(v, g, edges, used, start);
}
for (int v = 0; v < g.size(); ++v) {
  if (start[v] == g[v].size()) continue;
  auto cycle = eulerpath1(v, g, edges, used, start);
}
