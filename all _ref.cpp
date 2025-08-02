#include<bits/stdc++.h>
ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
// ############################ GRAPH #################################        
///////////////////////////////////////////////////////////////////////

// LCA

const int N =  , LOG = ;
vector<int>gr[N];
int n,m,q,in[N],out[N] , tim , up[N][LOG];

void pre(int node = 0 ,int par = 0){
    in[node] = ++tim;
    up[node][0] = par;
    for (int i = 1 ; i < LOG ; i++)
        up[node][i] = up[up[node][i-1]][i-1];
    for (auto ch:gr[node])
        pre(ch , node);
    out[node] = ++tim;
}

bool if_anc(int x,int y){
    return in[x] <= in[y] && out[x] >= out[y];
}
int LCA(int x,int y){
    if (if_anc(x,y))
        return x;
    if (if_anc(y,x))
        return y;
    for (int i = LOG-1;i>=0;i--)
        if (!if_anc(up[x][i],y))
            x = up[x][i];
    return up[x][0];
}



// min , max

const int N = 1e5+2 , LOG = 18;
vector<pair<int,int>>gr[N];
int n,in[N],out[N],tim,up[N][LOG];
pair<int,int>que[N][LOG];

void pre(int node=1,int par=1,int w = 0){
    in[node] = ++tim;
    up[node][0] = par;
    if (node != 1)
        que[node][0] = {w,w};
    else
        que[node][0] = {1e16,0};
    for (int i =1;i<LOG;i++)
        up[node][i] = up[up[node][i-1]][i-1],
        que[node][i].first = min(que[node][i-1].first,que[up[node][i-1]][i-1].first),
        que[node][i].second = max(que[node][i-1].second,que[up[node][i-1]][i-1].second);

    for (auto [ch,cost]:gr[node])
        if (ch != par)
            pre(ch , node , cost);

    out[node] = ++tim;
}
bool anc(int x,int y){
    return in[x] <= in[y] && out[x] >= out[y];
}

pair<int,int>get(int x,int y){
    if (anc(y,x))swap(x,y);
    pair<int,int>rt={1e16,0};
    for (int i = LOG-1 ; i >= 0 ;i--){
        if (anc(x , up[y][i])){
            rt.first = min(rt.first , que[y][i].first);
            rt.second = max(rt.second , que[y][i].second);
            y = up[y][i];
        }
    }
    return rt;
}

pair<int,int>LCA(int x,int y){
    if (anc(x,y) || anc(y,x))
        return get(x,y);
    pair<int,int>rt = {1e16 , 0};
    for (int i = LOG-1;i>=0;i--){
        if (!anc(up[x][i],y)){
            rt.first = min(rt.first , que[x][i].first);
            rt.second = max(rt.second , que[x][i].second);
            x = up[x][i];
        }
    }
    rt.first = min(rt.first , que[x][0].first);
    rt.second = max(rt.second , que[x][0].second);
    return rt;
}

//////////
// Kth ancestor

int get(int node,int tar){
    for (int i = LOG-1 ; i >= 0; i--)
        if ((1<<i) <= tar)
            node = up[node][i] , tar -= (1<<i);
    return node;
}
//

// merge and no overlap 
const int N = 2e5+5 , LOG = 20;
vector<int>gr[N];
int n,a[N],in[N],out[N],tim,up[N][LOG];
vector<tuple<int,int,int>>que;

struct Node{
    int pre_mx = 0 , suf_mx = 0 , MX = 0 , sum = 0;
    int pre_mn = 0 , suf_mn = 0 , MN = 0 ;
}spar[N][LOG];

Node Merge(Node L , Node R){
    Node rt;
    rt.pre_mx = max(L.pre_mx , L.sum + R.pre_mx);
    rt.pre_mn = min(L.pre_mn , L.sum + R.pre_mn);

    rt.suf_mx = max(R.suf_mx , R.sum + L.suf_mx);
    rt.suf_mn = min(R.suf_mn , R.sum + L.suf_mn);

    rt.sum = L.sum + R.sum;

    rt.MX = max({L.MX , R.MX , L.suf_mx + R.pre_mx});
    rt.MN = min({L.MN , R.MN , L.suf_mn + R.pre_mn});
    return rt;
}

