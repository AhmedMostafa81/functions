void build(int blk){
    for (int i =0;i<26;i++)
        fr[blk][i].clear();
    for (int i = blk*sq ; i < min(n,(blk+1)*sq);i++) {
        if (lazy[blk] != '*')
            s[i] = lazy[blk];
        fr[blk][s[i]-'a'].push_back(i);
    }
    lazy[blk] = '*';
}

void update(int l,int r,char c){
    build(l/sq);
    build(r/sq);
    for (int i = l ; i <= r;){
        if (i %sq == 0 && i + sq - 1 <= r){
            lazy[i/sq] = c;
            i+=sq;
        }
        else {
            s[i] = c;
            i++;
        }
    }
    build(l/sq);
    build(r/sq);
}
