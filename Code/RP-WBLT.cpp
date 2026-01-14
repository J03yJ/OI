#include<bits/stdc++.h>

using namespace std;

#define fir(x) x.first
#define sec(x) x.second
using ll=long long;
using pii=pair<int,int>;
template<class T1,class T2>inline void Pair(T1 &x,T2 &y,pair<T1,T2> p){x=fir(p),y=sec(p);}

const int N=2e5+9;

struct Node{
    int lc,rc,siz,rev;
    ll dat;
}tr[N<<7];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define siz(x) tr[x].siz
#define dat(x) tr[x].dat
#define rev(x) tr[x].rev

int trs[N<<6],top,cnt;
inline int Allc(){return top?trs[top--]:++cnt;}
inline int Allc(int l,int r,int s,ll d){
    int x=Allc();
    lc(x)=l,rc(x)=r,siz(x)=s,dat(x)=d,rev(x)=0;
    return x;
}
inline int Allc(ll d){return Allc(0,0,1,d);}
inline int Bind(int x,int y){return Allc(x,y,siz(x)+siz(y),dat(x)+dat(y));}
inline void Copy(int x,int y){memcpy(&tr[y],&tr[x],sizeof tr[x]);}
inline int Clone(int x){int y=Allc();Copy(x,y);return y;}
inline void Delete(int x){
    if(!x) return ;
    Delete(lc(x)),Delete(rc(x));
    trs[++top]=x;
}
inline int Leaf(int x){return !lc(x);}

inline void Push(int &x){x=Clone(x),swap(lc(x),rc(x)),rev(x)^=1;}
inline void PushDown(int x){if(rev(x)) Push(lc(x)),Push(rc(x)),rev(x)=0;}
inline int Merge(int x,int y){
    if(!x||!y) return x|y;
    if(5*min(siz(x),siz(y))>=siz(x)+siz(y)) return Bind(x,y);
    if(siz(x)>siz(y)){
        PushDown(x);
        if(5*siz(lc(x))>=siz(x)+siz(y)) return Merge(lc(x),Merge(rc(x),y));
        else return PushDown(rc(x)),Merge(Merge(lc(x),lc(rc(x))),Merge(rc(rc(x)),y));
    }else{
        PushDown(y);
        if(5*siz(rc(y))>=siz(x)+siz(y)) return Merge(Merge(x,lc(y)),rc(y));
        else return PushDown(lc(y)),Merge(Merge(x,lc(lc(y))),Merge(rc(lc(y)),rc(y)));
    }
}
pii Split(int x,int k){
    if(!k) return {0,x};
    if(k==siz(x)) return {x,0};
    PushDown(x);
    if(k<=siz(lc(x))){
        pii res=Split(lc(x),k);
        return {fir(res),Merge(sec(res),rc(x))};
    }else{
        pii res=Split(rc(x),k-siz(lc(x)));
        return {Merge(lc(x),fir(res)),sec(res)};
    }
}

inline ll Query(int x,int p){
    if(!p||!x) return 0;
    if(p==siz(x)) return dat(x);
    PushDown(x);
    if(p<=siz(lc(x))) return Query(lc(x),p);
    else return Query(rc(x),p-siz(lc(x)))+dat(lc(x));
}
inline ll Query(int x,int l,int r){return Query(x,r)-Query(x,l-1);}
inline void Reverse(int &x,int l,int r){
    int lr,mr,rr;
    Pair(x,rr,Split(x,r));
    Pair(lr,mr,Split(x,l-1));
    Push(mr);
    x=Merge(Merge(lr,mr),rr);
}
inline void Insert(int &x,int pos,int k){
    int lr,rr;
    Pair(lr,rr,Split(x,pos));
    x=Merge(Merge(lr,Allc(k)),rr);
}
inline void Erase(int &x,int pos){
    int lr,mr,rr;
    Pair(x,rr,Split(x,pos));
    Pair(lr,mr,Split(x,pos-1));
    x=Merge(lr,rr);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    vector<int> root={Allc(0)};
    int T;ll lst=0;
    cin>>T;
    for(int p=1;p<=T;p++){
        int v,op;
        ll x,y;
        cin>>v>>op;
        root.push_back(root[v]);
        if(op==2) cin>>x;
        else cin>>x>>y;
        x^=lst,y^=lst;
        if(op==1) Insert(root.back(),x,y);
        else if(op==2) Erase(root.back(),x);
        else if(op==3) Reverse(root.back(),x,y);
        else cout<<(lst=Query(root.back(),x,y))<<endl;
    }

    return 0;
}