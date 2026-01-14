#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5+9;
const int mod=1e9+7;
inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) MulAs(res,x);
        MulAs(x,x);
        y>>=1;
    }
    return res;
}
inline int Inv(int x){return QPow(x,mod-2);}

int fi[N],ne[N<<1],to[N<<1],adj;
inline void AddEdge(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int dis[N],dit[N],cnt[N],s,t,n;
inline void DFS(int x,int fa,int *dis){
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa) continue ;
        dis[y]=dis[x]+1;
        DFS(y,x,dis);
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n;
    for(int i=1,u,v;i<=n;i++){
        cin>>u>>v;
        AddEdge(u,v);
        AddEdge(v,u);
    }

    dis[1]=0,DFS(1,0,dis);
    s=max_element(dis+1,dis+n+1)-dis;
    dis[s]=0,DFS(s,0,dis);
    t=max_element(dis+1,dis+n+1)-dis;
    dit[t]=0,DFS(t,0,dit);

    int lo=0,hi=dis[t];
    for(int i=1;i<=n;i++){
        if(i==s||i==t) continue ;
        lo=max(lo,min(dis[i],dit[i]));
        hi=max(hi,max(dis[i],dit[i]));
        cnt[max(dis[i],dit[i])]++;
    }
    
    int ans=0;
    partial_sum(cnt+1,cnt+hi+1,cnt+1);
    for(int i=lo;i<=hi;i++) AddAs(ans,Mul(i,Sub(QPow(2,cnt[i]),i!=lo?QPow(2,cnt[i-1]):0)));
    AddAs(ans,Mul(dis[t],QPow(2,n-2)));
    AddAs(ans,ans);

    cout<<ans<<endl;

    return 0;
}