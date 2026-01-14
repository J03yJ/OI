#include<bits/stdc++.h>

using namespace std;

const int mod=104857601;
const int N=1e6+9;

int QPow(int x,int y){
    int res=1;
    x%=mod;
    while(y){
        if(y&1) res=1ll*res*x%mod;
        x=1ll*x*x%mod;
        y>>=1;
    }
    return res;
}
int pri[N],phi[N],ntp[N],cnt;
void InitP(int n){
    ntp[1]=phi[1]=1;
    for(int i=2;i<=n;i++){
        if(!ntp[i]) pri[++cnt]=i,phi[i]=i-1;
        for(int j=1;j<=cnt&&pri[j]*i<=n;j++){
            ntp[pri[j]*i]=1;
            if(i%pri[j]) phi[pri[j]*i]=phi[pri[j]]*phi[i];
            else{
                phi[pri[j]*i]=pri[j]*phi[i];
                break ;
            }
        }
    }
    for(int i=1;i<=n;i++) phi[i]=(phi[i]+phi[i-1])%(mod-1);
}

int main(){
    int n;
    cin>>n;

    InitP(n);
    int ans=1;
    for(int i=1;i<=n;i++) ans=1ll*ans*i%mod;
    ans=QPow(ans,n<<1);
    for(int i=1;i<=n;i++){
        int e=(phi[n/i]*2-1)%(mod-1);
        ans=1ll*ans*QPow(QPow(QPow(i,e),mod-2),2)%mod;
    }

    cout<<ans<<endl;

    return 0;
}