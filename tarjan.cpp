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
