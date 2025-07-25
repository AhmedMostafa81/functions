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

    vector<vector<int>> extract_flow_paths(long long flow_limit = -1) {
    vector<vector<int>> paths;

    while (true) {
        vector<int> path = {s};
        vector<bool> visited(n, false);
        long long pushed = flow_inf;

        bool found = false;
        function<bool(int)> dfs = [&](int v) -> bool {
            if (v == t) return true;
            visited[v] = true;
            for (int& i = ptr[v]; i < (int)adj[v].size(); ++i) {
                int id = adj[v][i];
                FlowEdge& e = edges[id];
                if (e.flow > 0 && !visited[e.u]) {
                    path.push_back(e.u);
                    long long minflow = min(pushed, e.flow);
                    pushed = minflow;
                    if (dfs(e.u)) {
                        e.flow -= pushed;
                        edges[id ^ 1].flow += pushed;
                        return true;
                    }
                    path.pop_back();
                }
            }
            return false;
        };

        fill(ptr.begin(), ptr.end(), 0);
        if (!dfs(s)) break;

        if (flow_limit != -1 && pushed > flow_limit) pushed = flow_limit;
        paths.push_back(path);
        if (flow_limit != -1) {
            flow_limit -= pushed;
            if (flow_limit <= 0) break;
        }
    }

    return paths;
    }


    vector<tuple<int, int, long long>> get_used_edges() {
        vector<tuple<int, int, long long>> result;
        for (const auto& e : edges) {
            if (e.cap > 0 && e.flow > 0) {
                result.emplace_back(e.v, e.u, e.flow);
            }
        }
        return result;
    }

    vector<pair<int, int>> min_cut() {
        // Step 1: Find reachable nodes from s in residual graph
        vector<bool> vis(n, false);
        queue<int> q;
        q.push(s);
        vis[s] = true;
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int id : adj[v]) {
                int u = edges[id].u;
                if (!vis[u] && edges[id].flow < edges[id].cap) {
                    vis[u] = true;
                    q.push(u);
                }
            }
        }

        // Step 2: Find saturated forward edges from reachable to unreachable
        vector<pair<int, int>> cut_edges;
        for (int i = 0; i < (int)edges.size(); i += 2) {
            const FlowEdge& e = edges[i];
            if (e.cap == e.flow && e.cap > 0 && vis[e.v] && !vis[e.u]) {
                cut_edges.emplace_back(e.v, e.u);
            }
        }

        return cut_edges;
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

/////////////////////////////////////////////////////////////
//ANOTHER TEMPLATE  (bedoo)
#include<bits/stdc++.h>

#define ll long long
#define f first
#define s second
using namespace std;
const int N = 1e2+5; //size of nodes

const int inf = 1000000010;
struct Edge {
    int to, cost, cap, flow, backEdge;
};
struct MCMF {
    int s, t, n;
    vector<Edge> g[N];
    MCMF(int _s, int _t, int _n) {
        s = _s, t = _t, n = _n+1;
    }
    void addEdge(int u, int v, int cost, int cap) {
        Edge e1 = { v, cost, cap, 0, (int)g[v].size() };
        Edge e2 = { u, -cost, 0, 0, (int)g[u].size() };
        g[u].push_back(e1); g[v].push_back(e2);
    }
    pair<int, int> minCostMaxFlow() {
        int flow = 0, cost = 0;
        vector<int> state(n), from(n), from_edge(n), d(n);
        deque<int> q;
        while (true) {
            for (int i = 0; i < n; i++)
                state[i] = 2, d[i] = inf, from[i] = -1;
            state[s] = 1; q.clear(); q.push_back(s); d[s] = 0;
            while (!q.empty()) {
                int v = q.front(); q.pop_front(); state[v] = 0;
                for (int i = 0; i < (int) g[v].size(); i++) {
                    Edge e = g[v][i];
                    if (e.flow >= e.cap || d[e.to] <= d[v] + e.cost)
                        continue;
                    int to = e.to; d[to] = d[v] + e.cost;
                    from[to] = v; from_edge[to] = i;
                    if (state[to] == 1) continue;
                    if (!state[to] || (!q.empty() && d[q.front()] > d[to]))
                        q.push_front(to);
                    else q.push_back(to);
                    state[to] = 1;
                }
            }
            if (d[t] == inf) break;
            int it = t, addflow = inf;
            while (it != s) {
                addflow = min(addflow,
                              g[from[it]][from_edge[it]].cap
                              - g[from[it]][from_edge[it]].flow);
                it = from[it];
            }
            it = t;
            while (it != s) {
                g[from[it]][from_edge[it]].flow += addflow;
                g[it][g[from[it]][from_edge[it]].backEdge].flow -= addflow;
                cost += g[from[it]][from_edge[it]].cost * addflow;
                it = from[it];
            }
            flow += addflow;
        }
        return {cost,flow};
    }
};

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    MCMF G(0 , 3 , 3);
    G.addEdge(0 , 1 , 3 , 2); //cost , cap
    G.addEdge(1 , 3 , 2 , 1);
    G.addEdge(0 , 2 , 2 , 2);
    G.addEdge(2 , 3 , 4 , 7);

    pair<ll,ll> pr = G.minCostMaxFlow(); //cost , flow
    cout << pr.f << ' ' << pr.s << '\n';

    return 0;
}





