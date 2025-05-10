vector<tuple<int,int,int,int>>mo;
int a[N],L,R;

void add(int idx) {

}
void rem(int idx) {

}

void pewpew() {
    
    L = 0,R=-1;
    int n,q;cin>>n>>q;
    int sq = sqrt(n)+2;
    for (int i =0;i<n;i++)cin>>a[i];
    for (int i =0;i<q;i++) {
        int l,r,x;cin>>l>>r>>x;
        l--,r--;
        mo.pb({l/sq,r,l,i});
    }
    int ans[q];
    sort(all(mo));
    for (auto &[tt,r,l,idx]:mo) {

        while(L > l)add(--L);
        while(R < r)add(++R);
        while(L < l)rem(L++);
        while(R > r)rem(R--);

        ans[idx] = ;
    }
    for (int i=0;i<q;i++)
        cout <<ans[i] << '\n';

}
