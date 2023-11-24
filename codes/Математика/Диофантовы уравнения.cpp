tuple<int, int, int> ext_gcd(int a, int b) {
  int x = 1, xx = 0, y = 0, yy = 1;
  while (b) {
    int q = a / b;
    int a_copy = a;
    a = b;
    b = a_copy % b;
    int x_copy = x, y_copy = y;
    x = xx;
    xx = x_copy - xx * q;
    y = yy;
    yy = y_copy - yy * q;
  }
  return {a, x, y};
}

int math_div(int a, int b) {
  int res = a / b;
  if (a % b < 0) --res;
  return res;
}

signed main() {
  int a, b, c;
  // a, b, c in NN !!!
  cin >> a >> b >> c;
  auto [d, k, l] = ext_gcd(a, b);
  int q = c / d;
  int x = q * k, y = q * l;
  if (c % d == 0) {
    x -= math_div(x, (b / d)) * (b / d);
    y = (c - a * x) / b;
    cout << x << ' ' << y << '\n';
  }
}
