// check if some patterns exist in a big string 


// iterative


const int N = , tot = ;
int ans[N] ;

struct Aho_Corasick {
    int id(char c) {
        // CODE
    }

    struct Node {
        int next[tot]{};
        int par = 0, link = 0;
        vector<int> IDs;
        int last = 0;          // <-- nearest output link (node index) on suffix path, 0 if none
        Node(int p = 0) : par(p) {}
    };
    //vector<vector<int>>gr;
    vector<Node> trie;
    Aho_Corasick() {
        trie.emplace_back();
        //gr.emplace_back();
    }
    void add(const string &s, int idx) {
        int node = 0;
        for (auto ch : s) {
            int c = id(ch);
            if (trie[node].next[c] == 0) {
                trie[node].next[c] = trie.size();
                trie.emplace_back(node);
                //gr.emplace_back();
            }
            node = trie[node].next[c];
        }
        trie[node].IDs.push_back(idx);
    }
    //vector<int>bfs_order;
    void build() {
        queue<int> q;
        q.push(0);
        while (q.size()) {
            int node = q.front();
            q.pop();
            //bfs_order.push_back(node);
            //gr[trie[node].link].push_back(node);
            // keep existing behavior: copy IDs from suffix-link node
            for (int idx : trie[trie[node].link].IDs)// n^2 if patterns are not unique, otherwise n * sqrt
                trie[node].IDs.emplace_back(idx);
            for (int c = 0; c < tot; c++) {
                int ch = trie[node].next[c];
                if (ch == 0)
                    trie[node].next[c] = trie[trie[node].link].next[c];
                else {
                    trie[ch].link = node ? trie[trie[node].link].next[c] : 0;
                    if (!trie[ trie[ch].link ].IDs.empty())
                        trie[ch].last = trie[ch].link;
                    else
                        trie[ch].last = trie[ trie[ch].link ].last;
                    q.push(ch);
                }
            }
        }
    }

    int go(int node, char c) {
        return trie[node].next[id(c)];
    }

    // helper: returns the nearest node that contains a pattern
    // including `node` itself (returns `node` if it has IDs),
    // otherwise returns `last` (0 if none).
    int nearest_output_node_including_self(int node) {
        if (!trie[node].IDs.empty()) return node;
        return trie[node].last;
    }

    // optional: return nearest output strictly below (i.e. excluding node itself)
    int nearest_output(int node) {
        return trie[node].last;
    }

    // void solve() {
    //     for (int i = bfs_order.size() - 1 ; i >= 0; i--) {
    //         int node = bfs_order[i];
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





//   arrays for large input 


const int N = 1e7+5;
int Next[N][2] , par[N] , link[N]  , last[N] , cur_node;
bool ID[N];

struct Aho_Corasick {
    int id(char c) {
        return c - 'a';
    }
    int add(const string &s ) {
        int node = 0;
        for (auto ch : s) {
            int c = id(ch);
            if (Next[node][c] == 0)
                Next[node][c] = ++cur_node;
            node = Next[node][c];
        }
        ID[node] = 1;
        return node;
    }
    void build() {
        queue<int> q;
        q.push(0);
        while (q.size()) {
            int node = q.front();
            q.pop();
            //ID[node] |= ID[link[node]];
            for (int c = 0; c < 2; c++) {
                int ch = Next[node][c];
                if (ch == 0)
                    Next[node][c] = Next[link[node]][c];
                else {
                    link[ch] = node ? Next[link[node]][c] : 0;
                    if (ID[link[ch] ])
                        last[ch] = link[ch];
                    else
                        last[ch] = last[ link[ch] ];
                    q.push(ch);
                }
            }
        }
    }

    int go(int node, char c) {
        return Next[node][id(c)];
    }

    int nearest_output_node_including_self(int node) {
        if (ID[node]) return node;
        return last[node];
    }
    int nearest_output(int node) {
        return last[node];
    }
}Aho;
