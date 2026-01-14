#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e5+9;

struct Node{
    int lc,rc,dep,siz,rev;
    long long dat;
}tr[N<<7];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define dep(x) tr[x].dep
#define siz(x) tr[x].siz
#define rev(x) tr[x].rev
#define dat(x) tr[x].dat

int cnt;
int New(long long k){
    int x=++cnt;
    dat(x)=k;
    dep(x)=siz(x)=1;
    return x;
}
int Clone(int x){
    int y=++cnt;
    tr[y]=tr[x];
    return y;
}
int Push(int x){
    if(!lc(x)) return x;
    int y=Clone(x);
    swap(lc(y),rc(y));
    rev(y)^=1;
    return y;
}
void PushDown(int x){
    if(!lc(x)||!rev(x)) return ;
    lc(x)=Push(lc(x));
    rc(x)=Push(rc(x));
    rev(x)=0;
}
void PushUp(int x){
    if(!lc(x)) siz(x)=dep(x)=1;
    else{
        siz(x)=siz(lc(x))+siz(rc(x));
        dep(x)=max(dep(lc(x)),dep(rc(x)))+1;
        dat(x)=dat(lc(x))+dat(rc(x));
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
    if(!flag) return PushDown(lc(x)),Bind(lc(lc(x)),Bind(rc(lc(x)),rc(x)));
    else return PushDown(rc(x)),Bind(Bind(lc(x),lc(rc(x))),rc(rc(x)));
}
int Maintain(int x){
    PushDown(x);
    if(dep(lc(x))>dep(rc(x))+1){
        PushDown(lc(x));
        if(dep(lc(lc(x)))==dep(rc(x))) x=Bind(Rotate(lc(x),1),rc(x));
        return Rotate(x,0);
    }else if(dep(rc(x))>dep(lc(x))+1){
        PushDown(rc(x));
        if(dep(rc(rc(x)))==dep(lc(x))) x=Bind(lc(x),Rotate(rc(x),0));
        return Rotate(x,1);
    }else return PushUp(x),x;
}

vector<int> root;
int Merge(int x,int y){
    if(!x||!y) return x|y;
    if(abs(dep(x)-dep(y))<=1) return Bind(x,y);
    if(dep(x)<dep(y)){
        PushDown(y);
        return Maintain(Bind(Merge(x,lc(y)),rc(y)));
    }else{
        PushDown(x);
        return Maintain(Bind(lc(x),Merge(rc(x),y)));
    }
}
pair<int,int> Split(int x,int k){
    if(!k) return {0,x};
    if(!lc(x)) return {x,0};
    PushDown(x); 
    if(k<=siz(lc(x))){
        pair<int,int> res=Split(lc(x),k);
        return {res.first,Merge(res.second,rc(x))};
    }else{
        pair<int,int> res=Split(rc(x),k-siz(lc(x)));
        return {Merge(lc(x),res.first),res.second};
    }
}
long long Query(int x,int l,int r){
    if(l<=1&&r>=siz(x)) return dat(x);
    PushDown(x);
    int mid=siz(lc(x));
    long long ans=0;
    if(l<=mid) ans+=Query(lc(x),l,r);
    if(r>mid) ans+=Query(rc(x),l-mid,r-mid);
    return ans;
}
inline int Reverse(int x,int l,int r){
    pair<int,int> rt=Split(x,r);
    pair<int,int> lrt=Split(rt.first,l-1);
    int a=lrt.first,b=lrt.second,c=rt.second;
    b=Push(b);
    return Merge(Merge(a,b),c);
}
inline int Insert(int x,int pos,int k){
    pair<int,int> rt=Split(x,pos);
    return Merge(Merge(rt.first,New(k)),rt.second);
}
inline int Erase(int x,int pos){
    pair<int,int> rt=Split(x,pos);
    pair<int,int> lrt=Split(rt.first,pos-1);
    return Merge(lrt.first,rt.second);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    root.push_back(New(0));

    int T,lst=0;
    cin>>T;
    while(T--){
        int v,op,x;
        cin>>v>>op>>x;
        x^=lst;
        if(op==2){
            root.push_back(Erase(root[v],x));
        }else{
            int y;
            cin>>y;
            y^=lst;
            if(op==1) root.push_back(Insert(root[v],x,y));
            else if(op==3)root.push_back(Reverse(root[v],x,y));
            else cout<<(lst=Query(root[v],x,y))<<endl,root.push_back(root[v]);
        }
    }

    return 0;
}