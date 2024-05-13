int floor_sum(int n, int div, int mul, int add) {
    // sum_{i=0}^{n-1} floor((add + i*mul)/div)
    int ans = 0;
    ans += (n * (n - 1) / 2) * (mul / div);
    mul %= div;
    ans += n * (add / div);
    add %= div;
    int l = mul * n + add;
    if (l >= div)
        ans += floor_sum(l / div, mul, div, l % div);
    return ans;
}
