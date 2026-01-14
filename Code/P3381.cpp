#include<bits/stdc++.h>

using namespace std;

const int M=5e4+9;
const int N=5e3+9;
const int inf=1e9;

int fi[N],ne[M<<1],to[M<<1],w[M<<1],cst[M<<1],adj=1;
void AddEdge(int x,int y,int z,int c){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y,w[adj]=z,cst[adj]=c;
}
void AddFlow(int x,int y,int z,int c){
    AddEdge(x,y,z,c),AddEdge(y,x,0,-c);
}

int dis[N],vis[N],pe[N],h[N],n,m,s,t;
bool Dij(){
    for(int i=1;i<=n;i++) dis[i]=inf,vis[i]=pe[i]=0;
    dis[s]=0;
    priority_queue<pair<int,int>> q;
    q.push({0,s});
    while(q.size()){
        int x=q.top().second;
        q.pop();
        if(vis[x]) continue ;
        vis[x]=1;
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(!w[i]) continue ;
            if(dis[x]+cst[i]+h[x]-h[y]<dis[y]){
                dis[y]=dis[x]+cst[i]+h[x]-h[y],pe[y]=i;
                q.push({-dis[y],y});
            }
        }
    }
    return dis[t]!=inf;
}
bool inq[N];
void SPFA(){
    queue<int> q;
    for(int i=1;i<=n;i++) h[i]=inf;
    inq[s]=1,q.push(s),h[s]=0;
    while(q.size()){
        int x=q.front();
        q.pop();
        inq[x]=1;
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(!w[i]) continue ;
            if(h[x]+cst[i]<h[y]){
                h[y]=h[x]+cst[i];
                if(!inq[y]) q.push(y),inq[y]=1;
            }
        }
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'   

    cin>>n>>m>>s>>t;
    for(int i=1,x,y,z,c;i<=m;i++){
        cin>>x>>y>>z>>c;
        AddFlow(x,y,z,c);
    }

    SPFA();
    int maxf=0,minc=0;
    while(Dij()){
        for(int i=1;i<=n;i++) h[i]+=dis[i]==inf?0:dis[i];
        int flw=inf,prc=0;
        int cur=t;
        while(cur!=s){
            flw=min(flw,w[pe[cur]]);
            prc+=cst[pe[cur]];
            cur=to[pe[cur]^1];
        }
        cur=t;
        while(cur!=s){
            w[pe[cur]]-=flw,w[pe[cur]^1]+=flw;
            cur=to[pe[cur]^1];
        }
        maxf+=flw;
        minc+=prc*flw;
    }

    cout<<maxf<<' '<<minc<<endl;

    return 0;
}