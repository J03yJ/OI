#include<bits/stdc++.h>

using namespace std;

const int N=5e1+9;
const int V=5e1;

int f[N][N][N][N],a[N],n;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    for(int len=1;len<=n;len++){
        for(int i=1;i+len-1<=n;i++){
            int j=i+len-1;
            for(int l=1;l<=V;l++){
                for(int r=l;r<=V;r++){
                    f[i][j][l][r]=max(f[i+1][j][l][r],f[i][j-1][l][r]);
                    if(l<=a[i]&&a[i]<=r){
                        int t=0;
                        for(int k=i;k<=n;k++) t=max(t,f[i+1][k][l][a[i]]+f[k+1][j][a[i]][r]);
                        f[i][j][l][r]=max(f[i][j][l][r],t+1);
                    }
                }
            }
        }
    }

    cout<<f[1][n][1][V]<<endl;

    return 0;
}