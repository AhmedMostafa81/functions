int n,m;cin>>n>>m;
    char arr[n][m];
    for (int r =0;r<n;r++){
        for (int c=0;c<m;c++){
            char inp;cin>>inp;
            arr[r][c]=inp;
        }
    }
    for (int r =0;r<n;r++){
        for (int c=0;c<m;c++){
            if (arr[r][c]=='o'){
                arr[r][c]='x';
                if(r!=0&&c!=0){
                    if (arr[r-1][c-1]=='.'){
                        arr[r-1][c-1]='x';
                    }
                }
                if (r!=0){
                    if (arr[r-1][c]=='.'){
                        arr[r-1][c]='x';
                    }
                }
                if (r!=0&&c+1<m){
                    if (arr[r-1][c+1]=='.'){
                        arr[r-1][c+1]='x';
                    }
                }
                if (c!=0){
                    if (arr[r][c-1]=='.'){
                        arr[r][c-1]='x';
                    }
                }
                if (c+1<m){
                    if (arr[r][c+1]=='.'){
                        arr[r][c+1]='x';
                    }
                }
                if (r+1<n&&c!=0){
                    if (arr[r+1][c-1]=='.'){
                        arr[r+1][c-1]='x';
                    }
                }
                if (r+1<n){
                    if (arr[r+1][c]=='.'){
                        arr[r+1][c]='x';
                    }
                }
                if (r+1<n&&c+1<m){
                    if (arr[r+1][c+1]=='.'){
                        arr[r+1][c+1]='x';
                    }
                }
            }
        }
    }
    for (int r =0;r<n;r++){
        for (int c=0;c<m;c++){
            cout <<arr[r][c];
        }
        cout <<"\n";
    }
