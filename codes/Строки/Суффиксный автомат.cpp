// (Обобщённый) суфавтомат с подсчётом кол-ва различных подстрок

const int SIGMA = 26;
long long ans = 0;

struct Node {
  ar(SIGMA) go;
  int s, p, len, firstpos;
  Node() {
    go.fill(-1);
    s=-1, p=-1, len=0, firstpos=-1;
  }
};

int add(int A, int ch, vector<Node> &sa) {
  auto clone = [&](int A, int C) {
    int D = sa.size();
    sa.pb(sa[C]);
    sa[D].p = A;
    sa[D].len = sa[A].len + 1;
    sa[C].s = D;
    for (; A != -1 && sa[A].go[ch] == C; A = sa[A].s)
      sa[A].go[ch] = D;
    return D;
  };
  int C = sa[A].go[ch];
  if (C != -1)
    return sa[C].p == A ? C : clone(A, C);
  int B = sa.size();
  sa.emplace_back();
  sa[B].p = A;
  sa[B].len = sa[A].len + 1;
  sa[B].firstpos = sa[B].len - 1; // no sense when generalized SAM
  for (; A != -1; A = sa[A].s) {
    if (sa[A].go[ch] == -1) {
      sa[A].go[ch] = B;
      continue;
    }
    C = sa[A].go[ch];
    sa[B].s = sa[C].p == A ? C : clone(A, C);
    break;
  }
  if (A == -1) sa[B].s = 0;
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
