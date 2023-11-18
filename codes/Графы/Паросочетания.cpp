bool dfs(int v, int c) {
    if (used[v] == c) return false;
    used[v] = c;
    for (auto u : g[v]) {
        if (res[u] == -1) {
            res[u] = v;
            return true;
        }
    }
    for (auto u : g[v]) {
        if (dfs(res[u], c)) {
            res[u] = v;
            return true;
        }
    }
    return false;
}

signed main() {
    for (int i = 0; i < s; ++i) {
        ans += dfs(i, i + 1);
    }
}

