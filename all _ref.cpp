#include<bits/stdc++.h>
ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
///////////////////////////////////////////////////////////////////////
const int N = ;
vector<int> e[N];
int f[N][22], dep[N];
int dfn[N], tot;
void dfs(int u = 1, int fa = 0) {
    dep[u] = dep[fa] + 1;
    f[u][0] = fa;
    dfn[u] = ++tot;
    for(int i = 1;i<22;++i) f[u][i] = f[f[u][i - 1]][i - 1];
    for(int v : e[u]) if(v != fa) {
        dfs(v, u);
    }
}
int LCA(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    for(int i = 21;~i;--i) {
        if(dep[f[u][i]] >= dep[v]) u = f[u][i];
        if(u == v) return u;
    }
    for(int i = 21;~i;--i) {
        if(f[u][i] != f[v][i]) {
            u = f[u][i];
            v = f[v][i];
        }
    }
    return f[u][0];
}
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
/////////////////////////////////////////////////////////////////////////
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
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type,less_equal<int>, rb_tree_tag,tree_order_statistics_node_update>

ordered_set st;
st.order_of_key(number);// number of elem. less than (..)
find_by_order(index) // get by index
/////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<int> rem;
sort(rem.begin(), rem.end());
rem.erase(unique(rem.begin(), rem.end()), rem.end());   
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
///////////////////////////////////////////////////////////////////////////////////////////////////////
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

void precalFactorial() {
    fact[0] = 1;

    for(int i =1 ; i < N; i++)
        fact[i] = mult(fact[i-1], i);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////////////////////////////
template < typename T = int > struct Sparse_Table {

    struct Node {
        ll val;
        Node(ll V = 0) : val(V) {}
        Node operator = (const T& rhs) {
            val = rhs;
            return *this;
        }
    };

    int n, LOG;
    vector < vector < Node > > table;
    vector < int > Bin_Log;
    Node DEFAULT;

    Sparse_Table(vector < T >& vec){
        n = sz(vec), DEFAULT = 0, LOG = __lg(n) + 1;
        table = vector < vector < Node > > (n + 10, vector < Node > (LOG));
        Bin_Log = vector < int > (n + 10);
        for(int i = 2; i <= n; i++)
            Bin_Log[i] = Bin_Log[i >> 1] + 1;
        for(int i = 0; i < n; i++)
            table[i][0] = vec[i];
        Build_Table();
    }

    Node operation(Node a, Node b){
        Node res;
        res.val = a.val + b.val;
        return res;
    }

    void Build_Table(){
        for(int log = 1; log < LOG; log++)
            for(int i = 0; i + (1 << log) - 1 < n; i++)
                table[i][log] = operation(table[i][log - 1], table[i + (1 << (log - 1))][log - 1]);
    }

    Node query_1(int L, int R){
        int log = Bin_Log[R - L + 1];
        return operation(table[L][log], table[R - (1 << log) + 1][log]);
    }
    

};
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

void ReadDoubleLine(vector<string>& numbers)
{
    string line;
    getline(cin, line);

    istringstream is(line);

    numbers = vector<string>(istream_iterator<string>(is), istream_iterator<string>());
}
