#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using Point=array<int,2>;
const int N=3e5+9;
inline int Dist(Point p,Point q){return abs(p[0]-q[0])+abs(p[1]-q[1]);}

struct Node{
    int lc,rc,siz;
    Point l,r,pos;
}tr[N<<1];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define siz(x) tr[x].siz
#define l(x) tr[x].l
#define r(x) tr[x].r
#define pos(x) tr[x].pos

int cnt;
inline int Allc(){return ++cnt;}
inline int Allc(Point p){
    int x=Allc();
    l(x)=r(x)=pos(x)=p;
    siz(x)=1;
    return x;
}
inline void PushUp(int x){
    siz(x)=1;
    l(x)=r(x)=pos(x);
    if(lc(x)){
        siz(x)+=siz(lc(x));
        l(x)[0]=min(l(x)[0],l(lc(x))[0]);
        l(x)[1]=min(l(x)[1],l(lc(x))[1]);
        r(x)[0]=max(r(x)[0],r(lc(x))[0]);
        r(x)[1]=max(r(x)[1],r(lc(x))[1]);
    }
    if(rc(x)){
        siz(x)+=siz(rc(x));
        l(x)[0]=min(l(x)[0],l(rc(x))[0]);
        l(x)[1]=min(l(x)[1],l(rc(x))[1]);
        r(x)[0]=max(r(x)[0],r(rc(x))[0]);
        r(x)[1]=max(r(x)[1],r(rc(x))[1]);
    }
}
const int inf=1e9;
inline int H(int x,Point p){
    if(!x) return inf;
    int res=0;
    res+=max(l(x)[0]-p[0],0)+max(p[0]-r(x)[0],0);
    res+=max(l(x)[1]-p[1],0)+max(p[1]-r(x)[1],0);
    return res;
}

int tmp[N<<1],top,n,m,root;
const double alpha=0.7;
inline void Slap(int x){
    if(!x) return ;
    Slap(lc(x)),Slap(rc(x));
    tmp[++top]=x;
    lc(x)=rc(x)=0;
    PushUp(x);
}
inline void Build(int &x,int l,int r,int k){
    if(l>r) return x=0,void();
    int mid=l+r>>1;
    nth_element(tmp+l,tmp+mid,tmp+r,[&k](int i,int j){return pos(i)[k]<pos(j)[k];});
    x=tmp[mid];
    Build(lc(x),l,mid-1,k^1);
    Build(rc(x),mid+1,r,k^1);
    PushUp(x);
}
inline void Maintain(int &x,int t){
    if(max(siz(lc(x)),siz(rc(x)))<=alpha*siz(x)) return ;
    Slap(x);
    Build(x,1,top,t);
    top=0;
}
inline void Insert(int &x,Point p,int t=0){
    if(!x) return x=Allc(p),void();
    if(p[t]<=pos(x)[t]) Insert(lc(x),p,t^1);
    else Insert(rc(x),p,t^1);
    PushUp(x);
    Maintain(x,t);
}
inline int Query(int x,Point p,int ans=inf){
    ans=min(ans,Dist(pos(x),p));
    int hl=H(lc(x),p),hr=H(rc(x),p);
    if(hl<hr){
        if(hl<ans) ans=min(ans,Query(lc(x),p,ans));
        if(hr<ans) ans=min(ans,Query(rc(x),p,ans));
    }else{
        if(hr<ans) ans=min(ans,Query(rc(x),p,ans));
        if(hl<ans) ans=min(ans,Query(lc(x),p,ans));
    }
    return ans;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n>>m;

    while(n--){
        Point p;
        cin>>p[0]>>p[1];
        Insert(root,p);
    }
    while(m--){
        int op;Point p;
        cin>>op>>p[0]>>p[1];
        if(op==1) Insert(root,p);
        else cout<<Query(root,p)<<endl;
    }

    return 0;
}