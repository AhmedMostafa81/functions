void KMP(string &s){
    int n = s.size();
    vector<int>pi(n);
    pi[0] = -1;
    for (int i =1;i<n;i++){
        int j = pi[i-1];
        while(j>=0 && s[i] != s[j])
            j = pi[j];
        pi[i] = j + 1;
    }
}
