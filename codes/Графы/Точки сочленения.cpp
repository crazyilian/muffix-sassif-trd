void dfs(int v, int par) {
    vis[v] = 1;
    up[v] = tin[v] = timer++;
    int child = 0;
    for (auto u : g[v]) {
        if (!vis[u]) {
            dfs(u, v);
            up[v] = min(up[v], up[u]);
            if (up[u] >= tin[v] && par != -1) {
                points.insert(v);
            }
            child++;
        } else if (u != par) {
            up[v] = min(up[v], tin[u]);
        }
    }
    if (par == -1 && child >= 2) {
        points.insert(v);
    }
}

