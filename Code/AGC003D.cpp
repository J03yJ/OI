#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e5+9;
const int mod=998244353;
const int mod_=1e9+7;

int pri[N],ntp[N],cnt;
void InitP(int n){
    for(int i=2;i<=n;i++){
        if(!ntp[i]) pri[++cnt]=i;
        for(int j=1;j<=cnt&&pri[j]*i<=n;j++){
            ntp[pri[j]*i]=1;
            if(i%pri[j]) continue ;
        }
    }
}

int a[N],n;
vector<pair<int,int>> c[N];
int Hsh(vector<pair<int,int>> v,int mod){
    int res=1;
    for(pair<int,int> p:v) for(int i=1;i<=p.second;i++) res=res*p.first%mod;
    return res;
}
int RHsh(vector<pair<int,int>> v,int mod){
    int res=1;
    for(pair<int,int> p:v) for(int i=1;i<=3-p.second;i++) res=res*p.first%mod;
    return res;
}
#define Hash(x) {Hsh(x,mod),Hsh(x,mod_)}
#define RHash(x) {RHsh(x,mod),RHsh(x,mod_)}

signed main(){
    InitP(1e5);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    for(int i=1;i<=n;i++){
        for(int j=1;j<=cnt&&pri[j]*pri[j]<=a[i];j++){
            int cnt=0;
            while(a[i]%pri[j]==0) a[i]/=pri[j],cnt++;
            if(cnt%3) c[i].push_back({pri[j],cnt%3});
        }
        if(a[i]!=1) c[i].push_back({a[i],1});
        // for(pair<int,int> p:c[i]) cout<<p.first<<'/'<<p.second<<' ';cout<<endl;
    }

    int ans=0;
    map<pair<int,int>,int> w;
    map<pair<int,int>,pair<int,int>> r;
    for(int i=1;i<=n;i++){
        pair<int,int> x=Hash(c[i]),y=RHash(c[i]);
        ans-=max(w[x],w[y]);
        if(x==y) w[x]=1;
        else w[x]++;
        ans+=max(w[x],w[y]);
        // cout<<x.first<<' '<<x.second<<' '<<y.first<<' '<<y.second<<endl;
    }

    cout<<ans<<endl;

    return 0;
}