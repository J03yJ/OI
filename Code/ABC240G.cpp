#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e7+9;
const int mod=998244353;

int fac[N<<1],ifac[N<<1],n;
int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=1ll*x*res%mod;
        x=1ll*x*x%mod;
        y>>=1;
    }
    return res;
}
inline void Init(int lim){
    fac[0]=1;
    for(int i=1;i<=lim;i++) fac[i]=1ll*fac[i-1]*i%mod;
    ifac[lim]=QPow(fac[lim],mod-2);
    for(int i=lim-1;~i;i--) ifac[i]=1ll*ifac[i+1]*(i+1)%mod;
}
inline int C(int n,int m){
    if(m>n||m<0) return 0;
    return 1ll*fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}
inline int F1(int n,int x){
    if(x<0) x=-x;
    if((n&1)^(x&1)) return 0;
    else return C(n,(n+x)>>1);
}
inline int F2(int n,int x,int y){
    int xx=x+y,yy=x-y;
    return 1ll*F1(n,xx)*F1(n,yy)%mod;
}

signed main(){
    int a,b,c;
    cin>>n>>a>>b>>c;
    
    Init(n<<1);
    int ans=0;
    for(int i=a;i<=n;i++){
        ans=(ans+1ll*C(n,i)*F2(n-i,b,c)%mod*F1(i,a)%mod)%mod;
    }

    cout<<ans<<endl;

    return 0;
}