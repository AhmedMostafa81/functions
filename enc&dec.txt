#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define loop(n)          for(int i = 0; i < (n); i++)
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

string normal="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789+-*/?%!@_.";
string enc="6h7qr-stTU?Wyk!Vbu_vPdw3clxzA+BCgpEH9I@QRi%jS/oXYZ.01fD24e5FG8m*JKLMNaOn";

char ntoe(char c){
    char ans;
    for (int i =0;i<72;i++){
        if (c==normal[i]){
            ans=enc[i];
            break;
        }
    }
    return ans;
}
char eton(char c){
    char ans;
    for (int i =0;i<72;i++){
        if (c==enc[i]){
            ans=normal[i];
            break;
        }
    }
    return ans;
}
string encryption (string s){
    string ans="";
    int siz=s.size();
    for (int k=0;k<siz;k++){
        ans+=ntoe(s[k]);
    }
    return ans;
}
string decryption (string s){
    string ans="";
    int siz=s.size();
    for (int k=0;k<siz;k++){
        ans+=eton(s[k]);
    }
    return ans;
}

int main()
{
    //IOS;
    bool T=1;
    while(T){
        cout <<"for encryption -> 1\n";
        cout <<"for decryption -> 2\n";
        int n;cin>>n;
        string s;cin>>s;
        string sol="";
        int siz=s.size();
        if (n==1){
            sol= encryption(s);
            loop(siz-1){
                sol=encryption(sol);
            }
            cout <<sol<<"\n";
        }
        if (n==2){
            sol= decryption(s);
            loop(siz-1){
                sol=decryption(sol);
            }
            cout <<sol<<"\n";
        }
        cout <<"if you want to \n";
        cout <<"exit type -> 0\n";
        cout <<"continue type -> 1\n";

        cin>>T;
    }

    return 0;
}
