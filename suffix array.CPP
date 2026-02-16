// very important note : if you want to concatenate two strings use this s = s1 + "*" + s2; 
// not "#" or "$"


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

// to build LCP (longest common prefix)

    lcp = vector<int>(n);
    k = 0;
    for (int i = 0 ; i < n -1 ; i++){
        int pi = c[i];
        int j = p[pi-1];
        // lcp[i] = lcp(s[i..] , s[j..])
        while(s[i+k] == s[j+k])k++;
        lcp[pi] = k;
        k = max(0ll , k-1);
    }




vector<int>match(string s1 , string s2) {
    vector<int>lcp;
    string s = s1 + "*" + s2;
    vector<int>help = suffix_array(s , lcp);
    int me = -1;
    for (int i = 0; i < help.size() ; i++)
        if (help[i] == s1.size() + 1)
            me = i;
    vector<int>v(s1.size() , 0);
    int cur = me-1 , mn = 1e10;
    while (cur >= 0) {
        mn = min(mn ,lcp[cur+1]);
        if (mn >= s2.size())
            v[help[cur]] = 1;
        else
            break;
        cur--;
    }
    cur = me + 1 , mn = 1e10;
    while (cur < help.size()) {
        mn = min(mn ,lcp[cur]);
        if (mn >= s2.size())
            v[help[cur]] = 1;
        else
            break;
        cur++;
    }
    return v;
}








// get Kth subarray or how many subarrays equal



//    ->> practice makes perfect


#include<bits/stdc++.h>
using namespace std;

/* ===================  NO CLEAN CODE HERE  =================== */

void count_sort(vector<int>&p , vector<int>&c) {
    int n = p.size();
    vector<int>cnt(n);
    for (auto &x:c)
        cnt[x]++;
    vector<int>p_new(n);
    vector<int>pos(n);
    pos[0] = 0;
    for (int i  = 1; i < n ; i++)
        pos[i] = pos[i-1] + cnt[i-1];
    for (auto &x:p) {
        int i = c[x];
        p_new[pos[i]] = x;
        pos[i]++;
    }
    p = p_new;
}

vector<int>suffix_adday(string &tmp , vector<int>&lcp) {
    string s = tmp + "$";
    int n = s.size();
    vector<int>p(n) , c(n);
    {
        vector<pair<int,int>>a(n);
        for (int i = 0; i < n ; i++)
            a[i] = {s[i] , i};
        sort(a.begin() , a.end());
        for (int i = 0; i < n ; i++)
            p[i] = a[i].second;
        c[p[0]] = 0;
        for (int i  = 1; i <n ; i ++) {
            if (a[i].first == a[i-1].first)
                c[p[i]] = c[p[i-1]];
            else
                c[p[i]] = c[p[i-1]] + 1;
        }
    }
    int k = 0 ;
    while ((1 << k) < n) {
        for (int i  =0 ; i < n ; i++)
            p[i] = (p[i] - (1 << k) + n)%n;
        count_sort(p,c);
        vector<int>c_new(n);
        c_new[p[0]] = 0;
        for (int i = 1; i < n ; i++) {
            pair<int,int>prv = {c[p[i-1]] , c[(p[i-1]+(1<<k)) % n]};
            pair<int,int>now = {c[p[i]] , c[(p[i]+(1<<k)) % n]};
            if (now == prv)
                c_new[p[i]] = c_new[p[i-1]];
            else
                c_new[p[i]] = c_new[p[i-1]] + 1;
        }
        k++;
        c = c_new;
    }

    lcp = vector<int>(n);
    k = 0 ;
    for (int i = 0 ; i < n-1 ; i++) {
        int pi = c[i];
        int j = p[pi-1];
        while (s[i+k] == s[j+k])k++;
        lcp[pi] = k;
        k = max(0 , k-1);
    }

    return p;
}

struct SP { // sparse table

    int n , lg;
    vector<vector<int>>t;
    vector<int>log;
    int merge(int a,int b){return min(a , b) ; }

    SP(vector<int>&a) {
        n = a.size();
        log.assign(n+1 , 0);
        for (int i  = 2 ; i <= n ; i++)
            log[i] = log[i/2] + 1;
        lg = log[n] + 1;
        t.assign(lg , vector<int>(n));

        for (int i  = 0; i < n ; i++)
            t[0][i] = a[i];
        for (int j = 1;  j < lg ; j++)
            for (int i  = 0; i + (1 << j) <= n ;i++)
                t[j][i] = merge(t[j-1][i] , t[j-1][i + (1 << (j-1))]);
    }

    int get(int l,  int r) {
        int j = log[r-l+1];
        return merge(t[j][l] , t[j][r - (1 << j) + 1]);
    }

    int get_first_less_than(int idx , int val) {
        int s = idx , e = n-1 , mid , rt = n;
        while (s <= e) {
            mid = (s + e) >> 1;
            if (get(idx , mid) < val)
                rt = mid , e = mid - 1;
            else
                s = mid + 1;
        }
        return rt;
    }

};

void maybe() {

    string s;cin>>s;
    int n = s.size();
    int k ; cin >> k;
    if (k > 1ll * n *(n + 1) / 2)
        return void(cout << "No such line.\n");
    vector<int>lcp , sa;
    sa = suffix_adday(s , lcp);

    SP table(lcp);

    int cur = 0 ;
    for (int i = 1 ; i < lcp.size() ; i++) {
        int from = sa[i];
        for (int to = sa[i] + lcp[i] ; to < n ; to++) {
            int sz = to - from + 1;
            int cnt = table.get_first_less_than(i + 1 , sz) - i ;
            if (cur + cnt >= k) {
                cout << s.substr(from , sz) << '\n';
                return ;
            }
            cur += cnt;
        }
    }

}


signed main() {

    ios::sync_with_stdio(0);cin.tie(0);
    int tc = 1;
    //cin>>tc;
    while(tc--)
        maybe();

}
