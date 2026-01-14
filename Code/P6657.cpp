#include<bits/stdc++.h>

using namespace std;

const int N=2e6+9;
const int M=1e2+9;
const int mod=998244353;
inline void AddAs(int &x,int y){x+=y;if(x>=mod) x-=mod;}
inline void SubAs(int &x,int y){x-=y;if(x<0) x+=mod;}
inline int Add(int x,int y){x+=y;if(x>=mod) x-=mod;return x;}
inline int Sub(int x,int y){x-=y;if(x<0) x+=mod;return x;}
inline int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=1ll*res*x%mod;
        x=1ll*x*x%mod;
        y>>=1;
    }
    return res;
}
#define Inv(x) QPow(x,mod-2)

int fac[N],ifac[N];
inline void Init(int lim){
    fac[0]=1;
    for(int i=1;i<=lim;i++) fac[i]=1ll*fac[i-1]*i%mod;
    ifac[lim]=Inv(fac[lim]);
    for(int i=lim-1;~i;i--) ifac[i]=1ll*ifac[i+1]*(i+1)%mod;
}
inline int C(int n,int m){
    if(m<0||m>n) return 0;
    else return 1ll*fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}

int a[M],b[M],r[M][M],n,m;
inline int Det(){
    int res=1;
    for(int i=1;i<=m;i++){
        for(int j=i+1;j<=m;j++){
            if(!r[i][i]&&r[j][i]){
                swap(r[i],r[j]);
                res=mod-res;
                break ;
            }
        }
        if(!r[i][i]) return 0;
        int tmp=Inv(r[i][i]);
        for(int j=i+1;j<=m;j++){
            int w=1ll*tmp*r[j][i]%mod;
            for(int k=i;k<=m;k++) SubAs(r[j][k],1ll*w*r[i][k]%mod);
        }
    }
    for(int i=1;i<=m;i++) res=1ll*res*r[i][i]%mod;
    return res;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'
    
    int T;
    cin>>T;
    Init(2e6);
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=m;i++) cin>>a[i]>>b[i];

        for(int i=1;i<=m;i++){
            for(int j=1;j<=m;j++) r[i][j]=C(b[j]-a[i]+n-1,n-1);
        }
        cout<<Det()<<endl;
    }

    return 0;
}