#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e5+9;
const int inf=1e18;

struct Node{
    int lc,rc,dep,siz;
    int rtag,atag,dat;
}tr[N<<5];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define dep(x) tr[x].dep
#define siz(x) tr[x].siz
#define atag(x) tr[x].atag
#define rtag(x) tr[x].rtag
#define dat(x) tr[x].dat

int trs[N],cnt,top;
inline int New(){
    if(top) return trs[top--];
    else return ++cnt;
}
inline void Del(int x){
    dep(x)=siz(x)=rtag(x)=atag(x)=dat(x)=0;
    trs[++top]=x;
}
inline void PushUp(int x){
    if(!lc(x)) dep(x)=1,siz(x)=1;
    else{
        dep(x)=max(dep(lc(x)),dep(rc(x)))+1;
        siz(x)=siz(lc(x))+siz(rc(x));
        dat(x)=max(dat(lc(x)),dat(rc(x)));
    }
}
inline void Push(int x,int k){
    atag(x)+=k;
    dat(x)+=k;
}
inline void PushDown(int x){
    if(!lc(x)) return ;
    if(rtag(x)){
        rtag(lc(x))^=1;
        rtag(rc(x))^=1;
        swap(lc(x),rc(x));
        rtag(x)=0;
    }
    if(atag(x)){
        Push(lc(x),atag(x));
        Push(rc(x),atag(x));
        atag(x)=0;
    }
}
inline int Bind(int x,int y){
    if(!x||!y) return x|y;
    int z=New();
    lc(z)=x,rc(z)=y;
    PushUp(z);
    return z;
}

void Rotate(int x,int flag){
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
void Maintain(int x){
    PushDown(x);
    if(dep(lc(x))>dep(rc(x))+1){
        if(dep(lc(lc(x)))==dep(rc(x))) Rotate(lc(x),1);
        Rotate(x,0);
    }else if(dep(rc(x))>dep(lc(x))+1){
        if(dep(rc(rc(x)))==dep(lc(x))) Rotate(rc(x),0);
        Rotate(x,1);
    }else PushUp(x);
}

int n,m;
int Make(int l,int r){
    if(l==r){
        int x=New();
        dep(x)=siz(x)=1;
        dat(x)=0;
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
pair<int,int> Split(int x,int k){
    if(!k) return {0,x};
    if(!lc(x)) return {x,0};
    PushDown(x);
    Del(x);
    if(k<=siz(lc(x))){
        pair<int,int> res=Split(lc(x),k);
        return {res.first,Merge(res.second,rc(x))};
    }else{
        pair<int,int> res=Split(rc(x),k-siz(lc(x)));
        return {Merge(lc(x),res.first),res.second};
    }
}

int Reverse(int x,int l,int r){
    pair<int,int> rt=Split(x,r);
    pair<int,int> lrt=Split(rt.first,l-1);
    rtag(lrt.second)^=1;
    return Merge(Merge(lrt.first,lrt.second),rt.second);
}
void Modify(int x,int l,int r,int k){
    if(l<=1&&r>=siz(x)) return Push(x,k);
    PushDown(x);
    int mid=siz(lc(x));
    if(l<=mid) Modify(lc(x),l,r,k);
    if(r>mid) Modify(rc(x),l-mid,r-mid,k);
    PushUp(x);
}
int Query(int x,int l,int r){
    if(l<=1&&r>=siz(x)) return dat(x);
    PushDown(x);
    int mid=siz(lc(x)),ans=-inf;
    if(l<=mid) ans=max(ans,Query(lc(x),l,r));
    if(r>mid) ans=max(ans,Query(rc(x),l-mid,r-mid));
    return ans;
}

signed main(){
    cin>>n>>m;
    dat(0)=-inf;
    int root=Make(1,n);
    while(m--){
        int op,l,r,k;
        cin>>op>>l>>r;
        if(op==1){
            cin>>k;
            Modify(root,l,r,k);
        }else if(op==2) root=Reverse(root,l,r);
        else cout<<Query(root,l,r)<<endl;
        assert(cnt<=2*n);
    }

    return 0;
}