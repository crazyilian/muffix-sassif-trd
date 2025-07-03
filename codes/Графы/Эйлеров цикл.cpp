// Эйлеров путь/цикл в компоненте связности s. Возвращает индексы рёбер. Если пути/цикла нет, то алгос найдёт хуйню.
// Если неориентированный граф, то edges[ei] и edges[ei ^ 1] - обратные друг к другу рёбра.
// edges[graph[v][i]] = {v, u}
vector<int> eulerpath1(int s, vector<vector<int>> &graph, vector<pair<int, int>> &edges, vector<char> &used, vector<int> &start) {
  vector<pair<int, int>> st = {{-1, s}};
  vector<int> res;
  while (!st.empty()) {
    auto [ei, v] = st.back();
    while (start[v] < graph[v].size() && used[graph[v][start[v]]])
      start[v]++;
    if (start[v] == graph[v].size()) {
      if (ei != -1) res.push_back(ei ^ 1);
      st.pop_back();
    } else {
      int ej = graph[v][start[v]++];
      used[ej] = true;
      used[ej ^ 1] = true; // Удалить если ориент. граф
      st.emplace_back(ej, edges[ej].second);
    }
  }
  return res;
}

vector<char> used(edges.size(), false);
vector<int> start(graph.size(), 0);
for (int v = 0; v < graph.size(); ++v) {
  // Если ориентированный граф, второе условие заменить на cnt_in[v] >= cnt_out[v]
  if (start[v]==graph[v].size() || graph[v].size()%2==0)
    continue;
  auto path = eulerpath1(v, graph, edges, used, start);
}
for (int v = 0; v < graph.size(); ++v) {
  if (start[v] == graph[v].size())
    continue;
  auto cycle = eulerpath1(v, graph, edges, used, start);
}

