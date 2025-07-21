vector<int> or_conv(int n, vector<int> a, vector<int> b) { // $|a| = |b| = 2^n$
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (1 << n); j++) {
            if ((j >> i) & 1) {
                a[j] = (a[j] + a[j ^ (1 << i)]) % MOD;
                b[j] = (b[j] + b[j ^ (1 << i)]) % MOD;
            }
        }
    }
    vector<int> c(1 << n);
    for (int i = 0; i < (1 << n); i++) {
        c[i] = (a[i] * b[i]) % MOD;
    }
    for (int i = n - 1; i >= 0; i--) {
        for (int j = (1 << n) - 1; j >= 0; j--) {
            if ((j >> i) & 1) {
                c[j] = (c[j] - c[j ^ (1 << i)] + MOD) % MOD;
            }
        }
    }
    return c;
}

vector<int> and_conv(int n, vector<int> a, vector<int> b) { // $|a| = |b| = 2^n$
    for (int i = 1; i < (1 << n); i *= 2) {
        for (int j = 0; j < (1 << n); j += i * 2) {
            for (int k = 0; k < i; k++) {
                a[j + k] = (a[j + k] + a[i + j + k]) % MOD;
                b[j + k] = (b[j + k] + b[i + j + k]) % MOD;
            }
        }
    }
    vector<int> c(1 << n);
    for (int i = 0; i < (1 << n); i++)
        c[i] = (a[i] * b[i]) % MOD;
    for (int i = 1; i < (1 << n); i *= 2) {
        for (int j = 0; j < (1 << n); j += i * 2) {
            for (int k = 0; k < i; k++) {
                c[j + k] = (c[j + k] - c[i + j + k] + MOD) % MOD;
            }
        }
    }
    return c;
}

const int inv2 = (MOD + 1) / 2;
vector<int> xor_conv(int n, vector<int> a, vector<int> b) { // $|a| = |b| = 2^n$
    for (int i = 1; i < (1 << n); i *= 2) {
        for (int j = 0; j < (1 << n); j++) {
            if ((j & i) == 0) {
                int x = a[j], y = a[j | i];
                a[j] = (x + y) % MOD, a[j | i] = (x - y + MOD) % MOD;
                x = b[j], y = b[j | i];
                b[j] = (x + y) % MOD, b[j | i] = (x - y + MOD) % MOD;
            }
        }
    }
    vector<int> c(1 << n);
    for (int i = 0; i < (1 << n); i++)
        c[i] = (a[i] * b[i]) % MOD;
    for (int i = 1; i < (1 << n); i *= 2) {
        for (int j = 0; j < (1 << n); j++) {
            if ((j & i) == 0) {
                int x = c[j], y = c[j | i];
                c[j] = (inv2 * (x + y)) % MOD, c[j | i] = (inv2 * (x - y + MOD)) % MOD;
            }
        }
    }
    return c;
}
