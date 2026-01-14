#include<bits/stdc++.h>

using namespace std;

const int N=5e5+9;
const int lgV=2e1;

struct Node{
    int son[2],dat,siz;
}tr[N<<2];
#define son(x,k) tr[x].son[k]
#define dat(x) tr[x].dat
#define siz(x) tr[x].siz
int trs[N],top,cnt;
inline int Allc(){return top?trs[top--]:cnt;}
inline void PushUp(int x){
    siz(x)=siz(son(x,0))+siz(son(x,1));
    dat(x)=(dat(son(x,0))^dat(son(x,1)))<<1|siz(x)&1;
}
inline void Insert(int &x,int k,int dep){
    if(!x) x=Allc();
    if(dep>=lgV) return siz(x)^=1,dat(x)^=1,void();
    Insert(son(x,k&1),k>>1,dep+1);
    PushUp(x);
}
inline void Shift(int x){
    if(!x) return ;
    Shift(son(x,1));
    swap(son(x,0),son(x,1));
    PushUp(x);
}

int fi[N],ne[N<<1],to[N<<1],adj;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}
int a[N],fa[N],tag[N],rt[N],n,m;
void DFS(int x){
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[i]) continue ;
        fa[y]=x;
        DFS(y);
    }
}

int main(){
    cin>>n>>m;
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        AdEg(u,v),AdEg(v,u);
    }
    for(int i=1;i<=n;i++) cin>>a[i];
    DFS(1);

    for(int i=1;i<=n;i++){
        for(int j=fi[i];j;j=ne[j]){
            int k=to[j];
            if(k==fa[i]) continue ;
            Insert(rt[i],a[k],0);
        }
    }

    while(m--){
        
    }

    return 0;
}