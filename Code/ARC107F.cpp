#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=3e2+9;
const int M=N*N;
const int inf=1e9+7;

int fi[N<<1],to[M<<1],ne[M<<1],w[M<<1],adj=1;
inline void AddEdge(int x,int y,int z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
}
inline void AddFlow(int x,int y,int z){AddEdge(x,y,z),AddEdge(y,x,0);}

int lev[N<<1],cur[N<<1],s,t;
inline bool BFS(){
    for(int i=1;i<=t;i++) lev[i]=0,cur[i]=fi[i];
    queue<int> q;
    q.push(s);
    lev[s]=1;
    while(q.size()){
        int x=q.front();
        q.pop();
        if(x==t) return 1;
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(!w[i]) continue ;
            if(lev[y]) continue ;
            lev[y]=lev[x]+1;
            q.push(y);
        }
    }
    return 0;
}
inline int DFS(int x,int rem){
    if(x==t) return rem;
    int k=rem;
    for(int &i=cur[x];i;i=ne[i]){
        int y=to[i];
        if(!w[i]) continue ;
        if(lev[y]!=lev[x]+1) continue ;
        int tmp=DFS(y,min(k,w[i]));
        w[i]-=tmp;
        w[i^1]+=tmp;
        k-=tmp;
        if(!k) return rem;
    }
    return rem-k;
}
inline ll MCMF(){
    ll ans=0;
    while(BFS()) ans+=DFS(s,inf);
    return ans;
}

int a[N],b[N],u[N],v[N],n,m;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    for(int i=1;i<=m;i++) cin>>u[i]>>v[i];

    ll ans=0;
    s=n+n+1,t=s+1;
    for(int i=1;i<=n;i++){
        if(b[i]>=0) AddFlow(s,i,2*b[i]);
        if(b[i]<0) AddFlow(i+n,t,-2*b[i]);
        AddFlow(i,i+n,a[i]+abs(b[i]));
        ans+=abs(b[i]);
    }
    for(int i=1;i<=m;i++) AddFlow(u[i]+n,v[i],inf),AddFlow(v[i]+n,u[i],inf);
    ans-=MCMF();

    cout<<ans<<endl;
 
    return 0;
}