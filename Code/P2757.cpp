#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=5e5+9;
const int mod=998244353;
const int base=2;

int bpw[N];
struct Data{
    int f,g,len;
    Data(){}
    Data(int _f,int _g,int _len){f=_f,g=_g,len=_len;}
    Data operator +(const Data x){
        return Data((f+1ll*x.f*bpw[len])%mod,(1ll*g*bpw[x.len]+x.g)%mod,len+x.len);
    }
};

struct Node{
    int l,r;
    Data dat;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat

inline void PushUp(int x){dat(x)=dat(x<<1)+dat(x<<1|1);}
inline void Build(int x,int l,int r){
    l(x)=l,r(x)=r;
    if(l(x)==r(x)) return dat(x)=Data(0,0,1),void();
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
    PushUp(x);
}
inline void Modify(int x,int pos,Data k){
    if(l(x)==r(x)) return dat(x)=k,void();
    int mid=l(x)+r(x)>>1;
    if(pos<=mid) Modify(x<<1,pos,k);
    else Modify(x<<1|1,pos,k);
    PushUp(x);
}
inline Data Query(int x,int l,int r){
    if(l>r) return Data(0,0,0);
    if(l<=l(x)&&r(x)<=r) return dat(x);
    int mid=l(x)+r(x)>>1;
    if(l<=mid&&r>mid) return Query(x<<1,l,mid)+Query(x<<1|1,mid+1,r);
    else if(l<=mid) return Query(x<<1,l,r);
    else return Query(x<<1|1,l,r);
}

int a[N],n;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];

        bool flag=0;
        Build(1,1,n);
        bpw[0]=1;for(int i=1;i<=n;i++) bpw[i]=1ll*bpw[i-1]*base%mod;
        for(int i=1;i<=n;i++){
            Modify(1,a[i],Data(1,1,1));
            int len=min(a[i]-1,n-a[i]);
            flag|=Query(1,a[i]-len,a[i]).f!=Query(1,a[i],a[i]+len).g;
        }

        if(flag) cout<<'Y'<<endl;
        else cout<<'N'<<endl;
    }
    

    return 0;
}