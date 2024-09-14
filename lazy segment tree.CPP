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

    Node mn(int l,int r,int node,int lx,int rx){
        prop(node);
        if (lx >= r || rx <= l) return neutral;
        if (lx>=l && rx<=r)return tree[node];
        int mid=(lx+rx)/2;
        return merge( mn(l,r,node*2+1,lx,mid),mn(l,r,node*2+2,mid,rx));
    }

    int mn(int l,int r){
        return mn(l,r,0,0,sz).mn;
    }
};
