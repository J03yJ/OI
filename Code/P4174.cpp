#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e5+9;
const int inf=1e18+9ll;

int fi[N<<1],ne[N<<3],to[N<<3],w[N<<3],adj=1;
void AddEdge(int x,int y,int z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
}
void AddFlow(int x,int y,int z){AddEdge(x,y,z),AddEdge(y,x,0);}

int lev[N],cur[N],s,t;
bool BFS(){
    for(int i=1;i<=t;i++) lev[i]=0,cur[i]=fi[i];
    queue<int> q;
    lev[s]=1,q.push(s);
    while(q.size()){
        int x=q.front();q.pop();
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
int DFS(int x,int p){
    if(x==t) return p;
    int k=p;
    for(int &i=cur[x];i;i=ne[i]){
        int y=to[i];
        if(!w[i]) continue ;
        if(lev[y]!=lev[x]+1) continue ;
        int tmp=DFS(y,min(k,w[i]));
        k-=tmp,w[i]-=tmp,w[i^1]+=tmp;
        if(!k) return p;
    }
    return p-k;
}

int n,m;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>m;
    s=n+m+1,t=s+1;
    for(int i=1,x;i<=n;i++){
        cin>>x;
        AddFlow(m+i,t,x);
    }
    int sum=0;
    for(int i=1,x,y,z;i<=m;i++){
        cin>>x>>y>>z;
        sum+=z;
        AddFlow(s,i,z);
        AddFlow(i,m+x,inf);
        AddFlow(i,m+y,inf);
    }

    while(BFS()) sum-=DFS(s,inf);
    cout<<sum<<endl;

    return 0;
}