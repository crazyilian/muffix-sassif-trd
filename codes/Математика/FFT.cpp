const double PI = acos(-1);
const int LOG = 19;
const int MAXN = 1 << LOG;

struct comp {
    double x, y;
    comp() : x(0), y(0) {}
    comp(double x, double y) : x(x), y(y) {}
    comp(int x) : x(x), y(0) {}
    comp operator+(const comp &o) const {
        return comp(x + o.x, y + o.y);
    }
    comp operator-(const comp &o) const {
        return comp(x - o.x, y - o.y);
    }
    comp operator*(const comp &o) const {
        return comp(x * o.x - y * o.y, x * o.y + y * o.x);
    }
    comp operator/(const int k) const {
        return comp(x / k, y / k);
    }
    comp conj() const {
        return comp(x, -y);
    }
};

comp OMEGA[MAXN + 10];
int tail[MAXN + 10];

comp omega(int n, int k) {
    return OMEGA[MAXN / n * k];
}

void calcomega() {
    for (int i = 0; i < MAXN; ++i) {
        double x = 2 * PI * i / MAXN;
        OMEGA[i] = {cos(x), sin(x)};
    }
}

void calctail() {
    tail[0] = 0;
    for (int i = 1; i < MAXN; ++i) {
        tail[i] = (tail[i >> 1] >> 1) | ((i & 1) << (LOG - 1));
    }
}

void fft(vector<comp> &A) {
    int n = A.size();
    for (int i = 0; i < n; ++i) {
        if (i < tail[i])
            swap(A[i], A[tail[i]]);
    }
    for (int len = 2; len <= n; len *= 2) {
        for (int i = 0; i < n; i += len) {
            for (int j = 0; j < len / 2; ++j) {
                auto v = A[i + j];
                auto u = A[i + j + len / 2] * omega(len, j);
                A[i + j] = v + u;
                A[i + j + len / 2] = v - u;
            }
        }
    }
}

void fft2(vector<comp> &A, vector<comp> &B) {
    int n = A.size();
    vector<comp> C(n);
    for (int i = 0; i < n; ++i) {
        C[i].x = A[i].x;
        C[i].y = B[i].x;
    }
    fft(C);
    C.push_back(C[0]);
    for (int i = 0; i < n; ++i) {
        A[i] = (C[i] + C[n - i].conj()) / 2;
        B[i] = (C[i] - C[n - i].conj()) / 2 * comp(0, -1);
    }
}
void invfft(vector<comp> &A) {
    fft(A);
    for (auto &el : A)
        el = el / MAXN;
    reverse(A.begin() + 1, A.end());
}

vector<int> mul(vector<int> &a, vector<int> &b) {
    vector<comp> A(MAXN, 0), B(MAXN, 0);
    for (int i = 0; i < (int)a.size(); ++i)
        A[i] = a[i];
    for (int i = 0; i < (int)b.size(); ++i)
        B[i] = b[i];
    fft2(A, B);
    for (int i = 0; i < MAXN; ++i)
        A[i] = A[i] * B[i];
    invfft(A);
    vector<int> c(MAXN);
    for (int i = 0; i < MAXN; ++i) {
        int x = round(A[i].x);
        c[i] = x;
    }
    while (!c.empty() && c.back() == 0)
        c.pop_back();
    return c;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    calcomega();
    calctail();
    string sa, sb;
    cin >> sa >> sb;
    reverse(sa.begin(), sa.end());
    reverse(sb.begin(), sb.end());
    vector<int> a(sa.size()), b(sb.size());
    bool minus = false;
    if (sa.back() == '-') {
        minus ^= true;
        sa.pop_back();
    }
    if (sb.back() == '-') {
        minus ^= true;
        sb.pop_back();
    }
    for (int i = 0; i < (int)sa.size(); ++i)
        a[i] = sa[i] - '0';
    for (int i = 0; i < (int)sb.size(); ++i)
        b[i] = sb[i] - '0';
    auto c = mul(a, b);
    int shift = 0;
    for (int i = 0; i < (int)c.size(); ++i) {
        int x = c[i] + shift;
        c[i] = x % 10;
        shift = x / 10;
    }
    while (shift > 0) {
        c.push_back(shift % 10);
        shift /= 10;
    }
    while (!c.empty() && c.back() == 0)
        c.pop_back();
    if (c.empty()) {
        cout << 0;
        return 0;
    }
    if (minus)
        cout << '-';
    for (int i = c.size() - 1; i >= 0; --i)
        cout << c[i];
}

