#include<bits/stdc++.h>

using namespace std;

#define int long long

const int inf=1e18;
const int N=1e5+9;

struct Node{
    int l,r;
    int tcnt,tsum,tag,dat,hdat;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define tcnt(x) tr[x].tcnt
#define tsum(x) tr[x].tsum
#define tag(x) tr[x].tag
#define dat(x) tr[x].dat
#define hdat(x) tr[x].hdat
#define len(x) (r(x)-l(x)+1)
void Push(int x,int cnt,int sum,int tg){
    hdat(x)+=cnt*dat(x)+sum*len(x);
    tsum(x)+=cnt*tag(x)+sum;
    tcnt(x)+=cnt;
    dat(x)+=tg*len(x);
    tag(x)+=tg;
}
void PushDown(int x){
    Push(x<<1,tcnt(x),tsum(x),tag(x));
    Push(x<<1|1,tcnt(x),tsum(x),tag(x));
    tag(x)=tsum(x)=tcnt(x)=0;
}
void PushUp(int x){
    dat(x)=dat(x<<1)+dat(x<<1|1);
    hdat(x)=hdat(x<<1)+hdat(x<<1|1);
}

void Build(int x,int l,int r){
    l(x)=l,r(x)=r,tcnt(x)=tsum(x)=tag(x)=dat(x)=hdat(x)=0;
    if(l(x)==r(x)) return ;
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l,mid);
    Build(x<<1|1,mid+1,r);
    PushUp(x);
}
void Modify(int x,int l,int r,int k){
    if(l<=l(x)&&r(x)<=r) return Push(x,0,0,k);
    int mid=l(x)+r(x)>>1;
    PushDown(x);
    if(l<=mid) Modify(x<<1,l,r,k);
    if(r>mid) Modify(x<<1|1,l,r,k);
    PushUp(x);
}
int Query(int x,int l,int r){
    if(l<=l(x)&&r(x)<=r) return hdat(x);
    int mid=l(x)+r(x)>>1;
    PushDown(x);
    if(l<=mid&&r>mid) return Query(x<<1,l,r)+Query(x<<1|1,l,r);
    else if(l<=mid) return Query(x<<1,l,r);
    else return Query(x<<1|1,l,r);
}

int a[N],ans[N],n=1e5,q;
vector<array<int,4>> qry[N];

signed main(){
    const int mod=1e9;
    int fst=1023,sec=1025;
    for(int i=1;i<=n;i++){
        a[i]=fst^sec;
        fst=fst*1023%mod;
        sec=sec*1025%mod;
    }
    a[0]=-inf;

    cin>>q;
    for(int i=1,l,r,L,R;i<=q;i++){
        cin>>l>>r>>L>>R;
        qry[L-1].push_back({i,l,r,-1});
        qry[R].push_back({i,l,r,1});
    }

    Build(1,1,n);
    vector<int> stk(1,0);
    for(int i=1;i<=n;i++){
        while(a[i]<a[stk.back()]){
            int cur=stk.back();
            stk.pop_back();
            Modify(1,stk.back()+1,cur,a[i]-a[cur]);
        }
        stk.push_back(i);
        Modify(1,i,i,a[i]);
        Push(1,1,0,0);
        for(auto t:qry[i]) ans[t[0]]+=Query(1,t[1],t[2])*t[3];
    }

    for(int i=1;i<=n;i++) a[i]=-a[i];

    Build(1,1,n);
    stk=vector<int>(1,0);
    for(int i=1;i<=n;i++){
        while(a[i]<a[stk.back()]){
            int cur=stk.back();
            stk.pop_back();
            Modify(1,stk.back()+1,cur,a[i]-a[cur]);
        }
        stk.push_back(i);
        Modify(1,i,i,a[i]);
        Push(1,1,0,0);
        for(auto t:qry[i]) ans[t[0]]+=Query(1,t[1],t[2])*t[3];
    }

    for(int i=1;i<=q;i++) cout<<-ans[i]<<endl;

    return 0;
}