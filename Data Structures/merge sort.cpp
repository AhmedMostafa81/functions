struct MergeSortTree {
    int n ;
    vector<vector<int>>seg;
    MergeSortTree(const vector<int>&a) {
        n = a.size();
        seg.resize(4*n);
        build(1 , 0 , n-1 , a);
    }

    void build(int node , int l , int r , const vector<int>&a) {
        if (l == r) {
            seg[node] = {a[l]};
            return ;
        }
        int mid = (l + r) >> 1;
        build(node << 1 , l , mid , a);
        build(node << 1 | 1, mid + 1 , r , a);
        auto &L = seg[node << 1];
        auto &R = seg[node << 1 | 1];
        seg[node].resize(L.size() + R.size());
        merge(L.begin() , L.end(),
              R.begin() , R.end(),
              seg[node].begin());
    }
    int query(int node , int l , int r , int ql,int qr,int x) {
        if (r < ql || l > qr)return 0;
        if (ql <= l && r <= qr)
            return lower_bound(seg[node].begin() , seg[node].end() , x) - seg[node].begin();
        int mid = ( l + r) >> 1;
        return query(node<<1,l,mid,ql,qr,x)+
            query(node<<1|1,mid+1,r,ql,qr,x);
    }
    int query(int l , int r , int x) {
        return query(1 , 0 , n-1 , l , r , x);
    }
    int get(int l , int r , int valL , int valR) {
        return query(l,r,valR+1)-query(l,r,valL);
    }

};
