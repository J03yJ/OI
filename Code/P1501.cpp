#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=1e5+9;
const int mod=51061;

struct Node{
    int fa,son[2],siz,rev;
    int val,sum,mtag=1,atag;
}tr[N];
#define fa(x) tr[x].fa
#define son(x,k) tr[x].son[k]
#define siz(x) tr[x].siz
#define rev(x) tr[x].rev
#define val(x) tr[x].val
#define sum(x) tr[x].sum
#define mtag(x) tr[x].mtag
#define atag(x) tr[x].atag

#define IsRoot(x) (son(fa(x),0)!=(x)&&son(fa(x),1)!=(x))
inline void Push(int x,int a,int m,int r){
    if(!x) return ;
    val(x)=(1ll*val(x)*m%mod+a)%mod;
    sum(x)=(1ll*sum(x)*m%mod+1ll*a*siz(x)%mod)%mod;
    atag(x)=(1ll*atag(x)*m%mod+a)%mod;
    mtag(x)=1ll*mtag(x)*m%mod;
    if(r) rev(x)^=1,swap(son(x,0),son(x,1));
}
inline void PushDown(int x){
    Push(son(x,0),atag(x),mtag(x),rev(x));
    Push(son(x,1),atag(x),mtag(x),rev(x));
    atag(x)=0,mtag(x)=1,rev(x)=0;
}
inline void PushUp(int x){
    siz(x)=siz(son(x,0))+siz(son(x,1))+1;
    sum(x)=(sum(son(x,0))+sum(son(x,1))+val(x))%mod;
}
inline void Update(int x){
    if(!IsRoot(x)) Update(fa(x));
    PushDown(x);
}

#define Id(x) ((x)==son(fa(x),1))
inline void Rotate(int x){
    int y=fa(x),z=fa(y),f=Id(x);
    if(!IsRoot(y)) son(z,Id(y))=x;
    son(y,f)=son(x,!f),fa(son(x,!f))=y,PushUp(y);
    son(x,!f)=y,fa(y)=x,PushUp(x);
    fa(x)=z;
}
inline void Splay(int x){
    Update(x);
    for(int y=fa(x);!IsRoot(x);Rotate(x),y=fa(x)){
        if(!IsRoot(y)) Rotate(Id(x)==Id(y)?y:x);
    }
}

int n,m;
inline int Access(int x){
    int p=0;
    for(;x;p=x,x=fa(x)) Splay(x),son(x,1)=p,PushUp(x);
    return p;
}
inline void MakeRoot(int x){Push(Access(x),0,1,1);}
inline int FindRoot(int x){
    Access(x),Splay(x),PushDown(x);
    while(son(x,0)) PushDown(x=son(x,0));
    return Splay(x),x;
}
inline void Split(int x,int y){MakeRoot(x),Access(y),Splay(y);}
inline void Cut(int x,int y){Split(x,y),fa(x)=son(y,0)=0,PushUp(y);}
inline void Link(int x,int y){MakeRoot(x),Splay(x),fa(x)=y;}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++) val(i)=sum(i)=1,siz(i)=1;
    for(int i=1,u,v;i<n;i++) cin>>u>>v,Link(u,v);

    while(m--){
        char op;
        cin>>op;
        if(op=='+'){
            int u,v,c;
            cin>>u>>v>>c;
            Split(u,v);
            Push(v,c,1,0);
        }else if(op=='-'){
            int u1,v1,u2,v2;
            cin>>u1>>v1>>u2>>v2;
            Cut(u1,v1);
            Link(u2,v2);
        }else if(op=='*'){
            int u,v,c;
            cin>>u>>v>>c;
            Split(u,v);
            Push(v,0,c,0);
        }else if(op=='/'){
            int u,v;
            cin>>u>>v;
            Split(u,v);
            cout<<sum(v)<<endl;
        }
    }

    return 0;
}