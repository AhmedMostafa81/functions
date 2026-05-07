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
