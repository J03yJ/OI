#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=3e2+9;
const int V=1e5+9;
const int mod=998244353;
const int inv2=(mod+1)>>1;
const int inv3=(mod+1)/3;

int f[V],g[V],a[N],n,sum,ans=1;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    f[0]=g[0]=1;
    for(int i=1;i<=n;i++){
        sum+=a[i],ans=ans*3%mod;
        for(int j=sum;~j;j--){
            f[j]=(f[j]<<1)%mod;
            if(j>=a[i]) f[j]=(f[j]+f[j-a[i]])%mod;
            if(j>=a[i]) g[j]=(g[j]+g[j-a[i]])%mod;
        }
    }
    for(int i=sum+1>>1;i<=sum;i++) ans=(ans-f[i]*3+mod)%mod;
    if(!(sum&1)) ans=(ans+g[sum/2]*3%mod)%mod;
    cout<<ans<<endl;

    return 0;
}