#include<bits/stdc++.h>

using namespace std;

#define int long long

const int N=3e3+9;
const int p=1e9+7;

int dp[N][N];

signed main(){
    int n,m;
    cin>>n>>m;
    for(int i=0;i<=max(n,m);i++) dp[i][0]=dp[0][i]=1;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            dp[i][j]=dp[i-1][j];
            dp[i][j]=(dp[i][j]+4*j*dp[i-1][j-1]%p)%p;
            if(i>1) dp[i][j]=(dp[i][j]+(i-1)*j%p*dp[i-2][j-1]%p)%p;
            if(j>1) dp[i][j]=(dp[i][j]+(j*(j-1)/2)%p*dp[i-1][j-2]%p)%p;
        }
    }

    cout<<(dp[n][m]-1+p)%p<<endl;

    return 0;
}