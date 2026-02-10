


const int base[] = {31 , 37} , mod[] ={ (int)1e9+7 , (int)1e9+9} , N = ;
int pw[2][N];

int mul(int a , int b , int type) {
    return (a * b) % mod[type];
}

int add(int a , int b , int type) {
    return (a + b + mod[type]) % mod[type];
}

int id(char c) {
    return c - 'a' + 1;
}

void HASH(string &s , vector<array<int,2>>&pre) {
    int n = s.size();
    array<int,2>cur = {0,0};
    for (int i = 0 ;i < n ; i++) {
        for (int b = 0 ;b < 2 ; b++) {
            cur[b] = mul(cur[b] , base[b] , b);
            cur[b] = add(cur[b] , id(s[i]) , b);
        }
        pre.push_back(cur);
    }
}

array<int,2>get(int l,int r ,vector<array<int,2>>&pre) {
    array<int,2>rt = pre[r];
    if (l != 0) {
        for (int b= 0 ;b < 2 ; b++)
            rt[b] = add(rt[b] , - mul(pre[l-1][b] , pw[b][r-l+1] , b) , b);
    }
    return rt;
}

void pre_calc() {
    for (int b = 0 ;b < 2 ; b++) {
        pw[b][0] = 1;
        for (int i = 1; i < N ; i++)
            pw[b][i] = mul(pw[b][i-1] , base[b] , b);
    }
}































const int N =  , base[2]={31,37},mod=1e9+7;
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
