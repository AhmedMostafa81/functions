int n, k;
vector<vector<int>> g;
vector<int> mt;
vector<bool> used;

bool try_kuhn(int v) {
    if (used[v])
        return false;
    used[v] = true;
    for (int to : g[v]) {
        if (mt[to] == -1 || try_kuhn(mt[to])) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}

int main() {
    //... reading the graph ...

    mt.assign(k, -1);
    for (int v = 0; v < n; ++v) {
        used.assign(n, false);
        try_kuhn(v);
    }

    for (int i = 0; i < k; ++i)
        if (mt[i] != -1)
            printf("%d %d\n", mt[i] + 1, i + 1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////


struct HopcroftKarp { // one based
    static const int inf = 1e16;
    int n;
    vector<int> l, r, d;
    vector<vector<int>> g;
    HopcroftKarp(int _n, int _m) {
        n = _n;
        int p = _n + _m + 1;
        g.resize(p);
        l.resize(p, 0);
        r.resize(p, 0);
        d.resize(p, 0);
    }
    void add_edge(int u, int v) {
        g[u].push_back(v + n); //right id is increased by n, so is l[u]
    }
    bool bfs() {
        queue<int> q;
        for (int u = 1; u <= n; u++) {
            if (!l[u]) d[u] = 0, q.push(u);
            else d[u] = inf;
        }
        d[0] = inf;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto v : g[u]) {
                if (d[r[v]] == inf) {
                    d[r[v]] = d[u] + 1;
                    q.push(r[v]);
                }
            }
        }
        return d[0] != inf;
    }
    bool dfs(int u) {
        if (!u) return true;
        for (auto v : g[u]) {
            if(d[r[v]] == d[u] + 1 && dfs(r[v])) {
                l[u] = v;
                r[v] = u;
                return true;
            }
        }
        d[u] = inf;
        return false;
    }
    int maximum_matching() {
        int ans = 0;
        while (bfs()) {
            for(int u = 1; u <= n; u++) if (!l[u] && dfs(u)) ans++;
        }
        return ans;
    }
};
