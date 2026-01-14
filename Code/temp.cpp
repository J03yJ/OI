#include<bits/stdc++.h>

using namespace std;

// ifstream fin("dcg.in");
// ofstream fout("dcg.out");
// #define cin fin
// #define cout fout
#define endl '\n'

using ll=long long;
const int N=1e6+9;
const int mod=998244353;
inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) MulAs(res,x);
        MulAs(x,x);
        y>>=1;
    }
    return res;
}
inline int Inv(int x){return QPow(x,mod-2);}
inline int Mod(ll x){return x%mod;}

int pri[N],ntp[N],mu[N],smu[N],pcnt,B;
inline void Init(int lim){
    mu[1]=1;
    for(int i=2;i<=lim;i++){
        if(!ntp[i]) pri[++pcnt]=i,mu[i]=-1;
        for(int j=1;j<=pcnt&&pri[j]*i<=lim;j++){
            ntp[i*pri[j]]=1;
            if(i%pri[j]) mu[i*pri[j]]=-mu[i];
            else{
                mu[i*pri[j]]=0;
                break ;
            }
        }
    }
    for(int i=1;i<=lim;i++) smu[i]=Add(smu[i-1],Sub(mu[i],0));
}
unordered_map<ll,int> sm;
inline int SMu(ll x){
    if(x<=B) return smu[x];
    else if(sm.count(x)) return sm[x];
    int res=1;
    for(ll l=2,r;l<=x;l=r+1){
        r=x/(x/l);
        SubAs(res,Mul(Mod(r-l+1),SMu(x/l)));
    }
    return sm[x]=res;
}

int sf[N<<1],w,cnt;
ll p[N],c[N],pp[N],val[N],n;
inline int Id(ll x){return x<=B?x:n/x+B;}

signed main(){
    cin>>n>>w;
    for(int i=1;i<=w;i++){
        pp[i]=1;
        cin>>p[i]>>c[i];
        for(int j=1;j<=c[i];j++) pp[i]*=p[i];
    }

    Init(B=sqrt(n));
    for(ll l=1,r;l<=n;l=r+1){
        r=n/(n/l);
        val[++cnt]=n/l;
        sf[Id(n/l)]=SMu(n/l);
    }
    for(int i=1;i<=cnt;i++) cout<<val[i]<<' ';cout<<endl;
    for(int i=1;i<=w;i++){
        for(int j=cnt;j>=1;j--) if(val[j]>=p[i]) AddAs(sf[Id(val[j])],sf[Id(val[j]/p[i])]),cout<<val[j]<<' '<<val[j]/p[i]<<' '<<Id(val[j])<<' '<<Id(val[j]/p[i])<<endl;
        if(pp[i]>n/p[i]) continue ;
        ll ppow=p[i]*pp[i];
        for(int j=1;j<=cnt;j++) if(val[j]>=ppow) SubAs(sf[Id(val[j])],sf[Id(val[j]/ppow)]);
    }

    int ans=1;
    for(int i=1;i<cnt;i++){
        int f=Sub(sf[Id(val[i])],sf[Id(val[i+1])]);
        SubAs(ans,Mul(f,Mul(Mod(n/val[i]),Inv(Mod(n-n/val[i])))));
    }
    cout<<ans<<endl;

    return 0;
}