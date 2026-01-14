# 4th UCUP 比赛记录

队友是 @wtcqwq 和 @DrAlfred，队名叫 `maze.size() = 0`，但是被邪恶青鱼吞了变成 `maze.size` 了。

会记录比赛大体情况和我过的题以及赛后订的题。

## Stage 1: Grand Prix of Korolyov

6 题，顺序是 CDFKHE。

过 4 题吃 1 罚，直接成为队伍大爹。

赛后 9 min 过 B。

### B. Domain Compression

考虑对每对 $(u,v)$ 分别计数它出现了几次，那么要求 $u,v$ 均未被删除且 $(u,v)$ 路径上的中间点全被删除，对删点树为 $k$ 的答案贡献为： $\displaystyle \binom {k}{\operatorname{dist}(u,v)-1}2^{n-{dist}(u,v)-1}$。

发现这个东西只和 $\operatorname{dist}(u,v)$ 相关，令 $\displaystyle c_k=\sum_{1\leq u\lt v\leq n} [\operatorname{dist}(u,v)=k]$，那么 $\displaystyle ans_k=\sum_{d=1}^{k+1} c_d2^{n-d-1}\binom{k}{d}$。

这显然是卷积的形式，那么只要求出 $c_k$ 就可以了，直接点分治+卷积计算可以做到 $O(n\log^2 n)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e5+9;
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

const int gmod=3;
const int invg=Inv(gmod);
using Poly=vector<int>;

inline void NTT(Poly &f,Poly &r,int lim,int flag){
    for(int i=0;i<lim;i++) if(i<r[i]) swap(f[i],f[r[i]]);
    for(int k=1;k<lim;k<<=1){
        int len=k<<1,gn=QPow(flag>0?gmod:invg,(mod-1)/len);
        for(int i=0;i<lim;i+=len){
            for(int j=0,g=1;j<k;j++,MulAs(g,gn)){
                int tmp=Mul(f[i+j+k],g);
                f[i+j+k]=Sub(f[i+j],tmp);
                f[i+j]=Add(f[i+j],tmp);
            }
        }
    }
    if(!~flag){
        int inv=Inv(lim);
        for(int &x:f) MulAs(x,inv);
    }
}
inline Poly Conv(Poly f,Poly g){
    int len=f.size()+g.size()-1,lim=1;
    while(lim<len) lim<<=1;
    f.resize(lim,0),g.resize(lim,0);

    Poly rev(lim,0),h(lim,0);
    for(int i=0;i<lim;i++){
        rev[i]=rev[i>>1]>>1;
        if(i&1) rev[i]|=lim>>1;
    }
    NTT(f,rev,lim,1),NTT(g,rev,lim,1);
    for(int i=0;i<lim;i++) h[i]=Mul(f[i],g[i]);
    NTT(h,rev,lim,-1);

    h.resize(len,0);
    return h;
}

int fac[N],ifac[N];
inline void Init(int lim){
	fac[0]=1;
	for(int i=1;i<=lim;i++) fac[i]=Mul(fac[i-1],i);
	ifac[lim]=Inv(fac[lim]);
	for(int i=lim-1;~i;i--) ifac[i]=Mul(ifac[i+1],i+1);
}
inline int C(int n,int m){
	if(m<0||m>n) return 0;
	else return Mul(fac[n],Mul(ifac[m],ifac[n-m]));
}

const int inv2=Inv(2);
int c[N],ans[N],n;
vector<int> e[N];

int siz[N],vis[N];
inline void GetGrv(int x,int fa,int tot,int &grv){
	bool flag=0;
	siz[x]=1;
	for(int y:e[x]){
		if(vis[y]) continue ;
		if(y==fa) continue ;
		GetGrv(y,x,tot,grv);
		siz[x]+=siz[y];
		if(siz[y]>tot/2) flag=1;
	}
	if(tot-siz[x]>tot/2) flag=1;
	if(!flag) grv=x;
}
inline void GetNode(int x,int fa,vector<int> &v){
	v.push_back(x);
	for(int y:e[x]){
		if(vis[y]) continue ;
		if(y==fa) continue ;
		GetNode(y,x,v);
	}
}
int dep[N];
inline void GetDep(int x,int fa){
	if(!~fa) dep[x]=0;
	for(int y:e[x]){
		if(vis[y]) continue ;
		if(y==fa) continue ;
		dep[y]=dep[x]+1;
		GetDep(y,x);
	}
}
inline void Solve(int x,int tot,int fa,int ftot){
	GetGrv(x,-1,tot,x);
	GetGrv(x,-1,tot,x);
	vis[x]=1;
	
	vector<int> node;
	GetNode(x,-1,node);
	if(~fa){
		int tmp=0;
		for(int u:node) tmp=max(tmp,dep[u]);
		tmp<<=1;
		vector<int> f(tmp+5,0);
		for(int u:node) f[dep[u]]++;
		f=Conv(f,f);
		for(int u:node) f[dep[u]*2]--;
		for(int i=0;i<=tmp;i++) MulAs(f[i],inv2);
		for(int i=0;i<=tmp;i++) SubAs(c[i+1],f[i]);
	}
	GetDep(x,-1);
	int tmp=0;
	for(int u:node) tmp=max(tmp,dep[u]);
	tmp<<=1;
	vector<int> g(tmp+5,0);
	for(int u:node) g[dep[u]]++;
	g=Conv(g,g);
	for(int u:node) g[dep[u]*2]--;
	for(int i=0;i<=tmp;i++) MulAs(g[i],inv2);
	for(int i=0;i<=tmp;i++) AddAs(c[i+1],g[i]);

	for(int y:e[x]){
		if(vis[y]) continue ;
		Solve(y,siz[y],x,tot);
	}
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

	cin>>n;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	Init(n);
	Solve(1,n,-1,n);

	vector<int> f(n+1,0),g(n+1,0);
	for(int i=0;i<=n;i++){
		f[i]=ifac[i];
		g[i]=Mul(fac[n-i],c[i]);
	}
	vector<int> h=Conv(f,g);
	for(int i=1;i<=n-2;i++) ans[i]=Mul(Mul(fac[i],ifac[n-i-2]),h[i+2]);

	for(int i=1;i<=n;i++) cout<<ans[i]<<' ';cout<<endl;

    return 0;
}
```

### C. Staple Stable

因为 $hw\leq S$，所以 $\min(h,w)\leq \sqrt S$。然后枚举 $\min(h,w)$ 之后可以得出另一维最小划分代价，对所有方案取最小值即可。

```cpp
#include<bits/stdc++.h>

using namespace std;

signed main(){
	int T;
	cin>>T;
	while(T--){
		int n,m,s;
		cin>>n>>m>>s;

		int ans=n+m,tmp=sqrt(s);
		for(int len=1;len<=min(tmp,n);len++){
			int i=(n+len-1)/len-1;
			int t=s/len;
			if(!t) continue ;
			int c=(m+t-1)/t-1;
			ans=min(ans,i+c);
		}
		for(int len=1;len<=min(tmp,m);len++){
			int i=(m+len-1)/len-1;
			int t=s/len;
			if(!t) continue ;
			int c=(n+t-1)/t-1;
			ans=min(ans,i+c);
		}

		cout<<ans<<endl;
	}

	return 0;
}
```

### F. Yet Another MST Problem

因为这是一个排列，所以每个数只出现一次，那么从小到大枚举 $i$，将所有 $r\lt pos_i$ 或 $l\gt pos_i$ 的区间 $[l,r]$ 缩在一起，代价是 $i$，拿两个 list 就可以维护了，时间复杂度 $O(n\alpha (n))$。

```cpp
#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=3e5+9;
const int lgN=2e1;

list<int> lp,rp;
int p[N],ip[N],l[N],r[N],fa[N],n,m;
inline int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
inline void Merge(int x,int y){fa[Find(y)]=Find(x);}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>p[i],ip[p[i]]=i;
	for(int i=1;i<=m;i++) cin>>l[i]>>r[i];
	ip[n]=1e9;

	iota(fa+1,fa+m+1,1);
	
	vector<int> id(m);
	iota(id.begin(),id.end(),1);
	sort(id.begin(),id.end(),[](int i,int j){return r[i]<r[j];});
	lp=list<int>(id.begin(),id.end());
	sort(id.begin(),id.end(),[](int i,int j){return l[i]<l[j];});
	rp=list<int>(id.begin(),id.end());

	ll ans=0;
	for(int t=0;t<=n;t++){
		vector<int> tmpl;
		while(lp.size()&&r[lp.front()]<ip[t]){
			tmpl.push_back(lp.front());
			lp.pop_front();
		}
		vector<int> tmpr;
		while(rp.size()&&l[rp.back()]>ip[t]){
			tmpr.push_back(rp.back());
			rp.pop_back();
		}
		int x=0;
		if(!x&&tmpl.size()) x=tmpl.front();
		if(!x&&tmpr.size()) x=tmpr.back();
		if(!x) continue ;
		for(int y:tmpl) if(Find(x)!=Find(y)) Merge(x,y),ans+=t;
		for(int y:tmpr) if(Find(x)!=Find(y)) Merge(x,y),ans+=t;
		if(tmpl.size()) lp.push_front(tmpl.front());
		if(tmpr.size()) rp.push_back(tmpr.front());
	}

	cout<<ans<<endl;

	return 0;
}
```

### H. Misread Problem

首先题面可以转化成求一组 $x_{1\sim n}$ 使得 $\displaystyle \sum_{i=1}^n\sum_{j=1}^k|x_i-a_{i,j}|$ 最小且 $\displaystyle \sum_{i=1}^n x_i=m$。

显然 $x_i$ 取到 $x$ 的代价函数为 $\displaystyle f_{i}(x)=\sum_{j=1}^k|x-a_{i,j}|$，然后发现它是下凸的。于是考虑在 $f_i(x)$ 的取到最小值的方案上，再添加 $x_i$ 之和的限制，那么每个函数每个单位的代价可以分成 $O(k)$ 段，一共是 $O(nk)$ 段，逐步贪心地添加即可。比较蠢地用堆实现了，时间复杂度 $O(nk\log n)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=4e2+9;
const ll inf=1e18;

int a[N][N],n,m,k;
vector<ll> len[N];

signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++){
		for(int j=1;j<=n;j++) cin>>a[i][j];
	}

	ll cst=0,sum=0;
	for(int i=1;i<=n;i++){
		vector<int> tmp;
		for(int j=1;j<=k;j++) tmp.push_back(a[j][i]);
		sort(tmp.begin(),tmp.end());
		ll x=tmp[k-1>>1];
		for(int j=1;j<=k;j++) cst+=abs(a[j][i]-x);
		sum+=x;
	}
	
	for(int i=1;i<=n;i++){
		vector<int> tmp;
		for(int j=1;j<=k;j++) tmp.push_back(a[j][i]);
		sort(tmp.begin(),tmp.end());
		if(sum>m){
			for(int j=k-1>>1;~j;j--){
				if(j==(k-1>>1)) len[i].push_back(0);
				else len[i].push_back(tmp[j+1]-tmp[j]);
			}
			len[i].push_back(tmp.front());
		}else{
			for(int j=k>>1;j<k;j++){
				if(j==(k-1>>1)) len[i].push_back(0);
				else len[i].push_back(tmp[j]-tmp[j-1]);
			}
			len[i].push_back(inf);
		}
	}

	priority_queue<array<int,2>> q;
	for(int i=1;i<=n;i++) q.push({-0,i});
	while(sum!=m&&q.size()){
		int i=q.top()[1],j=-q.top()[0];
		q.pop();
		ll dlt=min(len[i][j],abs(m-sum));
		if(sum<=m) sum+=dlt;
		else sum-=dlt;
		cst+=(2ll*j-(k&1))*dlt;
		if(j+1<len[i].size()) q.push({-(j+1),i});
	}
	cst>>=1;

	cout<<cst<<endl;

	return 0;
}
```

