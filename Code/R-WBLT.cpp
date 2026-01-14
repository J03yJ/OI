#include<bits/stdc++.h>

using namespace std;

const int N=5e5+9;
const int inf=INT_MAX;
using pii=pair<int,int>;

struct Node{
    int lc,rc,val,siz,rev;
}tr[N<<5];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define val(x) tr[x].val
#define siz(x) tr[x].siz
#define rev(x) tr[x].rev

int trs[N<<5],top,cnt;
inline int Allc(){int x=top?trs[top--]:++cnt;memset(&tr[x],0,sizeof tr[x]);return x;}
inline int Allc(int l,int r,int s,int k){
    int x=Allc();
    siz(x)=s,val(x)=k,lc(x)=l,rc(x)=r;
    return x;
}
inline int Allc(int k){return Allc(0,0,1,k);}
inline int Bind(int x,int y){return x&&y?Allc(x,y,siz(x)+siz(y),max(val(x),val(y))):x|y;}
inline void Destroy(int x){trs[++top]=x;}

inline void Push(int x){swap(lc(x),rc(x)),rev(x)^=1;}
inline void PushDown(int x){
    if(!rev(x)) return ;
    Push(lc(x)),Push(rc(x));
    rev(x)=0;
}

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
        return {res.first,Merge(res.second,rc(x))};
    }else{
        pii res=Split(rc(x),k-siz(lc(x)));
        return {Merge(lc(x),res.first),res.second};
    }
}
int Make(int l,int r){
    if(l==r) return Allc(l);
    int mid=l+r>>1;
    return Bind(Make(l,mid),Make(mid+1,r));
}
void Print(int x){
    if(!lc(x)) cout<<val(x)<<' ';
    else PushDown(x),Print(lc(x)),Print(rc(x));
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    int n,m;
    cin>>n>>m;
    int root=Make(1,n);
    while(m--){
        int l,r;
        cin>>l>>r;
        pii rt=Split(root,r);
        pii lrt=Split(rt.first,l-1);
        Push(lrt.second);
        root=Merge(Merge(lrt.first,lrt.second),rt.second);
    }
    Print(root),cout<<endl;

    return 0;
}