#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e5+9;

int val[N<<2],f[N],n,m,cnt;

int tr[N<<2];
void Add(int x,int k){
    while(x<=cnt){
        tr[x]=max(tr[x],k);
        x+=x&-x;
    }
}
int Ask(int x){
    int res=0;
    while(x){
        res=max(res,tr[x]);
        x&=x-1;
    }
    return res;
}
void Clear(int x){
    while(x<=cnt){
        tr[x]=0;
        x+=x&-x;
    }
}

struct Data{
    array<int,4> a;
    int op,id,w;
    inline int &operator [](int pos){
        return a[pos];
    }
}a[N],b[N];
bool Cmp0(Data x,Data y){
    return x.a<y.a;
}
bool Cmp1(Data x,Data y){
    if(x[1]!=y[1]) return x[1]<y[1];
    else if(x.a!=y.a) return x.a<y.a;
    else return x.op<y.op;
}
bool Cmp2(Data x,Data y){
    if(x[2]!=y[2]) return x[2]<y[2];
    else if(x.a!=y.a) return x.a<y.a;
    else return x.op<y.op;
}
void Solve2(int l,int r){
    if(l==r) return ;
    int mid=l+r>>1;
    Solve2(l,mid);
    Solve2(mid+1,r);
    for(int i=l;i<=mid;i++) if(b[i].op==0) b[i].op=2;
    for(int i=mid+1;i<=r;i++) if(b[i].op==1) b[i].op=3;
    stable_sort(b+l,b+r+1,Cmp2);

    // cout<<": "<<l<<' '<<r<<" : ";
    // for(int i=l;i<=r;i++) cout<<b[i][0]<<'/'<<b[i][1]<<'/'<<b[i][2]<<'/'<<b[i][3]<<'('<<b[i].op<<") ";
    // cout<<endl;

    for(int i=l;i<=r;i++){
        if(b[i].op==2) Add(b[i][3],f[b[i].id]);
        else if(b[i].op==3) f[b[i].id]=max(f[b[i].id],Ask(b[i][3]));
    }
    for(int i=l;i<=r;i++){
        if(b[i].op==2) Clear(b[i][3]);
        if(b[i].op>=2) b[i].op-=2;
    }
}
void Solve1(int l,int r){
    if(l==r){
        f[a[l].id]+=a[l].w;
        return ;
    }
    int mid=l+r>>1;
    Solve1(l,mid);
    memcpy(b+l,a+l,sizeof(Data)*(r-l+1));
    for(int i=mid+1;i<=r;i++) b[i].op=1;
    stable_sort(b+l,b+r+1,Cmp1);
    Solve2(l,r);

    // cout<<l<<' '<<r<<" : ";
    // for(int i=l;i<=r;i++) cout<<b[i][0]<<'/'<<b[i][1]<<'/'<<b[i][2]<<'/'<<b[i][3]<<'('<<b[i].op<<") ";
    // cout<<endl;

    Solve1(mid+1,r);
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int k=0;k<4;k++){
            cin>>a[i][k];
            val[++cnt]=a[i][k];
            cin>>a[i].w;
        }
    }

    sort(val+1,val+cnt+1);
    cnt=unique(val+1,val+cnt+1)-val-1;
    for(int i=1;i<=n;i++){
        for(int k=0;k<4;k++) a[i][k]=lower_bound(val+1,val+cnt+1,a[i][k])-val;
    }

    int tot=0;
    stable_sort(a+1,a+n+1,Cmp0);
    for(int i=1;i<=n;i++){
        if(a[i].a==a[i-1].a) a[tot].w+=a[i].w;
        else a[++tot]=a[i];
    }
    n=tot;
    for(int i=1;i<=n;i++) a[i].id=i;
    Solve1(1,n);

    // for(int i=1;i<=n;i++) cout<<f[i]<<' ';
    // cout<<endl;

    int ans=0;
    for(int i=1;i<=n;i++) ans=max(ans,f[i]);
    cout<<ans<<endl;

    return 0;
}