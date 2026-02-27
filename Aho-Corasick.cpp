// check if some patterns exist in a big string 




//    ->> practice makes perfect


#include<bits/stdc++.h>
using namespace std;

/* ===================  NO CLEAN CODE HERE  =================== */

const int N =  1e5+5;
bool vis[N] , ans[N] ;

const int tot = 26 + 26;
struct Aho_Corasick {
    int id(char c) {
        if (c >= 'a' && c <= 'z')
            return c - 'a';
        return c - 'A' + 26;
    }
    struct Node {
        int next[tot] , go[tot];
        int par = - 1, link = -1 ;
        bool no = 0;
        vector<int>IDs;
        char par_c;
        Node(int p = -1 , char c = '$') : par(p) , par_c(c) {
            memset(next , -1 , sizeof next);
            memset(go , -1 , sizeof go);
        }
    };
    vector<Node>trie;
    vector<vector<int>>gr;
    Aho_Corasick() {
        trie.emplace_back();
        gr.emplace_back();
    }
    void add(string const&s , int idx) {
        int node = 0 ;
        for (char ch:s) {
            int c = id(ch);
            if (trie[node].next[c] == -1) {
                trie[node].next[c] = trie.size();
                trie.emplace_back(node , ch);
                gr.emplace_back();
            }
            node = trie[node].next[c];
        }
        trie[node].IDs.push_back(idx);
    }
    int get_link(int node) {
        if (trie[node].link == -1) {
            if (node == 0 || trie[node].par == 0)
                trie[node].link = 0;
            else
                trie[node].link = go(get_link(trie[node].par) , trie[node].par_c);
        }
        gr[trie[node].link].push_back(node); // reversed tree
        return trie[node].link;
    }
    int go(int node , char ch) {
        int c = id(ch);
        if (trie[node].go[c] == -1) {
            if (trie[node].next[c] != -1)
                trie[node].go[c] = trie[node].next[c];
            else
                trie[node].go[c] = node == 0 ? 0 : go(get_link(node) , ch);
        }
        return trie[node].go[c];
    }
    void dfs(int node = 0) {
        if (trie[node].no)
            return ;
        trie[node].no = 1;
        for (int i = 0 ;i < tot ; i++)
            if (~trie[node].next[i]) {
                dfs(trie[node].next[i]);
                if (vis[trie[node].next[i]])
                    vis[node] = 1;
            }
        for (auto ch:gr[node]) {
            dfs(ch);
            if (vis[ch])
                vis[node] = 1;
        }
        if (vis[node] ) {
            for (auto idx:trie[node].IDs)
                ans[idx] = true;
        }
    }
};

void maybe() {

    string s;cin >>s ;
    int n = s.size();
    memset(ans , 0 , sizeof ans);
    memset(vis , 0 , sizeof vis);
    Aho_Corasick Aho;
    int q;cin >> q;
    for (int i= 0 ; i < q ; i++) {
        string t; cin >> t;
        Aho.add(t,i);
    }
    int cur_node = 0 ;
    for (int i = 0 ; i < n ;i ++) {
        cur_node = Aho.go(cur_node , s[i]);
        vis[cur_node] = 1;
    }
    Aho.dfs();
    for (int i  = 0 ; i < q ; i++)
        cout << (ans[i] ? "y" : "n") << '\n';

}


signed main() {

    ios::sync_with_stdio(0);cin.tie(0);
    int tc = 1;
    cin>>tc;
    while(tc--)
        maybe();

}




// iterative


const int N = , tot = ;
int ans[N] ;

struct Aho_Corasick {
    int id(char c) {
        // CODE
    }

    struct Node {
        int next[tot]{} , go[tot]{};
        int par = 0,  link = 0;
        //int fr = 0;
        vector<int>IDs;
        char par_c;
        Node(int p  , char c ) : par(p) , par_c(c) {};
    };
    //vector<vector<int>>gr;
    vector<Node>trie;
    Aho_Corasick() {
        trie.emplace_back(0,'$');
    }
    void add(const string&s , int idx) {
        int node = 0;
        for (auto ch:s) {
            int c = id(ch);
            if (trie[node].next[c] == 0) {
                trie[node].next[c] = trie.size();
                trie.emplace_back(node , ch);
                //gr.emplace_back();
            }
            node = trie[node].next[c] ;
        }
        trie[node].IDs.push_back(idx);
    }

    void build() {
        queue<int> q;
        q.push(0);
        while (q.size()) {
            int node = q.front();
            q.pop();
            //gr[trie[node].link].push_back(node);
            for (int idx: trie[trie[node].link].IDs)
                trie[node].IDs.emplace_back(idx);
            for (int c = 0 ; c < tot ; c++) {
                int ch = trie[node].next[c];
                if (ch == 0)
                    trie[node].next[c] = trie[trie[node].link].next[c];
                else {
                    trie[ch].link = node ? trie[trie[node].link].next[c] : 0;
                    q.push(ch);
                }
            }
        }
    }

    int go(int node, char c) {
        return trie[node].next[id(c)];
    }

    // void solve() {
    //     queue<int>q;
    //     vector<int>all;
    //     q.push(0);
    //     while (q.size()) {
    //         int node = q.front();
    //         q.pop();
    //         all.push_back(node);
    //         for (int i  = 0 ;i  < tot ; i++)
    //             if (~trie[node].next[i])
    //                 q.push(trie[node].next[i]);
    //     }
    //     for (int i = all.size() - 1 ; i >= 0; i--) {
    //         int node = all[i];
    //         for (auto ch:gr[node]) {
    //             trie[node].fr += trie[ch].fr;
    //         }
    //         for (auto idx:trie[node].IDs)
    //             ans[idx] = trie[node].fr;
    //     }
    // }


};

void maybe() {

    int n ; cin >> n ;
    Aho_Corasick Aho;
    for (int i  = 0 ;i  < n ;i++) {
        string tmp ; cin >> tmp;
        Aho.add(tmp, i);
    }
    Aho.build();
    int q;cin >> q;
    while (q--) {
        string s; cin >> s;
        int node = 0 ;
        for (auto c:s) {
            node = Aho.go(node , c);
            for (auto idx:Aho.trie[node].IDs)
                ans[idx]++;
        }
    }
    for (int i  = 0; i < n ;i++)
        cout << ans[i] << '\n';

}
