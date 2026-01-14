#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=5e5+9;

int a[N],rk[N],n,q,tot;
vector<int> lft[N];

namespace SgT{
    struct Node{
        int l,r;
        ll sum,siz;
    }tr[N<<2];
    #define l(x) tr[x].l
    #define r(x) tr[x].r
    #define sum(x) tr[x].sum
    #define siz(x) tr[x].siz

    inline void PushUp(int x){
        sum(x)=sum(x<<1)+sum(x<<1|1);
        siz(x)=siz(x<<1)+siz(x<<1|1);
    }
    inline void Build(int x,int l,int r){
        l(x)=l,r(x)=r;
        if(l(x)==r(x)) return ;
        int mid=l(x)+r(x)>>1;
        Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
        PushUp(x);
    }
    inline void Insert(int x,int pos,int k){
        if(l(x)==r(x)) return sum(x)+=k,siz(x)++,void();
        int mid=l(x)+r(x)>>1;
        if(pos<=mid) Insert(x<<1,pos,k);
        else Insert(x<<1|1,pos,k);
        PushUp(x);
    }
    inline ll Query(int x,int k){
        if(!k) return 0;
        if(k>=siz(x)) return sum(x);
        if(l(x)==r(x)) return k*(sum(x)/siz(x));
        if(k<=siz(x<<1)) return Query(x<<1,k);
        else return sum(x<<1)+Query(x<<1|1,k-siz(x<<1));
    }
}
namespace Fenw{
    struct Fenw{
        ll tr[N];
        inline void Add(int x,int k){while(x<=n){tr[x]+=k,x+=x&-x;}}
        inline ll Ask(int x){ll sum=0;while(x){sum+=tr[x],x&=x-1;}return sum;}
        inline ll Ask(int l,int r){return Ask(r)-Ask(l-1);}
    }val,cnt,sum;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    vector<int> val(a+1,a+n+1);
    val.push_back(0);
    sort(val.begin(),val.end());
    val.erase(unique(val.begin(),val.end()),val.end());
    for(int i=1;i<=n;i++) rk[i]=lower_bound(val.begin(),val.end(),a[i])-val.begin();
    tot=val.size()-1;

    for(int i=1;i<=n;i++){
        Fenw::val.Add(rk[i],1);
        Fenw::cnt.Add(i,1);
        Fenw::sum.Add(i,a[i]);
        lft[Fenw::val.Ask(rk[i]+1,n)+1].push_back(i);
    }

    int t=0;
    auto PreQ=[&t](int pos){
        int qos=min(pos+t,n);
        return Fenw::sum.Ask(qos)+SgT::Query(1,pos-Fenw::cnt.Ask(qos));
    };
    SgT::Build(1,1,tot);
    cin>>q;
    while(q--){
        int op;
        cin>>op;
        if(op==1){
            t++;
            for(int i:lft[t]){
                Fenw::cnt.Add(i,-1);
                Fenw::sum.Add(i,-a[i]);
                SgT::Insert(1,rk[i],a[i]);
            }
        }else{
            int l,r;
            cin>>l>>r;
            cout<<PreQ(r)-PreQ(l-1)<<endl;
        }
    }

    return 0;
}