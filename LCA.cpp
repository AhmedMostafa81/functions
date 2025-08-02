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
