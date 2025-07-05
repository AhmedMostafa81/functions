void Z(){
    int l = 0 , r = 0;
    for (int i =1;i<n;i++){
        if(i < r)
            z[i] = min(r-i,z[i-l]);
        while(i + z[i] < n && s[i+z[i]] == s[z[i]])
            z[i]++;
        if (i + z[i] > r)
            l = i , r = i + z[i] ;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void KMP(){
    for (int i = 1; i < n ; i++){
        int j = pi[i-1];
        while(j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

deque<int> manacher_odd(string &s){
    s = "@" + s + "!";
    int n = s.size();
    deque<int>pal(n);
    int l = 0 , r = 1;
    for (int i = 1 ; i < n ; i++ ){
        pal[i] = min(r-i , pal[l + (r - i)]);
        while(s[i - pal[i]] == s[i+pal[i]])
            pal[i]++;
        if (i + pal[i] > r)
            l = i - pal[i] , r = i + pal[i];
    }
    pal.pop_front();
    pal.pop_back();
    return pal;
}

deque<int> manacher_even_odd(string &s){
    string t;
    for(auto c:s)
        t += '#' , t+=c;
    t += '#';
    return manacher_odd(t);
}

signed main() {
/* ^^^ */    AhmedPlusPlus    /* ^^^ */

//    ->> practice makes perfect

    string s;cin>>s;
    deque<int>pal = manacher_even_odd(s);
    int mx = -1 , tar = -1;
    bool odd;
    for (int i = 1; i < pal.size() -1 ; i++){
        int nw = pal[i] - 1;
        if (nw > mx)
            mx = nw , tar = (i-1) / 2 , odd = i & 1;
    }
    string ans;
    for (int i = tar - mx/2 + (!odd) ; i <= tar + mx / 2 ; i++)
        ans += s[i];
    cout << ans << '\n';

}
///////////////////////////////////////////////////////////////////////////////////////
Tricks

// Number of distinct substrings in a string
/*
To count distinct substrings of a string s, append characters one by one and track new substrings.
When adding a character c to s, form t = s + c, then reverse t to turn suffixes into prefixes.
Compute the Z-function of reversed t to find the longest prefix that repeats elsewhere (z_max).
The number of new substrings ending in c is length(t) - z_max.
Summing this over all characters gives total distinct substrings.
The total time complexity is O(n²) for a string of length n.
*/
/////////////////////////////////////////////////////////////////////////////////////
// freq of each one
/*
    string s;cin>>s;
    string t ;
    vector<int>fr(n+1) , ans(n+5);
    for(int i = n-1; i >= 0 ; --i){
        t = s[i] + t;
        vector<int>z = Z(t);
        z[0] = n - i;
        vector<int>tmp(n+2);
        for (auto j:z)tmp[0]++ , tmp[j+1]--;
        for (int j = 1 ; j <= n ;++j)
            tmp[j] += tmp[j-1] , fr[tmp[j]]++;
    }
    int prv = 0;
    for (int i = n  ; i >= 1 ; --i)
        fr[i] -= prv , prv += fr[i];
*/






