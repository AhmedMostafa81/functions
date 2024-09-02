ll gcd(ll x, ll y) { return (!y ? x : gcd(y, x % y)); }
 
ll lcm(ll x, ll y) { return x / gcd(x, y) * y; }


void binary(int n){   // Recursion 
    if (n){
        binary(n/2);
        cout <<n%2;
    }
}

the lexicographically largest†
 subsequence of string s

    string s;cin>>s;int n=s.size();
    int index_mx;
    char mx='a'-1;
    for (int i =0;i<n;i++){
        if (s[i]>mx){
            mx=s[i];
            index_mx=i;
        }
    }
    vector<pair<char,int>>v;
    for (int i =index_mx+1;i<n;i++){
        v.pb({s[i],-1*i});
    }
    sort(rall(v));
    int prv=-1;
    string sol="";sol.pb(mx);
    for (int i =0;i<v.size();i++){
        if ((v[i].S*-1)>prv){
            sol.pb(v[i].F);
            prv=(v[i].S*-1);
        }
    }
    cout <<sol;




bool is_permutation(vector<int>v){
    sort(all(v));
    vector<int>t;for (int i =1;i<=v.size();i++)t.pb(i);
    for (int i =0;i<v.size();i++)if (v[i]!=t[i])return 0;
    return 1;
}


// orderd set
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type,less_equal<int>, rb_tree_tag,tree_order_statistics_node_update>

ordered_set st;
st.order_of_key(number);// number of elem. less than (..)
find_by_order(index) // get by index



//   permutation the arr
 cin>>n;
    vector<int>arr(n);
    //   permutation the arr
    for (int i = 0; i < n; ++i) {
        arr[i] = i+1;
    }
    do{
        for (int i: arr)cout << i << " ";
             cout << "\n";
    }while(next_permutation(arr.begin(),arr.end()));


long long GCD(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long LCM (long long a, long long b) {
    return a/GCD(a,b)*b;
}


 long long c(int n, int k) {
     long long result = 1;
    for (int i = 0; i < k; ++i) {
        result *= (n - i);
        result /= (i + 1);
    }
    return result;
}

ll p(int n, int k) {
    ll result = 1;
    for (int i = 0; i < k; ++i) {
        result *= (n - i);
    }
    return result;
}
ll f (ll a){
    ll res=1;
    for (int i =2;i<=a;i++){
        res*=i;
    }
    return res;
}
void re(int &a,int &b){
    // make a<b always;
    if (b<a)
        swap(a,b);
}

bool is_prime(ll n){
    if (n==1)return 0;
    if (n==2)return 1;
    int z=sqrt(n);
    for (int i =2;i<=z;i++){
        if (n%i==0)return 0;
    }
    return 1;
}

string to_bin(int n){
    string sol="";
    while (n>0) {
        if (n & 1)sol.pb('1');
        else sol.pb('0');n/=2;
    }sol.pb('0');reverse(all(sol));
    return sol;
}
long long fast_pow (ll x,ll n){
    //  x  power n;
    ll res=1;
    while(n>0){
        if (n%2==1){
            res*=x;
        }
        x*=x;
        n/=2;
    }
    return res;
}

//    sum of two strings
string findSum(string str1, string str2)
{
    if (str1.length() > str2.length())
        swap(str1, str2);
    string str = "";
    int n1 = str1.length(), n2 = str2.length();
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());
    int carry = 0;
    for (int i=0; i<n1; i++)
    {
        int sum = ((str1[i]-'0')+(str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');
        carry = sum/10;
    }

    for (int i=n1; i<n2; i++)
    {
        int sum = ((str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');
        carry = sum/10;
    }

    if (carry)
        str.push_back(carry+'0');

    reverse(str.begin(), str.end());
    return str;
}
//  dijkstra
    set<pair<int,int>>st;
    st.insert({0,1});
    while(st.size()){
        int node=(*st.begin()).S;
        int cost=(*st.begin()).F;
        st.erase(st.begin());
        if (cost >= dis[node]) continue;
        dis[node]=cost;
        for (auto child:graph[node]){
            if (cost+child.F < dis[child.S])
                st.insert({cost+child.F,child.S});
        }
    }
    
    
//   make vector unique
    
vector<int> rem;
sort(rem.begin(), rem.end());
rem.erase(unique(rem.begin(), rem.end()), rem.end());   
