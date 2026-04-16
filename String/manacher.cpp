deque<int> manacher_odd(string &s){
    s = "@" + s + "!";
    int n = s.size();
    deque<int>pal(n);
    int l = 0 , r = 1;
    for (int i = 1 ; i < n ; i++ ){
        pal[i] = min(r-i , pal[l + (r - i)]);
        while(s[i - pal[i]] == s[i+pal[i]])
            pal[i]++;
        if (i + pal[i] > r)
            l = i - pal[i] , r = i + pal[i];
    }
    pal.pop_front();
    pal.pop_back();
    return pal;
}

deque<int> manacher_even_odd(string &s){
    string t;
    for(auto c:s)
        t += '#' , t+=c;
    t += '#';
    return manacher_odd(t);
}

bool check_pal(int l , int r , deque<int>&de) {
    int i_l = l * 2 + 1 , i_r = r * 2 + 1;
    int mid = (i_r + i_l) >> 1;
    return mid + de[mid] - 1 >= i_r;
}
