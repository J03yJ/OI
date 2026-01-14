#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;

struct Node{
    int lc,rc;
    int val,dep,siz,tag;
}tr[N<<6];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define val(x) tr[x].val
#define dep(x) tr[x].dep
#define siz(x) tr[x].siz
#define tag(x) tr[x].tag

int cnt;
inline void PushUp(int x){
    if(!lc(x)) dep(x)=siz(x)=1;
    else{
        dep(x)=max(dep(lc(x)),dep(rc(x)))+1;
        siz(x)=siz(lc(x))+siz(rc(x));
    }
}
inline void PushDown(int x){
    if(!tag(x)) return ;
    tag(lc(x))^=1;tag(rc(x))^=1;
    swap(lc(x),rc(x));
    tag(x)=0;
}
inline void Rotate(int x,int flag){
    if(!flag){
        int y=lc(x);
        PushDown(y);
        lc(x)=lc(y);
        lc(y)=rc(y);
        rc(y)=rc(x);
        rc(x)=y;
        PushUp(y);
    }else{
        int y=rc(x);
        PushDown(y);
        rc(x)=rc(y);
        rc(y)=lc(y);
        lc(y)=lc(x);
        lc(x)=y;
        PushUp(y);
    }
    PushUp(x);
}
inline void Maintain(int x){
    if(!lc(x)) return ;
    if(dep(lc(x))>dep(rc(x))+1){
        if(dep(lc(lc(x)))==dep(rc(x))) Rotate(lc(x),1);
        Rotate(x,0);
    }else if(dep(rc(x))>dep(lc(x))+1){
        if(dep(rc(rc(x)))==dep(lc(x))) Rotate(rc(x),0);
        Rotate(x,1);
    }else PushUp(x);
}
int Bind(int u,int v){
    if(!u||!v) return u|v;
    int x=++cnt;
    lc(x)=u;rc(x)=v;
    PushUp(x);
    return x;
}

int Make(int l,int r){
    if(l==r){
        int x=++cnt;
        val(x)=l;
        dep(x)=siz(x)=1;
        return x;
    }
    int mid=l+r>>1;
    return Bind(Make(l,mid),Make(mid+1,r));
}
int Merge(int x,int y){
    if(abs(dep(x)-dep(y))<=1) return Bind(x,y);
    if(dep(x)<dep(y)){
        PushDown(y);
        lc(y)=Merge(x,lc(y));
        Maintain(y);
        return y;
    }else{
        PushDown(x);
        rc(x)=Merge(rc(x),y);
        Maintain(x);
        return x;
    }
}
pair<int,int> Split(int x,int val){
    if(!lc(x)){
        if(!val) return {0,x};
        else return {x,0};
    }
    PushDown(x);
    if(val<=siz(lc(x))){
        pair<int,int> res=Split(lc(x),val);
        return {res.first,Merge(res.second,rc(x))};
    }else{
        pair<int,int> res=Split(rc(x),val-siz(lc(x)));
        return {Merge(lc(x),res.first),res.second};
    }
}
void Print(int x){
    if(!lc(x)){
        cout<<val(x)<<' ';
        return ;
    }
    PushDown(x);
    Print(lc(x));
    Print(rc(x));
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n,m;
    cin>>n>>m;

    int root=Make(1,n);
    while(m--){
        int l,r;
        cin>>l>>r;
        pair<int,int> rt=Split(root,r);
        pair<int,int> lrt=Split(rt.first,l-1);
        tag(lrt.second)^=1;
        root=Merge(Merge(lrt.first,lrt.second),rt.second);
    }

    Print(root);

    return 0;
}