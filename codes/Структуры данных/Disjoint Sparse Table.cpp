int LOG[N];
int ST[N][L];
int CNT[N][L];
for (int i = 2; i < N; i++) {
  LOG[i] = LOG[i / 2] + 1;
}
int n;
cin >> n;
int norig = n;
int n2 = (1 << (LOG[n] + 1));
n = n2;
vector<int> A(n, -1);
for (int i = 0; i < norig; i++) {
  cin >> A[i];
}
for (int level = 0; level < L; level++) {
  int m = n / (1 << level);
  if (m == 0) break;
  for (int i = 0; i < n; i++) {
    if (i % m == 0 && ((i / m) % 2 == 1)) {
      ST[level][i] = A[i];
      CNT[level][i] = 1;
    } else if ((i / m) % 2 == 1) {
      if (ST[level][i - 1] == A[i]) {
        ST[level][i] = A[i];
        CNT[level][i] = CNT[level][i - 1] + 1;
      } else if (ST[level][i - 1] < A[i]) {
        ST[level][i] = A[i];
        CNT[level][i] = 1;
      } else {
        ST[level][i] = ST[level][i - 1];
        CNT[level][i] = CNT[level][i - 1];
      }
    }
  }
  for (int i = n - 1; i >= 0; i--) {
    if (i % m == m - 1 && ((i / m) % 2 == 0)) {
      ST[level][i] = A[i];
      CNT[level][i] = 1;
    } else if (((i / m) % 2 == 0)) {
      if (ST[level][i + 1] == A[i]) {
        ST[level][i] = A[i];
        CNT[level][i] = CNT[level][i + 1] + 1;
      } else if (ST[level][i + 1] < A[i]) {
        ST[level][i] = A[i];
        CNT[level][i] = 1;
      } else {
        ST[level][i] = ST[level][i + 1];
        CNT[level][i] = CNT[level][i + 1];
      }
    }
  }
}
{ // query
  int l, r;
  if (l > r) swap(l, r);
  if (l == r) {
    return 1; // answer
  } else {
    int xr = l ^ r;
    int level = LOG[n] - LOG[xr];
    int max1 = ST[level][l], cnt1 = CNT[level][l], max2 = ST[level][r], cnt2 = CNT[level][r];
    if (max1 == max2) {
      return cnt1 + cnt2; // answer
    } else if (max1 > max2) {
      return cnt1; // answer
    } else {
      return cnt2; // answer
    }
  }
}
