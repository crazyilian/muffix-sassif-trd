vector<edge> g[MAXN];
pair<int, int> pred[MAXN];
int d[MAXN];
int inds[MAXN];

bool dfs(int v, int final, int W) {
    if (v == final) {
        return true;
    }
    for (int i = inds[v]; i < (int) g[v].size(); i++) {
        auto e = g[v][i];
        if (e.f + W <= e.c && d[v] + 1 == d[e.v]) {
            pred[e.v] = {v, i};
            bool flag = dfs(e.v, final, W);
            if (flag) {
                return true;
            }
            inds[v]++;
        } else {
            inds[v]++;
        }
    }
    return false;
}

bool bfs(int start, int final, int W) {
    fill(d, d + MAXN, INF);
    d[start] = 0;
    deque<int> q = {start};
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        for (auto e : g[v]) {
            if (e.f + W <= e.c && d[e.v] > d[v] + 1) {
                d[e.v] = d[v] + 1;
                q.push_back(e.v);
            }
        }
    }
    if (d[final] == INF) {
        return false;
    }
    fill(inds, inds + MAXN, 0);
    while (dfs(start, final, W)) {
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
    }
    return true;
}

void Dinic(int start, int final) {
    int W = (1LL << 30);
    do {
        while (bfs(start, final, W));
        W /= 2;
    } while (W >= 1);
}

signed main() {
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        edges.emplace_back(u, v);
        g[u].push_back({v, 0, c, (int) g[v].size()});
        g[v].push_back({u, 0, c, (int) g[u].size() - 1});
    }
    Dinic(1, n);
    int res = 0;
    for (auto e : g[1]) {
        res += e.f;
    }
    vector<int> ans;
    for (int i = 0; i < m; i++) {
        int u = edges[i].first, v = edges[i].second;
        if ((d[u] != INF && d[v] == INF) || (d[u] == INF && d[v] != INF)) {
            ans.push_back(i + 1);
        }
    }
}

