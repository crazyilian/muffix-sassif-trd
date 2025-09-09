vector<int> gcd_convolution(vector<int> a, vector<int> b) {
    // a,b is 1-indexed array; a[0],b[0] doesnt matter
    int n = ssize(a) - 1;
    for (int p = 2; p <= n; ++p) {
        if (!isprime[p]) continue; // alt: for (auto p : primes) if (p>n)break;
        for (int i = n / p; i > 0; --i) {
            a[i] += a[i * p];
            if (a[i] >= mod) a[i] -= mod;
            b[i] += b[i * p];
            if (b[i] >= mod) b[i] -= mod;
        }
    }
    for (int i = 1; i <= n; ++i) a[i] = (a[i] * b[i]) % mod;
    for (int p = 2; p <= n; ++p) {
        if (!isprime[p]) continue;
        for (int i = 1; i * p <= n; ++i) {
            a[i] += mod - a[i * p];
            if (a[i] >= mod) a[i] -= mod;
        }
    }
    return a;
}

vector<int> lcm_convolution(vector<int> a, vector<int> b) {
    int n = ssize(a) - 1;
    for (int p = 2; p <= n; ++p) {
        if (!isprime[p]) continue;
        for (int i = 1; i * p <= n; ++i) {
            a[i * p] += a[i];
            if (a[i * p] >= mod) a[i * p] -= mod;
            b[i * p] += b[i];
            if (b[i * p] >= mod) b[i * p] -= mod;
        }
    }
    for (int i = 1; i <= n; ++i) a[i] = (a[i] * b[i]) % mod;
    for (int p = 2; p <= n; ++p) {
        if (!isprime[p]) continue;
        for (int i = n / p; i > 0; --i) {
            a[i * p] += mod - a[i];
            if (a[i * p] >= mod) a[i * p] -= mod;
        }
    }
    return a;
}