Node single(int val){
    Node rt;
    rt.sum = val;

    rt.pre_mx = max(0ll,val);
    rt.suf_mx = max(0ll,val);
    rt.MX = max(0ll,val);

    rt.pre_mn = min(0ll , val);
    rt.suf_mn = min(0ll , val);
    rt.MN = min(0ll , val);
    return rt;
}

void init(){
    que.clear();
    tim = 0;
    for (int i =1;i<=n;i++){
        gr[i].clear();
        a[i] = in[i] = out[i] = 0;
        for (int j = 0; j < LOG ; j ++)
            up[i][j] = 0 , spar[i][j] = single(0);
    }
    a[1] = 1;
}

void pre(int node = 1,int par = 1){
    in[node] = ++tim;
    up[node][0] = par;
    if (node != 1)
        spar[node][0] = single(a[par]);
    else
        spar[node][0] = single(0);
    for (int i = 1;i<LOG;i++) {
        up[node][i] = up[up[node][i - 1]][i - 1];
        spar[node][i] = Merge(spar[node][i-1] , spar[up[node][i-1]][i-1]);
    }
    for (auto ch:gr[node])
        pre(ch , node);
    out[node] = ++tim;
}
bool anc(int x,int y){
    return in[x] <= in[y] && out[x] >= out[y];
}
Node get(int x,int y,bool one){
    vector<Node>all = {single(a[x])};
    for (int i = LOG - 1; i >=0 ;i--)
        if (!anc(up[x][i],y)) {
            all.push_back(spar[x][i]);
            x = up[x][i];
        }
    if (one)
        all.push_back(spar[x][0]);
    Node rt = single(0);
    for (int i =0;i<all.size();i++)
        rt = Merge(rt,all[i]);
    return rt;
}
int LCA(int x,int y){
    if (anc(x,y))return x;
    if (anc(y,x))return y;
    for (int i = LOG - 1; i >= 0 ;i--)
        if (!anc(up[x][i] , y))
            x = up[x][i];
    return up[x][0];
}
Node solve(int x,int y){
    int lca = LCA(x,y);
    if (lca == x)return get(y,x,1);
    if (lca == y)return get(x,y,1);
    Node L = get(x,lca,0) , R = get(y,lca,0);
    Node rt;
    rt.MX = max({L.MX , R.MX , L.suf_mx + a[lca] + R.suf_mx});
    rt.MN = min({L.MN , R.MN , L.suf_mn + a[lca] + R.suf_mn});
    return rt;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////
bellman for min path

    int n,m;cin>>n>>m;
    vector<tuple<int,int,int>>gr;
    vector<int>dis(n+1,inf);
    loop(i,m){
        int x,y,c;cin>>x>>y>>c;
        gr.pb({x,y,c});
        dis[y]=min(dis[y],c);
    }
    bool INF=0;
    for(int i =0 ;i<n;i++){
        for (int j=0;j<m;j++){
            auto[x,y,c]=gr[j];
            if (dis[x]+c < dis[y]){
                dis[y]=dis[x]+c;
                if (n==i+1)INF=1;
            }
        }
    }

normal bellman

    int n,m;cin>>n>>m;
    vector<int>dis(n+1,inf);
    vector<tuple<int,int,int>>edges;
    loop(i,m){
        int x,y,c;cin>>x>>y>>c;
        edges.pb({x,y,c});
        dis[y]=min(dis[y],c);
    }
    bool pos=0;
    loop(i,n){
        loop(j,m){
            auto[x,y,c]=edges[j];
            if (dis[y] > dis[x]+c){
                dis[y]=dis[x]+c;
                if (i==n-1)
                    pos=1;
            }
        }
    }
    if (pos)cout<<"possible\n";
    else cout <<"not possible\n";


        //                          floyd
        for (int a=1;a<=n;a++)
            for(int b=1;b<=n;b++)
                    dis[a][b]=min(dis[a][k]+dis[k][b],dis[a][b]);
/////////////////////////////////////////////////////////
        for (int i = 'a'; i <= 'z'; i++) {
            for (int a = 'a'; a <= 'z'; a++) {
                for (int b = 'a'; b <= 'z'; b++) {
                    if (cost[a][b] > cost[a][i] + cost[i][b] && cost[a][i]!=inf && cost[i][b]!=inf)
                    cost[a][b] =cost[a][i] + cost[i][b];
                }
            }
        }
///////////////////////
tarjan

const int N=1e5+5;
vector<int>gr[N];
vector<int>new_gr[N];
vector<int>lowlink,dfn,col,dis,vis;
vector<pair<int,int>>br;
int df,cl;
stack<int>st;
 
void tar(int node,int par){
    lowlink[node] = dfn[node] =df++;
    st.push(node);
    for (auto ch:gr[node]){
        if (ch==par)continue;
        if (!dfn[ch]){
            tar(ch,node);
            if (lowlink[ch] > lowlink[node])
                br.push_back({ch,node});
            lowlink[node] = min(lowlink[node],lowlink[ch]);
        }
        else if (!col[ch]){
            lowlink[node] = min(lowlink[node],dfn[ch]);
        }
    }
    if (lowlink[node] == dfn[node]){
        int x=-1;
        while(x!=node){
            x=st.top();
            st.pop();
            col[x]=cl;
        }
        cl++;
    }
}

    df=cl=1;
    br.clear();
    cin>>n>>m;
    for (int i =1;i<=n;i++)gr[i].clear();
    for (int i =1;i<=n;i++)new_gr[i].clear();
    for (int i=0;i<m;i++){
        int x,y;cin>>x>>y;
        gr[x].push_back(y);
        gr[y].push_back(x);
    }
    lowlink.assign(n+1,0);
    dfn.assign(n+1,0);
    col.assign(n+1,0);
    tar(1,-1);
    int fin=0;
    for (int i =0;i<br.size();i++){
        auto [x,y] = br[i];
        if (col[x]!=col[y])fin++;
        new_gr[col[x]].push_back(col[y]);
        new_gr[col[y]].push_back(col[x]);
    }



// articulation point

int n; // number of nodes
vector<vector<int>> adj; // adjacency list of graph

vector<bool> visited;
vector<int> tin, low;
int timer;

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    int children=0;
    for (int to : adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] >= tin[v] && p!=-1)
                IS_CUTPOINT(v);
            ++children;
        }
    }
    if(p == -1 && children > 1)
        IS_CUTPOINT(v);
}

