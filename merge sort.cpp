#include <bits/stdc++.h>
using namespace std;

#define fast ios::sync_with_stdio(false); cin.tie(nullptr);

int n, q;
vector<int> arr;
vector<vector<int>> seg;

// Build the tree on range [l, r]
void build(int node, int l, int r) {
    if (l == r) {
        seg[node] = {arr[l]};
        return;
    }
    int mid = (l + r) >> 1;
    build(node << 1, l, mid);
    build(node << 1 | 1, mid + 1, r);

    auto &left = seg[node << 1];
    auto &right = seg[node << 1 | 1];
    seg[node].resize(left.size() + right.size());
    merge(left.begin(), left.end(),
          right.begin(), right.end(),
          seg[node].begin());
}

// Count numbers < x in range [ql, qr]
int query(int node, int l, int r, int ql, int qr, int x) {
    if (r < ql || l > qr) return 0;
    if (ql <= l && r <= qr) {
        return lower_bound(seg[node].begin(), seg[node].end(), x) - seg[node].begin();
    }
    int mid = (l + r) >> 1;
    return query(node << 1, l, mid, ql, qr, x)
         + query(node << 1 | 1, mid + 1, r, ql, qr, x);
}

int main() {
    fast

    cin >> n >> q;
    arr.resize(n);
    seg.resize(4 * n);

    for (int i = 0; i < n; i++)
        cin >> arr[i];

    build(1, 0, n - 1);

    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;

        // If input is 1-based, uncomment:
        // l--, r--;

        cout << query(1, 0, n - 1, l, r, x) << '\n';
    }
}
