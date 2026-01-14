#include<bits/stdc++.h>

using namespace std;

#define ssiz(x) (signed)x.size()

const int N=2e5+9;

int fi[N],ne[N<<1],to[N<<1],adj,n,m;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

long long ans;
int dfn[N],low[N],dcnt,scnt,tot;
vector<int> stk,w,a[N];
void Tj(int x,int fa){
    tot++;
    dfn[x]=low[x]=++dcnt;
    stk.push_back(x);
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(!dfn[y]){
            Tj(y,x);
            low[x]=min(low[x],low[y]);
            if(low[y]>=dfn[x]){
                scnt++;
                vector<int> tmp;
                while(ssiz(stk)){
                    int p=stk.back();
                    stk.pop_back();
                    tmp.push_back(p);
                    if(p==y) break ;
                }
                tmp.push_back(x);
                w.push_back(ssiz(tmp));
                for(int z:tmp){
                    a[z].push_back(scnt+n);
                    a[scnt+n].push_back(z);
                }
            }
        }else if(y!=fa) low[x]=min(low[x],dfn[y]);
    }
}
int siz[N];
void DFS(int x,int fa){
    siz[x]=x<=n;
    for(int y:a[x]){
        if(y==fa) continue ;
        DFS(y,x);
        ans+=1ll*siz[x]*siz[y]*w[x];
        siz[x]+=siz[y];
    }
    ans+=1ll*siz[x]*(tot-siz[x])*w[x];
}

int main(){
    cin>>n>>m;
    for(int i=1,u,v;i<=m;i++){
        cin>>u>>v;
        AdEg(u,v),AdEg(v,u);
    }
    w=vector<int>(n+1,-1);

    for(int i=1;i<=n;i++){
        if(dfn[i]) continue ;
        tot=0;
        Tj(i,0);
        DFS(i,0);
        stk.clear();
    }
    cout<<ans*2<<endl;

    return 0;
}