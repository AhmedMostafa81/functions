


// Bi connected == block cut tree

const int N = ;
int dfn[N], lowlink[N], tim = 0;
stack<int> st;
bool inS[N], art[N];
vector<vector<int>> comp;   
vector<int> gr[N];

void tarjan(int node, int par) {               
    dfn[node] = lowlink[node] = ++tim;
    st.push(node);
    inS[node] = true;
    int cnt = 0;

    for (const int& ch : gr[node]) {          
        if (ch == par) continue;

        if (!dfn[ch]) {
            tarjan(ch, node);
            lowlink[node] = min(lowlink[node], lowlink[ch]);

            if (lowlink[ch] >= dfn[node]) {
                if (node != par) art[node] = true;
                comp.push_back({node});
                while (comp.back().back() != ch)
                    comp.back().push_back(st.top()), st.pop();
            }
            ++cnt;
        }
        else if (inS[ch])
            lowlink[node] = min(lowlink[node], dfn[ch]);
    }
    if (cnt > 1 && node == par)
        art[node] = true;

}

vector<vector<int>> new_gr(2 * N);
int ID[N];

signed main() {

    // input
    
    
    
    for (int node = 1; node <= n; ++node)
        if (!dfn[node])
            tarjan(node, node);

    int cur = 1;
    // articulation points
    for (int node = 1; node <= n; ++node)
        if (art[node])
            ID[node] = cur++;
    // components
    for (const vector<int>& v : comp) {
        for (const int& node : v) {
            if (art[node]) {
                new_gr[cur].push_back(ID[node]);
                new_gr[ID[node]].push_back(cur);
            }
            else ID[node] = cur;
        }
        ++cur;
    }
   
}










