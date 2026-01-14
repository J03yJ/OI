#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=5e2+9;
const int M=2e5+9;
const int mod=998244353;
    
int dp[N][N],vld[N][N][N],n,m;
int fac[N],ifac[N];
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
    // for(int i=1;i<=n;i++) cout<<fac[i]<<' ';cout<<endl;
    // for(int i=1;i<=n;i++) cout<<ifac[i]<<' ';cout<<endl;
}
int C(int n,int m){
    if(m>n) return 0;
    return fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}

signed main(){
    cin>>n>>m;
    for(int i=1,l,r,v;i<=m;i++){
        cin>>l>>r>>v;
        vld[l][r][v]=1;
    }

    Init(n);
    for(int k=1;k<=n;k++){
        for(int len=2;len<=n;len++){
            for(int i=1;i<=n-len+1;i++){
                int j=i+len-1;
                vld[i][j][k]|=vld[i][j-1][k];
                vld[i][j][k]|=vld[i+1][j][k];
            }
        }
    }
    for(int i=1;i<=n;i++) dp[i][i]=!vld[i][i][i];
    for(int len=2;len<=n;len++){
        for(int i=1;i<=n-len+1;i++){
            int j=i+len-1;
            // cout<<i<<' '<<j<<" : ";
            for(int k=i;k<=j;k++){
                if(vld[i][j][k]) continue ;
                int res=(k==i?1:dp[i][k-1])*(k==j?1:dp[k+1][j])%mod;
                res=res*C(len-1,k-i)%mod;
                dp[i][j]=(dp[i][j]+res)%mod;
            }
            // cout<<dp[i][j]<<endl;
        }
    }

    cout<<dp[1][n]<<endl;

    return 0;
}