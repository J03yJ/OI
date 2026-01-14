#include<bits/stdc++.h>

using namespace std;

#define For(i,l,r) for(int i=(l);i<=(r);i++)
#define Rof(i,l,r) for(int i=(r);i>=(l);i--)
#define Rep(i,n) for(int i=0;i<(n);i++)
#define ssiz(x) (signed)x.size()
#define allc(x) x.begin(),x.end()
#define fir(x) x.first
#define sec(x) x.second
using ll=long long;
using ull=unsigned long long;
using pii=pair<int,int>;
template<class T1,class T2>void ChMin(T1 &x,T2 y){if(y<x) x=y;}
template<class T1,class T2>void ChMax(T1 &x,T2 y){if(y>x) x=y;}
template<class T>using svector=vector<vector<T>>;
template<class T>using cvector=vector<vector<vector<T>>>;

const int N=1e5+9;
const int inf=1e9+7;

struct Node{
    int lc,rc,siz,val;
}tr[N<<6];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define siz(x) tr[x].siz
#define val(x) tr[x].val

int trs[N<<6],top,cnt;
inline int Allc(){return top?trs[top--]:++cnt;}
inline int Allc(int l,int r,int s,int v){
    int x=Allc();
    lc(x)=l,rc(x)=r,siz(x)=s,val(x)=v;
    return x;
}
inline void Erase(int x){memset(&tr[x],0,sizeof(tr[x])),trs[++top]=x;}
inline void PushUp(int x){
    if(lc(x)){
        siz(x)=siz(lc(x))+siz(rc(x));
        val(x)=val(rc(x));
    }else siz(x)=1;
}
inline int Bind(int x,int y){
    if(!x||!y) return x|y;
    return Allc(x,y,siz(x)+siz(y),val(y));
}
inline void Rotate(int x,int flag){
    if(!flag){
        rc(x)=Bind(rc(lc(x)),rc(x));
        lc(x)=lc(lc(x));
    }else{
        lc(x)=Bind(lc(x),lc(rc(x)));
        rc(x)=rc(rc(x));
    }
}
inline void Maintain(int x){
    PushUp(x);
    if(siz(lc(x))>siz(rc(x))*3){
        if(siz(rc(lc(x)))>siz(lc(lc(x)))*2) Rotate(lc(x),1);
        Rotate(x,0);
    }else if(siz(rc(x))>siz(lc(x))*3){
        if(siz(lc(rc(x)))>siz(rc(rc(x)))*2) Rotate(rc(x),0);
        Rotate(x,1);
    };
}
void Insert(int x,int k){
    if(!lc(x)){
        lc(x)=Allc(0,0,1,min(val(x),k));
        rc(x)=Allc(0,0,1,max(val(x),k));
        return Maintain(x);
    }
    if(k<=val(lc(x))) Insert(lc(x),k);
    else Insert(rc(x),k);
    Maintain(x);
}
void Erase(int x,int k,int fa=-1){
    if(!lc(x)){
        int u=lc(fa),v=rc(fa);
        if(val(u)==k) tr[fa]=tr[v];
        else if(val(v)==k) tr[fa]=tr[u];
        return ;
    }
    if(k<=val(lc(x))) Erase(lc(x),k,x);
    else Erase(rc(x),k,x);
    Maintain(x);
}
int Rank(int x,int k){
    if(siz(x)==1) return 1;
    if(k<=val(lc(x))) return Rank(lc(x),k);
    else return Rank(rc(x),k)+siz(lc(x));
}
int Kth(int x,int k){
    if(siz(x)==k) return val(x);
    if(k<=siz(lc(x))) return Kth(lc(x),k);
    else return Kth(rc(x),k-siz(lc(x)));
}
int Pre(int x,int k){return Kth(x,Rank(x,k)-1);}
int Suc(int x,int k){return Kth(x,Rank(x,k+1));}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    int root=Allc(0,0,1,inf),T;
    cin>>T;
    while(T--){
        int op,k;
        cin>>op>>k;
        if(op==1) Insert(root,k);
        else if(op==2) Erase(root,k);
        else if(op==3) cout<<Rank(root,k)<<endl;
        else if(op==4) cout<<Kth(root,k)<<endl;
        else if(op==5) cout<<Pre(root,k)<<endl;
        else if(op==6) cout<<Suc(root,k)<<endl;
    }

    return 0;
}