#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;

int fi[N],to[N],ne[N],adj;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int dfn[N],low[N],ins[N],bel[N],scnt,dcnt,n,m;
vector<int> scc[N],stk;
void Tj(int x){
    dfn[x]=low[x]=++dcnt;
    ins[x]=1,stk.push_back(x);
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(!dfn[y]) Tj(y),low[x]=min(low[x],low[y]);
        else if(ins[y]) low[x]=min(low[x],dfn[y]);
    }
    if(low[x]==dfn[x]){
        scnt++;
        while(stk.size()){
            int p=stk.back();
            stk.pop_back();
            scc[scnt].push_back(p);
            bel[p]=scnt;
            ins[p]=0;
            if(p==x) break ;
        }
    }
}

int main(){
    cin>>n>>m;
    for(int i=1,u,v;i<=m;i++){
        cin>>u>>v;
        AdEg(u,v);
    }
    for(int i=1;i<=n;i++) if(!dfn[i]) Tj(i);

    cout<<scnt<<endl;
    for(int i=1;i<=n;i++){
        if(!scc[bel[i]].size()) continue ;
        sort(scc[bel[i]].begin(),scc[bel[i]].end());
        for(int x:scc[bel[i]]) cout<<x<<' ';cout<<endl;
        scc[bel[i]].clear();
    }

    return 0;
}