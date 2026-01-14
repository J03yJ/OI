#include<bits/stdc++.h>

using namespace std;

#define int long long
const int mod=998244353;

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
    int n;
    cin>>n;
    vector<int> a(n+1,0),d(n+1,0),H(n+1,0);
    d[1]=1;
    for(int i=2;i<=n;i++) cin>>a[i],d[i]=d[a[i]]+1;

    int ans=0;
    for(int i=1;i<=n;i++) H[i]=(H[i-1]+QPow(i,mod-2))%mod;
    for(int i=1;i<=n;i++) ans=(ans+H[d[i]])%mod;

    cout<<ans<<endl;

    return 0;
}