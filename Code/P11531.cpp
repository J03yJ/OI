#include<bits/stdc++.h>

using namespace std;

const int N=4e5+9;
const int inf=1e9;

int fi[N<<2],to[N<<3],ne[N<<3],w[N<<3],adj=1;
void AdEg(int x,int y,int z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
}
#define AddFlow(x,y,z) AdEg(x,y,z),AdEg(y,x,0)
int pos[N],n,m,c;

int lev[N],cur[N],s,t;
bool BFS(){
    for(int i=1;i<=n+c+c;i++) lev[i]=0,cur[i]=fi[i];
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
int DFS(int x,int mn){
    if(x==t) return mn;
    int k=mn;
    for(int &i=cur[x];i;i=ne[i]){
        int y=to[i];
        if(!w[i]) continue ;
        if(lev[y]!=lev[x]+1) continue ;
        int tmp=DFS(y,min(w[i],k));
        k-=tmp,w[i]-=tmp,w[i^1]+=tmp;
        if(!k) return mn;
    }
    return mn-k;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>m>>c;
    for(int i=1;i<=c;i++) cin>>pos[i];
    for(int i=1,u,v,r;i<=m;i++){
        cin>>u>>v>>r;
        AddFlow(u,n+r,inf);
        AddFlow(n+c+r,v,inf);
    }
    for(int i=1;i<=c;i++) AddFlow(n+i,n+c+i,1);
    s=1,t=n;

    int sum=0;
    while(BFS()) sum+=DFS(s,inf);
    cout<<sum<<endl;

    return 0;
}