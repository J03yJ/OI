#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e2+9;
const int mod=998244353;

inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int QPow(int x,int y){
	int ans=1;
	while(y){
		if(y&1) MulAs(ans,x);
		MulAs(x,x);
		y>>=1;
	}
	return ans;
}
inline int Inv(int x){return QPow(x,mod-2);}

int fac[N],ifac[N];
inline void Init(int lim){
	fac[0]=1;
	for(int i=1;i<=lim;i++) fac[i]=Mul(fac[i-1],i);
	ifac[lim]=Inv(fac[lim]);
	for(int i=lim-1;~i;i--) ifac[i]=Mul(ifac[i+1],i+1);
}
inline int C(int n,int m){
	if(m<0||m>n) return 0;
	else return Mul(fac[n],Mul(fac[m],fac[n-m]));
}

int p[N],q[N],f[N][N][N],g[N],vis[N],n;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n;
	for(int i=1;i<=n;i++) cin>>p[i];
	for(int i=1;i<=n;i++) cin>>q[i];
	for(int i=1;i<=n;i++){
		while(p[i]!=i) swap(q[i],q[p[i]]),swap(p[i],p[p[i]]);
	}

	Init(n);
	f[0][0][0]=1;
	for(int i=1;i<=n;i++) if(q[i]) vis[q[i]]=1;
	for(int i=0;i<=n;i++){
		for(int j=0;j<=i;j++){
			for(int k=0;k<=n;k++){
				if(q[i+1]){
					AddAs(f[i+1][j][k],f[i][j][k]);
					if(q[i+1]>k) AddAs(f[i+1][j][q[i+1]],f[i][j][k]);
				}else{
					AddAs(f[i+1][j][k],f[i][j][k]);
					AddAs(g[k+1],f[i][j][k]);
				}
			}
			for(int k=0;k<=n;k++){
				if(k+1<=n) AddAs(g[k+1],g[k]);
				if(!vis[k]) AddAs(f[i+1][j+1][k],g[k]);
				g[k]=0;
			}
		}
	}

	int m=n-accumulate(vis+1,vis+n+1,0),ans=0;
	for(int j=0;j<=n;j++){
		for(int k=0;k<=n;k++) AddAs(ans,Mul(f[n][j][k],fac[m-j]));
	}

	cout<<ans<<endl;

	return 0;
}