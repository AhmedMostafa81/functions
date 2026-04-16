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
