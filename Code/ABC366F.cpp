#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e5+9;
const int K=1e1+9;

int a[N],b[N],p[N],dp[N][K],n,k;
#define W(x) (double(a[x]-1)/b[x])
bool Cmp(int x,int y){
    return W(x)<W(y);
}

signed main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i]>>b[i];

    for(int i=1;i<=n;i++) p[i]=i;
    sort(p+1,p+n+1,Cmp);
    dp[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=k;j++) dp[i][j]=dp[i-1][j];
        for(int j=1;j<=k;j++) dp[i][j]=max(dp[i][j],a[p[i]]*dp[i-1][j-1]+b[p[i]]);
    }

    cout<<dp[n][k]<<endl;

    return 0;
}