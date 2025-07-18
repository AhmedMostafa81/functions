const int N = ;
vector<int> gr[N];
int dfn[N];
int low[N];
bool vis[N];
int cnt;
// directed graph
// Need everything to be in one SCC
bool IsOneSCC(int u , int root) // the root of SCC
{
    low[u] = dfn[u] = cnt++;

    vis[u] = true;

    for (int adj : gr[u])
    {
        if (dfn[adj] == -1)
            if (!IsOneSCC(adj , root))
                return false;

        if (vis[adj])
            low[u] = min(low[u], low[adj]);
    }

    if (low[u] == dfn[u] && u != root)
        return false;

    return true;
}

void init(){
    cnt = 1;
    for (int i = 1; i < N; ++i)
    {
        gr[i].clear();
        dfn[i] = -1;
        vis[i] = false;
    }
}





// Bi connected 

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










