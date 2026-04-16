//For any index i, find the nearest or farthest R such that the range [i, R] contains at most k distinct numbers, in O(log n) time.


/*
if you make it with pointers
you can make this trick to make it (10× faster than `new`)

const int MAXNODE = (40~50) * N;

Node pool[MAXNODE];
int ptr = 0;

Node* newnode(unsigned long long val) {
    Node* x = &pool[ptr++];
    x->l = x->r = nullptr;
    x->XOR = val;
    return x;
}

Node* merge(Node* l, Node* r) {
    Node* x = &pool[ptr++];
    x->l = l;
    x->r = r;
    x->XOR = 0;
    if (l) x->XOR ^= l->XOR;
    if (r) x->XOR ^= r->XOR;
    return x;
}

return new Node(0);   ->   return newnode(0);
return new Node(l , r); -> return merge(l , r);
*/




const int N = ;
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


    vector<Node*>v = {seg.build(0,n+5)};

// without pointers     (faster)


#define M ((st + ed) >> 1)

const int MAXM = ;          // max compressed positions
const int SZ = MAXM * 40 + 5;     // node pool size (2 * MAXM * log(MAXM)) (best practice is MAXM * (40~50))

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





//   bigger version

#define M ((st + ed) >> 1)

const int MAXM = 100002;
const int SZ = MAXM * 40 + 5;

// Persistent Segment Tree

int ptr = 1;
int L[SZ], R[SZ];

struct Node {
    long long sum = 0;
    int pref = 0 , suf = 0 , mx = 0  , len = 0 ; // neutral

    static Node leaf(int v){
        Node t;
        t.sum = v;
        t.pref = max(0,v);
        t.suf  = t.pref;
        t.mx   = t.pref;
        t.len  = 1;
        return t;
    }

    static Node merge(const Node &a,const Node &b){
        if(!a.len) return b;
        if(!b.len) return a;
        Node c;
        c.len = a.len + b.len;
        c.sum = a.sum + b.sum;
        c.pref = max((long long)a.pref , a.sum + b.pref);
        c.suf  = max((long long)b.suf , b.sum + a.suf);
        c.mx   = max({a.mx , b.mx , a.suf + b.pref});
        return c;
    }
};

Node Seg[SZ];

void init_segment_tree(){
    ptr = 1;
    L[0] = R[0] = 0;
    Seg[0] = Node();   // neutral node
}

int new_leaf(int v){
    int p = ptr++;
    L[p] = R[p] = 0;
    Seg[p] = Node::leaf(v);
    return p;
}

int Merge(int a,int b){
    int p = ptr++;
    L[p] = a;
    R[p] = b;
    Seg[p] = Node::merge(Seg[a], Seg[b]);
    return p;
}

int build(int st,int ed){
    if(st==ed) return new_leaf(-2e5);
    return Merge(build(st,M), build(M+1,ed));
}

int update(int old,int st,int ed,int pos,int val){
    if(st==ed) return new_leaf(val);

    if(pos<=M)
        return Merge(update(L[old],st,M,pos,val), R[old]);
    else
        return Merge(L[old], update(R[old],M+1,ed,pos,val));
}

Node query(int node,int st,int ed,int l,int r){
    if(r<st || l>ed) return Node();

    if(l<=st && ed<=r)
        return Seg[node];

    Node a = query(L[node],st,M,l,r);
    Node b = query(R[node],M+1,ed,l,r);

    return Node::merge(a,b);
}

