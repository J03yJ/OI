#include<bits/stdc++.h>

using namespace std;

#define fir(x) x.first
#define sec(x) x.second
using ll=long long;
using pii=pair<int,int>;
using pli=pair<ll,int>;
using pll=pair<ll,ll>;
const int N=1e3+9;
const ll inf=1e9;

int fi[N<<1],to[N<<3],ne[N<<3],w[N<<3],cst[N<<3],adj=1;
inline void AddEdge(int x,int y,int z,int c){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
    cst[adj]=c;
}
inline void AddFlow(int x,int y,int z,int c){
    AddEdge(x,y,z,c),AddEdge(y,x,0,-c);
}

ll h[N<<1];
int inq[N<<1],s,t;
inline void SPFA(){
    queue<int> q;
    for(int i=1;i<=t;i++) h[i]=inf;
    h[s]=0,q.push(s);
    while(q.size()){
        int x=q.front();
        q.pop();
        inq[x]=0;
        for(int i=fi[x];i;i=ne[i]){
            if(!w[i]) continue ;
            int y=to[i];
            if(h[x]+cst[i]<h[y]){
                h[y]=h[x]+cst[i];
                if(!inq[y]) q.push(y),inq[y]=1;
            }
        }
    }
}
ll dis[N<<1];
int prv[N<<1],vis[N<<1];
inline bool Dijkstra(){
    for(int i=1;i<=t;i++) dis[i]=inf,vis[i]=prv[i]=0;
    priority_queue<pli> q;
    q.push({dis[s]=0,s});
    while(q.size()){
        int x=sec(q.top());
        q.pop();
        if(vis[x]) continue ;
        vis[x]=1;
        for(int i=fi[x];i;i=ne[i]){
            if(!w[i]) continue ;
            int y=to[i];
            if(dis[x]+cst[i]+h[x]-h[y]<dis[y]){
                dis[y]=dis[x]+cst[i]+h[x]-h[y];
                prv[y]=i^1;
                q.push({-dis[y],y});
            }
        }
    }
    return dis[t]!=inf;
}
inline pll MCMF(){
    ll minc=0,maxf=0;
    SPFA();
    while(Dijkstra()){
        for(int i=1;i<=t;i++) h[i]+=dis[i];
        ll f=inf,c=0,cur=t;
        while(cur!=s){
            f=min(f,(ll)w[prv[cur]^1]);
            c+=cst[prv[cur]^1];
            cur=to[prv[cur]];
        }
        cur=t;
        while(cur!=s){
            w[prv[cur]^1]-=f;
            w[prv[cur]]+=f;
            cur=to[prv[cur]];
        }
        maxf+=f;
        minc+=c*f;
    }
    return {maxf,minc};
}

int xl[N],xr[N],yl[N],yr[N],n,k;
ll len[N];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>xl[i]>>yl[i]>>xr[i]>>yr[i];
        if(xl[i]>xr[i]) swap(xl[i],xr[i]),swap(yl[i],yr[i]);
        len[i]=sqrt(1ll*(xr[i]-xl[i])*(xr[i]-xl[i])+1ll*(yr[i]-yl[i])*(yr[i]-yl[i]));
    }

    vector<int> val({-1});
    for(int i=1;i<=n;i++) val.push_back(xl[i]),val.push_back(xr[i]);
    sort(val.begin(),val.end());
    val.erase(unique(val.begin(),val.end()),val.end());
    for(int i=1;i<=n;i++){
        xl[i]=lower_bound(val.begin(),val.end(),xl[i])-val.begin();
        xr[i]=lower_bound(val.begin(),val.end(),xr[i])-val.begin();
        xl[i]=xl[i]<<1|1;
        xr[i]=xr[i]<<1;
        if(xl[i]>xr[i]) swap(xl[i],xr[i]);
    }
    int tot=val.size()-1<<1;

    s=tot+1,t=s+1;
    for(int i=1;i<tot;i++) AddFlow(i,i+1,inf,0);
    AddFlow(s,1,k,0),AddFlow(tot,t,inf,0);
    for(int i=1;i<=n;i++) AddFlow(xl[i],xr[i],1,-len[i]);

    cout<<-sec(MCMF())<<endl;

    return 0;
}