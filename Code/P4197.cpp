#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;
const int M=5e5+9;
const int inf=1e9+7;
const int V=1e9;

int a[N];

struct edge{
    int u,v,w;
    bool operator <(edge e){
        return w<e.w;
    }
}e[N];
int fa[N];
inline int find(int x){
    if(fa[x]==x) return x;
    else return fa[x]=find(fa[x]);
}
inline void merge(int x,int y){
    fa[find(y)]=find(x);
}

int w[N<<1],st[N<<1][20],lc[N<<1],rc[N<<1],siz[N<<1];
int dfn[N<<1],rdf[N<<1],dcnt;
void dfs(int x){
    // cout<<x<<endl;
    dfn[x]=++dcnt;
    rdf[dcnt]=x;
    if(lc[x]) dfs(lc[x]),dfs(rc[x]);
    siz[x]=siz[lc[x]]+siz[rc[x]]+1;
}

struct node{
    int lc,rc,siz;
}tr[N<<6];int cnt;
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define siz(x) tr[x].siz
int insert(int x,int L,int R,int k){
    int y=++cnt;
    tr[y]=tr[x];
    if(L==R){
        siz(y)++;
        return y;
    }
    int mid=L+R>>1;
    if(k<=mid) lc(y)=insert(lc(x),L,mid,k);
    else rc(y)=insert(rc(x),mid+1,R,k);
    siz(y)=siz(lc(y))+siz(rc(y));
    return y;
}
int query(int x,int y,int L,int R,int k){
    // cout<<siz(x)<<' '<<siz(y)<<' '<<L<<' '<<R<<' '<<x<<' '<<y<<' '<<k<<endl;
    if(k>siz(y)-siz(x)) return -1;
    if(L==R) return L;
    int mid=L+R>>1;
    if(k<=siz(rc(y))-siz(rc(x))) return query(rc(x),rc(y),mid+1,R,k);
    else return query(lc(x),lc(y),L,mid,k-siz(rc(y))+siz(rc(x)));
}
int root[N];
#undef lc
#undef rc
#undef siz

int main(){
    int n,m,q;
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=m;i++) cin>>e[i].u>>e[i].v>>e[i].w;
    
    int cnt=n;
    sort(e+1,e+m+1);
    for(int i=1;i<=(n<<1);i++) fa[i]=i;
    for(int i=1;i<=m;i++){
        int x=find(e[i].u),y=find(e[i].v);
        // cout<<x<<" --- "<<y<<endl;
        if(x!=y){
            w[++cnt]=e[i].w;
            st[x][0]=st[y][0]=cnt;
            lc[cnt]=x;rc[cnt]=y;
            // cout<<cnt<<'|'<<x<<'|'<<y<<": "<<w[cnt]<<endl;
            merge(cnt,x);merge(cnt,y);
            if(cnt==(1<<n)-1) break ;
        }
    }
    w[0]=inf;
    for(int k=1;k<20;k++){
        for(int i=1;i<=cnt;i++){
            st[i][k]=st[st[i][k-1]][k-1];
        }
    }
    for(int i=1;i<=cnt;i++) if(!dfn[i]&&find(i)==i) dfs(i);
    for(int i=1;i<=cnt;i++){
        if(rdf[i]>n) root[i]=root[i-1];
        else root[i]=insert(root[i-1],1,V,a[rdf[i]]);
    }

    while(q--){
        int x,v,k;
        cin>>x>>v>>k;
        for(int i=19;~i;i--) if(w[st[x][i]]<=v) x=st[x][i];
        // cout<<x<<' '<<v<<' '<<k<<endl;
        cout<<query(root[dfn[x]],root[dfn[x]+siz[x]-1],1,V,k)<<endl;
    }

    return 0;
}