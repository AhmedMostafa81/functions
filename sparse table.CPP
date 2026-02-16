struct ST { // sparse table version 1
    int n, lg;
    vector<vector<int>> t;
    vector<int> log;

    int merge(int a, int b){ return min(a,b); }

    ST(vector<int>& a){
        n = a.size();

        log.assign(n+1,0);
        for(int i=2;i<=n;i++)
            log[i]=log[i/2]+1;

        lg = log[n] + 1;

        t.assign(lg, vector<int>(n));

        for(int i=0;i<n;i++)
            t[0][i]=a[i];

        for(int j=1;j<lg;j++)
            for(int i=0;i+(1<<j)<=n;i++)
                t[j][i]=merge(t[j-1][i],
                              t[j-1][i+(1<<(j-1))]);
    }

    int get(int l,int r){
        int j=log[r-l+1];
        return merge(t[j][l], t[j][r-(1<<j)+1]);
    }
};




// sparse table version 2

struct SparseTable {
    int n, LOG;
    vector<vector<long long>> st;
    vector<int> lg;

    long long merge(long long a, long long b) {
        return min(a, b);
    }

    SparseTable(vector<long long>& a) {
        n = a.size();

        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++)
            lg[i] = lg[i / 2] + 1;

        LOG = lg[n] + 1;

        st.assign(LOG, vector<long long>(n));

        for (int i = 0; i < n; i++)
            st[0][i] = a[i];

        for (int j = 1; j < LOG; j++)
            for (int i = 0; i + (1 << j) <= n; i++)
                st[j][i] = merge(st[j - 1][i],
                                 st[j - 1][i + (1 << (j - 1))]);
    }

    long long query(int l, int r) {
        int j = lg[r - l + 1];
        return merge(st[j][l],
                     st[j][r - (1 << j) + 1]);
    }

    long long query_log(int l, int r) {
        long long res = 0; // change neutral if needed
        for (int j = LOG - 1; j >= 0; j--) {
            if ((1 << j) <= r - l + 1) {
                res = merge(res, st[j][l]);
                l += 1 << j;
            }
        }
        return res;
    }
};





// get index and value

struct RMQ {
    int n, LOG;
    vector<vector<int>> st;
    vector<int> lg;
    vector<int>& a;

    RMQ(vector<int>& arr) : a(arr) {
        n = a.size();

        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++)
            lg[i] = lg[i / 2] + 1;

        LOG = lg[n] + 1;

        st.assign(LOG, vector<int>(n));

        for (int i = 0; i < n; i++)
            st[0][i] = i;

        for (int j = 1; j < LOG; j++)
            for (int i = 0; i + (1 << j) <= n; i++) {
                int x = st[j-1][i];
                int y = st[j-1][i + (1 << (j-1))];
                st[j][i] = (a[x] <= a[y] ? x : y);
            }
    }

    int get_index(int l, int r) {
        int j = lg[r - l + 1];
        int x = st[j][l];
        int y = st[j][r - (1 << j) + 1];
        return (a[x] <= a[y] ? x : y);
    }

    int get_value(int l, int r) {
        return a[get_index(l, r)];
    }
};



// 2d sparse table 


struct SparseTable2D {
    int n, m;
    int LOGN, LOGM;
    vector<int> lg;
    vector<vector<vector<vector<int>>>> st;

    int merge(int a, int b){
        return min(a,b);
    }

    SparseTable2D(vector<vector<int>>& a) {
        n = a.size();
        m = a[0].size();

        lg.assign(max(n, m) + 1, 0);
        for (int i = 2; i < (int)lg.size(); i++)
            lg[i] = lg[i/2] + 1;

        LOGN = lg[n] + 1;
        LOGM = lg[m] + 1;

        st.assign(LOGN,
            vector<vector<vector<int>>>(LOGM,
                vector<vector<int>>(n,
                    vector<int>(m))));

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                st[0][0][i][j] = a[i][j];

        for (int x = 0; x < LOGN; x++)
            for (int y = 0; y < LOGM; y++) {

                if (x == 0 && y == 0) continue;

                for (int i = 0; i + (1<<x) <= n; i++)
                    for (int j = 0; j + (1<<y) <= m; j++) {

                        if (x)
                            st[x][y][i][j] =
                                merge(st[x-1][y][i][j],
                                      st[x-1][y][i+(1<<(x-1))][j]);
                        else
                            st[x][y][i][j] =
                                merge(st[x][y-1][i][j],
                                      st[x][y-1][i][j+(1<<(y-1))]);
                    }
            }
    }

    int query(int x1,int y1,int x2,int y2){
        int kx = lg[x2-x1+1];
        int ky = lg[y2-y1+1];

        int a1 = st[kx][ky][x1][y1];
        int a2 = st[kx][ky][x2-(1<<kx)+1][y1];
        int a3 = st[kx][ky][x1][y2-(1<<ky)+1];
        int a4 = st[kx][ky][x2-(1<<kx)+1][y2-(1<<ky)+1];

        return merge(merge(a1,a2), merge(a3,a4));
    }
};

