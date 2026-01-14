#include<bits/stdc++.h>

using namespace std;

const int N=5e2+9;

int vld[N][N][N],f[N][N],n,m;

int main(){
    cin>>n>>m;
    for(int i=1,l,r;i<=m;i++){
        cin>>l>>r;
        for(int k=l;k<=r;k++) vld[l][r][k]=1;
    }

    for(int len=1;len<=n;len++){
        for(int i=1,j=len;j<=n;i++,j++){
            for(int k=i;k<=j;k++){
                vld[i][j][k]|=vld[i][j-1][k]|vld[i+1][j][k];
            }
        }
    }   
    for(int len=1;len<=n;len++){
        for(int i=1,j=len;j<=n;i++,j++){
            for(int k=i;k<=j;k++){
                if(!vld[i][j][k]) continue ;
                f[i][j]=max(f[i][j],f[i][k-1]+f[k+1][j]+1);
            }
        }
    }
    cout<<f[1][n]<<endl;

    return 0;
}