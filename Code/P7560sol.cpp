#include <bits/stdc++.h>
#define lc(x) (x<<1)
#define rc(x) (x<<1|1)
using namespace std;
using ll=long long;
using pii=pair<int,int>;
const int N=2.5e5+5;
int n,m,m0,m1,c[N],ans[N],tg[N];
ll h[N],f[N<<2],g[N<<2],tgf[N<<2],tgg[N<<2];
vector<pii>p[N],q[N];
void addf(int x,ll k){ f[x]+=k,tgf[x]+=k; }
void addg(int x,ll k){ g[x]+=k,tgg[x]+=k; }
void pushup(int x){ f[x]=max(f[lc(x)],f[rc(x)]),g[x]=min(g[lc(x)],g[rc(x)]); }
void pushdw(int x){
	if(tgf[x]) addf(lc(x),tgf[x]),addf(rc(x),tgf[x]),tgf[x]=0;
	if(tgg[x]) addg(lc(x),tgg[x]),addg(rc(x),tgg[x]),tgg[x]=0;
}
void updf(int x,int l,int r,int u,int v,ll k){
	if(l>v||r<u) return ; if(u<=l&&r<=v) return addf(x,k); int mid=l+r>>1;
	pushdw(x),updf(lc(x),l,mid,u,v,k),updf(rc(x),mid+1,r,u,v,k),pushup(x);
}
void updg(int x,int l,int r,int u,int v,ll k){
	if(l>v||r<u) return ; if(u<=l&&r<=v) return addg(x,k); int mid=l+r>>1;
	pushdw(x),updg(lc(x),l,mid,u,v,k),updg(rc(x),mid+1,r,u,v,k),pushup(x);
}
ll askF(int x,int l,int r,int u,int v){
	if(l>v||r<u) return -1e16; if(u<=l&&r<=v) return f[x]; int mid=l+r>>1;
	pushdw(x); return max(askF(lc(x),l,mid,u,v),askF(rc(x),mid+1,r,u,v));
}
ll askG(int x,int l,int r,int u,int v){
	if(l>v||r<u) return 1e16; if(u<=l&&r<=v) return g[x]; int mid=l+r>>1;
	pushdw(x); return min(askG(lc(x),l,mid,u,v),askG(rc(x),mid+1,r,u,v));
}
ll askf(int x,int l,int r,int u,int v,ll k){
	if(f[x]<k||l>v||r<u) return 0;
	if(l==r) return l; int mid=l+r>>1,w; pushdw(x);
	return (w=askf(lc(x),l,mid,u,v,k))?w:askf(rc(x),mid+1,r,u,v,k);
}
ll askg(int x,int l,int r,int u,int v,ll k){
	if(g[x]>k||l>v||r<u) return 0;
	if(l==r) return l; int mid=l+r>>1,w; pushdw(x);
	return (w=askg(rc(x),mid+1,r,u,v,k))?w:askg(lc(x),l,mid,u,v,k);
}
inline ll F(int x){ return x?askF(1,1,m0,x,x):0; }
inline ll G(int x){ return x?askG(1,1,m0,x,x):0; }
int main(){
	scanf("%d%d%d",&n,&m,&m);
	for(int i=1;i<=m;i++){
		int op,l,k; ll r;
		scanf("%d%d%lld",&op,&l,&r);
		if(op==3) ++m1,p[l].push_back({m0,m1}),h[m1]=r;
		else{
			++m0,op==1?scanf("%d%d",c+m0,&k),tg[m0]=1:(scanf("%d",&k),k=-k);
			q[l].push_back({m0,k}),q[r+1].push_back({m0,-k});
		}
	} if(m0)
	for(int i=1;i<=n;i++){
		for(auto x:q[i]){ if(tg[x.first])
			updf(1,1,m0,x.first,m0,x.second);
			updg(1,1,m0,x.first,m0,x.second);
		}
		for(auto x:p[i]){
			if(!x.first) continue;
			ll w=askG(1,1,m0,1,x.first),k=w>0?0:askg(1,1,m0,1,x.first,w);
            cout<<w<<endl;
			ans[x.second]=c[askf(1,1,m0,k+1,x.first,F(x.first)-G(x.first)+G(k)+h[x.second])];
		}
	}
	for(int i=1;i<=m1;i++) printf("%d\n",ans[i]);
	return 0;
}