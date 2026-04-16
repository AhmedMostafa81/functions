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
