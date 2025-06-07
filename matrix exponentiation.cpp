#include <bits/stdc++.h>

using namespace std;
#define  ll long long
#define ld long double
#define f first
#define s second
#define matrix vector<vector<ll>>
#define zero(n,m) matrix(n , vector<ll>(m,0))
const int mod = 1e9+7;

ll n , nth , m;

void init(matrix &M , matrix &res)
{
    M[0][0] = 0 , M[0][1] = 1 , M[1][0] = 1 , M[1][1] = 1;
    res[0][0]=0 , res[1][0]=1;
}

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

matrix matrix_fp(matrix &a , ll p)
{
    if (p==1)
        return a;

    matrix res = matrix_fp(a , p/2);
    res = mul(res , res);
    if (p%2) res = mul(res , a);

    return res;
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin >> n;
    if (n<2)
    {
        cout << n << "\n";
    }
    else
    {
        matrix M = zero(2,3) , A = zero(2,1);
        init(M , A);


        M = matrix_fp(M , n-2+1);
        A = mul(M , A);

        cout << A[1][0] << '\n';
    }

    return 0;
}

