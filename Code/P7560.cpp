#include<bits/stdc++.h>

using namespace std;

#define int long long
#define fir(x) x.first
#define sec(x) x.second
using ll=long long;
using pll=pair<ll,ll>;
using pii=pair<int,int>;

const int N=2.5e5+9;

namespace Total{
    struct Node{
        int l,r;
        ll tag;pll dat;
    }tr[N<<2];
    #define l(x) tr[x].l
    #define r(x) tr[x].r
    #define dat(x) tr[x].dat
    #define tag(x) tr[x].tag

    inline void PushUp(int x){dat(x)=min(dat(x<<1),dat(x<<1|1));}
    inline void Push(int x,int k){fir(dat(x))+=k,tag(x)+=k;}
    inline void PushDown(int x){Push(x<<1,tag(x)),Push(x<<1|1,tag(x)),tag(x)=0;}

    inline void Build(int x,int l,int r){
        l(x)=l,r(x)=r,fir(dat(x))=tag(x)=0;
        if(l(x)==r(x)) return sec(dat(x))=l(x),void();
        int mid=l(x)+r(x)>>1;
        Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
        PushUp(x);
    }
    inline void Modify(int x,int l,int r,int k){
        if(l<=l(x)&&r(x)<=r) return Push(x,k);
        int mid=l(x)+r(x)>>1;
        PushDown(x);
        if(l<=mid) Modify(x<<1,l,r,k);
        if(r>mid) Modify(x<<1|1,l,r,k);
        PushUp(x);
    }
    inline pll Min(int x,int l,int r){
        if(l<=l(x)&&r(x)<=r) return dat(x);
        int mid=l(x)+r(x)>>1;
        PushDown(x);
        if(l<=mid&&r>mid) return min(Min(x<<1,l,r),Min(x<<1|1,l,r));
        else if(l<=mid) return Min(x<<1,l,r);
        else return Min(x<<1|1,l,r);
    }
    inline ll Get(int pos){return pos?fir(Min(1,pos,pos)):0;}
}
namespace Add{
    struct Node{
        int l,r;
        ll dat,tag;
    }tr[N<<2];
    inline void PushUp(int x){dat(x)=max(dat(x<<1|1),dat(x<<1|1));}
    inline void Push(int x,int k){dat(x)+=k,tag(x)+=k;}
    inline void PushDown(int x){Push(x<<1,tag(x)),Push(x<<1|1,tag(x)),tag(x)=0;}

    inline void Build(int x,int l,int r){
        l(x)=l,r(x)=r,dat(x)=tag(x)=0;
        if(l(x)==r(x)) return ;
        int mid=l(x)+r(x)>>1;
        Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
    }
    inline void Modify(int x,int l,int r,int k){
        if(l<=l(x)&&r(x)<=r) return Push(x,k);
        int mid=l(x)+r(x)>>1;
        PushDown(x);
        if(l<=mid) Modify(x<<1,l,r,k);
        if(r>mid) Modify(x<<1|1,l,r,k);
        PushUp(x);
    }
    inline ll Max(int x,int l,int r){
        if(l<=l(x)&&r(x)<=r) return dat(x);
        int mid=l(x)+r(x)>>1;
        PushDown(x);
        if(l<=mid&&r>mid) return max(Max(x<<1,l,r),Max(x<<1|1,l,r));
        else if(l<=mid) return Max(x<<1,l,r);
        else return Max(x<<1|1,l,r);
    }
    inline ll Get(int pos){return pos?Max(1,pos,pos):0;}
    inline int Find(int x,int k){
        if(dat(x)<k) return 0;
        if(l(x)==r(x)) return l(x);
        PushDown(x);
        if(k<=dat(x<<1)) return Find(x<<1,k);
        else return Find(x<<1|1,k);
    }
    inline int Query(int x,int k){int tmp=Find(1,k);return tmp<=x?tmp:0;}
}

vector<pii> qry[N],mdf[N];
int c[N],n,m,q,ans[N],ifq[N];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>m>>q;
    for(int i=1,op,x,y,k;i<=q;i++){
        cin>>op>>x>>y;
        if(op==3) qry[x].push_back({i,y}),ifq[i]=1;
        else{
            if(op==1) cin>>c[i]>>k;
            else cin>>k,k=-k;
            mdf[x].push_back({i,k});
            mdf[y+1].push_back({i,-k});
        }
    }

    Total::Build(1,1,q);
    Add::Build(1,1,q);
    for(int i=1;i<=n;i++){
        for(pii p:mdf[i]){
            Total::Modify(1,fir(p),q,sec(p));
            if(c[fir(p)]) Add::Modify(1,fir(p),q,sec(p));
        }
        for(pii p:qry[i]){
            pll res=Total::Min(1,1,fir(p));
            ll pos=fir(res)>0?0:sec(res),bsc=Total::Get(pos);
            ll tmp=bsc+Add::Get(fir(p))-Total::Get(fir(p))+sec(p);
            ans[fir(p)]=c[Add::Query(fir(p),tmp)];
        }
    }

    for(int i=1;i<=q;i++) if(ifq[i]) cout<<ans[i]<<endl;

    return 0;
}