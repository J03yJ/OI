#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=3e5+9;
const int lgN=2e1;
const int inf=1e9;

int fi[N],ne[N<<1],to[N<<1],w[N<<1],adj;
inline void AddEdge(int x,int y,int z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
}

int elr[N<<1],pos[N],dep[N],ecnt;
inline void DFS(int x,int f){
    elr[++ecnt]=x;
    pos[x]=ecnt;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==f) continue ;
        dep[y]=dep[x]+w[i];
        DFS(y,x);
        elr[++ecnt]=x;
    }
}
int mn[lgN][N<<1],lg[N<<1];
inline void InitLCA(){
    for(int i=2;i<=ecnt;i++) lg[i]=lg[i>>1]+1;
    for(int i=1;i<=ecnt;i++) mn[0][i]=pos[elr[i]];
    for(int k=1;k<=lg[ecnt];k++){
        for(int i=1;i<=ecnt-(1<<k)+1;i++) mn[k][i]=min(mn[k-1][i],mn[k-1][i+(1<<k-1)]);
    }
}
inline int LCA(int x,int y){
    x=pos[x],y=pos[y];
    if(x>y) swap(x,y);
    int k=lg[y-x+1];
    return elr[min(mn[k][x],mn[k][y-(1<<k)+1])];
}
inline int Dist(int x,int y){return dep[x]+dep[y]-2*dep[LCA(x,y)];}

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
        return p.size()?p.top():-inf;
    }
    inline int Size(){return p.size()-q.size();}
    inline int Calc(){
        if(Size()<2) return -inf;
        int mx1=Top();
        Pop(mx1);
        int mx2=Top();
        Push(mx1);
        return mx1+mx2;
    }
}h[N],son[N],ans;

int c[N],n,m;
inline void Insert(int x){
    int cur=x,a=-inf,b=0;
    ans.Push(0);
    while(cur){        
        if(a!=b){
            if(h[cur].Size()>=2) ans.Pop(h[cur].Calc());
            if(a!=-inf) h[cur].Pop(a);
            if(b!=-inf) h[cur].Push(b);
            if(h[cur].Size()>=2) ans.Push(h[cur].Calc());
        }
        if(fa[cur]){
            a=son[cur].Top();
            int tmp=Dist(x,fa[cur]);
            son[cur].Push(tmp);
            b=max(a,tmp);
        }
        cur=fa[cur];
    }
}
inline void Erase(int x){
    int cur=x,a=0,b=-inf;
    ans.Pop(0);
    while(cur){
        if(a!=b){
            if(h[cur].Size()>=2) ans.Pop(h[cur].Calc());
            if(a!=-inf) h[cur].Pop(a);
            if(b!=-inf) h[cur].Push(b);
            if(h[cur].Size()>=2) ans.Push(h[cur].Calc());
        }
        if(fa[cur]){
            int tmp=Dist(x,fa[cur]);
            son[cur].Pop(tmp);
            b=son[cur].Top();
            a=max(b,tmp);
        }
        cur=fa[cur];
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n;
    for(int i=1,u,v,w;i<n;i++){
        cin>>u>>v>>w;
        AddEdge(u,v,w);
        AddEdge(v,u,w);
    }

    DFS(1,0);
    InitLCA();
    Build(1,n);
    for(int i=1;i<=n;i++) Insert(i),c[i]^=1;

    int m;
    cin>>m;
    while(m--){
        char op;
        cin>>op;
        if(op=='A'){
            if(ans.Top()==-inf) cout<<"They have disappeared."<<endl;
            else cout<<ans.Top()<<endl;
        }else{
            int x;
            cin>>x;
            if(!c[x]) Insert(x);
            else Erase(x);
            c[x]^=1;
        }
    }

    return 0;
}