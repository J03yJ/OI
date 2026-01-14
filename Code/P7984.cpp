#include<bits/stdc++.h>

using namespace std;

#define fir(x) x.first
#define sec(x) x.second
using ll=long long;
using pli=pair<ll,int>;
const int N=1e6+9;
const int M=7e6+9;

int fi[N],ne[M],to[M],w[M],adj;
inline void AddEdge(int x,int y,int z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
}
int lc[N],rc[N],tot,n,k,root;
inline void Build(int &x,int l,int r){
    if(l==r) return x=l,void();
    if(!x) x=++tot;
    int mid=l+r>>1;
    Build(lc[x],l,mid),Build(rc[x],mid+1,r);
    AddEdge(lc[x],x,0),AddEdge(rc[x],x,0);
}
inline void Link(int x,int l,int r,int ql,int qr,int u,int w){
    if(ql<=l&&r<=qr) return AddEdge(x,u,w);
    int mid=l+r>>1;
    if(ql<=mid) Link(lc[x],l,mid,ql,qr,u,w);
    if(qr>mid) Link(rc[x],mid+1,r,ql,qr,u,w);
}

const ll inf=0x3f3f3f3f3f3f3f3f;
ll f[N][4];
int vis[N];
inline void Dijkstra(int sta){
    priority_queue<pli> q;
    for(int i=1;i<=tot;i++){
        if(f[i][sta]!=inf) q.push({-f[i][sta],i});
        vis[i]=0;
    }
    while(q.size()){
        int x=sec(q.top());
        q.pop();
        if(vis[x]) continue ;
        vis[x]=1;
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(f[x][sta]+w[i]<f[y][sta]){
                f[y][sta]=f[x][sta]+w[i];
                q.push({-f[y][sta],y});
            }
        }
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>k;
    tot=n,Build(root,1,n);
    for(int i=1,u,w,l,r;i<=k;i++){
        cin>>u>>w>>l>>r;
        AddEdge(++tot,u,w);
        Link(root,1,n,l,r,tot,0);
    }

    memset(f,0x3f,sizeof f);
    // for(int i=1;i<=tot;i++) f[i][0]=0;
    f[1][1]=f[n][2]=0;
    for(int sta=1;sta<4;sta++){
        for(int tta=sta;tta;tta=tta-1&sta){
            for(int i=1;i<=tot;i++) f[i][sta]=min(f[i][sta],f[i][tta]+f[i][sta^tta]);
        }
        Dijkstra(sta);
    }

    for(int i=1;i<=n;i++){
        if(f[i][3]==inf) cout<<-1<<endl;
        else cout<<f[i][3]<<endl;
    }

    return 0;
}