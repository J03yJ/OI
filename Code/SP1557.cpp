#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e5+9;

struct Data{
    int mx=0,hmx=0,tag=0,htag=0;
};
struct Node{
    int l,r;
    Data dat;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat

void PushUp(int x){
    dat(x).mx=max(dat(x<<1).mx,dat(x<<1|1).mx);
    dat(x).hmx=max(dat(x<<1).hmx,dat(x<<1|1).hmx);
}
void Push(int x,int tag,int htag){
    dat(x).hmx=max(dat(x).hmx,dat(x).mx+htag);
    dat(x).mx+=tag;
    dat(x).htag=max(dat(x).htag,dat(x).tag+htag);
    dat(x).tag+=tag;
}
void PushDown(int x){
    Push(x<<1,dat(x).tag,dat(x).htag);
    Push(x<<1|1,dat(x).tag,dat(x).htag);
    dat(x).tag=dat(x).htag=0;
}
void Build(int x,int l,int r){
    l(x)=l,r(x)=r;
    if(l(x)==r(x)) return ;
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
    PushUp(x);
}
void Modify(int x,int l,int r,int k){
    if(l<=l(x)&&r(x)<=r) return Push(x,k,k);
    int mid=l(x)+r(x)>>1;
    PushDown(x);
    if(l<=mid) Modify(x<<1,l,r,k);
    if(r>mid) Modify(x<<1|1,l,r,k);
    PushUp(x);
}
int Query(int x,int l,int r){
    if(l<=l(x)&&r(x)<=r) return dat(x).hmx;
    int mid=l(x)+r(x)>>1;
    PushDown(x);
    if(l<=mid&&r>mid) return max(Query(x<<1,l,r),Query(x<<1|1,l,r));
    else if(l<=mid) return Query(x<<1,l,r);
    else return Query(x<<1|1,l,r);
}

int a[N],ans[N],pre[N],_buc[N<<1],n,q,*buc=_buc+N;
vector<pair<int,int>> qry[N];

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    cin>>q;
    for(int i=1,l,r;i<=q;i++) cin>>l>>r,qry[r].push_back({i,l});

    Build(1,1,n);
    for(int i=1;i<=n;i++) pre[i]=buc[a[i]],buc[a[i]]=i;
    for(int i=1;i<=n;i++){
        Modify(1,pre[i]+1,i,a[i]);
        // for(int j=1;j<=n;j++) cout<<Query(1,j,j)<<' ';cout<<endl;
        for(pair<int,int> p:qry[i]){
            ans[p.first]=Query(1,p.second,i);
        }
    }
    for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

    return 0;
}