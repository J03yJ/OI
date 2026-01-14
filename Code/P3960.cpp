#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;

struct Node{
    int fa,son[2],dat,val;
    bool rev;
}tr[N];
#define fa(x) tr[x].fa
#define son(x,k) tr[x].son[k]
#define rev(x) tr[x].rev
#define dat(x) tr[x].dat
#define val(x) tr[x].val

int n,m;

#define IsRoot(x) (x!=son(fa(x),1)&&x!=son(fa(x),0))
inline void Push(int x){if(x) rev(x)^=1,swap(son(x,0),son(x,1));}
inline void PushDown(int x){if(rev(x)) Push(son(x,0)),Push(son(x,1)),rev(x)=0;}
inline void PushUp(int x){dat(x)=dat(son(x,0))^dat(son(x,1))^val(x);}
inline void Update(int x){
    if(!IsRoot(x)) Update(fa(x));
    PushDown(x);
}

#define Id(x) (x==son(fa(x),1))
inline void Rotate(int x){
    int y=fa(x),z=fa(y);
    if(!IsRoot(y)) son(z,Id(y))=x;
    if(!Id(x)){
        son(y,0)=son(x,1),fa(son(x,1))=y;
        son(x,1)=y,fa(y)=x;
    }else{
        son(y,1)=son(x,0),fa(son(x,0))=y;
        son(x,0)=y,fa(y)=x;            
    }
    PushUp(y),PushUp(x);
    fa(x)=z;
}
inline void Splay(int x){
    Update(x);
    for(int y=fa(x);!IsRoot(x);Rotate(x),y=fa(x)){
        if(!IsRoot(y)) Rotate(Id(x)==Id(y)?y:x);
    }
}

inline int Access(int x){
    int p=0;
    for(;x;p=x,x=fa(x)) Splay(x),son(x,1)=p,PushUp(x);
    return p;
}
inline void MakeRoot(int x){Push(Access(x));}
inline int FindRoot(int x){
    Access(x),Splay(x),PushDown(x);
    while(son(x,0)) PushDown(x=son(x,0));
    Splay(x);
    return x;
}

inline void Split(int x,int y){
    MakeRoot(x);
    Access(y);
    Splay(y);
}
inline bool Cut(int x,int y){
    Split(x,y);
    if(fa(x)==y&&!son(x,1)){
        fa(x)=son(y,0)=0;
        PushUp(y);
        return 1;
    }
    return 0;
}
inline void Link(int x,int y){
    MakeRoot(x),Splay(x);
    if(FindRoot(y)!=x) fa(x)=y;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>val(i),dat(i)=val(i);

    while(m--){
        int op,x,y;
        cin>>op>>x>>y;
        if(op==0){
            Split(x,y);
            cout<<dat(y)<<endl;
        }else if(op==1) Link(x,y);
        else if(op==2) Cut(x,y);
        else{
            Splay(x);
            val(x)=y;
            PushUp(x);
        }
    }

    return 0;
}