#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e3+9;
const int mod=924844033;

int f[N<<1][N][2],adj[N<<1],n,m,k;
int fac[N];

signed main(){
    cin>>n>>k;

    for(int i=k+1;i<=n&&i<=k+k;i++){
        int x=i,y=i-k,cnt=0;
        while(x<=n&&y<=n){
            if(!cnt) adj[++m]=1;
            else adj[++m]=0;
            if(cnt&1) x+=k<<1;
            else y+=k<<1;
            cnt++;
        }
    }
    for(int i=k+1;i<=n&&i<=k+k;i++){
        int x=i-k,y=i,cnt=0;
        while(x<=n&&y<=n){
            if(!cnt) adj[++m]=1;
            else adj[++m]=0;
            if(cnt&1) y+=k<<1;
            else x+=k<<1;
            cnt++;
        }
    }

    f[0][0][0]=1;
    for(int i=1;i<=m;i++){
        f[i][0][0]=1;
        for(int j=1;j<=n;j++){
            f[i][j][0]=(f[i-1][j][0]+f[i-1][j][1])%mod;
            if(adj[i]) f[i][j][1]=f[i][j-1][0];
            else f[i][j][1]=f[i-1][j-1][0];
        }
    }

    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;

    int ans=0;
    for(int i=0;i<=n;i++){
        if(i&1) ans=(ans-(f[m][i][0]+f[m][i][1])%mod*fac[n-i]%mod+mod)%mod;
        else ans=(ans+(f[m][i][0]+f[m][i][1])%mod*fac[n-i]%mod)%mod;
    }
    cout<<ans<<endl;

    return 0;
}