ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
----------------------------------------------------------
//freopen("input.txt", "r", stdin);
//freopen("output.txt", "w", stdout);
----------------------------------------------------------
  //   make vector unique
    
vector<int> rem;
sort(rem.begin(), rem.end());
rem.erase(unique(rem.begin(), rem.end()), rem.end());   
----------------------------------------------------------
