#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=5e5+9;
const int mod=998244353;

int ntp[N],phi[N],pri[N],pcnt;
vector<int> d[N];
void InitP(int lim){
    phi[1]=1;
    for(int i=2;i<=lim;i++){
        if(!ntp[i]) pri[++pcnt]=i,phi[i]=i-1;
        for(int j=1;j<=pcnt&&i*pri[j]<=lim;j++){
            ntp[i*pri[j]]=1;
            if(i%pri[j]) phi[i*pri[j]]=phi[i]*phi[pri[j]];
            else{
                phi[i*pri[j]]=phi[i]*pri[j];
                break ;
            }
        }
    }
    for(int i=1;i<=lim;i++){
        for(int j=i;j<=lim;j+=i) d[j].push_back(i);
    }
}

int a[N],f[N],sum[N],pw2[N],n;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    pw2[0]=1;for(int i=1;i<=n;i++) pw2[i]=pw2[i-1]*2%mod;
    
    InitP(1e5);
    for(int i=1;i<=n;i++){
        f[i]=f[i-1]*2%mod;
        for(int x:d[a[i]]) f[i]=(f[i]+sum[x]*phi[x]%mod)%mod;
        for(int x:d[a[i]]) sum[x]=(sum[x]+pw2[i-1])%mod;
        cout<<f[i]<<endl;
    }

    return 0;
}