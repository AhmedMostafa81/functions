struct Node {
    int mn=inf;
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


// another version
// range sum + range add + range multiply


struct lazy_segment_tree {
    struct Node {
        long long sum = 0;
    };

    struct Tag {
        long long mul = 1;
        long long add = 0;
    };

    int sz;
    vector<Node> tree;
    vector<Tag> lazy;

    Node neutral;

    void init(int n) {
        sz = 1;
        while (sz < n) sz <<= 1;
        tree.assign(2 * sz, neutral);
        lazy.assign(2 * sz, Tag());
    }

    Node merge(const Node& a, const Node& b) {
        return Node{a.sum + b.sum};
    }

    // old first, then new
    Tag compose(const Tag& old, const Tag& nw) {
        return Tag{
            old.mul * nw.mul,
            old.add * nw.mul + nw.add
        };
    }

    void apply(int node, int lx, int rx, const Tag& t) {
        tree[node].sum = tree[node].sum * t.mul + t.add * (rx - lx);
        lazy[node] = compose(lazy[node], t);
    }

    void push(int node, int lx, int rx) {
        if (lazy[node].mul == 1 && lazy[node].add == 0) return;
        if (rx - lx == 1) {
            lazy[node] = Tag();
            return;
        }

        int mid = (lx + rx) / 2;
        apply(node * 2 + 1, lx, mid, lazy[node]);
        apply(node * 2 + 2, mid, rx, lazy[node]);
        lazy[node] = Tag();
    }

    void build(const vector<long long>& a, int node, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < (int)a.size()) tree[node].sum = a[lx];
            return;
        }

        int mid = (lx + rx) / 2;
        build(a, node * 2 + 1, lx, mid);
        build(a, node * 2 + 2, mid, rx);
        tree[node] = merge(tree[node * 2 + 1], tree[node * 2 + 2]);
    }

    void build(const vector<long long>& a) {
        init((int)a.size());
        build(a, 0, 0, sz);
    }

    void update(int l, int r, const Tag& t, int node, int lx, int rx) {
        if (r <= lx || rx <= l) return;
        if (l <= lx && rx <= r) {
            apply(node, lx, rx, t);
            return;
        }

        push(node, lx, rx);
        int mid = (lx + rx) / 2;
        update(l, r, t, node * 2 + 1, lx, mid);
        update(l, r, t, node * 2 + 2, mid, rx);
        tree[node] = merge(tree[node * 2 + 1], tree[node * 2 + 2]);
    }

    void add(int l, int r, long long x) {
        update(l, r, Tag{1, x}, 0, 0, sz);
    }

    void mul2(int l, int r) {
        update(l, r, Tag{2, 0}, 0, 0, sz);
    }

    Node query(int l, int r, int node, int lx, int rx) {
        if (r <= lx || rx <= l) return neutral;
        if (l <= lx && rx <= r) return tree[node];

        push(node, lx, rx);
        int mid = (lx + rx) / 2;
        return merge(
            query(l, r, node * 2 + 1, lx, mid),
            query(l, r, node * 2 + 2, mid, rx)
        );
    }

    long long sum(int l, int r) {
        return query(l, r, 0, 0, sz).sum;
    }
};
