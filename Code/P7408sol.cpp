#include<bits/stdc++.h>
#define pbk emplace_back
#define Mn(x,y) (b[x]<b[y]?x:y)
#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define ROF(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
typedef long long ll;
const int N=2e5+7,LG=18;
int n,m,l,r,k,w,u[N],C,S[N],*c=S;
struct BIT{
	ll t[N],R;
	void upd(int x,ll v){for(;x<=C;x+=x&-x)t[x]+=v;}
	ll qry(int x){for(R=0;x;x&=x-1)R+=t[x];return R;}
}K,B;
ll d[N],D,sd[N][LG+1],mx,b[N],st[N][LG+1],ans[N];
struct qry{
	int t,v,id;
	qry(int L,int V,int ID){t=L,v=V,id=ID;}
	void work(){
		int h=lower_bound(u+1,u+C,t)-u;
		ans[id]+=v*(B.qry(h)+t*K.qry(h));
	}
};
vector<qry>q[N];
void mdf(int i,ll l,ll r,int vl){
	int L=lower_bound(u+1,u+C,l=d[l]-d[i])-u,R=lower_bound(u+1,u+C,r=d[r]-d[i])-u;
	B.upd(L,-vl*l),B.upd(R,vl*r),K.upd(L,vl),K.upd(R,-vl);
}
signed main(){
	scanf("%d%d",&n,&m);
	FOR(i,2,n+1)scanf("%lld",d+i),sd[i][0]=d[i],d[i]+=d[i-1];
	// for(int i=1;i<=n;i++) cout<<d[i]<<' ';cout<<endl;
	FOR(i,1,n)scanf("%lld",b+i),st[i][0]=i;
	st[1+n][0]=1+n;
	FOR(w,1,LG)FOR(i,1<<w,1+n){
		st[i][w]=Mn(st[i][w-1],st[i-(1<<(w-1))][w-1]);
		sd[i][w]=max(sd[i][w-1],sd[i-(1<<(w-1))][w-1]);
	}
	// for(int i=1;i<=n+1;i++) cout<<d[i]<<endl;
	FOR(i,1,m){
		scanf("%d%d%d",&l,&r,u+i),k=w=r,D=0;
		ROF(j,__lg(w),0)if(w-(1<<j)>=l)D=max(D,sd[w][j]),w-=(1<<j);
		if(D>u[i]){ans[i]=-1;continue;}
		q[l].pbk(u[i],1,i),w=r;
		ROF(j,__lg(w),0)if(w-(1<<j)>=l-1&&d[r]-d[w-(1<<j)+1]<=u[i]){
			// cout<<w-(1<<j)<<endl;
			k=Mn(k,st[w][j]),w-=(1<<j);
		}
		q[k].pbk(u[i],-1,i),ans[i]=b[k]*(d[r]-d[k]);
		cout<<k<<' '<<l<<' '<<r<<' '<<b[k]<<' '<<b[1756]<<' '<<d[r]<<' '<<d[1756]<<' '<<d[r]-d[1756]<<' '<<u[i]<<endl;
	}
	sort(u+1,u+m+1),C=unique(u+1,u+m+1)-u,*c=n+1;
	ROF(i,n+1,1){
		for(;c!=S&&b[i]<b[*c];--c)mdf(i,*c,c[-1],-b[*c]);
		mdf(i,i,*c,b[i]),*(++c)=i;
		for(qry k:q[i])k.work();
	}
	// FOR(i,1,m)printf("%lld\n",ans[i]);
	return 0;
}
