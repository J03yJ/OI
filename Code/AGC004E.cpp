#include<bits/stdc++.h>

using namespace std;

const int N=1e2+9;

short dp[N][N][N][N],vsum[N][N],hsum[N][N],a[N][N],n,m,x,y;
inline void ChMax(short &x,short y){
    if(y>x) x=y;
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char c;
            cin>>c;
            if(c=='E') x=i,y=j;
            else if(c=='o') a[i][j]=1;
        }
    }

    #define V(l,r,k) (vsum[k][r]-vsum[k][(l)-1])
    #define H(l,r,k) (hsum[r][k]-hsum[(l)-1][k])
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            vsum[i][j]=vsum[i][j-1]+a[i][j];
            hsum[i][j]=hsum[i-1][j]+a[i][j];
        }
    }

    short ans=0;
    for(int l=0;l<y;l++){
        for(int r=0;r<m-y+1;r++){
            for(int u=0;u<x;u++){
                for(int d=0;d<n-x+1;d++){
                    ans=max(ans,dp[l][r][u][d]);
                    if(l+r<y-1) ChMax(dp[l+1][r][u][d],dp[l][r][u][d]+H(max(x-u,d+1),min(x+d,n-u),y-l-1));
                    if(l+r<m-y) ChMax(dp[l][r+1][u][d],dp[l][r][u][d]+H(max(x-u,d+1),min(x+d,n-u),y+r+1));
                    if(u+d<x-1) ChMax(dp[l][r][u+1][d],dp[l][r][u][d]+V(max(y-l,r+1),min(y+r,m-l),x-u-1));
                    if(u+d<n-x) ChMax(dp[l][r][u][d+1],dp[l][r][u][d]+V(max(y-l,r+1),min(y+r,m-l),x+d+1));
                }
            }
        }
    }
    cout<<ans<<endl;

    return 0;
}