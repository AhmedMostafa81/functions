//  maximum bipartite matching == minimum vertex cover(minimum number of nodes that cover all edges)
//minimum vertex cover (the complement of maximum independent set)


#include <bits/stdc++.h>
using namespace std;

struct Kuhn {
    int n, m;                       // left: 0..n-1, right: 0..m-1
    vector<vector<int>> adj;        // adj[v] = list of right nodes
    vector<int> matchR;             // matchR[to] = matched left node or -1
    vector<bool> used;

    Kuhn(int _n, int _m) : n(_n), m(_m) {
        adj.assign(n, {});
        matchR.assign(m, -1);
        used.assign(n, false);
    }

    void addEdge(int u, int v) {    // u in [0..n-1], v in [0..m-1]
        adj[u].push_back(v);
    }

    bool dfs(int v) {
        if (used[v]) return false;
        used[v] = true;
        for (int to : adj[v]) {
            if (matchR[to] == -1 || dfs(matchR[to])) {
                matchR[to] = v;
                return true;
            }
        }
        return false;
    }

    int maximumMatching() {
        int match = 0;
        for (int v = 0; v < n; ++v) {
            fill(used.begin(), used.end(), false);
            if (dfs(v)) ++match;
        }
        return match;
    }

    vector<pair<int,int>> getMatchingPairs() {
        vector<pair<int,int>> res;
        for (int v = 0; v < m; ++v)
            if (matchR[v] != -1)
                res.emplace_back(matchR[v], v);
        return res;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <bits/stdc++.h>
using namespace std;

struct HopcroftKarp {
    int n, m;                              // n = #left (1..n), m = #right (1..m)
    vector<vector<int>> adj;               // adj[u] = list of right vertices (1..m)
    vector<int> pairLeft, pairRight;       // pairLeft[u]=v (0 if free), pairRight[v]=u (0 if free)
    vector<int> dist;                      // distance used by BFS
    const int INF = 1e9;

    HopcroftKarp(int _n, int _m)
        : n(_n), m(_m),
          adj(_n + 1),
          pairLeft(_n + 1, 0),
          pairRight(_m + 1, 0),
          dist(_n + 1, 0) {}

    void addEdge(int u, int v) {           // u in [1..n], v in [1..m]
        adj[u].push_back(v);
    }

    // build layered graph, return true if there is an augmenting path
    bool bfs() {
        queue<int> q;
        int foundDist = INF;
        for (int u = 1; u <= n; ++u) {
            if (pairLeft[u] == 0) { dist[u] = 0; q.push(u); }
            else dist[u] = INF;
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (dist[u] >= foundDist) continue;
            for (int v : adj[u]) {
                int pu = pairRight[v];
                if (pu == 0) {
                    foundDist = dist[u] + 1;
                } else if (dist[pu] == INF) {
                    dist[pu] = dist[u] + 1;
                    q.push(pu);
                }
            }
        }
        return foundDist != INF;
    }

    // try to find augmenting path starting at left node u
    bool dfs(int u) {
        for (int v : adj[u]) {
            int pu = pairRight[v];
            if (pu == 0 || (dist[pu] == dist[u] + 1 && dfs(pu))) {
                pairLeft[u] = v;
                pairRight[v] = u;
                return true;
            }
        }
        dist[u] = INF; // prune
        return false;
    }

    // compute maximum matching size
    int maximumMatching() {
        int matching = 0;
        while (bfs()) {
            for (int u = 1; u <= n; ++u) {
                if (pairLeft[u] == 0 && dfs(u)) ++matching;
            }
        }
        return matching;
    }

    // return matching as vector of (left, right)
    vector<pair<int,int>> getMatchingPairs() {
        vector<pair<int,int>> res;
        for (int u = 1; u <= n; ++u)
            if (pairLeft[u]) res.emplace_back(u, pairLeft[u]);
        return res;
    }

    // minimum vertex cover (after running maximumMatching)
    // returns {left_list, right_list} (1-based indices)
    pair<vector<int>, vector<int>> minVertexCover() {
        maximumMatching(); // ensure matching exists

        vector<char> visL(n + 1, 0), visR(m + 1, 0);
        queue<int> q;

        // start from all free left vertices
        for (int u = 1; u <= n; ++u) {
            if (pairLeft[u] == 0) {
                visL[u] = 1;
                q.push(u);
            }
        }

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (visR[v]) continue;
                if (pairLeft[u] != v) {        // non-matching edge u -> v
                    visR[v] = 1;
                    if (pairRight[v] && !visL[pairRight[v]]) {
                        visL[pairRight[v]] = 1;
                        q.push(pairRight[v]);
                    }
                }
            }
        }

        vector<int> leftCover, rightCover;
        for (int u = 1; u <= n; ++u) if (!visL[u]) leftCover.push_back(u);
        for (int v = 1; v <= m; ++v) if (visR[v]) rightCover.push_back(v);
        return {leftCover, rightCover};
    }
};

// small usage example
/*
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, E;
    cin >> n >> m >> E;
    HopcroftKarp hk(n, m);
    for (int i = 0; i < E; ++i) {
        int u, v; cin >> u >> v;   // u in [1..n], v in [1..m]
        hk.addEdge(u, v);
    }
    int ans = hk.maximumMatching();
    cout << ans << '\n';
    for (auto [u, v] : hk.getMatchingPairs()) cout << u << ' ' << v << '\n';
}
*/

