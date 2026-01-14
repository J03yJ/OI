#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=3e5+9;
const int lgN=2e1;

int fi[N],ne[N<<1],to[N<<1],adj;
inline void AddEdge(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int pos[N],elr[N],dep[N],ecnt;
inline void DFS(int x,int f){
    elr[++ecnt]=x;
    pos[x]=ecnt;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==f) continue ;
        dep[y]=dep[x]+1;
        DFS(y,x);
        elr[++ecnt]=x;
    }
}
int mn[N][lgN],lg[N];
inline void InitLCA(){
    for(int i=2;i<=ecnt;i++) lg[i]=lg[i>>1]+1;
    for(int i=1;i<=ecnt;i++) mn[i][0]=pos[elr[i]];
    for(int k=1;k<=lg[ecnt];k++){
        for(int i=1;i<=ecnt-(1<<k)+1;i++) mn[i][k]=min(mn[i][k-1],mn[i+(1<<k-1)][k-1]);
    }
}
inline int LCA(int u,int v){
    u=pos[u],v=pos[v];
    if(u>v) swap(u,v);
    int k=lg[v-u+1];
    return elr[min(mn[u][k],mn[v-(1<<k)+1][k])];
}
inline int Dist(int u,int v){return dep[u]+dep[v]-2*dep[LCA(u,v)];}

int siz[N],vis[N];
inline void GetGrv(int x,int f,int tot,int &grv){
    siz[x]=1;
    bool flag=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(vis[y]) continue ;
        if(y==f) continue ;
        GetGrv(y,x,tot,grv);
        siz[x]+=siz[y];
        if(siz[y]>tot/2) flag=0;
    }
    if(tot-siz[x]>tot/2) flag=0;
    if(flag) grv=x;
}
int fa[N];
inline int Build(int x,int tot){
    GetGrv(x,0,tot,x);
    GetGrv(x,0,tot,x);
    vis[x]=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(vis[y]) continue ;
        fa[Build(y,siz[y])]=x;
    }
    return x;
}

struct DelHeap{
    priority_queue<int> p,q;
    inline void Push(int x){p.push(x);}
    inline void Pop(int x){q.push(x);}
    inline int Top(){
        while(q.size()&&p.top()==q.top()) p.pop(),q.pop();
        return p.top();
    }
    inline int Size(){return p.size()-q.size();}
}h[N];

int c[N],n,m;
inline void Insert(int x){
    int cur=x;
    while(cur){
        h[cur].Push(-Dist(x,cur));
        cur=fa[cur];
    }
}
inline void Erase(int x){
    int cur=x;
    while(cur){
        h[cur].Pop(-Dist(x,cur));
        cur=fa[cur];
    }
}
inline int Query(int x){
    int cur=x,ans=n+1;
    while(cur){
        if(h[cur].Size()) ans=min(ans,-h[cur].Top()+Dist(x,cur));
        cur=fa[cur];
    }
    return ans!=n+1?ans:-1;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n;
    for(int i=1,u,v;i<n;i++) cin>>u>>v,AddEdge(u,v),AddEdge(v,u);
    DFS(1,-1),InitLCA();
    Build(1,n);

    cin>>m;
    while(m--){
        int op,x;
        cin>>op>>x;
        if(op==0){
            if(!c[x]) Insert(x);
            else Erase(x);
            c[x]^=1;
        }else cout<<Query(x)<<endl;
    }

    return 0;
}