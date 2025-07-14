 //   n * log^2

vector<int>suffix_array(string &tmp){
    string s = tmp + "$";
    int n = s.size();
    vector<int>p(n) , c(n); // order , class
    {
        // k = 0
        vector<pair<int, int>> a(n);
        for (int i = 0; i < n; i++)a[i] = {s[i], i};
        sort(a.begin(), a.end());
        for (int i = 0; i < n; i++)p[i] = a[i].second;
        c[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            if (a[i].first == a[i - 1].first)
                c[p[i]] = c[p[i - 1]];
            else
                c[p[i]] = c[p[i - 1]] + 1;
        }
    }

    int k = 0;
    while((1 << k) < n){
        // k -> k + 1
        vector<pair<pair<int,int>,int>>a(n);
        for(int i =0;i<n;i++)
            a[i] = {{c[i], c[(i + (1 << k)) % n]} , i};
        sort(a.begin(), a.end());
        for (int i = 0; i < n; i++)p[i] = a[i].second;
        c[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            if (a[i].first == a[i - 1].first)
                c[p[i]] = c[p[i - 1]];
            else
                c[p[i]] = c[p[i - 1]] + 1;
        }
        k++;
    }
    return p;
}
/////////////////////////////////////////////////////////////////////////////////////////
//   fast suffix array
//   n * log

void count_sort(vector<int>&p , vector<int>&c){
    int n = p.size();
    vector<int>cnt(n);
    for (auto &x : c)
        cnt[x]++;
    vector<int>p_new(n);
    vector<int>pos(n);
    pos[0] = 0;
    for (int i =1;i<n;i++)
        pos[i] = pos[i-1] + cnt[i-1];
    for (auto &x:p){
        int i = c[x];
        p_new[pos[i]] = x;
        pos[i]++;
    }
    p = p_new;
}

vector<int>suffix_array(string &tmp){
    string s = tmp + "$";
    int n = s.size();
    vector<int>p(n) , c(n); // order , class
    {
        // k = 0
        vector<pair<int, int>> a(n);
        for (int i = 0; i < n; i++)a[i] = {s[i], i};
        sort(a.begin(), a.end());
        for (int i = 0; i < n; i++)p[i] = a[i].second;
        c[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            if (a[i].first == a[i - 1].first)
                c[p[i]] = c[p[i - 1]];
            else
                c[p[i]] = c[p[i - 1]] + 1;
        }
    }

    int k = 0;
    while((1 << k) < n){
        // k -> k + 1
        for (int i = 0; i < n ;i++)
            p[i] = (p[i] - (1 << k) + n) % n;
        count_sort(p,c);
        vector<int> c_new(n);
        c_new[p[0]] = 0;
        for(int i =1;i<n;i++){
            pair<int,int>prv = {c[p[i-1]],c[(p[i-1]+(1<<k)) % n]};
            pair<int,int>now = {c[p[i]],c[(p[i]+(1<<k)) % n]};
            if (now == prv)
                c_new[p[i]] = c_new[p[i-1]];
            else
                c_new[p[i]] = c_new[p[i-1]] + 1;
        }
        c = c_new;
        k++;
    }
    return p;
}
