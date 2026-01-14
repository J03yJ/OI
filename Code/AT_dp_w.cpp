#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e5+9;
const int inf=1e18;

struct Node{
    int l,r,dat,tag;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat
#define tag(x) tr[x].tag

void PushUp(int x){dat(x)=min(dat(x<<1),dat(x<<1|1));}
void Push(int x,int k){tag(x)+=k,dat(x)+=k;}
void PushDown(int x){Push(x<<1,tag(x)),Push(x<<1|1,tag(x)),tag(x)=0;}
void Build(int x,int l,int r){
    l(x)=l,r(x)=r;
    if(l(x)==r(x)) return ;
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l,mid);
    Build(x<<1|1,mid+1,r);
    PushUp(x);
}
void Modify(int x,int l,int r,int k){
    if(l<=l(x)&&r(x)<=r) return Push(x,k);
    PushDown(x);
    int mid=l(x)+r(x)>>1;
    if(l<=mid) Modify(x<<1,l,r,k);
    if(r>mid) Modify(x<<1|1,l,r,k);
    PushUp(x);
}
int Query(int x,int l,int r){
    if(l<=l(x)&&r(x)<=r) return dat(x);
    PushDown(x);
    int mid=l(x)+r(x)>>1,ans=inf;
    if(l<=mid) ans=min(ans,Query(x<<1,l,r));
    if(r>mid) ans=min(ans,Query(x<<1|1,l,r));
    return ans;
}

int f[N][2],n,m,ans;
vector<pair<int,int>> q[N];

signed main(){
    cin>>n>>m;
    for(int i=1,l,r,w;i<=m;i++){
        cin>>l>>r>>w;
        ans+=w;
        q[r].push_back({l,w});
    }
    
    Build(1,0,n);
    for(int i=1;i<=n;i++){
        for(auto p:q[i]) Modify(1,0,p.first-1,p.second);
        f[i][1]=min(f[i-1][0],f[i-1][1]);
        f[i][0]=Query(1,0,i-1);
        Modify(1,i,i,f[i][1]);
    }

    cout<<ans-min(f[n][1],f[n][0])<<endl;

    return 0;
}