### K. Robot Construction

首先任意时刻能凑出来的值一定是一个前缀，所以可以做以下分讨：

-   $lim\geq2a_i$：直接 $lim'\leftarrow lim-a_i$。
-   $lim\lt a_i$：低分通过，$lim'\leftarrow lim$。
-   $a_i\leq lim\lt 2a_i$：那么还不如低分通过，$lim'\leftarrow a_i-1$。

显然 $lim$ 有区间单调性，所以直接对 $l$ 扫描线，每次二分出这三段的分界点，再修改即可，时间复杂度 $O((n+q)\log n)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=3e5+9;
const ll inf=1e18;

struct Node{
	int l,r;
	ll dat,atag,ctag;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat
#define atag(x) tr[x].atag
#define ctag(x) tr[x].ctag

inline void PushUp(int x){dat(x)=max(dat(x<<1),dat(x<<1|1));}
inline void PushAdd(int x,ll k){dat(x)+=k,atag(x)+=k;}
inline void PushCov(int x,ll k){dat(x)=ctag(x)=k,atag(x)=0;}
inline void PushDown(int x){
	if(~ctag(x)) PushCov(x<<1,ctag(x)),PushCov(x<<1|1,ctag(x)),ctag(x)=-1;
	if(atag(x)) PushAdd(x<<1,atag(x)),PushAdd(x<<1|1,atag(x)),atag(x)=0;
}

inline void Build(int x,int l,int r){
	l(x)=l,r(x)=r,dat(x)=atag(x)=0,ctag(x)=-1;
	if(l(x)==r(x)) return ;
	int mid=l(x)+r(x)>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void AddVal(int x,int l,int r,ll k){
	if(l<=l(x)&&r(x)<=r) return PushAdd(x,k);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(l<=mid) AddVal(x<<1,l,r,k);
	if(r>mid) AddVal(x<<1|1,l,r,k);
	PushUp(x);
}
inline void Cover(int x,int l,int r,ll k){
	if(l<=l(x)&&r(x)<=r) return PushCov(x,k);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(l<=mid) Cover(x<<1,l,r,k);
	if(r>mid) Cover(x<<1|1,l,r,k);
	PushUp(x);
}
inline int LowerBound(int x,ll k){
	if(l(x)==r(x)) return l(x)+(dat(x)<k);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(k<=dat(x<<1)) return LowerBound(x<<1,k);
	else return LowerBound(x<<1|1,k);
}
inline ll Get(int x,int pos){
	if(l(x)==r(x)) return dat(x);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(pos<=mid) return Get(x<<1,pos);
	else return Get(x<<1|1,pos);
}
inline void Set(int x,int pos,ll k){
	if(l(x)==r(x)) return dat(x)=k,void();
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(pos<=mid) Set(x<<1,pos,k);
	else Set(x<<1|1,pos,k);
	PushUp(x);
}

int a[N],ql[N],qr[N],ans[N],n,q,d;
vector<int> qry[N];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>q>>d;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=q;i++) cin>>ql[i]>>qr[i],qry[qr[i]].push_back(i);

	Build(1,1,n);
	Cover(1,1,n,inf);
	for(int i=1;i<=n;i++){
		Set(1,i,d);
		int lp=LowerBound(1,a[i]);
		int rp=LowerBound(1,a[i]*2);
		if(rp<=n) AddVal(1,rp,n,-a[i]);
		if(lp<rp) Cover(1,lp,rp-1,a[i]-1);
		for(int j:qry[i]) ans[j]=Get(1,ql[j]);
	}

	for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

	return 0;
}
```

## Stage 2: Grand Prix of Paris

7 题，GKBFHAI，光荣成为队伍战犯。

### A. Apple Tree

首先题目条件转化之后变成树高最多是 $\sqrt{2n}$，考虑枚举中心节点 $v$，令 $c_{v,d}$ 为到 $v$ 距离恰好为 $d$ 的点的个数，那么最终答案即为 $\displaystyle \sum_{v\in V} \sum_{d=1}^{\lfloor\sqrt{2n}\rfloor} \binom{c_{v,d}}{k-1}$。

然后直接换根求 $c_{v,d}$ 即可，注意到 $\displaystyle \sum_{v\in V} siz_v$ 是 $O(n\sqrt n)$ 级别的，所以每个点暴力枚举子树内节点是可以接受的。

时间复杂度 $O(n\sqrt n)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=5e5+9;
const int B=1e3+9;
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

int fac[N],ifac[N];
inline void Init(int lim){
	fac[0]=1;
	for(int i=1;i<=lim;i++) fac[i]=Mul(fac[i-1],i);
	ifac[lim]=Inv(fac[lim]);
	for(int i=lim-1;~i;i--) ifac[i]=Mul(ifac[i+1],i+1);
}
inline int C(int n,int m){
	if(m<0||m>n) return 0;
	else return Mul(fac[n],Mul(ifac[m],ifac[n-m]));
}

vector<int> e[N];

int dep[N],fa[N],dfn[N],idfn[N],siz[N],n,k,lim,dcnt;
inline void GetDep(int x){
	dfn[x]=++dcnt;
	idfn[dcnt]=x;
	siz[x]=1;
	for(int y:e[x]){
		dep[y]=dep[x]+1;
		GetDep(y);
		siz[x]+=siz[y];
	}
}

int cnt[B<<1],ans;
inline void Work(int x){
	if(fa[x]){
		for(int i=lim;i;i--) cnt[i]=cnt[i-1];
		cnt[0]=0;
		for(int i=dfn[x];i<dfn[x]+siz[x];i++){
			int y=idfn[i];
			cnt[dep[y]-dep[x]+2]--;
			cnt[dep[y]-dep[x]]++;
		}
	}
	for(int i=1;i<=lim;i++) AddAs(ans,C(cnt[i],k-1));
	int rec[B<<1];
	memcpy(rec,cnt,sizeof cnt);
	for(int y:e[x]){
		Work(y);
		memcpy(cnt,rec,sizeof cnt);
	}
}

inline void Solve(){
	cin>>n>>k;
	for(int i=2;i<=n;i++){
		cin>>fa[i];
		e[fa[i]].push_back(i);
	}

	Init(n);
	GetDep(1);
	for(int i=1;i<=n;i++) cnt[dep[i]]++,lim=max(lim,dep[i]);
	lim<<=1;
	Work(1);
	if(k==1) ans=n;

	cout<<ans<<endl;

	for(int i=0;i<=lim;i++) cnt[i]=0;
	for(int i=1;i<=n;i++){
		dep[i]=fa[i]=dfn[i]=idfn[i]=siz[i]=0;
		e[i].clear();
	}
	dcnt=ans=lim=0;
}

signed main(){
	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}
```

### B. Balatro

