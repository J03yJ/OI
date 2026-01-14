#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=3e3+9;
const int mod=1e9+7;

inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
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

int f[N][N][2],n,m;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>m;
	
	f[1][1][0]=m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=min(i,m);j++){
			AddAs(f[i+1][j][1],Mul(f[i][j][0],j));
			AddAs(f[i+1][j][0],Mul(f[i][j][0],m-j));
			AddAs(f[i+1][j][1],Mul(f[i][j][1],j));
			AddAs(f[i+1][j+1][0],Mul(f[i][j][1],m-j));
		}
	}

	int ans=0;
	for(int j=1;j<=min(n,m);j++) AddAs(ans,f[n][j][1]);

	cout<<ans<<endl;

	return 0;
}