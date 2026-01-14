#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;

int fa[N],dis[N],n,k,res;
vector<int> son[N];
void DFS(int x){
    int lim=k-1+(x==1);
    dis[x]=0;
    for(int y:son[x]){
        DFS(y);
        if(dis[y]==lim){
            res++;
            continue ;
        }
        dis[x]=max(dis[x],dis[y]+1);
    }
}

int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>fa[i];

    if(fa[1]!=1) res++,fa[1]=1;
    for(int i=2;i<=n;i++) son[fa[i]].push_back(i);
    DFS(1);

    cout<<res<<endl;

    return 0;
}