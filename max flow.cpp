//    ->     max flow == min cut (edges have cost and i want to get minimum cost to disconnect src and sink)
// maximum edge disjoint path (no two paths share the same edge)
// maximum independent path (no two paths share the same edge or the same node) (add constraint on vertex)

// minimum path cover (minimum number of paths that covers all graph without sharing edges) (DAG)
//   = n - max_matching


// slow max flow

#include<bits/stdc++.h>
using namespace std;
#define int long long
#define AhmedPlusPlus ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define hi cerr<<"HI\n";

/*                        ->    NO CLEAN CODE HERE    <-                        */


int n;
vector<vector<int>> capacity(N , vector<int>(N));
vector<vector<int>> adj(N);

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, 1e9});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

signed main() {
/* ^^^ */    AhmedPlusPlus    /* ^^^ */

//    ->> practice makes perfect

    n = ;

    int q;cin>>q;
    while(q--){
        int x,y,c;cin>>x>>y>>c;
        adj[x].push_back(y);
        adj[y].push_back(x);
        capacity[x][y] = c;
    }
    cout << maxflow(S , T);

}
///////////////////////////////////////////////////////////////////////////////////////////////////
//    fast max flow

struct FlowEdge {
    int v, u;
    long long cap, flow = 0;
    FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
    const long long flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int v, int u, long long cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap == edges[id].flow)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u])
                continue;
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    long long flow() {
        long long f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
};



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//    minimum cost max flow



struct FlowEdge {
    int v, u;
    long long cap, flow = 0, cost;
    FlowEdge(int v, int u, long long cap, long long cost) : v(v), u(u), cap(cap), cost(cost) {}
};

struct FlowNetwork {
    const long long INF = 1e18;
    int n, m = 0, s, t;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    vector<int> level, ptr;
    queue<int> q;

    FlowNetwork(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int v, int u, long long cap, long long cost = 0) {
        edges.emplace_back(v, u, cap, cost);
        edges.emplace_back(u, v, 0, -cost);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    // Dinic's Max Flow
    bool bfs() {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        q = queue<int>();
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow < 1) continue;
                if (level[edges[id].u] != -1) continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (pushed == 0) return 0;
        if (v == t) return pushed;
        for (int &cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
                continue;
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0) continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    long long max_flow() {
        long long f = 0;
        while (true) {
            if (!bfs()) break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, INF)) {
                f += pushed;
            }
        }
        return f;
    }

    // Min Cost Flow of K units using SPFA
    long long min_cost_flow(long long K) {
        long long flow = 0, cost = 0;
        vector<long long> dist(n);
        vector<int> in_queue(n), parent(n), parent_edge(n);

        while (flow < K) {
            fill(dist.begin(), dist.end(), INF);
            dist[s] = 0;
            queue<int> q;
            q.push(s);
            in_queue[s] = 1;
            parent[s] = -1;

            while (!q.empty()) {
                int v = q.front(); q.pop();
                in_queue[v] = 0;
                for (int i = 0; i < (int)adj[v].size(); i++) {
                    int id = adj[v][i];
                    int u = edges[id].u;
                    if (edges[id].cap - edges[id].flow < 1) continue;
                    if (dist[u] > dist[v] + edges[id].cost) {
                        dist[u] = dist[v] + edges[id].cost;
                        parent[u] = v;
                        parent_edge[u] = id;
                        if (!in_queue[u]) {
                            in_queue[u] = 1;
                            q.push(u);
                        }
                    }
                }
            }

            if (dist[t] == INF) break;

            long long push = K - flow;
            int v = t;
            while (v != s) {
                int id = parent_edge[v];
                push = min(push, edges[id].cap - edges[id].flow);
                v = parent[v];
            }

            flow += push;
            cost += push * dist[t];
            v = t;
            while (v != s) {
                int id = parent_edge[v];
                edges[id].flow += push;
                edges[id ^ 1].flow -= push;
                v = parent[v];
            }
        }

        return (flow < K ? -1 : cost);
    }
};






