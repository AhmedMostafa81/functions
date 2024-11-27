long long FloorSumAP(long long a, long long b, long long c, long long n){
    if(!a) return (b / c) * (n + 1);
    if(a >= c or b >= c) return ( ( n * (n + 1) ) / 2) * (a / c) + (n + 1) * (b / c) + FloorSumAP(a % c, b % c, c, n);
    long long m = (a * n + b) / c;
    return m * n - FloorSumAP(c, c - b - 1, a, m - 1);
} // find sum of floor((a * i + b) / c) for i in [0, n] in O(log(n))
// from: https://asfjwd.github.io/2020-04-24-floor-sum-ap/
