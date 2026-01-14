#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e5+9;
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
    int n,m;
    cin>>n>>m;
    int ans=0;
    for(int i=1;i<=n;i++) ans=(ans+QPow(i,mod-2))%mod;
    ans=ans*n%mod;
    ans=(ans+ans-1)%mod;
    ans=ans*m%mod*m%mod;
    cout<<ans<<endl;

    return 0;
}