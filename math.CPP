double LOG( int x, int k){
    double answer;
    answer = log10( x ) / log10( k );
    return answer;
}

const int N = 2e5+7, P1 = 31, P2 = 37, mod= 1e9 + 7;
 
int spf[N];
void primes(){
    for (int i =0;i<N;i++)spf[i]=i;
    for (int i=2;i*i<N;i++){
	if(spf[i] != i) continue;
        for (int j=i*i;j<N;j+=i)
            spf[j]=min(i,spf[j]);
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
 
ll modInv(ll n) {
    return fp(n, mod - 2);
}
 
ll fact[N], inv[N];
 
void pre() {
    fact[0] = inv[0] = 1;
    for (ll i = 1; i < N; i++)
        fact[i] = (fact[i - 1] * i) % mod, inv[i] = fp(fact[i], mod - 2);
}
 
ll nCr(ll n, ll r) {
    return ((fact[n] * inv[r]) % mod * inv[n - r]) % mod;
}
 
ll nPr(ll n, ll r) {
    return ((fact[n] * inv[n - r])) % mod;
}
