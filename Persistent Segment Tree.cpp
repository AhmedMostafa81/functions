
const int N = 3e4+10;
int fr[N];

struct Node {
    Node *l , *r;
    int sum = 0;
    Node(int val):l(nullptr) , r(nullptr) , sum(val){}
    Node(Node *l ,Node *r) :l(l) , r(r) , sum(0) {
        if (l) sum += l -> sum;
        if (r) sum += r -> sum;
    }
};

struct persistent_segment_tree {
    Node* build(int st ,int ed) {
        if (st == ed)
            return new Node(fr[st]);
        int mid = (st + ed) >> 1;
        return new Node(build(st , mid) , build(mid + 1 , ed));
    }
    Node* update(Node* v, int st , int ed , int pos , int new_fr) {
        if (st == ed)
            return new Node(new_fr);
        int mid = (st + ed) >> 1;
        if (pos <= mid)
            return new Node(update(v->l , st , mid , pos , new_fr) ,v->r );
        else
            return new Node(v->l , update(v->r , mid + 1 , ed , pos , new_fr)  );
    }
    int query(Node* L , Node* R , int st , int ed , int k) {
        if (st >= k)
            return R->sum - L->sum;
        if (ed < k)
            return 0;
        int mid = (st + ed) >> 1;
        return query(L->l , R->l , st , mid , k) + query(L -> r , R -> r , mid + 1 , ed , k );
    }
};

int a[N] ;

void maybe() {

    int n ; cin >> n ;
    set<int>st;
    for (int i = 0; i < n ; i++)
        cin >> a[i] , st.insert(a[i]);
    int cur = 0 ;
    map<int,int>id;
    for (auto num:st)
        id[num] = cur++;
    persistent_segment_tree seg;
    vector<Node*>v = {seg.build(0,n+5)};
    for (int  i = 0 ; i < n ; i++) {
        fr[id[a[i]]]++;
        v.push_back(seg.update(v.back() , 0 , n+5 , id[a[i]] , fr[id[a[i]]]));
    }
    int q;cin >> q;
    int last_ans = 0 ;
    while (q--) {
        int a , b , c; cin >> a >> b >> c;
        int i = a ^ last_ans;
        int j = b ^ last_ans;
        int k = c ^ last_ans;
        i = max(i , 1);
        j = min(j , n);
        if (i > j)
            last_ans = 0 ;
        else {
            auto it = st.upper_bound(k);
            if (it != st.end())
                last_ans = seg.query(v[i-1],v[j],0,n+5,id[*it]);
            else
                last_ans = 0;
        }
        cout << last_ans << '\n';
    }

}






// without pointers     (faster)


#define M ((st + ed) >> 1)

const int MAXM = 5000;          // max compressed positions
const int SZ = MAXM * 20 + 5;     // node pool size (MAXM * log(MAXM)) (best practice is MAXM * 20)

int ptr = 1;
int L[SZ], R[SZ];
long long sum[SZ]; // sum of each node in segment tree
int A[MAXM + 5]; // array (input)


//Persistent Segment Tree

void init_segment_tree(){ // initialize segment tree
    ptr = 1;
    L[0] = R[0] = 0;
    sum[0] = 0;
}

int leaf(int v){
    int p = ptr++;
    L[p] = R[p] = 0;
    sum[p] = v;
    return p;
}

int Merge(int a, int b){
    int p = ptr++;
    L[p] = a; R[p] = b;
    sum[p] = sum[a] + sum[b];
    return p;
}

int build(int st, int ed){
    if (st == ed) return leaf(A[st]);
    return Merge(build(st , M) , build(M + 1 , ed));
}

int update(int old, int st, int ed, int pos, int new_val){
    if (st == ed)
        return leaf(new_val);
    if (pos <= M)
        return Merge(update(L[old], st, M, pos, new_val),R[old]);
    else
        return Merge(L[old] , update(R[old], M + 1, ed, pos, new_val));
}

long long query(int L_node, int R_node, int st, int ed, int k){
    if (st >= k) return sum[R_node] - sum[L_node];
    if (ed < k) return 0;
    return query(L[L_node], L[R_node], st, M, k) + query(R[L_node], R[R_node], M + 1, ed, k);
}

