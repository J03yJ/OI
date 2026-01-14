#include<bits/stdc++.h>

using namespace std;

#define fir(x) x.first
#define sec(x) x.second
#define ssiz(x) (signed)x.size()
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

void Cop(int &x,int l,int r,int k){
    vector<int> root(__lg(k)+1);
    int lr,mr,rr;
    Pair(x,rr,Split(x,r));
    Pair(lr,mr,Split(x,l-1));
    root[0]=mr,mr=0;
    for(int i=1;i<ssiz(root);i++) root[i]=Merge(root[i-1],root[i-1]);
    for(int i=ssiz(root)-1;~i;i--) if(k>>i&1) mr=Merge(mr,root[i]);
    x=Merge(Merge(lr,mr),rr);
}
void FCop(int &x,int l,int r,int k){
    vector<int> root(__lg(k)+1),froot(__lg(k)+1);
    int lr,mr,rr;
    Pair(x,rr,Split(x,r));
    Pair(lr,mr,Split(x,l-1));
    froot[0]=root[0]=mr,mr=0;
    Push(froot[0]);

    for(int i=1;i<ssiz(root);i++){
        root[i]=Merge(root[i-1],froot[i-1]);
        froot[i]=Merge(froot[i-1],root[i-1]);
    }
    for(int i=ssiz(root)-1,r=0;~i;i--){
        if(k>>i&1){
            mr=Merge(mr,r?froot[i]:root[i]);
            r^=1;
        }
    }
    x=Merge(Merge(lr,mr),rr);
}
void Erase(int &x,int l,int r){
    int lr,mr,rr;
    Pair(x,rr,Split(x,r));
    Pair(lr,mr,Split(x,l-1));
    x=Merge(lr,rr);
}
int Query(int x,int k){
    if(k>dat(x)) return -1;
    if(!lc(x)) return 1;
    PushDown(x);
    if(k<=dat(lc(x))) return Query(lc(x),k);
    else return Query(rc(x),k-dat(lc(x)))+siz(lc(x));
}

int a[N],n;
inline int Make(int l,int r){
    if(l==r) return Allc(a[l]);
    int mid=l+r>>1;
    return Bind(Make(l,mid),Make(mid+1,r));
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n;
    for(int i=1;i<=n;i++){
        char c;
        cin>>c;
        if(c=='1') a[i]=1;
        else a[i]=0;
    }

    int T,root=Make(1,n);
    cin>>T;
    for(int p=1,op,l,r,k;p<=T;p++){
        cin>>op;
        if(op==1) cin>>l>>r>>k,Cop(root,l,r,k);
        else if(op==2) cin>>l>>r>>k,FCop(root,l,r,k);
        else if(op==3) cin>>l>>r,Erase(root,l,r);
        else cin>>k,cout<<Query(root,k)<<endl;
    }

    return 0;
}