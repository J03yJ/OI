#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e5+9;
const int V=2e9;
const int inf=1e18;

pair<int,int> a[N];
bool cmp(pair<int,int> x,pair<int,int> y){
    if(x.second!=y.second) return x.second<y.second;
    else return x.first<y.first;
}

struct node{
    int lc,rc,dat,siz;
    node(){}
    node(int L,int R,int D){
        lc=L;rc=R;dat=D;
    }
}tr[N*80];int cnt;
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define dat(x) tr[x].dat
#define siz(x) tr[x].siz

inline void pushup(int x){
    siz(x)=siz(lc(x))+siz(rc(x));
    dat(x)=dat(lc(x))+dat(rc(x));
}
int insert(int x,int L,int R,int k){
    int y=++cnt;
    tr[y]=tr[x];
    if(L==R){
        siz(y)++;
        dat(y)+=L;
        return y;
    }
    int mid=L+R>>1;
    if(k<=mid) lc(y)=insert(lc(x),L,mid,k);
    else rc(y)=insert(rc(x),mid+1,R,k);
    pushup(y);
    return y;
}
int query(int l,int r,int L,int R,int k){
    if(siz(r)-siz(l)<=k) return dat(r)-dat(l);
    if(L==R) return min(k,siz(r)-siz(l))*L;
    int mid=L+R>>1;
    if(k<=(siz(rc(r))-siz(rc(l)))) return query(rc(l),rc(r),mid+1,R,k);
    else return query(lc(l),lc(r),L,mid,k-(siz(rc(r))-siz(rc(l))))
                +(dat(rc(r))-dat(rc(l)));
}
int root[N];

int n,m;

int f[N];
void solve(int l,int r,int L,int R){
    if(l>r) return ;
    int mid=l+r>>1;
    int opt=0,ans=-inf;

    for(int i=L;i<=min(mid-m+1,R);i++){
        int res=query(root[i-1],root[mid],1,V,m)-2*(a[mid].second-a[i].second);
        if(res>=ans) ans=res,opt=i;
    }
    f[mid]=ans;

    solve(l,mid-1,L,opt);
    solve(mid+1,r,opt,R);
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i].first>>a[i].second;

    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++) root[i]=insert(root[i-1],1,V,a[i].first);

    solve(m,n,1,n);
    int res=-inf;
    for(int i=m;i<=n;i++) res=max(res,f[i]);
    cout<<res<<endl;

    return 0;
}