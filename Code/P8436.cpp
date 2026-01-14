#include<bits/stdc++.h>

using namespace std;

#define ssiz(x) (signed)x.size()

const int N=2e6+9;

int fi[N],ne[N<<1],to[N<<1],adj=1,n,m;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int dfn[N],low[N],dcnt;
vector<int> stk;
vector<vector<int>> ans;
void Tj(int x,int in){
    dfn[x]=low[x]=++dcnt;
    stk.push_back(x);
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(!dfn[y]) Tj(y,i),low[x]=min(low[x],low[y]);
        else if(i!=(in^1)) low[x]=min(low[x],dfn[y]);
    }
    if(low[x]==dfn[x]){
        ans.push_back(vector<int>());
        while(ssiz(stk)){
            int p=stk.back();
            stk.pop_back();
            ans.back().push_back(p);
            if(p==x) break ;
        }
    }
}

int main(){
    cin>>n>>m;
    for(int i=1,u,v;i<=m;i++){
        cin>>u>>v;
        AdEg(u,v),AdEg(v,u);
    }

    for(int i=1;i<=n;i++){
        if(dfn[i]) continue ;
        stk.clear();
        Tj(i,-1);
    }

    cout<<ssiz(ans)<<endl;
    for(auto &v:ans){
        cout<<ssiz(v)<<' ';
        for(int x:v) cout<<x<<' ';cout<<endl;
    }

    return 0;
}