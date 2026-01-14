#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=4e2+9;
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

struct Basis{
	bitset<N> b[N];
	inline bool Insert(bitset<N> x){
		for(int i=N-1;~i;i--){
			if(!x[i]) continue ;
			if(b[i].none()){
				b[i]=x;
				return 1;
			}else x^=b[i];
		}
		return 0;
	}
}b;

bitset<N> pre[N];
int vis[N],n,m,cnt;
vector<array<int,2>> e[N];
inline void DFS(int x){
	vis[x]=1;
	for(auto t:e[x]){
		if(!vis[t[0]]){
			pre[t[0]]=bitset<N>(pre[x]).set(t[1]);
			DFS(t[0]);
		}else cnt+=b.Insert(bitset<N>(pre[x]^pre[t[0]]).set(t[1]));
	}
}

signed main(){
	cin>>n>>m;
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		e[u].push_back({v,i});
	}

	for(int i=1;i<=n;i++){
		DFS(i);
		for(int j=1;j<=n;j++) vis[j]=0;
	}

	cout<<QPow(2,m-cnt)<<endl;

	return 0;
}