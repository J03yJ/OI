#include<bits/stdc++.h>

using namespace std;

const int N=5e5+9;
const int inf=INT_MAX;

struct Node{
    int lc,rc,dep,siz;
    int dat;
}tr[N<<5];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define dep(x) tr[x].dep
#define siz(x) tr[x].siz
#define dat(x) tr[x].dat

int cnt;
inline int New(int val){
    int x=++cnt;
    dat(x)=val;
    siz(x)=dep(x)=1;
    return x;
}
inline int Clone(int x){
    int y=++cnt;
    tr[y]=tr[x];
    return y;
}
inline void PushUp(int x){
    if(!lc(x)) dep(x)=siz(x)=1;
    else{
        dep(x)=max(dep(lc(x)),dep(rc(x)))+1;
        siz(x)=siz(lc(x))+siz(rc(x));
        dat(x)=dat(rc(x));
    }
}
inline int Bind(int x,int y){
    if(!x||!y) return x|y;
    int z=++cnt;
    lc(z)=x,rc(z)=y;
    PushUp(z);
    return z;
}
int Rotate(int x,int flag){
    if(!flag) return Bind(lc(lc(x)),Bind(rc(lc(x)),rc(x)));
    else return Bind(Bind(lc(x),lc(rc(x))),rc(rc(x)));
}
int Maintain(int x){
    if(dep(lc(x))>dep(rc(x))+1){
        if(dep(lc(lc(x)))==dep(rc(x))) x=Bind(Rotate(lc(x),1),rc(x));
        return Rotate(x,0);
    }else if(dep(rc(x))>dep(lc(x))+1){
        if(dep(rc(rc(x)))==dep(lc(x))) x=Bind(lc(x),Rotate(rc(x),0));
        return Rotate(x,1);
    }else return PushUp(x),x;
}

int Insert(int x,int k){
    if(!lc(x)){
        if(k>dat(x)) return Bind(New(dat(x)),New(k));
        else return Bind(New(k),New(dat(x)));
    }
    int y=Clone(x);
    if(k<=dat(lc(x))) lc(y)=Insert(lc(x),k);
    else rc(y)=Insert(rc(y),k);
    return Maintain(y);
}
int Erase(int x,int k,int fa=-1){
    if(!lc(x)){
        if(dat(lc(fa))==k) tr[fa]=tr[rc(fa)];
        else if(dat(rc(fa))==k) tr[fa]=tr[lc(fa)];
        return 0;
    }
    int y=Clone(x);
    if(k<=dat(lc(x))){
        int z=Erase(lc(x),k,y);
        if(z) lc(y)=z;
    }else{
        int z=Erase(rc(x),k,y);
        if(z) rc(y)=z;
    }
    return Maintain(y);
}
int Rank(int x,int k){
    if(!lc(x)) return 1;
    if(k>dat(lc(x))) return Rank(rc(x),k)+siz(lc(x));
    else return Rank(lc(x),k);
}
int Kth(int x,int k){
    if(siz(x)==k) return dat(x);
    if(k>siz(lc(x))) return Kth(rc(x),k-siz(lc(x)));
    else return Kth(lc(x),k);
}
int Pre(int x,int k){
    return Kth(x,Rank(x,k)-1);
}
int Suc(int x,int k){
    return Kth(x,Rank(x,k+1));
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    int T;
    cin>>T;
    vector<int> root;
    root.push_back(Bind(New(inf),New(-inf)));
    while(T--){
        int v,op,x;
        cin>>v>>op>>x;
        if(op==1) root.push_back(Insert(root[v],x));
        else if(op==2) root.push_back(Erase(root[v],x));
        else{
            if(op==3) cout<<Rank(root[v],x)<<endl;
            else if(op==4) cout<<Kth(root[v],x)<<endl;
            else if(op==5) cout<<Pre(root[v],x)<<endl;
            else if(op==6) cout<<Suc(root[v],x)<<endl;
            root.push_back(root[v]);
        }
    }
    
    return 0;
}