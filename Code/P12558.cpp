#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=5e3+9;
const int mod=998244353;

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

int a[N],b[N],f[N][N],g[N][N],ans[N],n,q;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];

	sort(a+1,a+n+1);
	sort(b+1,b+n+1);

	f[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=n;j++){
			AddAs(f[i][j],f[i-1][j]);
			if(j&&a[i]>b[j]) AddAs(f[i][j],f[i-1][j-1]);
		}
	}
	g[n+1][0]=1;
	for(int i=n;i>=1;i--){
		for(int j=0;j<=n;j++){
			AddAs(g[i][j],g[i+1][j]);
			if(j&&a[i]<b[n-j+1]) AddAs(g[i][j],g[i+1][j-1]);
		}
	}

	for(int i=0;i<=n;i++){
		int p=0;
		while(p<n&&a[p+1]<b[i]) p++;
		for(int j=0;j<=p;j++) AddAs(ans[i],Mul(f[p][j],g[p+1][n-p-(i-j)]));
		AddAs(ans[i],ans[i-1]);
	}

	cin>>q;
	while(q--){
		int l,r;
		cin>>l>>r;
		cout<<(l?Sub(ans[r],ans[l-1]):ans[r])<<endl;
	}
	
	return 0;
}