void find_cutpoints() {
    timer = 0;
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs (i);
    }
}

// Bi connected == block cut tree

const int N = ;
int dfn[N], lowlink[N], tim = 0;
stack<int> st;
bool inS[N], art[N];
vector<vector<int>> comp;   
vector<int> gr[N];

void tarjan(int node, int par) {               
    dfn[node] = lowlink[node] = ++tim;
    st.push(node);
    inS[node] = true;
    int cnt = 0;

    for (const int& ch : gr[node]) {          
        if (ch == par) continue;

        if (!dfn[ch]) {
            tarjan(ch, node);
            lowlink[node] = min(lowlink[node], lowlink[ch]);

            if (lowlink[ch] >= dfn[node]) {
                if (node != par) art[node] = true;
                comp.push_back({node});
                while (comp.back().back() != ch)
                    comp.back().push_back(st.top()), st.pop();
            }
            ++cnt;
        }
        else if (inS[ch])
            lowlink[node] = min(lowlink[node], dfn[ch]);
    }
    if (cnt > 1 && node == par)
        art[node] = true;

}

vector<vector<int>> new_gr(2 * N);
int ID[N];

signed main() {

    // input
    
    
    
    for (int node = 1; node <= n; ++node)
        if (!dfn[node])
            tarjan(node, node);

    int cur = 1;
    // articulation points
    for (int node = 1; node <= n; ++node)
        if (art[node])
            ID[node] = cur++;
    // components
    for (const vector<int>& v : comp) {
        for (const int& node : v) {
            if (art[node]) {
                new_gr[cur].push_back(ID[node]);
                new_gr[ID[node]].push_back(cur);
            }
            else ID[node] = cur;
        }
        ++cur;
    }
   
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
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


// fast matching

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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





















//############################ DS ######################################
//////////////////////////////////////////////////////////////////////////
struct Trie {
    const int BIT = 30;
    struct Node {
        static const int MX = 2;
        int children[MX] = {};
        int f = 0;
    };

    vector<Node> trie;

    Trie() {
        trie.emplace_back();
        insert(0);
    }

    void insert(int x) {
        int idx = 0;
        for(int bit = BIT; bit >= 0; bit--) {
            int nxt = ((x&(1<<bit)) != 0);

            if(trie[idx].children[nxt] == 0) {
                trie[idx].children[nxt] = trie.size();
                trie.emplace_back();
            }
            idx = trie[idx].children[nxt];
            trie[idx].f++;
        }
    }

    void erase(int x) {
        int idx = 0;
        for(int bit = BIT; bit >= 0; bit--) {
            int nxt = ((x&(1<<bit)) != 0);

            idx = trie[idx].children[nxt];
            trie[idx].f--;
        }
    }

    int query(int x) {
        int idx = 0;
        int ret = 0;
        for(int bit = BIT; bit >= 0; bit--) {
            int nxt = ((x&(1<<bit)) == 0);

            if(trie[trie[idx].children[nxt]].f == 0)
                nxt ^= 1;
            else
                ret |= (1<<bit);
            idx = trie[idx].children[nxt];
        }
        return ret;
    }

    void clear() {
        trie.clear();
        trie.emplace_back();
        insert(0);
    }
};

struct Trie {
    struct Node {
        static const int MX = 29;
        int children[MX] = {};
        int f = 0;
    };

    vector<Node> trie;

    Trie() {
        trie.emplace_back();
    }

    void insert(string& s) {
        int idx = 0;
        for(auto i : s) {
            int nxt = i-'a';

            if(trie[idx].children[nxt] == 0) {
                trie[idx].children[nxt] = trie.size();
                trie.emplace_back();
            }
            idx = trie[idx].children[nxt];
            trie[idx].f++;
        }
    }

    void erase(string& s) {
        int idx = 0;
        for(auto i : s) {
            int nxt = i-'a';

            idx = trie[idx].children[nxt];
            trie[idx].f--;
        }
    }

    int query(string& s) {
        int idx = 0;
        for(auto i : s) {
            int nxt = i-'a';
            if(trie[trie[idx].children[nxt]].f == 0)
                return 0;
            idx = trie[idx].children[nxt];
        }
        return trie[idx].f;
    }
};
//////////////////////////////////////////////////////////////////////////////////////////////////
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type,less_equal<int>, rb_tree_tag,tree_order_statistics_node_update>

ordered_set st;
st.order_of_key(number);// number of elem. less than (..)
find_by_order(index) // get by index


/////////////////////////////////////////////////////////////////////////
struct Node {
    
}neutral;

struct lazy_segment_tree{
    int sz;
    vector<Node>tree;
    vector<int>lazy;
    void init(int n){
        sz=1;
        while(sz < n)sz*=2;
        tree.assign(2*sz,neutral);
        lazy.assign(2*sz,0);
    }

    Node merge(Node a,Node b) {
        Node rt ;
        rt.mn = min(a.mn , b.mn);
        return rt;
    }

    void prop(int node) {
        tree[node].mn+=lazy[node];
        if (node*2+1 < 2*sz)
            lazy[node*2+1]+=lazy[node];
        if (node*2+2 < 2*sz)
            lazy[node*2+2]+=lazy[node];
        lazy[node]=0;
    }

    void set(int i ,int v,int node,int lx,int rx){
        if (rx-lx==1) {
            tree[node].mn = v;
            return ;
        }
        int mid = (lx+rx)/2;
        if (i<mid)
            set(i,v,node*2+1,lx,mid);
        else
            set(i,v,node*2+2,mid,rx);
        tree[node] = merge(tree[node*2+1] , tree[node*2+2]);
    }

    void set(int i,int v){
        set(i,v,0,0,sz);
    }

    void update(int l,int r,int val,int node,int s,int e) {
        prop(node);
        if (s>=l && e<=r) {
            lazy[node] += val;
            prop(node);
            return ;
        }
        if (s>=r || e<=l)return ;
        int mid = (s+e)>>1;
        update(l,r,val,node*2+1,s,mid);
        update(l,r,val,node*2+2,mid,e);
        tree[node] = merge(tree[node*2+1] , tree[node*2+2]);
    }

    void update(int l,int r,int val) {
        update(l,r,val,0,0,sz);
    }

    Node mn(int l,int r,int node,int s,int e){
        prop(node);
        if (s >= r || e <= l) return neutral;
        if (s>=l && e<=r)return tree[node];
        int mid=(s+e)/2;
        return merge( mn(l,r,node*2+1,s,mid),mn(l,r,node*2+2,mid,e));
    }

    int mn(int l,int r){
        return mn(l,r,0,0,sz).mn;
    }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
set<tuple<int,int,int,int>>mo;
const int N = 2e5+5;
int a[N],rs=0,L,R;

void add(int idx) {
    
}
void rem(int idx) {
    
}

void pewpew() {

    mo.clear();
    rs=0,L = 1,R=0;
    int n,q;cin>>n>>q;
    int sq = sqrt(n);
    for (int i =0;i<n;i++)cin>>a[i];
    for (int i =0;i<q;i++) {
        int l,r;cin>>l>>r;
        l--,r--;
        mo.insert({l/sq,r,l,i});
    }
    int ans[q];
    for (auto it = mo.begin() ; it!=mo.end() ; it++) {
        auto [tt,r,l,idx] = *it;

        while(L < l)rem(L++);
        while(L > l)add(--L);
        while(R < r)add(++R);
        while(R > r)rem(R--);

        ans[idx] = rs; 
    }
    for (int i=0;i<q;i++)
        cout <<ans[i];

}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//sqrt
void build(int blk){
    for (int i =0;i<26;i++)
        fr[blk][i].clear();
    for (int i = blk*sq ; i < min(n,(blk+1)*sq);i++) {
        if (lazy[blk] != '*')
            s[i] = lazy[blk];
        fr[blk][s[i]-'a'].push_back(i);
    }
    lazy[blk] = '*';
}

void update(int l,int r,char c){
    build(l/sq);
    build(r/sq);
    for (int i = l ; i <= r;){
        if (i %sq == 0 && i + sq - 1 <= r){
            lazy[i/sq] = c;
            i+=sq;
        }
        else {
            s[i] = c;
            i++;
        }
    }
    build(l/sq);
    build(r/sq);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////





















// ################################ string ###############################
//////////////////////////////////////////////////////////////////////////

void Z(){
    int l = 0 , r = 0;
    for (int i =1;i<n;i++){
        if(i < r)
            z[i] = min(r-i,z[i-l]);
        while(i + z[i] < n && s[i+z[i]] == s[z[i]])
            z[i]++;
        if (i + z[i] > r)
            l = i , r = i + z[i] ;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void KMP(){
    for (int i = 1; i < n ; i++){
        int j = pi[i-1];
        while(j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

deque<int> manacher_odd(string &s){
    s = "@" + s + "!";
    int n = s.size();
    deque<int>pal(n);
    int l = 0 , r = 1;
    for (int i = 1 ; i < n ; i++ ){
        pal[i] = min(r-i , pal[l + (r - i)]);
        while(s[i - pal[i]] == s[i+pal[i]])
            pal[i]++;
        if (i + pal[i] > r)
            l = i - pal[i] , r = i + pal[i];
    }
    pal.pop_front();
    pal.pop_back();
    return pal;
}

deque<int> manacher_even_odd(string &s){
    string t;
    for(auto c:s)
        t += '#' , t+=c;
    t += '#';
    return manacher_odd(t);
}

signed main() {
/* ^^^ */    AhmedPlusPlus    /* ^^^ */

//    ->> practice makes perfect

    string s;cin>>s;
    deque<int>pal = manacher_even_odd(s);
    int mx = -1 , tar = -1;
    bool odd;
    for (int i = 1; i < pal.size() -1 ; i++){
        int nw = pal[i] - 1;
        if (nw > mx)
            mx = nw , tar = (i-1) / 2 , odd = i & 1;
    }
    string ans;
    for (int i = tar - mx/2 + (!odd) ; i <= tar + mx / 2 ; i++)
        ans += s[i];
    cout << ans << '\n';

}
///////////////////////////////////////////////////////////////////////////////////////
Tricks

// Number of distinct substrings in a string
/*
To count distinct substrings of a string s, append characters one by one and track new substrings.
When adding a character c to s, form t = s + c, then reverse t to turn suffixes into prefixes.
Compute the Z-function of reversed t to find the longest prefix that repeats elsewhere (z_max).
The number of new substrings ending in c is length(t) - z_max.
Summing this over all characters gives total distinct substrings.
The total time complexity is O(n²) for a string of length n.
*/
/////////////////////////////////////////////////////////////////////////////////////
// freq of each one
/*
    string s;cin>>s;
    string t ;
    vector<int>fr(n+1) , ans(n+5);
    for(int i = n-1; i >= 0 ; --i){
        t = s[i] + t;
        vector<int>z = Z(t);
        z[0] = n - i;
        vector<int>tmp(n+2);
        for (auto j:z)tmp[0]++ , tmp[j+1]--;
        for (int j = 1 ; j <= n ;++j)
            tmp[j] += tmp[j-1] , fr[tmp[j]]++;
    }
    int prv = 0;
    for (int i = n  ; i >= 1 ; --i)
        fr[i] -= prv , prv += fr[i];
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  suffix array
// very important note : if you want to concatenate two strings use this s = s1 + "*" + s2; 
// not "#" or "$"


//   n * log^2

vector<int>suffix_array(string &tmp){
    string s = tmp + "$";
    int n = s.size();
    vector<int>p(n) , c(n); // order , class
    {
        // k = 0
        vector<pair<int, int>> a(n);
        for (int i = 0; i < n; i++)a[i] = {s[i], i};
        sort(a.begin(), a.end());
        for (int i = 0; i < n; i++)p[i] = a[i].second;
        c[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            if (a[i].first == a[i - 1].first)
                c[p[i]] = c[p[i - 1]];
            else
                c[p[i]] = c[p[i - 1]] + 1;
        }
    }

    int k = 0;
    while((1 << k) < n){
        // k -> k + 1
        vector<pair<pair<int,int>,int>>a(n);
        for(int i =0;i<n;i++)
            a[i] = {{c[i], c[(i + (1 << k)) % n]} , i};
        sort(a.begin(), a.end());
        for (int i = 0; i < n; i++)p[i] = a[i].second;
        c[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            if (a[i].first == a[i - 1].first)
                c[p[i]] = c[p[i - 1]];
            else
                c[p[i]] = c[p[i - 1]] + 1;
        }
        k++;
    }
    return p;
}
/////////////////////////////////////////////////////////////////////////////////////////
//   fast suffix array
//   n * log

void count_sort(vector<int>&p , vector<int>&c){
    int n = p.size();
    vector<int>cnt(n);
    for (auto &x : c)
        cnt[x]++;
    vector<int>p_new(n);
    vector<int>pos(n);
    pos[0] = 0;
    for (int i =1;i<n;i++)
        pos[i] = pos[i-1] + cnt[i-1];
    for (auto &x:p){
        int i = c[x];
        p_new[pos[i]] = x;
        pos[i]++;
    }
    p = p_new;
}

vector<int>suffix_array(string &tmp){
    string s = tmp + "$";
    int n = s.size();
    vector<int>p(n) , c(n); // order , class
    {
        // k = 0
        vector<pair<int, int>> a(n);
        for (int i = 0; i < n; i++)a[i] = {s[i], i};
        sort(a.begin(), a.end());
        for (int i = 0; i < n; i++)p[i] = a[i].second;
        c[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            if (a[i].first == a[i - 1].first)
                c[p[i]] = c[p[i - 1]];
            else
                c[p[i]] = c[p[i - 1]] + 1;
        }
    }

    int k = 0;
    while((1 << k) < n){
        // k -> k + 1
        for (int i = 0; i < n ;i++)
            p[i] = (p[i] - (1 << k) + n) % n;
        count_sort(p,c);
        vector<int> c_new(n);
        c_new[p[0]] = 0;
        for(int i =1;i<n;i++){
            pair<int,int>prv = {c[p[i-1]],c[(p[i-1]+(1<<k)) % n]};
            pair<int,int>now = {c[p[i]],c[(p[i]+(1<<k)) % n]};
            if (now == prv)
                c_new[p[i]] = c_new[p[i-1]];
            else
                c_new[p[i]] = c_new[p[i-1]] + 1;
        }
        c = c_new;
        k++;
    }
    return p;
}

// to build LCP (longest common prefix)

    lcp = vector<int>(n);
    k = 0;
    for (int i = 0 ; i < n -1 ; i++){
        int pi = c[i];
        int j = p[pi-1];
        // lcp[i] = lcp(s[i..] , s[j..])
        while(s[i+k] == s[j+k])k++;
        lcp[pi] = k;
        k = max(0ll , k-1);
    }

/////////////////////////////////////////////////////////////////////////////////////////////////////










// ###################################### math #######################################
//////////////////////////////////////////////////////////////////////////////////////

long long FloorSumAP(long long a, long long b, long long c, long long n){
    if(!a) return (b / c) * (n + 1);
    if(a >= c or b >= c) return ( ( n * (n + 1) ) / 2) * (a / c) + (n + 1) * (b / c) + FloorSumAP(a % c, b % c, c, n);
    long long m = (a * n + b) / c;
    return m * n - FloorSumAP(c, c - b - 1, a, m - 1);
} // find sum of floor((a * i + b) / c) for i in [0, n] in O(log(n))
// from: https://asfjwd.github.io/2020-04-24-floor-sum-ap/



//  g ->  sum of floor((a * i + b) / c) for i in [0, n] in O(log(n))
//  h -> sum of (floor((a * i + b) / c) )^2 for i in [0, n] in O(log(n))

struct dat {
  long long f, g, h;
  dat(long long f = 0, long long g = 0, long long h = 0) : f(f), g(g), h(h) {};
};

long long mul(long long a, long long b){
  return (a * b) % MOD;
}

dat query(long long a, long long b, long long c, long long n){
  if(!a) return {mul(n + 1, b / c), mul(mul(mul(b / c, n), n + 1), inv2), mul(mul(n + 1, b / c), b /c)};
  long long f, g, h; 
  dat nxt;
  if(a >= c or b >= c){
    nxt = query(a % c, b % c, c, n);
    f = (nxt.f + mul(mul(mul(n, n + 1), inv2), a / c) + mul(n + 1, b / c)) % MOD;
    g = (nxt.g + mul(a / c, mul(mul(n, n + 1), mul(2 * n + 1, inv6))) + mul(mul(b / c, mul(n, n + 1)), inv2)) % MOD;
    h = (nxt.h + 2 * mul(b / c, nxt.f) + 2 * mul(a / c, nxt.g) + mul(mul(a / c, a / c), mul(mul(n, n + 1), mul(2 * n + 1, inv6))) + mul(mul(b / c, b / c), n + 1) + mul(mul(a / c, b / c), mul(n, n + 1)) ) % MOD;   
    return {f, g, h};
  }
  long long m = (a * n + b ) / c;
  nxt = query(c, c - b - 1, a, m - 1);
  f = (mul(m, n) - nxt.f) % MOD;
  g = mul( mul(m, mul(n, n + 1)) - nxt.h - nxt.f, inv2);
  h = (mul(n, mul(m, m + 1)) - 2 * nxt.g - 2 * nxt.f - f) % MOD;
  return {f, g, h};
}

///////////////////////////////////////////////////////////////////////////////////////////////////////// 
///////////////////////////////////////////////////////////////////////////////////////////////////////
//   math and hashing
const int N =  , base[2]={31,37},mod=1e9+7;
int pw[2][N];
int add(int a,int b) {
    return (a+b+mod)%mod;
}
int mul(int a,int b) {
    return(a*b)%mod;
}
int fp (int x,int n){
    int res=1;
    while(n>0){
        if (n%2==1)
            res = mul(res,x);
        x = mul(x,x);
        n/=2;
    }
    return res;
}
int midINV(int a) {
    return fp(a,mod-2);
}
void init() {
    for (int b=0;b<2;b++) {
        pw[b][0]=1;
        for (int i =1;i<N;i++)
            pw[b][i] = mul(pw[b][i-1],base[b]);
    }
}
vector<pair<int,int>>pre;

void HASH(string&s) {
    pair<int,int>sum;
    for (int i=0;i<s.size();i++) {
        sum.F = mul(sum.F,base[0]);
        sum.F = add(sum.F,s[i]-'a'+1);
        sum.S = mul(sum.S,base[1]);
        sum.S = add(sum.S,s[i]-'a'+1);
        pre.pb(sum);
    }
}
pair<int,int>get(int l,int r) {
    pair<int,int>rt;
    rt.F = add(pre[r].F ,  - mul((l?pre[l-1].F:0) , pw[0][r-l+1])) ;
    rt.S = add(pre[r].S ,  - mul((l?pre[l-1].S:0) , pw[1][r-l+1])) ;
    return rt;
}
//------------------------
/*
to get sum 2^(0*n) + 2^(1*n) + 2^(2*n) + 2^(3*n) + 2^(4*n) + .... + 2^(k*n)

 the formula is
    (   (2 ^ ((k+1)*n)) - 1   ) /   (  2^n - 1   )
    
    
    
 to get 
	a^1 + a^2 + a^3 + .... + a^k
    (a * (a^k - 1)) / (a-1)
    this doesn't work for a = 1
*/
long long c(int n, int k) {
     long long result = 1;
    for (int i = 0; i < k; ++i) {
        result *= (n - i);
        result /= (i + 1);
    }
    return result;
}

ll p(int n, int k) {
    ll result = 1;
    for (int i = 0; i < k; ++i) {
        result *= (n - i);
    }
    return result;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//matrix exponentiation
matrix mul(matrix &a , matrix &b)
{
    int n = a.size() , m = b[0].size();
    matrix res = zero(n , m);

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            for(int k=0; k<n; k++)
            {
                res[i][j] += a[i][k]*b[k][j];
                res[i][j] %= mod;
            }
        }
    }
    return res;
}

matrix matrix_fp(matrix &a , ll p)
{
    if (p==1)
        return a;

    matrix res = matrix_fp(a , p/2);
    res = mul(res , res);
    if (p%2) res = mul(res , a);

    return res;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////


double LOG( int x, int k){
    double answer;
    answer = log10( x ) / log10( k );
    return answer;
}

const int N = 2e5+7, P1 = 31, P2 = 37, mod= 1e9 + 7;

bitset<N> notPrime;
void sieve() {
    notPrime[0] = notPrime[1] = 1;
    for(int i = 2; i*i < N; i++) {
        if(notPrime[i]) continue;

        for(int j = i*i; j < N; j+=i)
            notPrime[j] = 1;
    }
}

int spf[N];
void SPF() {
    for(int i = 1; i < N; i++)
        spf[i] = i;
    for(int i = 2; i*i < N; i++) {
        if(spf[i] != i) continue;

        for(int j = i*i; j < N; j+=i)
            spf[j] = min(spf[j], i);
    }
}

short spf[N];
void SPF() {
    for(int i = 2; i*i < N; i++) {
        if(spf[i] != 0) continue;

        for(int j = i*i; j < N; j+=i) {
            if(spf[j] == 0)
                spf[j] = i;
        }
    }
}

int mul(int a, int b) {
    return (1LL * a * b) % mod;
}
 
int add(int a, int b) {
    a = (a + mod) % mod;
    b = (b + mod) % mod;
    return (a + b) % mod;
}
 
int fp(int b, int p) {
    if (b == 1 or p == 0)
        return 1;
 
    int ret = fp(b, p >> 1);
    ret = mul(ret, ret);
 
    if (p & 1)
        ret = mul(ret, b);
 
    return ret;
}
 
int inv(int a) {
    return fastPower(a, mod-2);
}

int divi(int a, int b) {
    return mult(a, inv(b));
}
 
int fact[N];


int nPr(int n, int r) {
    if(r > n) return 0;
    if(n < 0 || r < 0) return 0;
    return divi(fact[n], fact[n-r]);
}

int nCr(int n, int r) {
    if(r > n) return 0;
    if(n < 0 || r < 0) return 0;
    return divi(fact[n], mult(fact[r], fact[n-r]));
}

int sNb(int n, int k) {
    return nCr(n+k-1, n);
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
int 
mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

unsigned long long
mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
//------------------------------
void ReadIntLine(vector<int>& numbers)
{
    string line;
    getline(cin, line);

    istringstream is(line);

    numbers = vector<int>(istream_iterator<int>(is), istream_iterator<int>());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<int> rem;
sort(rem.begin(), rem.end());
rem.erase(unique(rem.begin(), rem.end()), rem.end());  
//////////////////////////////////////////////////////////////////////////////////////////////////////////////




