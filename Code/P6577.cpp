#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e3+9;
const int inf=1e12;

vector<int> e[N];
int cst[N][N],w[N][N];
void AddEdge(int x,int y,int z,int c){
    e[x].push_back(y);
    cst[x][y]=c,w[x][y]=z;
}
void AddFlow(int x,int y,int z,int c){
    AddEdge(x,y,z,c),AddEdge(y,x,0,-c);
}

int dis[N],vis[N],pe[N],h[N],n,m,s,t;
int nxt[N],pre[N];
bool Dij(){
    for(int i=1;i<=t;i++) dis[i]=inf,vis[i]=pe[i]=0;
    for(int i=0;i<=t;i++) nxt[i]=i+1,pre[i]=i-1;
    dis[s]=0;
    for(int p=1;p<=t;p++){
        int x=0;
        for(int i=nxt[0];i<=t;i=nxt[i]) if(!x||dis[i]<dis[x]) x=i;
        if(!x) break ;
        vis[x]=1,pre[nxt[x]]=pre[x],nxt[pre[x]]=nxt[x];
        for(int y:e[x]){
            if(!w[x][y]) continue ;
            if(dis[x]+cst[x][y]+h[x]-h[y]<dis[y]){
                dis[y]=dis[x]+cst[x][y]+h[x]-h[y],pe[y]=x;
            }
        }
    }
    return dis[t]!=inf;
}
bitset<N> inq;
int q[N*N],l,r;
void SPFA(){
    for(int i=1;i<=t;i++) h[i]=inf;
    l=1,r=0;
    inq.set(s,1),q[++r]=s,h[s]=0;
    while(l<=r){
        int x=q[l++];
        inq.set(x,1);
        for(int y:e[x]){
            if(!w[x][y]) continue ;
            if(h[x]+cst[x][y]<h[y]){
                h[y]=h[x]+cst[x][y];
                if(!inq[y]) q[++r]=y,inq[y]=1;
            }
        }
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'   

    cin>>n>>m;
    s=n<<1|1,t=s+1;
    for(int i=1;i<=m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        AddFlow(a,b+n,1,-c);
    }

    for(int i=1;i<=n;i++) AddFlow(s,i,1,0);
    for(int i=1;i<=n;i++) AddFlow(i+n,t,1,0);

    SPFA();
    int maxf=0,minc=0;
    while(Dij()){
        for(int i=1;i<=t;i++) h[i]+=dis[i];
        int flw=inf,prc=0;
        int cur=t;
        while(cur!=s){
            flw=min(flw,w[pe[cur]][cur]);
            prc+=cst[pe[cur]][cur];
            cur=pe[cur];
        }
        cur=t;
        while(cur!=s){
            w[pe[cur]][cur]-=flw,w[cur][pe[cur]]+=flw;
            cur=pe[cur];
        }
        maxf+=flw;
        minc+=prc*flw;
    }


    cout<<-minc<<endl;
    for(int i=1+n;i<=n+n;i++){
        for(int j:e[i]){
            if(j==t) continue ;
            if(w[i][j]){
                cout<<j<<' ';
                break ;
            }
        }
    }
    cout<<endl;

    return 0;
}