棒棒糖（/**b**angbangt）题。

直接分别对 $a_i \leq 100$ 和 $b_i\leq 100$ 的数做背包，两边拼起来就可以了，时间复杂度 $O(nk^2C+k^3)$，其中 $C = 100$。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e5+9;
const int T=5e2+9;
const int K=6;
const ll inf=1e18;

ll f[K][T],g[K][T];
int a[N],b[N],n,k;

inline void Solve(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i];

	int lim=k*100;
	for(int i=0;i<=k;i++) for(int j=0;j<=lim;j++) f[i][j]=g[i][j]=-inf;
	f[0][0]=g[0][0]=0;
	for(int i=1;i<=n;i++){
		if(a[i]<=100){
			for(int j=k-1;~j;j--){
				for(int p=0;p+a[i]<=lim;p++){
					f[j+1][p+a[i]]=max(f[j+1][p+a[i]],f[j][p]+b[i]);
				}
			}
		}else{
			for(int j=k-1;~j;j--){
				for(int p=0;p+b[i]<=lim;p++){
					g[j+1][p+b[i]]=max(g[j+1][p+b[i]],g[j][p]+a[i]);
				}
			}
		}
	}

	ll ans=0;
	for(int i=0;i<=k;i++){
		vector<int> s,t;
		for(int p=0;p<=lim;p++) if(f[i][p]>=0) s.push_back(p);
		for(int q=0;q<=lim;q++) if(g[k-i][q]>=0) t.push_back(q);
		for(int p:s){
			for(int q:t){
				ans=max(ans,(f[i][p]+q)*(g[k-i][q]+p));
			}
		}
	}

	cout<<ans<<endl;

	for(int i=0;i<=k;i++) for(int j=0;j<=lim;j++) f[i][j]=g[i][j]=0;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T;
	cin>>T;
	while(T--) Solve();
	
	return 0;
}
```

### D. Digit Division

乱搞过了。

首先将 $k$ 的倍数进行字符串拼接一定也是 $k$ 的倍数，那么考虑用 $k$ 的倍数拼出一个数位和为 $k$ 的数。

注意到 $n$ 的数位和最多是 $9\lg n$，而且 $ik$ 的数位和分布的较为随机，因此猜想大概存在用两个数凑出来方案，因此预处理出 $k$ 的 $1$ 到 $2k$ 倍，离散化之后两两 exgcd 即可。

然后就过了。

```cpp
#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=2e5+9;

inline int Digit(ll k){
	int sum=0;
	while(k) sum+=k%10,k/=10;
	return sum;
}

inline void ExGCD(ll a,ll b,ll &x,ll &y){
	if(!b) return x=1,y=0,void();
	ExGCD(b,a%b,x,y);
	ll z=x;
	x=y;
	y=z-(a/b)*y;
}

inline void Solve(){
	ll k;
	cin>>k;

	map<int,ll> mp;
	for(int i=1;i<=2*k;i++){
		ll tmp=k*i,c=Digit(tmp);
		if(!mp[c]) mp[c]=tmp;
	}

	for(auto p:mp){
		for(auto q:mp){
			ll a=p.first,b=q.first,x=0,y=0,g=__gcd(a,b);
			if(k%g) continue ;
			ExGCD(a,b,x,y);
			x*=k/g,y*=k/g;
			ll ta=b/g,tb=a/g;
			if(x<0){
				ll c=(abs(x)+ta-1)/ta;
				x+=ta*c,y-=tb*c;
			}
			if(x>0){
				ll c=x/ta;
				x-=ta*c,y+=tb*c;
			}
			if(y<0) continue ;
			ll s=p.second,t=q.second;
			for(int i=1;i<=x;i++) cout<<s;
			for(int i=1;i<=y;i++) cout<<t;
			cout<<endl;
			return ;
		}
	}

	assert(0);
}

signed main(){
	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}
```

### F. Framboise 2

枚举第 $1/2$ 行最左/右边是否向左/右连了，剩下对于每一列：

-   上下都有的，贡献是 $4$。
-   只有一行有的，上下连不和已有的水平的交叉的，贡献是 $4$。
-   只有一行有的，上下连会和已有的水平的交叉的，贡献是 $2$。

乘在一起算贡献积即可，时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e6+9;
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

int x[N],y[N],cnt[N],r[N],o[N],n,k;

inline void Solve(){
	cin>>n>>k;
	for(int i=1;i<=k;i++) cin>>x[i]>>y[i],x[i]--;

	vector<int> yval(y+1,y+k+1);
	yval.push_back(-1);
	sort(yval.begin(),yval.end());
	yval.erase(unique(yval.begin(),yval.end()),yval.end());
	for(int i=1;i<=k;i++) y[i]=lower_bound(yval.begin(),yval.end(),y[i])-yval.begin();

	for(int i=1;i<=k;i++) cnt[y[i]]++;

	int l[2]={k+1,k+1},r[2]={0,0};
	for(int i=1;i<=k;i++){
		o[y[i]]|=x[i];
		l[x[i]]=min(l[x[i]],y[i]);
		r[x[i]]=max(r[x[i]],y[i]);
	}

	int ans=0;
	int t[2]={0,0};
	for(t[0]=0;t[0]<4;t[0]++){
		if((t[0]&1)&&l[0]>k) continue ;
		if((t[0]&2)&&r[0]<1) continue ;
		for(t[1]=0;t[1]<4;t[1]++){
			if((t[1]&1)&&l[1]>k) continue ;
			if((t[1]&2)&&r[1]<1) continue ;
			int res=1;
			for(int i=1;i<=k;i++){
				if(cnt[i]==2) MulAs(res,4);
				else if(cnt[i]==1){
					if((t[o[i]^1]&1)&&i<l[o[i]^1]) MulAs(res,2);
					else if((t[o[i]^1]&2)&&i>r[o[i]^1]) MulAs(res,2);
					else MulAs(res,4);
				}
			}
			AddAs(ans,res);
		}
	}

	cout<<ans<<endl;

	for(int i=1;i<=k;i++) cnt[i]=o[i]=0;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}
```

### J. JamBrains

手玩一些数据发现倒闭的一定是所有行的一个后缀，判断依据从该行的最左端向上跳 $u$ 行跨过的格子是不是超过 $r$ 个，这个拿区间加区间最小值线段树维护即可，时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e5+9;

struct Node{
	int l,r;
	ll dat,tag;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat
#define tag(x) tr[x].tag

inline void PushUp(int x){dat(x)=min(dat(x<<1),dat(x<<1|1));}
inline void Push(int x,ll k){dat(x)+=k,tag(x)+=k;}
inline void PushDown(int x){
	if(!tag(x)) return ;
	Push(x<<1,tag(x)),Push(x<<1|1,tag(x));
	tag(x)=0;
}
inline void Build(int x,int l,int r){
	l(x)=l,r(x)=r;
	if(l(x)==r(x)) return ;
	int mid=l(x)+r(x)>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Modify(int x,int l,int r,ll k){
	if(l<=l(x)&&r(x)<=r) return Push(x,k);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(l<=mid) Modify(x<<1,l,r,k);
	if(r>mid) Modify(x<<1|1,l,r,k);
	PushUp(x);
}
inline int Find(int x){
	if(l(x)==r(x)) return l(x)+(dat(x)>0);
	PushDown(x);
	if(dat(x<<1)<=0) return Find(x<<1);
	else return Find(x<<1|1);
}

int n,q,len;
ll a[N],t[N],u,r;
inline void Add(int x,ll k){while(x<=n) t[x]+=k,x+=x&-x;}
inline ll Ask(int x){ll sum=0;while(x) sum+=t[x],x&=x-1;return sum;}
inline ll Ask(int l,int r){return Ask(r)-Ask(l-1);}
inline ll Query(){return Ask(min(n,Find(1)+len-1));}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>u>>r;
	for(int i=1;i<=n;i++) cin>>a[i];
	
	len=min(u,ll(n));
	Build(1,1,n-len+1);
	for(int i=1;i<=n;i++){
		int l=max(2,i-len+1),r=min(i,n-len+1);
		Modify(1,l,r,a[i]);
		Add(i,a[i]);
	}
	Modify(1,1,n,-r);
	Modify(1,1,1,r+1);

	cout<<Query()<<endl;

	cin>>q;
	while(q--){
		int i;ll k;
		cin>>i>>k;
		int l=max(2,i-len+1),r=min(i,n-len+1);
		Modify(1,l,r,k-a[i]);
		Add(i,k-a[i]);
		a[i]=k;
		cout<<Query()<<endl;
	}

	return 0;
}
```

## Stage 3: Polar Grand Prix

5 题，CDGIK，第一次没有被【数据删除】击败。

但是我怎么胡了 3 个就写了一个啊。

### B. Christmas Tree

这题没过真的是我全责。

令 $f_{u,i,j}$ 表示当前考虑完 $u$ 子树内的贡献，$u$ 向内可以到达 $i$ 个点，并**钦定** $u$ 向内向外一共可以到达 $j$ 个点。那么对于一条 $u\leftrightarrow v$ 的边的定向可以分为以下两种转移：

-   $u\rightarrow v$：那么 $v$ 能到达的点 $u$ 也能到达，所以有 $f'_{u,i+p,j}\leftarrow f_{u,i,j}+f_{v,p,p}$。
-   $u\leftarrow v$：那么 $u$ 能到达的点 $v$ 也能到达，所以有 $f'_{u,i,j}\leftarrow f_{u,i,j}+f_{v,p,j+p}$。

最后还有 $f'_{u,i,j}\leftarrow f_{u,i,j}+ja_u$，答案是 $\displaystyle \min_{p=1}^n f_{root,p,p}$。

复杂度是书上背包的复杂度再多乘一个 $n$，即 $O(n^3)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=5e2+9;
const ll inf=1e18;

vector<int> e[N];
ll f[N][N][N],tmp[N][N],a[N];
int fa[N],siz[N],n;
inline void DFS(int x){
	siz[x]=1;
	for(int i=1;i<=n;i++) f[x][1][i]=i*a[x];
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		fa[y]=x;
		DFS(y);
		for(int i=1;i<=siz[x]+siz[y];i++){
			for(int j=1;j<=n;j++) tmp[i][j]=inf;
		}
		for(int i=1;i<=siz[x];i++){
			for(int j=1;j<=siz[y];j++){
				for(int k=1;k<=n;k++){
					if(j+k<=n) tmp[i][k]=min(tmp[i][k],f[x][i][k]+f[y][j][j+k]);
					tmp[i+j][k]=min(tmp[i+j][k],f[x][i][k]+f[y][j][j]);
				}
			}
		}
		for(int i=1;i<=siz[x]+siz[y];i++){
			for(int j=1;j<=n;j++) f[x][i][j]=tmp[i][j];
		}
		siz[x]+=siz[y];
	}
}

inline void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	
	DFS(1);
	
	ll ans=inf;
	for(int i=1;i<=n;i++) ans=min(ans,f[1][i][i]);
	
	cout<<ans<<endl;
	
	for(int i=1;i<=n;i++) e[i].clear();
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}
```

### C. Roman Numerals

按照优先级先建出笛卡尔树，那么一个点的左儿子对它的贡献系数是 $-1$，右儿子是 $1$，查询的是区间笛卡尔树的 DP 值。

直接上离线的区间笛卡尔树即可。

```cpp
#include<bits/stdc++.h>
 
using namespace std;
 
#define endl '\n'
using ll=long long;
const int N=3e5+9;
const int lgN=20;

map<string,int> id;
string s[N],t[N];
int prio[N],val[N],a[N],v[N],pos[N],ql[N],qr[N],n,m,q;
ll ans[N],cur[N];
vector<int> lq[N],rq[N];
 
int mxp[N][lgN],lg[N];
inline int Cmp(int i,int j){
	if(a[i]^a[j]) return a[i]<a[j]?j:i;
	else return i<j?i:j;
}
inline void Init(){
	lg[0]=-1;
	for(int i=1;i<=n;i++) lg[i]=lg[i>>1]+1;
	for(int i=1;i<=n;i++) mxp[i][0]=i;
	for(int k=1;k<=lg[n];k++){
		for(int i=1;i<=n-(1<<k)+1;i++) mxp[i][k]=Cmp(mxp[i][k-1],mxp[i+(1<<k-1)][k-1]);
	}
}
inline int MaxPos(int l,int r){
	int k=lg[r-l+1];
	return Cmp(mxp[l][k],mxp[r-(1<<k)+1][k]);
}

ll tr[N];
inline void Add(int x,ll k){while(x<=n) tr[x]+=k,x+=x&-x;}
inline ll Ask(int x){ll sum=0;while(x) sum+=tr[x],x&=x-1;return sum;}
inline ll Ask(int l,int r){return Ask(r)-Ask(l-1);}
inline ll F(int x){return x&1?-1:1;}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
 
	cin>>m>>n>>q;
	for(int i=1;i<=m;i++) cin>>prio[i]>>val[i]>>s[i];
	for(int i=1;i<=n;i++) cin>>t[i];
	for(int i=1;i<=q;i++) cin>>ql[i]>>qr[i];

	for(int i=1;i<=m;i++) id[s[i]]=i;
	for(int i=1;i<=n;i++) a[i]=prio[id[t[i]]],v[i]=val[id[t[i]]];
 
	Init();
	for(int i=1;i<=q;i++){
		if(ql[i]>qr[i]) continue ;
		pos[i]=MaxPos(ql[i],qr[i]);
		ans[i]=v[pos[i]];
		lq[ql[i]].push_back(i);
		rq[qr[i]].push_back(i);
	}
	
	vector<int> stk;
	for(int i=1;i<=n;i++){
		int lst=0;
		while(stk.size()&&Cmp(stk.back(),i)==i){
			Add(stk.size(),-cur[stk.back()]);
			cur[stk.back()]+=cur[lst];
			lst=stk.back();
			stk.pop_back();
		}
		cur[i]=v[i]-cur[lst];
		stk.push_back(i);
		Add(stk.size(),cur[i]);
		for(int j:rq[i]){
			int p=lower_bound(stk.begin(),stk.end(),pos[j])-stk.begin()+1;
			ans[j]+=Ask(p+1,n);
		}
	}

	stk.clear();
	for(int i=1;i<=n;i++) cur[i]=0;
	for(int i=1;i<=n;i++) tr[i]=0;

	for(int i=n;i>=1;i--){
		int lst=0;
		while(stk.size()&&Cmp(stk.back(),i)==i){
			Add(stk.size(),-(cur[stk.back()]*F(stk.size())));
			cur[stk.back()]-=cur[lst];
			lst=stk.back();
			stk.pop_back();
		}
		cur[i]=v[i]+cur[lst];
		stk.push_back(i);
		Add(stk.size(),cur[i]*F(stk.size()));
		for(int j:lq[i]){
			int p=lower_bound(stk.begin(),stk.end(),pos[j],greater<int>())-stk.begin()+1;
			ans[j]-=Ask(p+1,n)*F(p+1);
		}
	}

	for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

	return 0;
}
```

### D. Disjoint Set Splitting

考虑到答案最终一定是前面一串 1 后面都是 0，因此可以把强制在线变成离线，二分出变化的转折点即可，需要卡卡常。

或者从后往前加边好像也是可以的。

代码是队友 @DrAlfred 写的。



### G. Far Away

首先如果两个点不在一个连通块里答案就是 Yes，如果都在一个大小不超过 $2\times 10^4$ 的连通块里答案就是 No。

剩下的点随机 roll 200 个分别跑 bfs 看能不能作为中转点即可。

代码是队友 @wtcqwq 写的。

### J. One Permutation

首先，$a_k$ 是上凸的，即 $2a_k\geq a_{k-1}+a_{k+1}$。

>   证明：
>
>   考虑将原问题转化成排列 $p$ 和 $1,2,3,\ldots,n,1,2,3,\ldots,n,\ldots,1,2,3,\ldots,n$（共 $k$ 次）的 LCS，显然该问题的答案就是 $a_k$。
>
>   那么，考虑建出经典 LCS DP 算法的自动机，即一个大小为 $nk\times n$ 的网格图，边权为 $0$ 或 $1$，原问题的答案在这个图上体现为从左上到右下的最长路。
>
>   将 $n(k-1)\times n$ 的网格图和 $n(k+1)\times n$ 的网格图重叠在一起，使他们共用一个中心，那么这两条路径必然相交。通过重新划分这两条路径，我们得到了两条 $nk\times n$ 的网格图上的路径，而他们的长度显然不大于 $a_k$。
>
>   因此，$a_{k-1}+a_{k+1}\leq 2a_k$。

然后我们对每种斜率 $\lambda$ 考察其作用域。

-   对于 $\lambda \leq \sqrt n$，我们可以通过 wqs 二分的套路找出凸壳上斜率大于等于 $\lambda$ 的最右侧的点。
-   对于 $\lambda \gt \sqrt n$，我们知道，最多只有 $O(n\lambda^{-1})$ 个整点的斜率是大于等于 $\lambda$ 的，换言之，这个情况下的斜率只会出现在最左侧的 $\sqrt n$ 个点上，二分找出他们即可。

时间复杂度 $O(n\sqrt n\log n)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e5+9;

int p[N],n;

array<ll,2> tr[N];
inline void Add(int x,array<ll,2> k){while(x<=n) tr[x]=max(tr[x],k),x+=x&-x;}
inline array<ll,2> Ask(int x){array<ll,2> res={0,0};while(x) res=max(res,tr[x]),x&=x-1;return res;}
inline void Clear(){for(int i=1;i<=n;i++) tr[i]={0,0};}

inline int GetP(int k){
	for(int i=1;i<=n;i++){
		array<ll,2> s=Ask(p[i]),t=Ask(n);
		Add(p[i],{s[0]+1,s[1]});
		Add(p[i],{t[0]+1-k,t[1]+1});
	}
	array<ll,2> s=Ask(n);
	Clear();
	return s[1]+1;
}

int k[N],f[N];
inline void Work(int l,int r){
	if(l>r) return ;
	if(k[l-1]==k[r+1]){
		for(int i=l;i<=r;i++) k[i]=k[l-1];
		return ;
	}
	int mid=l+r>>1;
	k[mid]=GetP(mid);
	Work(l,mid-1),Work(mid+1,r);
}

inline void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>p[i];

	k[0]=n+1,k[n+1]=0;
	Work(1,n);
	for(int i=0;i<n;i++){
		for(int j=k[i+1];j<k[i];j++) f[j]=i;
	}
	f[n]=n;
	for(int i=n-1;i>=1;i--) f[i]=f[i+1]-f[i];

	for(int i=1;i<=n;i++) cout<<f[i]<<' ';cout<<endl;
	for(int i=0;i<=n+1;i++) f[i]=k[i]=0;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}
```

## Stage 4: Grand Prix of Chengdu

呃呃，8 题，JGABLDKC。

### C. Crossing River

首先，如果一个人的过河时间不构成瓶颈的话，是可以适当地把他的过河时间尽量向后延的。换句话说，在不影响最终答案的情况下，存在一种方式使得在两边人数充足的时候船是来回划的。因此直接从后向前贪，枚举最后船在哪侧，剩下的就是按题意模拟。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e5+9;

int n,m,k;
array<int,2> a[N],b[N];

inline ll Calc(int op){
	ll t=0;
	int i=1,j=1,cnt=0;
	while(i<=n||j<=m){
		cnt++;
		if(op==0){
			if(i<=n){
				t=max(t,1ll*k*cnt+a[i][0]);
				i++;
			}
		}else if(op==1){
			if(j<=m){
				t=max(t,1ll*k*cnt+b[j][0]);
				j++;
			}
		}
		op^=1;
	}
	return t;
}
inline vector<array<ll,3>> Work(ll t,int op){
	vector<array<ll,3>> ans;
	int i=1,j=1,cnt=0;
	while(i<=n||j<=m){
		cnt++;
		if(op==0){
			if(i<=n){
				ans.push_back({t-1ll*k*cnt,op,a[i][1]});
				i++;
			}
		}else if(op==1){
			if(j<=m){
				ans.push_back({t-1ll*k*cnt,op,b[j][1]});
				j++;
			}
		}
		op^=1;
	}
	reverse(ans.begin(),ans.end());
	return ans;
}

inline void Solve(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++) cin>>a[i][0],a[i][1]=i;
	for(int i=1;i<=m;i++) cin>>b[i][0],b[i][1]=i;

	sort(a+1,a+n+1,greater<array<int,2>>());
	sort(b+1,b+m+1,greater<array<int,2>>());

	if(Calc(0)<Calc(1)){
		ll t=Calc(0);
		cout<<t<<endl;
		auto ans=Work(t,0);
		for(auto p:ans) cout<<p[0]<<' '<<p[1]<<' '<<p[2]<<endl;
	}else{
		ll t=Calc(1);
		cout<<t<<endl;
		auto ans=Work(t,1);
		for(auto p:ans) cout<<p[0]<<' '<<p[1]<<' '<<p[2]<<endl;
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	Solve();

	return 0;
}
```

### G. GCD of Subsets

签到题做半个小时吃两罚，是人？

首先肯定先把不是 $k$ 的全变成 $k$，再把 $k$ 的倍数逐一变成 $k$，剩下的相邻的 $k$ 的倍数相邻的两两配对，原因显然。

```cpp
#include<bits/stdc++.h>

using namespace std;

using ll=long long;

signed main(){
	int T;
	cin>>T;
	while(T--){
		ll n,m,k;
		cin>>n>>k>>m;
		m=min(m,n-1);

		ll lft=n-n/k;
		if(m<=lft) cout<<m+1+((n/k-1)/2)<<endl;
		else cout<<m+1+((n-m-1)/2)<<endl;
	}

	return 0;
}
```

### K. K-Coverage

根据题意，至多可以移动一个段，那么考虑枚举这个段，并将不移动看成是该段移动回原来的位置了。

为了方便，下文中令 $c_i$ 表示某一位置被覆盖的次数，原位置和新位置分别为 $S=[l,l+L),T=[l',l'+L)$，$\displaystyle cnt_k(S)=\sum_{x\in S}[c_x=k]$。

那么：

- 若移动到的新位置与原来位置无交：那么增长量即为 $cnt_{k+1}(S)-cnt_k(S)+cnt_{k-1}(T)-cnt_k(
    T)$。因此，只要找到和 $S$ 无交的 $cnt_{k-1}(T)-cnt_k(T)$ 最大的 $T$ 即可。
- 若移动到的新位置与原来位置于左侧有交：那么增长量为 $cnt_{k+1}(S')-cnt_k(S')+cnt_{k-1}(T')-cnt_k(
    T')$，其中 $S'=S/(S\cup T)=[l'+L,l+L),T'=T/(S\cup T)=[l',l)$。令 $w_i=[c_i=k+1]-[c_i=k]+[c_{i-L}=k-1]-[c_{i-L}=k]$，不难发现，增长量其实是 $\displaystyle\sum_{i=l'+L}^{l+L-1} w_i$。也就是说，最优的的是 $w_i$ 以 $l+L-1$ 为右端点且长度不超过 $L$ 的最大后缀和，这个可以简单维护。
- 新位置与原来位置于右侧有交和上一种情况是类似的。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=1e6+9;
const int lgN=2e1+1;

int a[N],c[N],pref[N],suff[N],posf[N],posg[N],wrg[N],n,len,k;

struct RMQ{
	int mn[N][lgN],lg[N],op;
	inline void Init(int n,int *a,int o){
		op=o;
		for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
		for(int i=0;i<=n;i++) mn[i][0]=a[i]*op;
		for(int k=1;k<=lg[n];k++){
			for(int i=0;i<=n-(1<<k)+1;i++){
				mn[i][k]=min(mn[i][k-1],mn[i+(1<<k-1)][k-1]);
			}
		}
	}
	inline int R(int l,int r){
		int k=lg[r-l+1];
		return min(mn[l][k],mn[r-(1<<k)+1][k])*op;
	}
	inline void Clear(int n){
		for(int k=0;k<=lg[n];k++){
			for(int i=0;i<=n;i++) mn[i][k]=0;
		}
		for(int i=0;i<=n;i++) lg[i]=0;
		op=0;
	}
}pmn,smx,wmx;

inline void Solve(){
	cin>>n>>len>>k;
	for(int i=1;i<=n;i++) cin>>a[i],a[i]++;

	int lim=4*n,ans=0,res=0;
	sort(a+1,a+n+1);
	for(int i=1;i<=lim;i++){
		c[i]=upper_bound(a+1,a+n+1,i)-lower_bound(a+1,a+n+1,i-len+1);
		if(c[i]==k) ans++;
	}
	for(int i=1;i<=lim;i++){
		if(i-len>=1){
			if(c[i]==k+1) pref[i]++;
			if(c[i]==k) pref[i]--;
			if(c[i-len]==k-1) pref[i]++;
			if(c[i-len]==k) pref[i]--;
		}
		if(i+len<=lim){
			if(c[i]==k+1) suff[i]++;
			if(c[i]==k) suff[i]--;
			if(c[i+len]==k-1) suff[i]++;
			if(c[i+len]==k) suff[i]--;
		}
		if(c[i]==k) posf[i]--,posg[i]--;
		if(c[i]==k+1) posf[i]++;
		if(c[i]==k-1) posg[i]++;
		pref[i]+=pref[i-1];
		suff[i]+=suff[i-1];
		posf[i]+=posf[i-1];
		posg[i]+=posg[i-1];
		if(i>=len) wrg[i]=posg[i]-posg[i-len];
	}
	wmx.Init(lim,wrg,-1);
	pmn.Init(lim,pref,1);
	smx.Init(lim,suff,-1);

	for(int i=1;i<=n;i++){
		int x=a[i];
		int spf=posf[x+len-1]-posf[x-1];
		if(x-len>=1) res=max(res,wmx.R(1,x-1)+spf);
		if(x+len+len-1<=lim) res=max(res,wmx.R(x+len+len-1,lim)+spf);
		res=max(res,pref[x+len-1]-pmn.R(x-1,x+len-1));
		res=max(res,smx.R(x-1,min(x+len-1,lim))-suff[x-1]);
	}

	cout<<ans+res<<endl;

	wmx.Clear(lim);
	pmn.Clear(lim);
	smx.Clear(lim);
	for(int i=0;i<=lim;i++) a[i]=c[i]=pref[i]=suff[i]=posf[i]=posg[i]=wrg[i]=0;
}

signed main(){
	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}
```

## Extra Stage 1: Xi'an

嘟嘟嘟，GJLMIFBK，遗憾 8 题了，死因是没写明白领域加。

### B. Beautiful Dangos

这个题是 @wtcqwq 做的前半部分（求区间），我做的后半部分（构造）。

如果可以通过调整一个区间使得答案合法，那么调整其超集也可以，因此答案具有可二分性。

判断 $[l,r]$ 是否合法，若存在 $\tt CWP$ 中的一种颜色使得：

- 令 $[l,r]$ 中的该颜色有 $+1$ 的贡献值，非该颜色有 $-1$ 的贡献值。
- 令 $l-1,r+1$ 位置上的该颜色有 $+1$ 的贡献值，非该颜色有 $0$ 的贡献值。
- $[l-1,r+1]$ 的总贡献大于 $1$。

那么 $[l,r]$ 不合法，反之则合法。

考虑如下构造：

定义一次对字符串 $s$ 插入 $t$ 次字符 $\tt A$ 的操作为：

- 如果 $s$ 中存在形如 $\tt BB$ 的子串且 $t\gt 0$，那么将其变成 $\tt BAB$，同时 $t\leftarrow t-1$。重复执行直到 $s$ 中不存在形如 $\tt BB$ 的子串或 $t\leq 0$。
- 如果 $s$ 中存在形如 $\tt BC$ 的子串且 $t\gt 0$，那么将其变成 $\tt BAC$，同时 $t\leftarrow t-1$。重复执行直到 $s$ 中不存在形如 $\tt BB$ 的子串或 $t\leq 0$。
- 将剩下的 $\tt A$ 随意插在 $s$ 当中，并尽量少产生 $\tt AA$ 子串。

那么不难发现，对于串 $\overline{s_{l-1}s_{r+1}}$ ，优先插入 $s_{l-1}$ 和 $s_{r+1}$ 在 $[l,r]$ 的出现次数次，最后插入剩下的字符并放回 $s[l-1:r+1]$，在 $[l,r]$ 合法的情况下，得到的新串即为合法构造，证明略去。

```cpp
#include<bits/stdc++.h>
#define all(x) x.begin(),x.end()
#define pb push_back
#define mp make_pair
#define dbg cerr<<"LINE "<<__LINE__<<":"
using namespace std;
const int N=2000009,inf=1e9,mod=998244353;
int n,cntc[N],cntw[N],cntp[N];
string str; 
int mn,mx;
int check(int len){
    for(int i=1;i+len-1<=n;i++){
        int j=i+len-1;
        if(i<=mn&&j>=mx) ;
        else continue;
        int cC=cntc[j]-cntc[i-1];
        int cW=cntw[j]-cntw[i-1];
        int cP=cntp[j]-cntp[i-1];
        int valc=cC-cW-cP,valw=cW-cC-cP,valp=cP-cC-cW;
        valc+=(i-1>=1&&str[i-1]=='C')+(j+1<=n&&str[j+1]=='C');
        valw+=(i-1>=1&&str[i-1]=='W')+(j+1<=n&&str[j+1]=='W');
        valp+=(i-1>=1&&str[i-1]=='P')+(j+1<=n&&str[j+1]=='P');
        if(valc<=1&&valw<=1&&valp<=1) return i;
    }
    return 0;
}
inline void Insert(string &s,int &t,char c){
	string res;
	if(t){
		res.push_back(s.front());
		for(int i=1;i<s.size();i++){
			if(s[i-1]==s[i]){
				if(t) res.push_back(c),t--;
			}
			res.push_back(s[i]);
		}
		s=res;
		res.clear();
	}
	if(t){
		res.push_back(s.front());
		for(int i=1;i<s.size();i++){
			if(s[i-1]!=c&&s[i]!=c){
				if(t) res.push_back(c),t--;
			}
			res.push_back(s[i]);
		}
		s=res;
		res.clear();
	}
	if(t){
		if(s.front()!=c){
			res.push_back(s.front());
			while(t) res.push_back(c),t--;
			for(int i=1;i<s.size();i++) res.push_back(s[i]);
			s=res;
		}else{
			for(int i=0;i+1<s.size();i++) res.push_back(s[i]);
			while(t) res.push_back(c),t--;
			res.push_back(s.back());
			s=res;
		}
	}
}
void sol(int l,int r){
	char c[3]={'C','W','P'};
	int t[3]={0,0,0};
	t[0]=cntc[r]-cntc[l-1];
	t[1]=cntw[r]-cntw[l-1];
	t[2]=cntp[r]-cntp[l-1];
	map<char,int> id;
	for(int i:{0,1,2}) id[c[i]]=i;
	string now;
	if(l==1) now.push_back('#');
	else now.push_back(str[l-1]);
	if(r==n) now.push_back('#');
	else now.push_back(str[r+1]);
	if(now.front()!='#') Insert(now,t[id[now.front()]],now.front());
	if(now.back()!='#') Insert(now,t[id[now.back()]],now.back());
	for(int i:{0,1,2}) Insert(now,t[i],c[i]);
	for(int i=l;i<=r;i++) str[i]=now[i-l+1];
}
void solve(){
    cin>>n;cin>>str;str=" "+str;
    for(int i=1;i<=n;i++){
        cntc[i]=cntc[i-1]+(str[i]=='C');
        cntw[i]=cntw[i-1]+(str[i]=='W');
        cntp[i]=cntp[i-1]+(str[i]=='P');
    }mn=n+1,mx=0;
    for(int i=2;i<=n;i++){
        if(str[i]==str[i-1]){
            mn=min(mn,i);
            mx=max(mx,i);
        }
    }
    mx--;
    if(mn==n+1&&mx==-1){
        cout<<"Beautiful\n";
        return;
    }
    int l=1,r=n;
    pair<int,int> ans={0,0};
    while(l<=r){
        int mid=(l+r)>>1;
        int g=check(mid);
        if(g){
            r=mid-1;
            ans=mp(g,g+mid-1);
        }
        else l=mid+1;
    }
    if(ans==mp(0,0)){
        cout<<"Impossible\n";
    }
    else{
		cout<<"Possible"<<endl;
        cout<<ans.first<<" "<<ans.second<<"\n";
        sol(ans.first,ans.second);
		cout<<str.substr(1)<<endl;
    }
}
int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int _; cin>>_; while(_--)
    solve();
    return 0;
}
```

### C. Catch the Monster

考虑对每个左端点判断能使区间合法的极大右端点。

通过巨量模拟，发现合法的树形态一定是毛毛虫，换句话说，删去所有叶子后剩的是若干条链，即新图不存在三度点。

因此，对于每个度数大于 $1$ 的点领域加 $1$，那么如果区间中没有权值大于 $2$ 就是合法的。

领域加可以使用小 I 神秘 bfn 科技。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=1e6+9;
const int inf=1e8;

struct Node{
	int l,r;
	int dat,tag;
}tr[N<<2];
inline void PushUp(int x){tr[x].dat=max(tr[x<<1].dat,tr[x<<1|1].dat)+tr[x].tag;}
inline void Push(int x,int k){tr[x].dat+=k,tr[x].tag+=k;}

inline void Build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r;
	if(tr[x].l==tr[x].r) return ;
	int mid=tr[x].l+tr[x].r>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Modify(int x,int l,int r,int k){
	if(l<=tr[x].l&&tr[x].r<=r) return Push(x,k);
	int mid=tr[x].l+tr[x].r>>1;
	if(l<=mid) Modify(x<<1,l,r,k);
	if(r>mid) Modify(x<<1|1,l,r,k);
	PushUp(x);
}

vector<int> e[N];
int pos[N],n,m,q;
int bfn[N],fa[N],st[N],ed[N],bcnt;
inline void BFS(int x){
	queue<int> q;
	q.push(x);
	while(q.size()){
		int x=q.front();
		q.pop();
		bfn[x]=++bcnt;
		st[x]=n,ed[x]=0;
		if(fa[x]){
			st[fa[x]]=min(st[fa[x]],bfn[x]);
			ed[fa[x]]=max(ed[fa[x]],bfn[x]);
		}
		for(int y:e[x]){
			if(bfn[y]) continue ;
			fa[y]=x;
			q.push(y);
		}
	}
}
inline void Near(int x,int k){
	if(ed[x]) Modify(1,st[x],ed[x],k);
	if(fa[x]) Modify(1,bfn[fa[x]],bfn[fa[x]],k);
}
int vis[N],d[N];
inline void Add(int u){
	vis[u]=1;
	Modify(1,bfn[u],bfn[u],inf);
	if(d[u]>1) Near(u,1);
	for(int v:e[u]){
		if(d[v]==1&&vis[v]) Near(v,1);
		d[v]++;
	}
}
inline void Del(int u){
	vis[u]=0;
	Modify(1,bfn[u],bfn[u],-inf);
	if(d[u]>1) Near(u,-1);
	for(int v:e[u]){
		d[v]--;
		if(d[v]==1&&vis[v]) Near(v,-1);
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>m>>q;
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	for(int i=1;i<=n;i++) if(!bfn[i]) BFS(i);
	Build(1,1,n);
	Modify(1,1,n,-inf);
	for(int i=1,j=0;i<=n;Del(i),i++){
		while(j<n&&tr[1].dat<3) Add(++j);
		if(tr[1].dat<3) pos[i]=j;
		else pos[i]=j-1;
	}

	for(int i=1;i<=q;i++){
		int l,r;
		cin>>l>>r;
		if(pos[l]>=r) cout<<"Yes"<<endl;
		else cout<<"No"<<endl;
	}

	return 0;
}
```

###  F. Follow the Penguins

首先偶像关系是一个基环树森林，而大手子都只会向其初始移动方向一直走下去，直到遇到自己的偶像，因此树边是好处理的。

对于环，考虑二分其第一条删去的边，如果两个构成偶像关系的大手子相向而行且距离不大于二分值，那么要么两个相遇了，要么偶像遇到了偶像的偶像，所以至少存在一个见到偶像的大手子（由此也可以知道距离最短的那对就是最早相遇的那对）。然后断边为树，剩下就是一些小分讨。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
#define int ll
using ll=long long;
const int N=5e5+9;

int a[N],to[N],in[N],vis[N],typ[N],t[N],n;
vector<int> son[N];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n;
	for(int i=1;i<=n;i++) cin>>to[i];
	for(int i=1;i<=n;i++) cin>>a[i];
	
	queue<int> q;
	for(int i=1;i<=n;i++) in[to[i]]++;
	for(int i=1;i<=n;i++) if(!in[i]) q.push(i);
	while(q.size()){
		int x=q.front();
		q.pop();
		if(!--in[to[x]]) q.push(to[x]);
	}
	
	for(int i=1;i<=n;i++) typ[i]=a[i]<a[to[i]]?1:-1;
	for(int u=1;u<=n;u++){
		if(!in[u]){
			son[to[u]].push_back(u);
		}
	}
	for(int u=1;u<=n;u++){
		if(!in[u]) continue ;
		if(vis[u]) continue ;
		int x=u;
		vector<int> v;
		while(!vis[x]){
			vis[x]=1;
			v.push_back(x);
			x=to[x];
		}
		
		int lt=0,rt=1e9+7;
		while(lt+1<rt){
			int mid=lt+rt>>1;
			
			bool flag=0;
			for(int i:v){
				if(typ[i]==typ[to[i]]) continue ;
				if(abs(a[i]-a[to[i]])<=mid) flag|=1;
			}

			if(flag) rt=mid;
			else lt=mid;
		}

		int p=-1,m=v.size();
		for(int i=0;i<v.size();i++){
			int x=v[i];
			if(typ[x]==typ[to[x]]) continue ;
			if(abs(a[x]-a[to[x]])==rt) t[x]=rt,p=i;
		}
		assert(~p);
		for(int i=(p-1+m)%m;i!=p;i=(i-1+m)%m){
			int x=v[i];
			if(t[x]) continue ;
			if(typ[x]==typ[to[x]]){
				t[x]=t[to[x]]+2*abs(a[x]-a[to[x]]);
			}else{
				t[x]=abs(a[x]-a[to[x]]);
				if(t[x]>t[to[x]]){
					t[x]=t[to[x]]+2*abs(a[x]-(a[to[x]]+typ[to[x]]*t[to[x]]));
				}
			}
		}
		for(int x:v){
			for(int y:son[x]) q.push(y);
		}
	}

	while(q.size()){
		int x=q.front();
		q.pop();
		
		if(typ[x]==typ[to[x]]){
			t[x]=t[to[x]]+2*abs(a[x]-a[to[x]]);
		}else{
			t[x]=abs(a[x]-a[to[x]]);
			if(t[x]>t[to[x]]){
				t[x]=t[to[x]]+2*abs(a[x]-(a[to[x]]+typ[to[x]]*t[to[x]]));
			}
		}
		
		for(int y:son[x]) q.push(y);
	}

	for(int i=1;i<=n;i++) cout<<t[i]<<' ';cout<<endl;

	return 0;
}
```

### L. Let's Make a Convex!

一个集合 $S$ 能拼成凸多边形的充要条件是 $\displaystyle 2\max_{x\in S} x \lt \sum_{x\in S} x$，因此排序后枚举最大值，那么可以构成答案的最小值（左端点）是一个前缀，而对于相同的 $k$，答案肯定是最大值越大越好，并且是一个区间，贪心地放置即可。

```cpp
#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=2e5+9;

int a[N],n;
ll s[N],ans[N];

signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];

		sort(a+1,a+n+1);
		for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];

		for(int i=n,j=n;i>=1;i--){
			int k=lower_bound(s,s+n+1,s[i]-2*a[i])-s-1;
			if(!~k) continue ;
			for(j=min(j,i);j>=i-k;j--) ans[j]=s[i]-s[i-j];
		}

		for(int i=1;i<=n;i++) cout<<ans[i]<<' ';cout<<endl;

		for(int i=1;i<=n;i++) ans[i]=s[i]=a[i]=0;
	}

	return 0;
}
```

## Stage 5: Grand Prix of Nanjing

嘟！最后半小时三人齐心合力做出 H！

CKFEMGIH。

### B. What, More Kangaroos?

考虑到 $ax+by+c>0,c>0$ 是一个背向 $(0,0)$ 点的半平面，于是考虑算出该半平面所控制的极角的范围，由于整点对于极角的分布是相对均匀的，因此覆盖次数最多的点 $(x,y)$ 的覆盖次数和覆盖次数最多的极角 $\theta$ 一样多。直接断环为链，求取覆盖次数最多的点即可。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ld=long double;
const int N=2e5+9;
const ld pi=acosl(-1);
const ld eps=1e-18;

int a[N],b[N],c[N],n;
ld tl[N],tr[N];

inline void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i]>>c[i];

	vector<ld> val;
	for(int i=1;i<=n;i++){
		if(!a[i]&&!b[i]) continue ;
		tr[i]=atan2l(a[i],-b[i]);
		if(tr[i]>=0) tl[i]=tr[i]-pi;
		else tl[i]=tr[i]+pi;
		tl[i]+=eps,tr[i]-=eps;
		val.push_back(tl[i]);
		val.push_back(tr[i]);
	}
	val.push_back(-pi),val.push_back(pi);

	sort(val.begin(),val.end());
	val.erase(unique(val.begin(),val.end()),val.end());

	vector<int> d(val.size()<<1,0);
	for(int i=1;i<=n;i++){
		if(!a[i]&&!b[i]) continue ;
		int l=lower_bound(val.begin(),val.end(),tl[i])-val.begin();
		int r=lower_bound(val.begin(),val.end(),tr[i])-val.begin();
		if(tl[i]<=tr[i]) d[l<<1|1]++,d[r<<1]--;
		else{
			d[l<<1|1]++,d.back()--;
			d.front()++,d[r<<1]--;
		}
	}
	partial_sum(d.begin(),d.end(),d.begin());

	cout<<*max_element(d.begin(),d.end())<<endl;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}
```

### C. Distributing Candies

long long!?

奇数无解，偶数显然 $\dfrac n2$ 和 $\dfrac n2$。

```cpp
#include<bits/stdc++.h>

using namespace std;

using ll=long long;

signed main(){
	int T;
	cin>>T;
	while(T--){
		ll n;
		cin>>n;
		if(n&1) cout<<"No"<<endl;
		else cout<<"Yes"<<endl<<n/2<<' '<<n/2<<endl;
	}

	return 0;
}
```

### E. Cyan White Tree

没过样例就交了，唐唐。

首先先拆绝对值，分讨是 $\sum w\leq \sum c$ 还是 $\sum w\gt\sum c$，贡献分别为 $3w-c$ 和 $3c-w$。上面两种情况分别是 $w-c$ 的一个前缀和一个后缀，线段树合并+启发式合并对每个值在 $\sum w-\sum c$ 处维护贡献即可。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=4e5+9;
const int inf=1e9;

struct Data{
	int f,g;
	Data(int _f=0,int _g=0){f=_f,g=_g;}
	inline friend Data operator +(Data x,Data y){return Data(max(x.f,y.f),max(x.g,y.g));};
};
struct Node{
	int lc,rc;
	Data dat;
}tr[N<<6];

int cnt;
inline int Allc(){return tr[++cnt].dat=Data(-inf,-inf),cnt;}
inline void Clear(){for(int x=1;x<=cnt;x++) tr[x].lc=tr[x].rc=0,tr[x].dat=Data(0,0);cnt=0;}
inline void PushUp(int x){
	tr[x].dat=Data(-inf,-inf);
	if(tr[x].lc) tr[x].dat=tr[x].dat+tr[tr[x].lc].dat;
	if(tr[x].rc) tr[x].dat=tr[x].dat+tr[tr[x].rc].dat;
}
inline void Insert(int &x,int L,int R,int pos,Data k){
	if(!x) x=Allc();
	if(L==R) return tr[x].dat=tr[x].dat+k,void();
	int mid=L+R>>1;
	if(pos<=mid) Insert(tr[x].lc,L,mid,pos,k);
	else Insert(tr[x].rc,mid+1,R,pos,k);
	PushUp(x);
}
inline void Merge(int &x,int y,int L,int R){
	if(!x||!y) return x|=y,void();
	if(L==R){
		tr[x].dat=tr[x].dat+tr[y].dat;
		return ;
	}
	int mid=L+R>>1;
	Merge(tr[x].lc,tr[y].lc,L,mid);
	Merge(tr[x].rc,tr[y].rc,mid+1,R);
	PushUp(x);
}
inline Data Query(int x,int L,int R,int l,int r){
	if(!x||l>r) return Data(-inf,-inf);
	if(l<=L&&R<=r) return tr[x].dat;
	int mid=L+R>>1;
	if(r<=mid) return Query(tr[x].lc,L,mid,l,r);
	else if(l>mid) return Query(tr[x].rc,mid+1,R,l,r);
	else return Query(tr[x].lc,L,mid,l,r)+Query(tr[x].rc,mid+1,R,l,r);
}

char typ[N];
int fa[N],csu[N],wsu[N],root[N],ans[N],siz[N],n;
vector<int> e[N],node[N];
inline void DFS(int x){
	siz[x]=1;
	csu[x]=csu[fa[x]],wsu[x]=wsu[fa[x]];
	if(typ[x]=='0') csu[x]++;
	else wsu[x]++;
	Insert(root[x],-n,n,csu[x]-wsu[x],Data(3*wsu[x]-csu[x],3*csu[x]-wsu[x]));
	node[x].push_back(x);
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		fa[y]=x;
		DFS(y);
		if(siz[x]<siz[y]){
			swap(root[x],root[y]);
			swap(node[x],node[y]);
			swap(siz[x],siz[y]);
		}
		for(int u:node[y]){
			int C=csu[u]-csu[x]-csu[fa[x]];
			int W=wsu[u]-wsu[x]-wsu[fa[x]];
			Data s1=Query(root[x],-n,n,W-C,n);
			ans[x]=max(ans[x],s1.f+3*W-C);
			Data s2=Query(root[x],-n,n,-n,W-C-1);
			ans[x]=max(ans[x],s2.g+3*C-W);
		}
		Merge(root[x],root[y],-n,n);
		node[x].insert(node[x].end(),node[y].begin(),node[y].end());
		node[y].clear();
		node[y].shrink_to_fit();
		siz[x]+=siz[y];
	}
}

inline void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>typ[i];
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	fill(ans+1,ans+n+1,-1);
	DFS(1);
	for(int i=1;i<=n;i++) cout<<ans[i]<<endl;

	for(int i=1;i<=n;i++){
		typ[i]=csu[i]=wsu[i]=root[i]=ans[i]=siz[i]=fa[i]=0;
		e[i].clear(),e[i].shrink_to_fit();
		node[i].clear(),node[i].shrink_to_fit();
	}
	Clear();
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}
```

### F. Bitwise And Path

考虑先使用道路重建的手法找出对每个 $w$ 会成为其最小瓶颈生成树的边，按照时间轴顺序添加即可，查询直接从高往低位贪心即可。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e3+9;
const int Q=1e6+9;
const int V=(1<<12)+9;

char op[Q];
int u[Q],v[Q],w[Q],n,q;
vector<int> e[V],g[V],o[Q];
struct DSU{
	int fa[N];
	inline void Init(int lim){iota(fa+1,fa+lim+1,1);}
	inline int Find(int x){return fa[x]==x?x:fa[x]=Find(fa[x]);}
	inline void Merge(int x,int y){fa[Find(y)]=Find(x);}
	inline bool Con(int x,int y){return Find(x)==Find(y);}
}d[V];

inline void Solve(){
	cin>>n>>q;
	for(int i=1;i<=q;i++){
		cin>>op[i]>>u[i]>>v[i];
		if(op[i]=='+') cin>>w[i],g[w[i]].push_back(i);
	}

	for(int sta=(1<<12)-1;~sta;sta--){
		for(int i=0;i<12;i++){
			if(sta>>i&1) continue ;
			int tta=sta|(1<<i);
			g[sta].insert(g[sta].begin(),e[tta].begin(),e[tta].end());
		}
		d[sta].Init(n);
		sort(g[sta].begin(),g[sta].end());
		for(int i:g[sta]){
			if(d[sta].Con(u[i],v[i])) continue ;
			d[sta].Merge(u[i],v[i]);
			o[i].push_back(sta);
			e[sta].push_back(i);
		}
		d[sta].Init(n);
	}

	ll sum=0;
	for(int i=1;i<=q;i++){
		if(op[i]=='+'){
			for(int j:o[i]) d[j].Merge(u[i],v[i]);
		}else{
			int ans=0;
			for(int j=11;~j;j--){
				if(d[ans|(1<<j)].Con(u[i],v[i])) ans|=1<<j;
			}
			if(!d[0].Con(u[i],v[i])) ans=-1;
			sum+=ans;
		}
	}
	cout<<sum<<endl;

	for(int i=0;i<(1<<12);i++) e[i].clear(),g[i].clear(),d[i].Init(n);
	for(int i=1;i<=q;i++) o[i].clear();
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}
```

### H. Pen Pineapple Apple Pen

设 $\displaystyle f(l,r)=\sum_{i=0}^{\lfloor\frac{r-l+1}2\rfloor}[s[l:l+i]=s[r-i:r]]$，$\displaystyle g(l,r)=\sum_{i=0}^{\min(l-1,n-r)}[s[l-i:l]=s[r:r+i]]$。

那么答案即为：$\displaystyle \sum_{i=1}^n\sum_{j=i+1}^ng(i,j)\sum_{p=i+1}^j\sum_{q=p+1}^j(p-i-1)f(p,q)$。

如果我们知道了所有 $f(l,r)$ 和 $g(l,r)$ 的取值，那么上式可以通过简单地拆贡献和二维数点计算。

-   $f(l,r)$ 就是 [NOI 2014] 动物园。

-   $g(l,r)$ 可以看成是 $s[r:n]$ 和 $s[1:l]$ 做 KMP 算 border 树上祖先个数。

时间复杂度 $O(n^2)$。

```cpp
#include "alfred/all"
using namespace std;
const int N = 5010;
std::string S;
m998 s1[N][N], s2[N][N];
int n, f[N][N], g[N][N], num[N], pi[N];
inline void InitF(void) {
    for (int l = 1, _n; l <= n; l++) {
        std::string s = ' ' + S.substr(l);
        s.pop_back(), _n = s.size() - 1, num[1] = 1;
        for (int i = 1; i < _n; i++) {
            int j = pi[i];
            while (j && s[i + 1] != s[j + 1]) j = pi[j];
            pi[i + 1] = (s[i + 1] == s[j + 1] ? j + 1 : 0);
        }
        for (int i = 1; i <= _n; i++) {
            num[i] = num[pi[i]] + 1;
        }
        for (int i = 1, j = 0; i <= _n; i++) {
            while (j && s[i] != s[j + 1]) j = pi[j];
            if (s[i] == s[j + 1]) j++;
            while (2 * j > i) j = pi[j];
            f[l][l + i - 1] = num[j];
        }
    }
}
inline void InitG() {
    for (int j = 1; j <= n; j++) {
        vector<int> a(n + 1, 0), b(n + 1, 0), cnt(n + 1, 0);
        int ld = j - 1;
        a[ld + 1] = 0, cnt[ld + 1] = 1;
        for (int k = 2, p = 0; ld + k <= n; k++) {
            while (p && S[ld + p + 1] != S[ld + k]) p = a[ld + p];
            if (S[ld + p + 1] == S[ld + k]) p++;
            a[ld + k] = p, cnt[ld + k] = cnt[ld + a[ld + k]] + 1;
        }
        for (int k = 1, p = 0; k <= n; k++) {
            while (p && S[ld + p + 1] != S[k]) p = a[ld + p];
            if (S[ld + p + 1] == S[k]) p++;
            b[k] = p;
        }
        for (int i = 1; i < j; i++) g[i][j] = cnt[ld + b[i]];
    }
}
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int main(int argc, char const *argv[]) {
    optimizeIO(), cin >> S;
    n = S.size(), S = '#' + S + ' ';
    InitF(), InitG();
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= n; j++) {
            s1[i][j] = s1[i + 1][j] + s1[i][j - 1] - s1[i + 1][j - 1];
            s2[i][j] = s2[i + 1][j] + s2[i][j - 1] - s2[i + 1][j - 1];
            s1[i][j] += f[i][j], s2[i][j] += m998(i - 1) * f[i][j];
        }
    }

    m998 ans = 0;
    for (int l1 = 1; l1 <= n; l1++) {
        for (int r1 = l1 + 2; r1 <= n; r1++) {
            ans += (s2[l1 + 1][r1 - 1] - l1 * s1[l1 + 1][r1 - 1]) * g[l1][r1];
        }
    }
    cout << ans << endl;
    return 0;
}
```

### J. Trajan Algorithm

猜了一手求的是存在于两个大小大于 $2$ 的点双的点。

然后就 WA on #2 了。

要特判有一个大小为 $2$ 的点双和割点相连的情况，这种时候该割点还是会被判作割点。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=1e5+9;

vector<int> e[N],stk;
vector<vector<int>> vdcc;
int dfn[N],low[N],n,m,dcnt;
inline void Tarjan(int x,int fa){
	bool flag=0;
	stk.push_back(x);
	dfn[x]=low[x]=++dcnt;
	for(int y:e[x]){
		if(y==fa) continue ;
		if(!dfn[y]){
			Tarjan(y,x);
			low[x]=min(low[x],low[y]);
			if(low[y]>=dfn[x]){
				flag=1;
				vdcc.push_back(vector<int>());
				while(stk.size()){
					int p=stk.back();
					stk.pop_back();
					vdcc.back().push_back(p);
					if(p==y) break ;
				}
				vdcc.back().push_back(x);
			}
		}else low[x]=min(low[x],dfn[y]);
	}
	if(!flag&&!~fa) vdcc.push_back({x});
}
inline void Solve(){
	cin>>n>>m;
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	for(int i=1;i<=n;i++) if(!dfn[i]) Tarjan(i,-1);

	vector<int> cnt(n+1,0),du(n+1,0);
	for(auto &v:vdcc){
		if(v.size()<=2) for(int x:v) du[x]=1;
		else for(int x:v) cnt[x]++;
	}

	bool flag=0;
	for(int x=1;x<=n;x++) if(cnt[x]>1&&!du[x]) cout<<x<<' ',flag=1;
	if(!flag) cout<<"Empty";
	cout<<endl;
	
	dcnt=0;
	for(int i=1;i<=n;i++) e[i].clear(),dfn[i]=low[i]=0;
	vdcc.clear();
	stk.clear();
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}
```

## Stage 6: Grand Prix of Shenyang

虽然没啥贡献，还是记录一下吧。

### B. Buggy Painting Software I

枚举总共创建了 $k$ 层画布，可以证明这 $k$ 层从上到下涂的分别是出现次数最多的 $k$ 种颜色，剩下的颜色直接画在画布上，透明直接擦穿画布即可，前缀和计算贡献取最小值即为答案。

```cpp
#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=5e2+9;

ll sf[N*N],sg[N*N];
int p[N][N],cnt[N*N],n,m,a,b;

inline void Solve(){
	cin>>n>>m>>a>>b;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) cin>>p[i][j],cnt[p[i][j]]++;
	}

	sort(cnt+1,cnt+n*m+1,greater<int>());
	for(int i=1;i<=n*m;i++) sf[i]=sf[i-1]+1ll*cnt[i]*(i-1)*b,sg[i]=sg[i-1]+1ll*cnt[i]*a;
	ll ans=LLONG_MAX;
	for(int k=0;k<=n*m;k++){
		ll res=1ll*cnt[0]*k*b+sf[k]+sg[n*m]-sg[k];
		ans=min(ans,res);
	}

	cout<<ans<<endl;

	for(int i=0;i<=n*m;i++) cnt[i]=sf[i]=sg[i]=0;
}

signed main(){
	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}
```

### J. The Echoes of Chronos

把区间内的所有数全部扔到 $[v,v+m]$ 上，那么答案就是最大的空白段的长度。

发现如果没有 $[v,v+m]$ 的限制就是秃子酋长，尝试继续用只删莫队维护区间最大空白段长度。

考虑对值域分块，每块块内维护最大空白段以及块内出现的极左极右位置，由于块内答案只增，故可以简单地使用链表维护，而块间答案则可以在询问时记录上一个出现的位置，暴力计算块间答案。

时间复杂度 $O(n\sqrt n+n\sqrt q+q\sqrt n)$，$n$ 和 $q$ 同阶，可视为 $O(n\sqrt n)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=4e5+9;
const int T=7e2+9;
inline void ChMax(int &x,int y){if(y>x) x=y;}

vector<int> val;
int a[N],ql[N],qr[N],qv[N],vl[N],vr[N],n,q,m,v,h;

int cnt;
namespace Block{
	int ocr[N<<1],blk[N<<1],L[T],R[T],B;
	inline void InitBlock(){
		B=sqrt(v);
		for(int i=1;i<=v;i++) blk[i]=(i-1)/B+1;
		for(int i=1;i<=v;i++) R[blk[i]]=i;
		for(int i=v;i>=1;i--) L[blk[i]]=i;
	}
	pair<int*,int> rcll[N];
	int cl[T],cr[T],res[T],pre[N],suc[N],top;
	inline void Build(){
		for(int x=1;x<=blk[v];x++){
			cr[x]=0;
			for(int i=L[x];i<=R[x];i++){
				if(!ocr[i]) continue ;
				pre[i]=cr[x],suc[cr[x]]=i,cr[x]=i;
				if(pre[i]) ChMax(res[x],val[i]-val[pre[i]]);
				else cl[x]=i;
			}
			pre[cl[x]]=suc[cr[x]]=0;
		}
	}
	inline void Del(int i){
		cnt++;
		if(--ocr[i]) return ;
		int x=blk[i];
		if(!pre[i]) cl[x]=suc[i];
		else suc[pre[i]]=suc[i];
		if(!suc[i]) cr[x]=pre[i];
		else pre[suc[i]]=pre[i];
		if(pre[i]&&suc[i]) ChMax(res[x],val[suc[i]]-val[pre[i]]);
	}
	inline void RDel(int i){
		rcll[++top]={&ocr[i],ocr[i]};
		if(--ocr[i]) return ;
		int x=blk[i];
		if(!pre[i]) rcll[++top]={&cl[x],cl[x]},cl[x]=suc[i];
		else rcll[++top]={&suc[pre[i]],suc[pre[i]]},suc[pre[i]]=suc[i];
		if(!suc[i]) rcll[++top]={&cr[x],cr[x]},cr[x]=pre[i];
		else rcll[++top]={&pre[suc[i]],pre[suc[i]]},pre[suc[i]]=pre[i];
		if(pre[i]&&suc[i]){
			rcll[++top]={&res[x],res[x]};
			ChMax(res[x],val[suc[i]]-val[pre[i]]);
		}
	}
	inline void Recall(){
		while(top){
			*rcll[top].first=rcll[top].second;
			top--;
		}
	}
	inline array<int,3> Buery(int l,int r,int nl=0,int nr=0,int ans=0){
		for(int i=l;i<=r;i++){
			if(!ocr[i]) continue ;
			if(nr) ChMax(ans,val[i]-val[nr]);
			else nl=i;
			nr=i;
		}
		return {nl,nr,ans};
	}
	inline array<int,3> Query(int l,int r){
		if(blk[l]==blk[r]) return Buery(l,r);
		array<int,3> tmp=Buery(l,R[blk[l]]);
		int nl=tmp[0],nr=tmp[1],ans=tmp[2];
		for(int i=blk[l]+1;i<blk[r];i++){
			if(!cl[i]) continue ;
			if(nr) ChMax(ans,val[cl[i]]-val[nr]);
			else nl=cl[i];
			ChMax(ans,res[i]);
			nr=cr[i];
		}
		return Buery(L[blk[r]],r,nl,nr,ans);
	}
	inline void Clear(){
		for(int i=0;i<=v;i++) pre[i]=suc[i]=ocr[i]=0;
		for(int i=0;i<=blk[v];i++) cl[i]=cr[i]=res[i]=0;
	}
}
namespace MoAlgo{
	int blk[N<<1],L[T],R[T],B;
	inline void Init(){
		B=sqrt(q);
		for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
		for(int i=1;i<=n;i++) R[blk[i]]=i;
		for(int i=n;i>=1;i--) L[blk[i]]=i;
	}
	int ans[N];
	vector<int> qry[T];
	inline void MoAlgo(){
		Init();
		Block::InitBlock();
		for(int i=1;i<=q;i++) qry[blk[ql[i]]].push_back(i);
		for(int i=1;i<=blk[n];i++){
			sort(qry[i].begin(),qry[i].end(),[](int x,int y){return qr[x]>qr[y];});
			int l=L[i],r=n;
			for(int j=l;j<=r;j++) Block::ocr[a[j]]++,Block::ocr[a[j]+h]++;
			Block::Build();
			vector<array<int,2>> p;
			for(int j=L[i];j<=R[i];j++) p.push_back({a[j],j}),p.push_back({a[j]+h,j});
			sort(p.begin(),p.end());
			for(int j:qry[i]){
				if(blk[ql[j]]==blk[qr[j]]){
					int nl=0,nr=0;
					for(auto t:p){
						if(t[1]<ql[j]||t[1]>qr[j]) continue ;
						if(t[0]<vl[j]||t[0]>vr[j]) continue ;
						if(nr) ChMax(ans[j],val[t[0]]-val[nr]);
						else nl=t[0];
						nr=t[0];
					}
					if(nl) ChMax(ans[j],val[nl]-qv[j]);
					if(nr) ChMax(ans[j],qv[j]+m-val[nr]);
					continue ;
				}
				while(r>qr[j]) Block::Del(a[r]),Block::Del(a[r]+h),r--;
				while(l<ql[j]) Block::RDel(a[l]),Block::RDel(a[l]+h),l++;
				auto tmp=Block::Query(vl[j],vr[j]);
				int nl=tmp[0],nr=tmp[1];
				ans[j]=tmp[2];
				if(nl) ChMax(ans[j],val[nl]-qv[j]);
				if(nr) ChMax(ans[j],qv[j]+m-val[nr]);
				Block::Recall();
				l=L[i];
			}
			Block::Clear();
		}
	}
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>q>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=q;i++) cin>>ql[i]>>qr[i]>>qv[i];

	val.push_back({-1});
	for(int i=1;i<=n;i++) val.push_back(a[i]),val.push_back(a[i]+m);
	sort(val.begin(),val.end());
	val.erase(unique(val.begin(),val.end()),val.end());
	v=val.size()-1,h=v>>1;
	for(int i=1;i<=n;i++) a[i]=lower_bound(val.begin(),val.end(),a[i])-val.begin();
	for(int i=1;i<=q;i++){
		vl[i]=lower_bound(val.begin(),val.end(),qv[i])-val.begin();
		vr[i]=upper_bound(val.begin(),val.end(),qv[i]+m)-val.begin()-1;
	}

	MoAlgo::MoAlgo();

	for(int i=1;i<=q;i++) cout<<m-MoAlgo::ans[i]<<endl;

	return 0;
}
```

