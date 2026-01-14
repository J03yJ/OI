#include<bits/stdc++.h>

using namespace std;

const int N=5e5+9;

int fi[N],ne[N<<1],to[N<<1],adj;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int vis[N],siz[N],dep[N],son[N],n,G;
void DFS(int x){
    int flag=1;
    siz[x]=vis[x]=1;
    son[x]=0;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(vis[y]) continue ;
        dep[y]=dep[x]+1;
        son[x]++;
        DFS(y);
        siz[x]+=siz[y];
        if(siz[y]>n/2) flag=0;
    }
    if(n-siz[x]>n/2) flag=0;
    if(flag) G=x;
    vis[x]=0;
}
#define M(x) ((x)%2?(x)+1:(x)-1)
vector<int> v[N];
void Get(int x,vector<int> &v){
    vis[x]=1;
    // if(!vis[M(x)]) Get(M(x),v);
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(vis[y]) continue ;
        // if(y==M(x)) continue ;
        Get(y,v);
    }
    v.push_back(x);
    vis[x]=0;
}

int main(){
    cin>>n;
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        AdEg(u,v);
        AdEg(v,u);
    }

    dep[1]=0;DFS(1);
    dep[G]=0;DFS(G);
    
    vis[G]=1;
    for(int i=fi[G];i;i=ne[i]){
        int x=to[i];
        Get(x,v[x]);
        reverse(v[x].begin(),v[x].end());
    }
    
    int cur=M(G);
    priority_queue<pair<int,int>> q;
    for(int i=fi[G];i;i=ne[i]){
        int x=to[i];
        if(x==cur) continue ;
        q.push({v[x].size(),x});
    }
    while(q.size()){
        int x=q.top().second;
        q.pop();
        cout<<v[cur].back()<<' '<<v[x].back()<<endl;
        v[cur].pop_back(),v[x].pop_back();
        if(v[cur].size()) q.push({v[cur].size(),cur});
        cur=x;
    }
    cout<<G<<' '<<cur<<endl;

    return 0;
}