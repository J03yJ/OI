#include<bits/stdc++.h>

using namespace std;

#define int long long
const int L=2e1;
const int mod=998244353;

void Xor(vector<int> &a){
    for(int i=1;i<(1ll<<L);i<<=1){
        for(int j=0;j<(1ll<<L);j++){
            if(j&i) continue ;
            int x=a[j],y=a[i+j];
            a[j]=(x+y)%mod;
            a[i+j]=(x-y+mod)%mod;
        }
    }
}
int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}

signed main(){
    int n,m,k;
    cin>>n>>m>>k;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];

    vector<int> cnt(1ll<<L,0);
    for(int i=1;i<=n;i++) cnt[a[i]]++;
    Xor(cnt);

    vector<vector<int>> f(n+1,vector<int>(m,0)),g(n+1,vector<int>(m,0));
    f[0][0]=g[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<m;j++){
            f[i][j]=(f[i-1][j]+f[i-1][(j+m-1)%m])%mod;
            g[i][j]=(g[i-1][j]-g[i-1][(j+m-1)%m]+mod)%mod;
        }
    }
    vector<int> h(n+1);
    for(int i=0;i<=n;i++){
        for(int j=0;j<m;j++){
            h[i]=(h[i]+f[i][j]*g[n-i][(m-j)%m]%mod)%mod;
        }
    }

    vector<int> res(1ll<<L);
    for(int i=0;i<(1ll<<L);i++) res[i]=h[(cnt[i]+n)%mod*QPow(2,mod-2)%mod];
    Xor(res);

    int ans=0,inv=QPow(1ll<<L,mod-2);
    for(int i=0;i<(1ll<<L);i++){
        res[i]=res[i]%mod*inv%mod;
        ans=(ans+res[i]*QPow(i,k)%mod)%mod;
    }
    cout<<ans<<endl;

    return 0;
}