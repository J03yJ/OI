#include<bits/stdc++.h>

using namespace std;

#define ssiz(x) (signed)x.size()

const int N=2e6+9;

int fi[N],ne[N<<1],to[N<<1],adj,n,m;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int low[N],dfn[N],dcnt;
vector<int> stk;
vector<vector<int>> ans;
void Tj(int x,int fa){
    dfn[x]=low[x]=++dcnt;
    stk.push_back(x);
    int flag=0;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(!dfn[y]){
            flag=1;
            Tj(y,x);
            low[x]=min(low[x],low[y]);
            if(low[y]>=dfn[x]){
                ans.push_back(vector<int>());
                while(ssiz(stk)){
                    int p=stk.back();
                    stk.pop_back();
                    ans.back().push_back(p);
                    if(p==y) break ;
                }
                ans.back().push_back(x);
            }
        }else if(y!=fa) low[x]=min(low[x],dfn[y]);
    }
    if(!fa&&!flag) ans.push_back(vector<int>(1,x));
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    cin>>n>>m;
    for(int i=1,u,v;i<=m;i++){
        cin>>u>>v;
        AdEg(u,v),AdEg(v,u);
    }
    for(int i=1;i<=n;i++){
        if(dfn[i]) continue ;
        // stk.clear();
        Tj(i,0);
    }

    cout<<ans.size()<<endl;
    for(auto &v:ans){
        cout<<v.size()<<' ';
        for(int x:v) cout<<x<<' ';cout<<endl;
    }

    return 0;
}