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
------------------------------------------------------------------------------
    // optimization
int get(int prv , char c){
    if (~dp[prv][c-'a'])return dp[prv][c-'a'];
    int nxt = prv;
    if (prv > 0 && c != s[prv])
        nxt = get(pi[prv-1],c) ;
    return dp[prv][c-'a'] = nxt;
}
void KMP(){
    for (int i =1;i<n;i++) {
        int j = get(pi[i - 1], s[i]);
        pi[i] = j + (s[i] == s[j]);
    }
}
void dfs(int node = 1){
    for (const auto &[ch,t]:gr[node]){
        int prv = p[node];
        for (int i = 0 ;i<t.size();i++){
            prv = get(prv , t[i]);
            if (t[i] == s[prv])prv++;
            if (prv == n-1) ans++;
        }
        p[ch] = prv;
    }
    for (const auto &[ch,t]:gr[node])
        dfs(ch);
}
------------------------------------------------------------------------------
// dp with kmp
int solve(int idx=0,int p1=0,int p2=0){
    if (idx == (int)s.size())
        return 0;
    int &ans = dp[idx][p1][p2];
    if (ans != -1e9)return ans;
    ans = -1e8;
    for (char i ='a';i<='z';i++){
        if (s[idx] == '*' || i == s[idx]){
            int new_p1 = p1;
            while(new_p1 > 0 && t[0][new_p1] != i)
                new_p1 = pi[0][new_p1-1];
            int new_p2 = p2;
            while(new_p2 > 0 && t[1][new_p2] != i)
                new_p2 = pi[1][new_p2-1];
            if (t[0][new_p1] == i)
                new_p1++;
            if (t[1][new_p2] == i)
                new_p2++;
            ans = max(ans ,solve(idx+1,new_p1,new_p2)+(new_p1==(int)t[0].size())-(new_p2==(int)t[1].size()));
        }
    }
    return ans;
}
------------------------------------------------------------------------------
  pi[i] = longest prefix = suffix for s[0..i]
  Let:
    L = i + 1
    p = L - pi[i]   // smallest period length
  then:
    Period exists if:
    L % p == 0 && L != p
    Number of repetitions = K = L / p


  // Code
        pi[i] = j;
        if ((i+1) % (i - j + 1) == 0 && (i+1) != (i - j + 1))
            ans.push_back({i + 1, (i+1) / (i - j + 1)});
------------------------------------------------------------------------------
// get freq. for each substring 
        pi[i] = j;
        fr[j]++;
    }
    for (int i =n-1;i>=1;i--)
        fr[pi[i-1]] += fr[i];
