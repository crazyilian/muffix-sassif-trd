struct edge {
    int v, f, c, ind;
};

vector<edge> g[MAXN];

bool bfs(int start, int final, int W) {
    vector<int> d(MAXN, INF);
    vector<pair<int, int>> pred(MAXN);
    d[start] = 0;
    deque<int> q = {start};
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        for (int i = 0; i < (int) g[v].size(); i++) {
            auto e = g[v][i];
            if (e.f + W <= e.c && d[e.v] > d[v] + 1) {
                d[e.v] = d[v] + 1;
                pred[e.v] = {v, i};
                q.push_back(e.v);
            }
        }
    }
    if (d[final] == INF) {
        return false;
    }
    int v = final;
    int x = INF;
    while (v != start) {
        int ind = pred[v].second;
        v = pred[v].first;
        x = min(x, g[v][ind].c - g[v][ind].f);
    }
    v = final;
    while (v != start) {
        int ind = pred[v].second;
        v = pred[v].first;
        g[v][ind].f += x;
        g[g[v][ind].v][g[v][ind].ind].f -= x;
    }
    return true;
}

signed main() {
    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        g[u].push_back({v, 0, c, (int) g[v].size()});
        g[v].push_back({u, 0, 0, (int) g[u].size() - 1});
    }
    int W = (1 << 30);
    do {
        while (bfs(1, n, W));
        W /= 2;
    } while (W >= 1);
    int res = 0;
    for (auto e : g[1]) {
        res += e.f;
    }
}

