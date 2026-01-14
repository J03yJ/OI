#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
#define likely(x) __builtin_expect(x,1)
#define unlikely(x) __builtin_expect(x,0)
using ll=long long;
using ull=unsigned ll;
const int N=2e6+9;
const int T=2e6/64+9;
const int M=1.5e3+9;

int px[N],py[N],n,m,lim;
vector<int> a[M],r[N];
vector<ll> cw[M],rw[M],f[M];

namespace Fenw{
	int tr[N];
	inline void Modify(int x,int k){while(x<=n) tr[x]+=k,x+=x&-x;}
	inline int Query(int x){int sum=0;while(x) sum+=tr[x],x&=x-1;return sum;}
}
int p[N];
inline void Work(int l,int r){
	if(l>=r) return ;
	int mid=l+r>>1;
	Work(l,mid),Work(mid+1,r);
	sort(p+l,p+mid+1,[](int i,int j){return py[i]>py[j];});
	sort(p+mid+1,p+r+1,[](int i,int j){return py[i]>py[j];});
	int i=l,j=mid+1;
	while(i<=mid){
		while(j<=r&&py[p[j]]>=py[p[i]]) Fenw::Modify(n-px[p[j++]]+1,1);
		cw[px[p[i]]][py[p[i]]]=rw[px[p[i]]][py[p[i]]]+=Fenw::Query(n-px[p[i]]+1);
		i++;
	}
	while(j>mid+1) Fenw::Modify(n-px[p[--j]]+1,-1);
}

namespace Block{
	ull val[T];
	int blk[T],pre[T],bpre[T],L[T],R[T],B;
	inline void Init(){
		B=ceil(sqrt(lim)/8);
		for(int i=1;i<=(lim>>6)+1;i++) blk[i]=(i-1)/B+1;
		for(int i=1;i<=(lim>>6)+1;i++) R[blk[i]]=i;
		for(int i=(lim>>6)+1;i>=1;i--) L[blk[i]]=i;
		for(int i=1;i<=(lim>>6)+1;i++) val[i]=pre[i]=bpre[i]=0;
	}
	inline void Insert(int x){
		int p=(x>>6)+1;
		val[p]|=1ull<<(x&63);
		for(int i=p;i<=R[blk[p]];i++) pre[i]++;
		for(int i=blk[p];i<=blk[(lim>>6)+1];i++) bpre[i]++;
	}
	inline int Query(int x){
		return bpre[blk[(x>>6)+1]-1]+pre[(x>>6)+1]-__builtin_popcountll((val[(x>>6)+1]>>(x&63))>>1);
	}
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>m;
	for(int i=1;i<=n;i++){
		a[i]=vector<int>(m+1,0);
		f[i]=cw[i]=rw[i]=vector<ll>(m+1,0);
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			px[a[i][j]]=i;
			py[a[i][j]]=j;
		}
	}
	lim=n*m;

	for(int i=1;i<=m;i++){
		r[i]=vector<int>(n+1,0);
		for(int j=1;j<=n;j++) r[i][j]=a[j][i];
	}

	for(int i=1;i<=lim;i++) p[i]=lim-i+1;
	Work(1,lim);

	for(int i=1;i<=n;i++){
		Block::Init();
		for(int j=m;j>=1;j--){
			ll sum=1ll*(n-i)*(m-j),cnt=0;
			for(int k=i+1;k<=n;k++){
				cnt+=Block::Query(r[j][k]);
			}
			rw[i][j]+=sum-cnt;
			cw[i][j]+=cnt;
			Block::Insert(a[i][j]);
		}
	}
	for(int i=n;i>=1;i--){
		for(int j=m;j>=1;j--){
			if(i<n) cw[i][j]+=cw[i+1][j];
			if(j<m) rw[i][j]+=rw[i][j+1];
		}
	}

	for(int i=n;i>=1;i--){
		for(int j=m;j>=1;j--){
			if(i==n&&j==m) continue ;
			f[i][j]=1e18;
			if(i!=n) f[i][j]=min(f[i][j],f[i+1][j]+rw[i][j]);
			if(j!=m) f[i][j]=min(f[i][j],f[i][j+1]+cw[i][j]);
		}
	}
	cout<<f[1][1]<<endl;

	return 0;
}