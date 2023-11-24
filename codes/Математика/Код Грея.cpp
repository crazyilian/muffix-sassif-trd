for (int i = 0; i < (1 << n); i++) {
  gray[i] = i ^ (i >> 1);
}
