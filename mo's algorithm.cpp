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
