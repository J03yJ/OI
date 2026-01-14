#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

int fi[N],ne[N<<1],to[N<<1],adj;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}
int siz[N],n,g;
void DFS1(int x){
    siz[x]=1;
    bool flag=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(siz[y]) continue ;
        DFS1(y);
        siz[x]+=siz[y];
        if(siz[y]>n/2) flag=0;
    }
    if(flag&&n-siz[x]<=n/2) g=x;
}
int idfn[N],dcnt;
void DFS2(int x,int fa){
    idfn[++dcnt]=x;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa) continue ;
        DFS2(y,x);
    }
}

int main(){
    cin>>n;
    for(int i=1,x,y;i<n;i++){
        cin>>x>>y;
        AdEg(x,y);
        AdEg(y,x);
    }

    DFS1(1);
    DFS2(g,-1);
    if(n%2) for(int i=2;i<=n/2+1;i++) cout<<idfn[i]<<' '<<idfn[i+n/2]<<endl;
    else  for(int i=1;i<=n/2;i++) cout<<idfn[i]<<' '<<idfn[i+n/2]<<endl;

    return 0;
}