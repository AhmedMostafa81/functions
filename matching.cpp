//  maximum bipartite matching == minimum vertex cover(minimum number of nodes that cover all edges)
//minimum vertex cover (the complement of maximum independent set)


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
    int n , m;
    vector<int> l, r, d;
    vector<vector<int>> g;

    HopcroftKarp(int _n, int _m) {
        n = _n;
        m = _m;
        int p = _n + _m + 1;
        g.resize(p);
        l.resize(p, 0);
        r.resize(p, 0);
        d.resize(p, 0);
    }

    void add_edge(int u, int v) {
        g[u].push_back(v + n); // right id is increased by n
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
            if (d[r[v]] == d[u] + 1 && dfs(r[v])) {
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
            for (int u = 1; u <= n; u++) {
                if (!l[u] && dfs(u)) ans++;
            }
        }
        return ans;
    }

    vector<pair<int, int>> build_matching() {
        vector<pair<int, int>> res;
        for (int u = 1; u <= n; ++u) {
            if (l[u]) {
                res.emplace_back(u, l[u] - n); // map back right node ID
            }
        }
        return res;
    }

    pair<vector<int>, vector<int>> get_min_vertex_cover() {
        maximum_matching();
        vector<bool> visL(n + 1, false), visR(m + 1, false);

        function<void(int)> dfs_cover = [&](int u) {
            visL[u] = true;
            for (int v : g[u]) {
                int vr = v - n; // Convert back to original column index
                if (!visR[vr] && l[u] != v) { // non-matching edge
                    visR[vr] = true;
                    if (r[v]) dfs_cover(r[v]);
                }
            }
        };

        for (int u = 1; u <= n; u++) {
            if (l[u] == 0) dfs_cover(u);
        }

        vector<int> rows, cols;
        for (int u = 1; u <= n; u++) {
            if (!visL[u]) rows.push_back(u);
        }
        for (int v = 1; v <= m; v++) {
            if (visR[v]) cols.push_back(v);
        }

        return {rows, cols};
    }
};
