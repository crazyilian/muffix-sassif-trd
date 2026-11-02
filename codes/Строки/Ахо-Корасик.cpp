const int SIGMA = 26; // letters from 'a'
struct AhoCorasick {
  vector<array<int, SIGMA>> go;
  vector<int> par, suf;
  vector<char> par_c;
  vector<vector<int>> term, g; // g: suffix link tree
  int cntv = 1, cnt_s = 0;
  // maxn >= sum of lengths + 1
  AhoCorasick(int maxn) : go(maxn), par(maxn), suf(maxn),
      par_c(maxn), term(maxn), g(maxn) {}

  // returns node of s, term[v] = ids of strings (from 0)
  int add(const string &s) {
    int v = 0;
    for (char el : s) {
      if (go[v][el - 'a'] == 0) {
        go[v][el - 'a'] = cntv;
        par[cntv] = v;
        par_c[cntv] = el;
        cntv++;
      }
      v = go[v][el - 'a'];
    }
    term[v].pb(cnt_s++);
    return v;
  }

  void bfs() {
    vector<int> q(cntv); // q[0] = 0
    for (int l = 0, r = 1; l < r; ++l) {
      int v = q[l];
      if (v > 0) g[suf[v]].pb(v);
      for (int c = 0; c < SIGMA; c++) {
        int &u = go[v][c];
        if (u == 0) u = go[suf[v]][c];
        else suf[u] = v ? go[suf[v]][c] : 0, q[r++] = u;
      }
    }
  }
};
