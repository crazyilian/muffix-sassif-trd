void dfs(int v, int par) {
    vis[v] = 1;
    up[v] = tin[v] = timer++;
    for (auto u : g[v]) {
        if (!vis[u]) {
            dfs(u, v);
            up[v] = min(up[v], up[u]);
        } else if (u != par) {
            up[v] = min(up[v], tin[u]);
        }
        if (up[u] > tin[v]) {
            bridges.emplace_back(v, u);
        }
    }
}

