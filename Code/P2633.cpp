#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;

int a[N],val[N],n,m,tot;

struct node{
    int lc,rc,siz;
}tr[N*40];
int cnt=0;
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define siz(x) tr[x].siz
int insert(int x,int L,int R,int pos){
    // cout<<x<<' '<<L<<' '<<R<<' '<<pos<<endl;
    int y=++cnt;
    tr[y]=tr[x];
    if(L==R) return siz(y)++,y;
    int mid=L+R>>1;
    if(pos<=mid) lc(y)=insert(lc(x),L,mid,pos);
    else rc(y)=insert(rc(x),mid+1,R,pos);
    siz(y)=siz(lc(y))+siz(rc(y));
    return y;
}
int query(int w,int x,int y,int z,int L,int R,int k){
    // cout<<L<<' '<<R<<' '<<siz(w)<<' '<<siz(x)<<' '<<siz(y)<<' '<<siz(z)<<endl;
    if(L==R) return L;
    int mid=L+R>>1,SIZ=siz(lc(w))+siz(lc(x))-siz(lc(y))-siz(lc(z));
    // cout<<"  >> "<<SIZ<<endl;
    if(k<=SIZ) return query(lc(w),lc(x),lc(y),lc(z),L,mid,k);
    else return query(rc(w),rc(x),rc(y),rc(z),mid+1,R,k-SIZ);
}

int fi[N],ne[N<<1],to[N<<1],adj;
void adeg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int fa[N],dep[N],siz[N],hson[N];
void dfs1(int x){
    siz[x]=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        dep[y]=dep[x]+1;
        fa[y]=x;
        dfs1(y);
        siz[x]+=siz[y];
        if(siz[hson[x]]<siz[y]) hson[x]=y;
    }
}
int top[N];
void dfs2(int x,int t){
    top[x]=t;
    if(hson[x]) dfs2(hson[x],t);
    else return ;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]||y==hson[x]) continue ;
        dfs2(y,y);
    }
}
int lca(int x,int y){
    while(top[x]!=top[y]){
        // cout<<top[x]<<'/'<<top[y]<<' '<<x<<'/'<<y<<endl;
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        x=fa[top[x]];
    }
    if(dep[x]<dep[y]) return x;
    else return y;
}
int root[N];
void dfs3(int x){
    // cout<<x<<" : "<<a[x]<<endl;
    root[x]=insert(root[fa[x]],1,tot,a[x]);
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        dfs3(y);
    }
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1,u,v;i<n;i++) cin>>u>>v,adeg(u,v),adeg(v,u);
    
    for(int i=1;i<=n;i++) val[i]=a[i];
    sort(val+1,val+n+1);
    tot=unique(val+1,val+n+1)-val-1;
    for(int i=1;i<=n;i++) a[i]=lower_bound(val+1,val+tot+1,a[i])-val;

    dfs1(1);
    dfs2(1,1);
    dfs3(1);

    int lst=0;
    while(m--){
        int u,v,k;
        cin>>u>>v>>k;
        u^=lst;
        int l=lca(u,v);
        // cout<<u<<' '<<v<<' '<<l<<' '<<fa[l]<<endl;
        lst=val[query(root[u],root[v],root[l],root[fa[l]],1,tot,k)];
        cout<<lst<<endl;
    }

    return 0;
}