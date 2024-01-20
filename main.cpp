#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define F first
#define S second
#define all(a)  a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define pf push_front
#define pb push_back
#define loop(n) for(int i = 0; i < (n); i++)
#define AhmedPlusPlus ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
/******************************************************************************************/
/*     _                        _
      | |                      | |  _     _
  __ _| |__  _ __ ___   ___  __| |_| |_ _| |_
 / _` | '_ \| '_ ` _ \ / _ \/ _` |_   _|_   _|
| (_| | | | | | | | | |  __| (_| | |_|   |_|
 \__,_|_| |_|_| |_| |_|\___|\__,_|

*/
/*****************************************************************************************/
void cin_v (vector <int> &v,int SIZE ){
    for (int i =0;i<SIZE;i++){
        int inp;cin >>inp;
        v.push_back(inp);
    }
}
// cout <<fixed<<setprecision(6)<<any number;
void cin_v_ll (vector <ll> &v,int SIZE ){
    for (int i =0;i<SIZE;i++){
        ll inp;cin >>inp;
        v.push_back(inp);
    }
}
void print_v (vector<ll>v){
    for (ll num : v){
        cout<<num<<" ";
    }
    cout <<"\n";
}
//vector<int>v;
//vector<ll>vl;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// START FROM HERE :------
void solve() {

    int n,m,k;cin>>n>>m>>k;
    vector<ll>v;
    vector<ll>sol(n+1,0);
    cin_v_ll(v,n);
    vector<pair<pair<int,int>,ll>>op;
    loop(m){
        int x,y,d;cin>>x>>y>>d;x--;y--;
        op.pb({{x,y},d});
    }
    vector<ll>t(m+1,0);
    loop(k){
        int x,y;cin>>x>>y;x--;y--;
        t[x]++;t[y+1]--;
    }
    for (int i=1;i<m;i++){
        t[i]=t[i]+t[i-1];
    }
    loop(m){
        op[i].S*=t[i];
    }

    loop(m){
        sol[op[i].F.F]+=op[i].S;
        sol[op[i].F.S+1]-=op[i].S;
    }

    for (int i =1;i<n;i++){
        sol[i]=sol[i]+sol[i-1];
    }
    for (int i =0;i<n;i++) {
        cout << sol[i]+v[i] << " ";
    }


}

int main() {
/* ^^^ */    AhmedPlusPlus;   /* ^^^ */

    int x_x = 1;
    //cin >> x_x;
    while (x_x--) {
        solve();
    }

    return 0;
}
