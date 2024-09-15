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
        else {
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


// orderd set
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type,less_equal<int>, rb_tree_tag,tree_order_statistics_node_update>

ordered_set st;
st.order_of_key(number);// number of elem. less than (..)
find_by_order(index) // get by index


the lexicographically largest†
 subsequence of string s

    string s;cin>>s;int n=s.size();
    int index_mx;
    char mx='a'-1;
    for (int i =0;i<n;i++){
        if (s[i]>mx){
            mx=s[i];
            index_mx=i;
        }
    }
    vector<pair<char,int>>v;
    for (int i =index_mx+1;i<n;i++){
        v.pb({s[i],-1*i});
    }
    sort(rall(v));
    int prv=-1;
    string sol="";sol.pb(mx);
    for (int i =0;i<v.size();i++){
        if ((v[i].S*-1)>prv){
            sol.pb(v[i].F);
            prv=(v[i].S*-1);
        }
    }
    cout <<sol;

