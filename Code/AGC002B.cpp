#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;

int res[N],vis[N],n,m;

int main(){
    cin>>n>>m;

    vis[1]=1;
    for(int i=1;i<=n;i++) res[i]=1;
    while(m--){
        int x,y;
        cin>>x>>y;
        res[x]--;
        res[y]++;
        vis[y]|=vis[x];
        if(!res[x]) vis[x]=0;
    }

    int cnt=0;
    for(int i=1;i<=n;i++) cnt+=vis[i];
    cout<<cnt<<endl;

    return 0;
}