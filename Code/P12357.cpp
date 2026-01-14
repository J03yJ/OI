#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
#define fir(x) (x).first
#define sec(x) (x).second
using ll=long long;
using pii=pair<int,int>;
const int N=2e5+9;
const int lgN=2e1;

int fi[N],ne[N<<1],to[N<<1],adj;
inline void AddEdge(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int fa[N][lgN],dep[N],n,m;
inline void DFS(int x){
    for(int k=1;k<lgN;k++) fa[x][k]=fa[fa[x][k-1]][k-1];
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x][0]) continue ;
        fa[y][0]=x;
        dep[y]=dep[x]+1;
        DFS(y);
    }
}
inline int LCA(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int k=lgN-1;~k;k--) if(dep[fa[x][k]]>=dep[y]) x=fa[x][k];
    if(x==y) return x;
    for(int k=lgN-1;~k;k--) if(fa[x][k]!=fa[y][k]) x=fa[x][k],y=fa[y][k];
    return fa[x][0];
}
inline int KAnc(int x,int k){
    for(int i=0;i<lgN;i++) if((k>>i)&1) x=fa[x][i];
    return x;
}
inline int Approx(int x,int y,int k=1){return KAnc(x,dep[x]-dep[y]-k);}

map<int,ll> asum[N];
map<pii,ll> bsum[N];
ll psum[N],ssum[N],dsum[N],bspc[N],ans[N],sum;
inline void AMdf(int u,int v,ll k,ll *a){a[u]+=k,a[fa[v][0]]-=k;}
inline void Sum(int x){
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x][0]) continue ;
        Sum(y);
        bspc[x]+=bspc[y];
        dsum[x]+=dsum[y];
        ssum[x]+=ssum[y];
    }
}
inline void Calc(int x){
    dsum[x]=sum-dsum[x];
    for(int i=fi[x];i;i=ne[i]) if(to[i]!=fa[x][0]) dsum[x]-=ssum[to[i]];
    asum[x][0]=asum[x][-1]=0;
    if(fa[x][0]) asum[x][fa[x][0]]=dsum[x];
    for(int i=fi[x];i;i=ne[i]) if(to[i]!=fa[x][0]) Calc(to[i]);
    for(auto p:bsum[x]){
        int u=fir(fir(p)),v=sec(fir(p));
        ans[x]=max(ans[x],psum[x]+asum[x][u]+asum[x][v]+bsum[x][{u,v}]);
    }
    ans[x]=max(ans[x],psum[x]+sec(*asum[x].rbegin())+sec(*next(asum[x].rbegin())));
    if(fa[x][0]) asum[fa[x][0]][x]+=ssum[x];
    if(dep[x]>1){
        int y=fa[x][0],z=fa[x][1];
        ans[y]=max(ans[y],psum[y]+asum[y][x]+asum[y][z]+bspc[x]);
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n>>m;
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        AddEdge(u,v);
        AddEdge(v,u);
    }

    dep[1]=1,DFS(1);
    while(m--){
        int u,v,w;
        cin>>u>>v>>w;
        int lca=LCA(u,v);
        ssum[lca]+=w;
        sum+=w;
        if(u==v){
            psum[u]+=w;
            continue ;
        }
        if(u!=lca) AMdf(fa[u][0],Approx(u,lca),w,dsum);
        if(v!=lca) AMdf(fa[v][0],Approx(v,lca),w,dsum);
        AMdf(lca,lca,w,dsum);
        if(dep[lca]+2<=dep[u]) AMdf(u,Approx(u,lca,2),w,bspc);
        if(dep[lca]+2<=dep[v]) AMdf(v,Approx(v,lca,2),w,bspc);
        if(u!=lca) asum[u][fa[u][0]]+=w;
        else asum[u][Approx(v,u)]+=w;
        if(v!=lca) asum[v][fa[v][0]]+=w;
        else asum[v][Approx(u,v)]+=w;
        if(u!=lca&&v!=lca){
            bsum[lca][{Approx(u,lca),Approx(v,lca)}]+=w;
            bsum[lca][{Approx(v,lca),Approx(u,lca)}]+=w;
        }
    }

    Sum(1),Calc(1);
    for(int i=1;i<=n;i++) cout<<ans[i]<<' ';cout<<endl;

    return 0;
}