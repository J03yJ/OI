#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e3+9;
const int mod=1e9+7;
inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) MulAs(res,x);
        MulAs(x,x);
        y>>=1;
    }
    return res;
}
#define Inv(x) QPow(x,mod-2)

int a[N],f[N][N],n;

struct Fenw{
    int tr[N];
    inline void Modify(int x,int k){
        while(x<=n){
            AddAs(tr[x],k);
            x+=x&-x;
        }
    }
    inline int Query(int x){
        int res=0;
        while(x){
            AddAs(res,tr[x]);
            x&=x-1;
        }
        return res;
    }
    inline int Query(int l,int r){return Sub(Query(r),Query(l-1));}
}l[N],r[N],c[N];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    a[0]=0,a[n+1]=n+1;
    for(int i=n+1;i>=0;i--){
        for(int j=i+2;j<=n+1;j++){
            c[i].Modify(a[j-1],1);
            if(a[i]>a[j]) continue ;
            int cnt=c[i].Query(a[i]+1,a[j]-1);
            AddAs(f[i][j],l[i].Query(1,a[j]-1));
            AddAs(f[i][j],r[j].Query(a[i]+1,n));
            AddAs(f[i][j],cnt);
            MulAs(f[i][j],Inv(cnt));
            if(i!=0) r[j].Modify(a[i],f[i][j]);
            if(j!=n+1) l[i].Modify(a[j],f[i][j]);
        }
    }

    cout<<f[0][n+1]<<endl;
    
    return 0;
}