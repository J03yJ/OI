#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;
const int inf=1e9+7;

int fi[N],ne[N],to[N],w[N],adj=1;
void AdEg(int x,int y,int z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
}

int lev[N],cur[N],s,t,n,m;
int BFS(){
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
int DFS(int x,int mn){
    if(x==t) return mn;
    int lft=mn;
    for(int i=cur[x];i;i=ne[i]){
        int y=to[i];
        if(!w[i]) continue ;
        if(lev[y]!=lev[x]+1) continue ;
        int tmp=DFS(y,min(lft,w[i]));
        w[i]-=tmp;
        w[i^1]+=tmp;
        lft-=tmp;
        if(!lft) return mn;
    }
    return mn-lft;
}

int suc[N],ind[N];

int main(){
    cin>>n>>m;
    for(int i=1,u,v;i<=m;i++){
        cin>>u>>v;
        AdEg(u,v+n,1);
        AdEg(v+n,u,0);
    }
    s=n+n+1,t=s+1;
    for(int i=1;i<=n;i++){
        AdEg(s,i,1),AdEg(i,s,0);
        AdEg(i+n,t,1),AdEg(t,i+n,0);
    }

    int sum=0;
    while(BFS()) sum+=DFS(s,inf);
    for(int x=1;x<=n;x++){
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(w[i]) continue ;
            if(y<=n||y>=s) continue ;
            suc[x]=y-n;
            ind[suc[x]]++;
            break ;
        }
    }

    for(int i=1;i<=n;i++){
        if(ind[i]) continue ;
        int cur=i;
        while(cur){
            cout<<cur<<' ';
            int tmp=suc[cur];
            suc[cur]=-1;
            cur=tmp;
        }
        cout<<endl;
    }

    cout<<n-sum<<endl;

    return 0;
}