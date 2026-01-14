#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=5e4+9;

int pri[N],mu[N],ntp[N],sum[N],cnt;
void InitP(int n){
    ntp[1]=1;mu[1]=1;
    for(int i=2;i<=n;i++){
        if(!ntp[i]) mu[i]=-1,pri[++cnt]=i;
        for(int j=1;j<=cnt&&pri[j]*i<=n;j++){
            ntp[pri[j]*i]=1;
            if(i%pri[j]) mu[i*pri[j]]=-mu[i];
            else{
                mu[i*pri[j]]=0;
                break ;
            }
        }
    }
    for(int i=1;i<=n;i++) mu[i]+=mu[i-1];
    for(int i=1;i<=n;i++){
        for(int l=1,r;l<=i;l=r+1){
            r=i/(i/l);
            sum[i]+=(r-l+1)*(i/l);
        }
    }
}

signed main(){
    InitP(5e4);
    int T;
    cin>>T;
    while(T--){
        int n,m;
        cin>>n>>m;
        if(n>m) swap(n,m);
        int ans=0;
        for(int l=1,r;l<=n;l=r+1){
            r=min(n/(n/l),m/(m/l));
            ans+=(mu[r]-mu[l-1])*sum[n/l]*sum[m/l];
        }
        cout<<ans<<endl;
    }

    return 0;
}