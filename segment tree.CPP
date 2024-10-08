struct segment_tree{
    int sz;
    vector<int>sums;
    void init(int n){
        sz=1;
        while(sz < n)sz*=2;
        sums.assign(2*sz,0);
    }

    void set(int i ,int v,int node,int lx,int rx){
        if (rx-lx==1) {
            sums[node] = v;
            return ;
        }
        int mid = (lx+rx)/2;
        if (i<mid)
            set(i,v,node*2+1,lx,mid);
        else
            set(i,v,node*2+2,mid,rx);
        sums[node] = sums[node*2+1] + sums[node*2+2];
    }

    void set(int i,int v){
        set(i,v,0,0,sz);
    }

    int sum(int l,int r,int node,int lx,int rx){
        if (lx >= r || rx <= l) return 0;
        if (lx>=l && rx<=r)return sums[node];
        int mid=(lx+rx)/2;
        return sum(l,r,node*2+1,lx,mid)+sum(l,r,node*2+2,mid,rx);
    }

    int sum(int l,int r){
        return sum(l,r,0,0,sz);
    }
};
