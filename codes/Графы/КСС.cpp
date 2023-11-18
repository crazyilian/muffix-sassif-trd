void dfs1(int v) {
    vis[v] = 1;
    for (auto u : g[v]) {
        if (!vis[u]) {
            dfs1(u);
        }
    }
    topsort.push_back(v);
}

void dfs2(int v) {
    vis[v] = 1;
    for (auto u : rg[v]) {
        if (!vis[u]) {
            dfs2(u);
        }
    }
    comp.push_back(v);
}

signed main() {
    for (int i = 1; i <= n; i++)
        if (!vis[i])
            dfs1(i);
    reverse(topsort.begin(), topsort.end());
    for (int j = 1; j <= n; j++) {
        int vert = topsort[j - 1];
        if (!vis[vert])
            dfs2(vert);
    }
}


