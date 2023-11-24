const int SIGMA = 26;
int ans = 0;

struct Node {
  int go[SIGMA];
  int s, p;
  int len;

  Node() {
    fill(go, go + SIGMA, -1);
    s = -1, p = -1;
    len = 0;
  }
};

int add(int A, int ch, vector<Node> &sa) {
  int B = sa.size();
  sa.emplace_back();
  sa[B].p = A;
  sa[B].s = 0;
  sa[B].len = sa[A].len + 1;
  for (; A != -1; A = sa[A].s) {
    if (sa[A].go[ch] == -1) {
      sa[A].go[ch] = B;
      continue;
    }
    int C = sa[A].go[ch];
    if (sa[C].p == A) {
      sa[B].s = C;
      break;
    }
    int D = sa.size();
    sa.emplace_back();
    sa[D].s = sa[C].s;
    sa[D].p = A;
    sa[D].len = sa[A].len + 1;
    sa[C].s = D;
    sa[B].s = D;
    copy(sa[C].go, sa[C].go + SIGMA, sa[D].go);
    for (; A != -1 && sa[A].go[ch] == C; A = sa[A].s)
      sa[A].go[ch] = D;
    break;
  }
  ans += sa[B].len - sa[sa[B].s].len;
  return B;
}

signed main() {
  string s;
  cin >> s;
  vector<Node> sa(1);
  int A = 0;
  for (char c : s)
    A = add(A, c - 'a', sa);
  cout << ans;
}
