const int N = , LOG = ;
vector<int> gr[N];
int  in[N], out[N], tim, up[N][LOG];

void pre(int node = 1, int par = 1){
    in[node] = ++tim;
    up[node][0] = par;

    for (int i = 1; i < LOG; i++)
        up[node][i] = up[up[node][i-1]][i-1];

    for (auto ch : gr[node]){
        if (ch == par) continue;
        pre(ch, node);
    }

    out[node] = ++tim;
}

bool if_anc(int x, int y){
    return in[x] <= in[y] && out[x] >= out[y];
}

int LCA(int x, int y){
    if (if_anc(x, y))
        return x;
    if (if_anc(y, x))
        return y;

    for (int i = LOG - 1; i >= 0; i--)
        if (!if_anc(up[x][i], y))
            x = up[x][i];

    return up[x][0];
}






// LCA , HASHING , BINARY SEARCH
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define AhmedPlusPlus ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define hi cerr<<"HI\n";
#define el '\n'

/*                        ->    NO CLEAN CODE HERE    <-                        */

const int N = 1e5+5 , LOG = 18 , base = 31 , mod = 1e9+7;
int add(int x,int y){
    return (x + y + mod) % mod;
}
int mul(int a,int b){
    return (a * b)%mod;
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
    return fp(a, mod-2);
}
vector<int>gr[N];
int n,q , up[N][LOG] , in[N] , out[N] , tim , dis[N]  , pw[N] , INV[N];
string s;

struct HA{
    int H = 0 , _H = 0 , sz = 0;
}HASH[N];

HA merge(HA a,HA b){
    HA rt;
    rt.H = mul(a.H , pw[b.sz]);
    rt.H = add(rt.H , b.H);

    rt._H = add(a._H , mul(b._H , pw[a.sz]));

    rt.sz = a.sz + b.sz;
    return rt;
}

HA single(char c){
    HA rt;
    rt.H = c - 'a' + 1;
    rt._H = c - 'a' + 1;
    rt.sz = 1;
    return rt;
}

HA sub(HA R , HA L){
    HA rt;
    int tar = R.sz - L .sz;
    // cout<<R.H<<" "<<L.H<<" "<<tar<<el;
    rt.H = add (R.H , - mul(L.H , pw[tar]));
    rt._H = add(R._H , -L._H);
    rt._H = mul(rt._H , INV[L.sz]);
    rt.sz = tar;
    return rt;
}

void init(){
    tim = 0 ;
    for (int i =1;i<=n;i++)gr[i].clear();
}

void pre(int node = 1 , int par = 1){
    in[node] = ++tim;
    up[node][0] = par;
    HASH[node] = single(s[node]);
    if(node!=1)
        HASH[node] = merge(HASH[par], HASH[node]);

    for (int i = 1 ; i < LOG ; i++)
        up[node][i] = up[up[node][i-1]][i-1];
    for (auto ch:gr[node])
        if (ch != par) {
            dis[ch] = dis[node] + 1;
            pre(ch, node);
        }
    out[node] = ++tim;
}

bool anc(int x,int y){
    return in[x] <= in[y] && out[x] >= out[y];
}

int LCA(int x,int y){
    if(anc(x,y))return x;
    if(anc(y,x))return y;
    for (int i = LOG - 1 ; i >= 0; --i)
        if (!anc(up[x][i] , y))
            x = up[x][i];
    return up[x][0];
}

int len(int x,int y){
    return dis[x] + dis[y] - dis[LCA(x,y)]*2;
}

int Kth(int node , int k){
    for(int i = LOG - 1 ; i >= 0 ; i--)
        if ((k >> i) & 1)
            node = up[node][i];
    return node;
}

int get_node(int from,int to,int tar){
    int lca = LCA(from,to);
    if (len(from, lca) >= tar)
        return Kth(from , tar);
    else
        return Kth(to, len(to,lca) - (tar - len(from, lca)) );
}

HA good (int from ,int to){
    // cout<<"test "<<from<<" "<<to<<el;
    return sub(HASH[from] , HASH[to]);
}

HA bad(int from,int to){
    HA rt = good(to,from);
    swap(rt.H , rt._H);
    return rt;
}

int get_hash(int from,int to){
    // cout<<from<<" "<<to<<el;
    int lca = LCA(from,to);
    // cout<<"lca "<<lca<<el;
    HA rt = bad(lca , from);
    // cout<<"test1 "<<rt.H<<el;
    rt = merge(rt , single(s[lca]));
    // cout<<"test2 "<<rt.H<<el;
    rt = merge(rt,good(to,lca));
    // cout<<"test3 "<<rt.H<<el;
    return rt.H;
}

int get(int from ,int to,int tar){
    // cout<<tar<<el;
    return get_hash(from , get_node(from , to , tar));
}

int solve(int a,int b,int x,int y){
    int sz1 = len(a , b);
    int sz2 = len(x , y);
    int st = 0 , ed = min(sz1 , sz2) , mid , fin = -1;
    while(st <= ed){
        mid = st + ed >> 1;
        if (get(a,b,mid) != get(x,y,mid))
            fin = mid , ed = mid - 1;
        else
            st = mid + 1;
    }
    if (fin == -1){
        if (sz1 > sz2)
            return 1;
        else if (sz1 < sz2)
            return 2;
        return 0;
    }
    else {
        char c1 = s[get_node(a,b,fin)];
        char c2 = s[get_node(x,y,fin)];
        if (c1 > c2)
            return 1;
        return 2;
    }
}

void pewpew(){

    cin>>n>>s;
    init();
    s = "*" + s;
    for (int i=0,x,y;i<n-1;i++){
        cin>>x>>y;
        gr[x].push_back(y);
        gr[y].push_back(x);
    }
    pre();
    cin>>q;
    while(q--){
        int a,b,x,y;cin>>a>>b>>x>>y;
        cout <<  solve(a,b,x,y) << '\n';
    }
    // cout << HASH[2].H << '\n';
    // cout << HASH[2]._H << '\n';

}

signed main() {
/* ^^^ */    AhmedPlusPlus    /* ^^^ */

//    ->> practice makes perfect


    pw[0] = INV[0] = 1;
    for (int i = 1; i<N;i++){
        pw[i] = mul(pw[i-1] , base);
        INV[i] = mul(INV[i-1] , inv(base));
    }
    int Hi;cin>>Hi;
    while(Hi--)
        pewpew();

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
