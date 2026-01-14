#include<bits/stdc++.h>

using namespace std;

const int N=5e5+9;
const int inf=INT_MAX;

struct Node{
    int lc,rc,val,siz;
}tr[N<<5];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define val(x) tr[x].val
#define siz(x) tr[x].siz

int trs[N<<5],top,cnt;
inline int Allc(){return top?trs[top--]:++cnt;}
inline int Allc(int l,int r,int s,int k){
    int x=Allc();
    siz(x)=s,val(x)=k,lc(x)=l,rc(x)=r;
    return x;
}
inline int Allc(int k){return Allc(0,0,1,k);}
inline int Bind(int x,int y){return x&&y?Allc(x,y,siz(x)+siz(y),val(y)):x|y;}
inline void Destroy(int x){memset(&tr[x],0,sizeof tr[x]),trs[++top]=x;}
inline void Copy(int x,int y){memcpy(&tr[y],&tr[x],sizeof tr[x]);}
inline int Clone(int x){int y=Allc();return Copy(x,y),y;}
inline void Comp(int &x,int y){if(y) x=y;}

inline void PushUp(int x){
    if(!lc(x)) siz(x)=1;
    else siz(x)=siz(lc(x))+siz(rc(x)),val(x)=val(rc(x));
}
inline int Rotate(int x,int flag){
    if(!flag) return Bind(lc(lc(x)),Bind(rc(lc(x)),rc(x)));
    else return Bind(Bind(lc(x),lc(rc(x))),rc(rc(x)));
}
inline int Maintain(int x){
    PushUp(x);
    if(siz(lc(x))>siz(rc(x))*3){
        if(siz(lc(rc(x)))>siz(lc(lc(x)))*2) lc(x)=Rotate(lc(x),1);
        return Rotate(x,0);
    }else if(siz(rc(x))>siz(lc(x))*3){
        if(siz(rc(lc(x)))>siz(rc(rc(x)))*2) rc(x)=Rotate(rc(x),0);
        return Rotate(x,1);
    }else return x;
}

inline int Insert(int x,int k){
    if(!lc(x)) return Bind(Allc(min(val(x),k)),Allc(max(val(x),k)));
    x=Clone(x);
    if(k<=val(lc(x))) lc(x)=Insert(lc(x),k);
    else rc(x)=Insert(rc(x),k);
    return Maintain(x);
}
inline int Erase(int x,int k,int fa=0){
    if(!lc(x)){
        if(val(lc(fa))==k) Copy(rc(fa),fa);
        else if(val(rc(fa))==k) Copy(lc(fa),fa);
        return 0;
    }
    x=Clone(x);
    if(k<=val(lc(x))) Comp(lc(x),Erase(lc(x),k,x));
    else Comp(rc(x),Erase(rc(x),k,x));
    return Maintain(x);
}
inline int Rank(int x,int k){
    if(siz(x)==1) return 1;
    if(k<=val(lc(x))) return Rank(lc(x),k);
    else return Rank(rc(x),k)+siz(lc(x));
}
inline int Kth(int x,int k){
    if(siz(x)==k) return val(x);
    if(k<=siz(lc(x))) return Kth(lc(x),k);
    else return Kth(rc(x),k-siz(lc(x)));
}
inline int Prev(int x,int k){return Kth(x,Rank(x,k)-1);}
inline int Next(int x,int k){return Kth(x,Rank(x,k+1));}

int root[N];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'
    
    int m;
    cin>>m;
    root[0]=Bind(Allc(-inf),Allc(inf));
    for(int p=1,v,op,x;p<=m;p++){
        cin>>v>>op>>x;
        root[p]=root[v];
        if(op==1) root[p]=Insert(root[p],x);
        else if(op==2) root[p]=Erase(root[p],x);
        else if(op==3) cout<<Rank(root[p],x)-1<<endl;
        else if(op==4) cout<<Kth(root[p],x+1)<<endl;
        else if(op==5) cout<<Prev(root[p],x)<<endl;
        else cout<<Next(root[p],x)<<endl;
    }

    return 0;
}