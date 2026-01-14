#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e5+9;
const int inf=INT_MAX;
const int mod=(1ll<<61)-1;
using ll=long long;

struct RankSet{
    struct Node{
        int lc,rc,dep,siz;
        ll ans,w;pair<int,ll> val;
    }tr[N<<4];
    #define lc(x) tr[x].lc
    #define rc(x) tr[x].rc
    #define dep(x) tr[x].dep
    #define siz(x) tr[x].siz
    #define val(x) tr[x].val
    #define ans(x) tr[x].ans
    #define w(x) tr[x].w
    int cnt;
    inline int Allc(pair<int,ll> k){
        val(++cnt)=k,siz(cnt)=dep(cnt)=1;
        w(cnt)=ans(cnt)=k.second;
        return cnt;
    }
    RankSet(){Allc({inf,0});}
    inline void PushUp(int x){
        if(!lc(x)) siz(x)=dep(x)=1;
        else{
            dep(x)=max(dep(lc(x)),dep(rc(x)))+1;
            siz(x)=siz(lc(x))+siz(rc(x));
            val(x)=val(rc(x));
            
            w(x)=(w(lc(x))+w(rc(x)))%mod;
            ans(x)=(ans(lc(x))+ans(rc(x))+__int128(1)*w(rc(x))*siz(lc(x))%mod)%mod;
        }
    }
    inline void Rotate0(int x){
        int y=lc(x);
        lc(x)=lc(y),lc(y)=rc(y),rc(y)=rc(x),rc(x)=y;
        PushUp(y),PushUp(x);
    }
    inline void Rotate1(int x){
        int y=rc(x);
        rc(x)=rc(y),rc(y)=lc(y),lc(y)=lc(x),lc(x)=y;
        PushUp(y),PushUp(x);
    }
    inline void Maintain(int x){
        if(dep(lc(x))>dep(rc(x))+1){
            // if(dep(lc(lc(x)))==dep(rc(x))) Rotate1(x);
            Rotate0(x);
        }else if(dep(rc(x))>dep(lc(x))+1){
            // if(dep(rc(rc(x)))==dep(lc(x))) Rotate0(x);
            Rotate1(x);
        }else PushUp(x);
    }
    inline void Insert(int x,pair<int,ll> k){
        if(!lc(x)){
            lc(x)=Allc(min(val(x),k)),rc(x)=Allc(max(val(x),k));
            return PushUp(x);
        }
        if(k<=val(lc(x))) Insert(lc(x),k);
        else Insert(rc(x),k);
        Maintain(x);
    }
    inline void Erase(int x,pair<int,ll> k,int fa=0){
        if(!lc(x)){
            if(val(lc(fa))==k) tr[fa]=tr[rc(fa)];
            else if(val(rc(fa))==k) tr[fa]=tr[lc(fa)];
            // else assert(0);
            return ;
        }
        if(k<=val(lc(x))) Erase(lc(x),k,x);
        else Erase(rc(x),k,x);
        Maintain(x);
    }
}aset,bset;

const int base=998244353;
int a[N],b[N],bn[N],n,m,q;
int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=__int128(1)*res*x%mod;
        x=__int128(1)*x*x%mod;
        y>>=1;
    }
    return res;
}
#define Inv(x) QPow(x,mod-2)

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>m>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=m;i++) cin>>b[i];

    if(m>n){
        while(q--) cout<<0<<endl;
        return 0;
    }
    bn[0]=1;for(int i=1;i<=n;i++) bn[i]=__int128(1)*bn[i-1]*base%mod;
    vector<int> res;
    for(int i=1;i<=n;i++){
        if(i>m) aset.Erase(1,{a[i-m],bn[i-m]});
        aset.Insert(1,{a[i],bn[i]});
        if(i>=m) res.push_back(__int128(1)*aset.tr[1].ans*Inv(bn[i-m])%mod);
    }
    for(int i=1;i<=m;i++) bset.Insert(1,{b[i],bn[i]});
    sort(res.begin(),res.end());

    while(q--){
        int x,pos;
        cin>>pos>>x;
        bset.Erase(1,{b[pos],bn[pos]});
        b[pos]=x;
        bset.Insert(1,{b[pos],bn[pos]});
        int t=bset.tr[1].ans;
        cout<<upper_bound(res.begin(),res.end(),t)-lower_bound(res.begin(),res.end(),t)<<endl;
    }

    return 0;
}