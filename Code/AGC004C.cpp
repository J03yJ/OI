#include<bits/stdc++.h>

using namespace std;

const int N=1e3+9;

int a[N][N],r[N][N],b[N][N];

int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char c;
            cin>>c;
            if(c=='#') a[i][j]=1;
        }
    }

    for(int i=1;i<=n;i++){
        r[i][1]=1;
        if(i%2) for(int j=1;j<m;j++) r[i][j]=1;
        else for(int j=1;j<=m;j++) r[i][j]|=a[i][j];
        b[i][m]=1;
        if(i%2) for(int j=1;j<=m;j++) b[i][j]|=a[i][j];
        else for(int j=2;j<=m;j++) b[i][j]=1;
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) cout<<(r[i][j]?'#':'.');
        cout<<endl;
    }
    cout<<endl;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) cout<<(b[i][j]?'#':'.');
        cout<<endl;
    }

    return 0;
}