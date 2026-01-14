#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
#define double long double
const int N=6e2+9;
const double eps=1e-12;

int n,s,t;
double sx[N],sy[N],tx[N],ty[N];
double Dist(double x0,double y0,double x1,double y1){
    return sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0));
}

int fi[N],ne[N*N<<1],to[N*N<<1],w[N*N<<1],in[N],out[N],adj=1;
inline void AddEdge(int x,int y,int z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
}
inline void AddFlow(int x,int y,int z){AddEdge(x,y,z);AddEdge(y,x,0);}
inline void Clear(int lim){
    for(int i=1;i<=lim;i++) in[i]=out[i]=fi[i]=0;
    for(int i=1;i<=adj;i++) ne[i]=to[i]=w[i]=0;
    adj=1;
}

int lvl[N],cur[N];
inline bool BFS(int s,int t,int lim){
    for(int i=1;i<=lim;i++) lvl[i]=0,cur[i]=fi[i];
    queue<int> q;
    q.push(s),lvl[s]=1;
    while(q.size()){
        int x=q.front();
        q.pop();
        if(x==t) return 1;
        for(int i=fi[x];i;i=ne[i]){
            if(!w[i]) continue ;
            int y=to[i];
            if(lvl[y]) continue ;
            lvl[y]=lvl[x]+1;
            q.push(y);
        }
    }
    return 0;
}
inline int DFS(int x,int t,int r){
    if(x==t) return r;
    int k=r;
    for(int &i=cur[x];i;i=ne[i]){
        if(!w[i]) continue ;
        int y=to[i];
        if(lvl[y]!=lvl[x]+1) continue ;
        int tmp=DFS(y,t,min(k,w[i]));
        k-=tmp,w[i]-=tmp,w[i^1]+=tmp;
        if(!k) return r;
    }
    return r-k;
}
inline int MaxFlow(int s,int t,int lim){
    int sum=0;
    while(BFS(s,t,lim)) sum+=DFS(s,t,n);
    return sum;
}

inline bool Check(double k){
    s=n+n+1,t=s+1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(Dist(sx[i],sy[i],tx[j],ty[j])<=k) AddFlow(i,j+n,1);
        }
        AddFlow(s,i,1);
        AddFlow(i+n,t,1);
    }
    int res=MaxFlow(s,t,t);
    Clear(t);
    return res==n;
}
double E(double x,double y){
    return (y-x)/x;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>sx[i]>>sy[i];
    for(int i=1;i<=n;i++) cin>>tx[i]>>ty[i];

    double l=0,r=2e19;
    while(E(l,r)>eps){
        double mid=(l+r)/2;
        // cout<<fixed<<setprecision(8)<<l<<' '<<r<<' '<<mid<<endl;
        if(Check(mid)) r=mid;
        else l=mid;
    }

    cout<<fixed<<setprecision(8)<<r<<endl;

    return 0;
}