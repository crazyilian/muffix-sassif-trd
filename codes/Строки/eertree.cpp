int len[MAXN], suf[MAXN];
int go[MAXN][ALPH];
char s[MAXN];

int n, last, sz;

void init() {
  n = 0, last = 0;
  s[n++] = -1;
  suf[0] = 1; // root of suflink tree = 1
  len[1] = -1;
  sz = 2;
}

int get_link(int v) {
  while (s[n - len[v] - 2] != s[n - 1])
    v = suf[v];
  return v;
}

void add_char(char c, int to_sm) {
  c -= 'a';
  s[n++] = c;
  last = get_link(last);
  if (!go[last][c]) {
    len[sz] = len[last] + 2;
    suf[sz] = go[get_link(suf[last])][c];
    go[last][c] = sz++;
  }
  last = go[last][c]; // cur v = last
}
