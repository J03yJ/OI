#include<bits/stdc++.h>

using namespace std;

ifstream fin("hswfwkj.in");
ofstream fout("hswfwkj.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e6+9;
const int lgN=2e1;

int a[N],ql[N],qr[N],n,q;
int mx[N][lgN],lg[N];
inline void Init(){
    for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
    for(int i=1;i<=n;i++) mx[i][0]=i;
    for(int k=1;k<=lg[n];k++){
        for(int i=1,x,y;i<=n;i++){
            x=mx[i][k-1],y=mx[i+(1<<k-1)][k-1];
            if(a[x]>a[y]) mx[i][k]=x;
            else mx[i][k]=y;
        }
    }
}
inline int MaxPoint(int l,int r){
    int k=lg[r-l+1],x=mx[l][k],y=mx[r-(1<<k)+1][k];
    return a[x]>a[y]?x:y;
}

struct SgT{
    struct Node{
        int l,r;
        ll sum,ktag,btag,ctag;
    }tr[N<<2];
    #define l(x) tr[x].l
    #define r(x) tr[x].r
    #define sum(x) tr[x].sum
    #define len(x) (r(x)-l(x)+1)
    #define ktag(x) tr[x].ktag
    #define btag(x) tr[x].btag
    #define ctag(x) tr[x].ctag

    inline void PushUp(int x){sum(x)=sum(x<<1)+sum(x<<1|1);}
    inline void PushLine(int x,ll k,ll b){
        ktag(x)+=k,btag(x)+=b;
        sum(x)+=k*(len(x)*(len(x)+1)/2)+b*len(x);
    }
    inline void PushCov(int x,ll c){
        ktag(x)=btag(x)=0;
        ctag(x)=c;
        sum(x)=c*len(x);
    }
    inline void PushDown(int x){
        if(~ctag(x)){
            PushCov(x<<1,ctag(x));
            PushCov(x<<1|1,ctag(x));
            ctag(x)=-1;
        }
        PushLine(x<<1,ktag(x),btag(x));
        PushLine(x<<1|1,ktag(x),btag(x)+ktag(x)*len(x<<1));
        ktag(x)=btag(x)=0;
    }
    inline void Build(int x,int l,int r){
        l(x)=l,r(x)=r,ctag(x)=-1,ktag(x)=btag(x)=0;
        if(l(x)==r(x)) return ;
        int mid=l(x)+r(x)>>1;
        Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
        PushUp(x);
    }
    inline void AddLine(int x,int l,int r,ll k,ll b){
        if(l<=l(x)&&r(x)<=r) return PushLine(x,k,b);
        int mid=l(x)+r(x)>>1;
        PushDown(x);
        if(l<=mid&&mid<r) AddLine(x<<1,l,mid,k,b),AddLine(x<<1|1,mid+1,r,k,b+k*(mid-l+1));
        else if(l<=mid) AddLine(x<<1,l,r,k,b);
        else AddLine(x<<1|1,l,r,k,b);
        PushUp(x);
    }
    inline void Cover(int x,int l,int r,ll c){
        if(l<=l(x)&&r(x)<=r) return PushCov(x,c);
        int mid=l(x)+r(x)>>1;
        PushDown(x);
        if(l<=mid) Cover(x<<1,l,r,c);
        if(r>mid) Cover(x<<1|1,l,r,c);
        PushUp(x);
    }
    inline ll Query(int x,int pos){
        if(pos<1||pos>n) return 0;
        if(l(x)==r(x)) return sum(x);
        int mid=l(x)+r(x)>>1;
        PushDown(x);
        if(pos<=mid) return Query(x<<1,pos);
        else return Query(x<<1|1,pos);
    }
    inline ll operator ()(int pos){return Query(1,pos);}
}f,g;

ll ans[N];
vector<int> v[N];
inline void Solve(int l,int r){
    if(l>r) return ;
    int mid=MaxPoint(l,r);
    Solve(l,mid-1),Solve(mid+1,r);
    for(int i:v[mid]){
        ll resl=g(ql[i])+1ll*(qr[i]-mid+1)*a[mid];
        ll resr=f(qr[i])+1ll*(mid-ql[i]+1)*a[mid];
        ans[i]=min(resl,resr);
    }
    ll fmid=f(mid-1),gmid=g(mid+1);
    f.Cover(1,mid,mid,mid>l?fmid+a[mid]:a[mid]);
    g.Cover(1,mid,mid,mid<r?gmid+a[mid]:a[mid]);
    if(r>mid){
        int lp=mid,rp=r+1;
        while(lp+1<rp){
            int midp=lp+rp>>1;
            ll lval=fmid+1ll*(midp-mid+1)*a[mid];
            ll rval=1ll*(mid-l+1)*a[mid]+f(midp);
            if(lval<=rval) lp=midp;
            else rp=midp;
        }
        if(lp>mid) f.Cover(1,mid+1,lp,fmid),f.AddLine(1,mid+1,lp,a[mid],a[mid]);
        if(rp<=r) f.AddLine(1,rp,r,0,1ll*(mid-l+1)*a[mid]);
    }
    if(l<mid){
        int lp=l-1,rp=mid;
        while(lp+1<rp){
            int midp=lp+rp>>1;
            ll lval=g(midp)+1ll*(r-mid+1)*a[mid];
            ll rval=1ll*(mid-midp+1)*a[mid]+gmid;
            if(rval<=lval) rp=midp;
            else lp=midp;
        }
        if(rp<mid) g.Cover(1,rp,mid-1,gmid),g.AddLine(1,rp,mid-1,-a[mid],1ll*a[mid]*(mid-rp+2));
        if(lp>=l) g.AddLine(1,l,lp,0,1ll*(r-mid+1)*a[mid]);
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=q;i++) cin>>ql[i]>>qr[i];

    Init();
    f.Build(1,1,n);
    g.Build(1,1,n);
    for(int i=1;i<=q;i++) v[MaxPoint(ql[i],qr[i])].push_back(i);
    Solve(1,n);

    for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

    return 0;
}