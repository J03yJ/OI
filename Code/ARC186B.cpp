#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=3e5+9;
const int mod=998244353;

int a[N],ans[N],siz[N],fac[N],ifac[N],n;
vector<int> son[N];
int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}
int C(int n,int m){
    return fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}
void DFS(int x){
    ans[x]=1;
    for(int y:son[x]){
        DFS(y);
        ans[x]=ans[x]*ans[y]%mod*C(siz[x]+siz[y]-1,siz[x])%mod;
        siz[x]+=siz[y];
    }
    siz[x]++;
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],son[a[i]].push_back(i);

    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    ifac[n]=QPow(fac[n],mod-2);
    for(int i=n-1;~i;i--) ifac[i]=ifac[i+1]*(i+1)%mod;

    DFS(0);
    cout<<ans[0]<<endl;

    return 0;
}