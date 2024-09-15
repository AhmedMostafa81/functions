const int N =4e5+5 , base[2]={31,37},mod=1e9+7;
int pw[2][N];
int add(int a,int b) {
    return (a+b+mod)%mod;
}
int mul(int a,int b) {
    return(a*b)%mod;
}
int fp (int x,int n){
    int res=1;
    while(n>0){
        if (n%2==1)
            res = mul(res,x);
        x = mul(x,x);
        n/=2;
    }
    return res;
}
int midINV(int a) {
    return fp(a,mod-2);
}
void init() {
    for (int b=0;b<2;b++) {
        pw[b][0]=1;
        for (int i =1;i<N;i++)
            pw[b][i] = mul(pw[b][i-1],base[b]);
    }
}
vector<pair<int,int>>pre;

void HASH(string&s) {
    pair<int,int>sum;
    for (int i=0;i<s.size();i++) {
        sum.F = mul(sum.F,base[0]);
        sum.F = add(sum.F,s[i]-'a'+1);
        sum.S = mul(sum.S,base[1]);
        sum.S = add(sum.S,s[i]-'a'+1);
        pre.pb(sum);
    }
}
pair<int,int>get(int l,int r) {
    pair<int,int>rt;
    rt.F = add(pre[r].F ,  - mul((l?pre[l-1].F:0) , pw[0][r-l+1])) ;
    rt.S = add(pre[r].S ,  - mul((l?pre[l-1].S:0) , pw[1][r-l+1])) ;
    return rt;
}
