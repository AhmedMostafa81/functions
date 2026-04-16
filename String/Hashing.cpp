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
