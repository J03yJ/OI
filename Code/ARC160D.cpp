#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e3+9;
const int mod=998244353;

int ifac[N<<1];
int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}
void Init(int lim){
    ifac[0]=1;
    for(int i=1;i<=lim;i++) ifac[i]=ifac[i-1]*QPow(i,mod-2)%mod;
}
int C(int x,int y){
    if(y>x) return 0;
    int res=ifac[y];
    for(int i=x-y+1;i<=x;i++) res=i%mod*res%mod;
    return res;
}

signed main(){
    int n,m,k;
    cin>>n>>m>>k;
    
    if(m%k){
        cout<<0<<endl;
        return 0;
    }
    m/=k;
    
    Init(n<<1);
    int ans=0;
    for(int i=0;i<=n-k+1;i++){
        int tmp=C(n-k+1,i)*C(m-i*k+2*n-k,2*n-k)%mod;
        if(i%2) ans=(ans+mod-tmp)%mod;
        else ans=(ans+tmp)%mod;
    }
    cout<<ans<<endl;

    return 0;
}