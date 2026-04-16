
matrix mul(matrix &a , matrix &b)
{
    int n = a.size() , m = b[0].size();
    matrix res = zero(n , m);

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            for(int k=0; k<n; k++)
            {
                res[i][j] += a[i][k]*b[k][j];
                res[i][j] %= mod;
            }
        }
    }
    return res;
}

//     floyd

#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef vector<vector<int>> matrix;
#define init(name,n,m,x) matrix name (n,vector<int>(m,x))
#define AhmedPlusPlus ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define hi cerr<<"HI\n";

/*                        ->    NO CLEAN CODE HERE    <-                        */

const int inf = 3e18;

matrix mul(matrix a , matrix &b)
{
    int n = a.size() , m = b[0].size();
    init(res, n,m,inf);
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            for(int k=0; k<n; k++)
            {
                res[i][j] = min(res[i][j],a[i][k]+b[k][j]);
            }
        }
    }
    return res;
}

matrix matrix_fp(matrix &a , int p)
{
    if (p==1)
        return a;

    matrix res = matrix_fp(a , p/2);
    res = mul(res , res);
    if (p%2) res = mul(res , a);

    return res;
}

signed main() {
/* ^^^ */    AhmedPlusPlus    /* ^^^ */

//    ->> practice makes perfect

    int n,m,k;cin>>n>>m>>k;
    init(base_case,n,1,0);
    init(T,n,n,inf);
    for(int i = 0,x,y,w;i <m;i++){
        cin>>x>>y>>w;
        x--,y--;
        T[y][x] = min(T[y][x],w);
    }
    matrix res = mul(matrix_fp(T,k),base_case);
    int ans = inf;
    for (int i =0;i<n;i++)ans = min(ans , res[i][0]);
    if (ans > 2e18+5)cout << "IMPOSSIBLE" ;
    else cout << ans << '\n';

}
