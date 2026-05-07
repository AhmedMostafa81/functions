const int N = ;
vector<int>gr[N] , par(N);
int sz[N];
bool del[N];

void init_size(int node , int cur_par) {
    sz[node] = 0 ;
    if (del[node])
        return ;
    sz[node] = 1;
    for (auto ch:gr[node])
        if (ch != cur_par) {
            init_size(ch , node);
            sz[node] += sz[ch];
        }
}

int centroid(int node , int cur_par , int tot) {
    for (auto ch:gr[node])
        if (cur_par != ch)
            if (!del[ch] && sz[ch] > tot / 2)
                return centroid(ch , node , tot);
    return node;
}

void decomposition(int node , int cur_par) {
    init_size(node , -1);
    int x = centroid(node , -1 , sz[node]);
    par[x] = cur_par;
    del[x] = true;
    for (auto ch:gr[x])
        if (!del[ch])
            decomposition(ch , x);
}

void update(int node) {
    int t = node;
    while (~node) {
        // CODE
        node = par[node];
    }
}

int query(int node) {
    int t = node;
    while (~node) {
        // CODE        
        node = par[node];
    }
    return ;
}
--------------------------------------------------------------------
// another version

int MX_DEP;

void solve(int node , int p , bool Fill , int dep) {
    MX_DEP = max(MX_DEP , dep);
    if (Fill)
        fr[dep]++;
    else if (k >= dep)
        ans += fr[k - dep];
    for (auto ch:gr[node])
        if (!del[ch] && ch != p)
            solve(ch , node , Fill , dep + 1);
}

void decomposition(int node) {
    get_sz(node , -1);
    int cen = centroid(node , -1 , sz[node]);
    del[cen] = true;
    MX_DEP = 0 ;
    fr[0] = 1; // add this node
    for (auto ch:gr[cen]) {
        if (!del[ch]) {
            solve(ch , cen , 0 , 1);
            solve(ch , cen , 1 , 1);
        }
    }
    for (int i = 0; i <= MX_DEP ; i++)
        fr[i] = 0;
    for (auto ch:gr[cen])
        if (!del[ch])
            decomposition(ch);
}

    
