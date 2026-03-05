const int N = 2e5+5;
int a[N];

struct V {
    V *l, *r;
    long long sum;

    V(int val) : l(nullptr), r(nullptr), sum(val) {}
    V(V *l, V *r) : l(l), r(r), sum(0) {
        if (l) sum += l->sum;
        if (r) sum += r->sum;
    }
};

V* build( int tl, int tr) {
    if (tl == tr)
        return new V(a[tl]);
    int tm = (tl + tr) / 2;
    return new V(build( tl, tm), build(tm+1, tr));
}

long long get_sum(V* v, int tl, int tr, int l, int r) {
    if (l > r)
        return 0;
    if (l == tl && tr == r)
        return v->sum;
    int tm = (tl + tr) / 2;
    return get_sum(v->l, tl, tm, l, min(r, tm))
         + get_sum(v->r, tm+1, tr, max(l, tm+1), r);
}

V* update(V* v, int tl, int tr, int pos, int new_val) {
    if (tl == tr)
        return new V(new_val);
    int tm = (tl + tr) / 2;
    if (pos <= tm)
        return new V(update(v->l, tl, tm, pos, new_val), v->r);
    else
        return new V(v->l, update(v->r, tm+1, tr, pos, new_val));
}

void maybe() {

    int n , q;cin >> n >> q;
    for (int i  = 0; i < n ; i++)
        cin >> a[i];
    vector<V*>roots;
    roots.push_back(build(0,n-1));
    while (q--) {
        int op , k , a, b , x; cin >> op;
        if (op == 1) {
            cin >> k >> a >> x;
            --k , --a;
            roots[k] = update(roots[k] , 0,n-1,a , x);
        }
        else if (op == 2) {
            cin >> k >> a >> b;
            --k , --a , --b;
            cout << get_sum(roots[k] ,0,n-1, a , b) << '\n';
        }
        else {
            cin >> k ;
            --k;
            roots.push_back(roots[k]);
        }
    }

}
