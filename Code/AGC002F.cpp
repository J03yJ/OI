#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e3+9;
const int mod=1e9+7;

int dp[N][N],n,k;
int fac[N*N],ifac[N*N];
int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}
void Init(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    ifac[n]=QPow(fac[n],mod-2);
    for(int i=n-1;~i;i--) ifac[i]=ifac[i+1]*(i+1)%mod;
}
int C(int n,int m){
    if(m>n) return 0;
    else return fac[n]*ifac[n-m]%mod*ifac[m]%mod;
}

signed main(){
    cin>>n>>k;
    Init(n*k);

    if(k==1){
        cout<<1<<endl;
        return 0;
    }

    dp[0][0]=1;
    for(int i=0;i<=n;i++){
        for(int j=max(i,1ll);j<=n;j++){
            dp[i][j]=((i?dp[i-1][j]:0)+dp[i][j-1]*C(i+j*(k-1)-1,k-2)%mod)%mod;
            // cout<<dp[i][j]<<'/'<<dp[i][j-1]<<'/'<<C(i+j*(k-1)-1,k-2)<<' ';
        }
        // cout<<endl;
    }

    cout<<dp[n][n]*fac[n]%mod<<endl;

    return 0;
}