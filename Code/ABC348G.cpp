// LUOGU_RID: 163009906
#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e5+9;
const int V=1e9;
const int inf=4e18;

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
}tr[N*40];int cnt;
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
int query(int x,int L,int R,int k){
    if(!x) return 0;
    if(L==R) return k*dat(x)/siz(x);
    int mid=L+R>>1;
    if(k<=siz(rc(x))) return query(rc(x),mid+1,R,k);
    else return query(lc(x),L,mid,k-siz(rc(x)))+dat(rc(x));
}
int root[N];

int f[N];
void solve(int l,int r,int L,int R){
    if(l>r) return ;
    int mid=l+r>>1;
    int opt=0,ans=-inf;
    for(int i=max(L,mid);i<=R;i++){
        int res=query(root[i],-V,V,mid)-a[i].second;
        if(res>ans) ans=res,opt=i;
    }
    f[mid]=ans;
    solve(l,mid-1,L,opt);
    solve(mid+1,r,opt,R);
}

signed main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i].first>>a[i].second;

    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++) root[i]=insert(root[i-1],-V,V,a[i].first);

    solve(1,n,1,n);
    for(int i=1;i<=n;i++) cout<<f[i]<<endl;

    return 0;
}