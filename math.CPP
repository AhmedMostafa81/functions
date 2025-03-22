/*
to get sum 2^(0*n) + 2^(1*n) + 2^(2*n) + 2^(3*n) + 2^(4*n) + .... + 2^(k*n)

 the formula is
    (   (2 ^ ((k+1)*n)) - 1   ) /   (  2^n - 1   )

*/

double LOG( int x, int k){
    double answer;
    answer = log10( x ) / log10( k );
    return answer;
}

const int N = 2e5+7, P1 = 31, P2 = 37, mod= 1e9 + 7;

bitset<N> notPrime;
void sieve() {
    notPrime[0] = notPrime[1] = 1;
    for(int i = 2; i*i < N; i++) {
        if(notPrime[i]) continue;

        for(int j = i*i; j < N; j+=i)
            notPrime[j] = 1;
    }
}

int spf[N];
void SPF() {
    for(int i = 1; i < N; i++)
        spf[i] = i;
    for(int i = 2; i*i < N; i++) {
        if(spf[i] != i) continue;

        for(int j = i*i; j < N; j+=i)
            spf[j] = min(spf[j], i);
    }
}

short spf[N];
void SPF() {
    for(int i = 2; i*i < N; i++) {
        if(spf[i] != 0) continue;

        for(int j = i*i; j < N; j+=i) {
            if(spf[j] == 0)
                spf[j] = i;
        }
    }
}

int mul(int a, int b) {
    return (1LL * a * b) % mod;
}
 
int add(int a, int b) {
    a = (a + mod) % mod;
    b = (b + mod) % mod;
    return (a + b) % mod;
}
 
int fp(int b, int p) {
    if (b == 1 or p == 0)
        return 1;
 
    int ret = fp(b, p >> 1);
    ret = mul(ret, ret);
 
    if (p & 1)
        ret = mul(ret, b);
 
    return ret;
}
 
int inv(int a) {
    return fastPower(a, mod-2);
}

int divi(int a, int b) {
    return mult(a, inv(b));
}
 
int fact[N];


int nPr(int n, int r) {
    if(r > n) return 0;
    if(n < 0 || r < 0) return 0;
    return divi(fact[n], fact[n-r]);
}

int nCr(int n, int r) {
    if(r > n) return 0;
    if(n < 0 || r < 0) return 0;
    return divi(fact[n], mult(fact[r], fact[n-r]));
}

int sNb(int n, int k) {
    return nCr(n+k-1, n);
}

void precalFactorial() {
    fact[0] = 1;

    for(int i =1 ; i < N; i++)
        fact[i] = mult(fact[i-1], i);
}
