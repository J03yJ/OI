#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e5+9;

int fi[N],ne[N<<1],to[N<<1],w[N<<1],adj;
void AdEg(int x,int y,int z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
}
int del[N][2],vis[N][2],n,m,err;
void DFS(int x,int k){
    vis[x][k]=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(vis[y][k^1]){
            if(del[y][k^1]+del[x][k]!=w[i]) err=1;
            continue ;
        }
        del[y][k^1]=w[i]-del[x][k];
        DFS(y,k^1);
    }
}

signed main(){
    cin>>n>>m;
    for(int i=1,u,v,w;i<=m;i++){
        cin>>u>>v>>w;
        AdEg(u,v,w);
        AdEg(v,u,w);
    }

    DFS(1,0);
    if(err){
        cout<<0<<endl;
        return 0;
    }
    
    int mx=-1e18,mn=1e18;
    for(int i=1;i<=n;i++){
        if(vis[i][0]) mn=min(mn,del[i][0]);
        if(vis[i][1]) mx=max(mx,-del[i][1]);
        
    }
    cout<<max(mn-mx-1,0ll)<<endl;

    return 0;
}