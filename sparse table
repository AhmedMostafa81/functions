struct sparseTable{

    int table[N][20] = {};
    int logs[N];
    void pre() {
        for(int i = 2; i < N; i++)
            logs[i] = logs[i / 2] + 1;
    }
    
    void build(int n)
    {
        for(int i = 0; i < n; i++)
            table[i][0] = arr[i];

        for(int j = 1; j <= logs[n]; j++)
        {
            for(int i = 0; i <= n - (1 << j); i++)
                table[i][j] = __gcd(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
        }
    }
    int query(int l, int r)
    {
        int sz = logs[r - l + 1];
        return __gcd(table[l][sz], table[r - (1 << sz) + 1][sz]);
    }
};
