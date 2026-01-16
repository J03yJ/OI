## 题目整理

### [IOI 2020] Tickets

一轮中选取让代价最小的 $b$ 相当于选取的是 $a_i$ 的中位数。

由于 $n$ 是偶数，和 $b$ 有关的代价全部抵消，相当于代价是 $\displaystyle \sum_{i=0}^{n-1}a_i(-1)^{[i\lt \frac n2]}$。

对于 $x$ 的每一行分别考虑，相当于选出一个长度为 $L_i$ 的后缀，使得 $\displaystyle \sum_{i=0}^n L_i=\dfrac {nk}2$ 的同时 $\displaystyle \sum_{i=0}^{n-1} \sum_{j=m-k+L_i}^{m-1}x_{i,j}-\sum_{i=0}^{n-1} \sum_{j=0}^{L_i-1}x_{i,j}$ 最大，以及需要保证 $\displaystyle \bigcap_{i=0}^{n-1} [x_{i,L_i-1},x_{i,m-k+L_i}]\neq \varnothing$。以上的 $x_i$ 全部都是升序排序后的结果。

不难想到先令 $L_i$ 全部都为 $k$，然后超级钢琴，随便分析一下凸性应该就可以证明其正确性，时间复杂度 $O(n^2\log n)$。

构造方案是简单的。

```cpp
#include<bits/stdc++.h>
#include"tickets.h"

using namespace std;

using ll=long long;

ll find_maximum(int k,vector<vector<int>> a){
	int n=a.size(),m=a[0].size();
	vector<vector<ll>> s(n);
	vector<vector<int>> p(n);
	for(int i=0;i<n;i++){
		p[i].resize(m);
		iota(p[i].begin(),p[i].end(),0);
		sort(p[i].begin(),p[i].end(),[&](int x,int y){return a[i][x]<a[i][y];});
		s[i].resize(m);
		for(int j=0;j<m;j++) s[i][j]=(j?s[i][j-1]:0)+a[i][p[i][j]];
	}
	auto Sum=[&](int i,int l,int r){return (r<0?0:s[i][r])-(l>0?s[i][l-1]:0);};
	auto W=[&](int i,int t){return Sum(i,m-k+t,m-1)-Sum(i,0,t-1);};
	
	ll ans=0;
	vector<int> len(n,k);
	priority_queue<pair<ll,int>> q;
	for(int i=0;i<n;i++){
		ans+=W(i,len[i]);
		q.push({W(i,len[i]-1)-W(i,len[i]),i});
	}
	for(int o=0;o<(n/2)*k;o++){
		int i=q.top().second;
		ans+=q.top().first;
		q.pop();
		if(--len[i]) q.push({W(i,len[i]-1)-W(i,len[i]),i});
	}

	vector<vector<int>> b(n);
	vector<array<int,2>> lp,rp;
	int lc=k-1,rc=0;
	auto Allc=[&](){return lc=(lc+1)%k;};
	auto Arrc=[&](){return rc=(rc+k-1)%k;};
	for(int i=0;i<n;i++){
		b[i].resize(m,-1);
		for(int j=0;j<len[i];j++) b[i][p[i][j]]=Allc();
		for(int j=m-k+len[i];j<m;j++) b[i][p[i][j]]=Arrc();
	}
	allocate_tickets(b);

	return ans;
}
```

### [IOI 2020] Plants

先思考特殊性质，即 $2k>n$。

在这种情况下意味着 $x\rightarrow y$ 或 $y\rightarrow x$ 是被记录在 $r$ 当中的。考虑从大到小放数，那么最大值的位置 $i$ 必须满足 $r_i=0$ 且任意 $(i-j)\bmod n\lt k$ 的 $j$ 都有 $r_j\neq 0$。找到之后删去再重复这个过程即可。

考虑把这个做法搬到 $k$ 任意的情况，根据这个做法我们还是可以找到一组合法解 $a$。

有性质：对于任意两组合法解 $a,b$，有 $\forall 0\leq i\lt n,0\leq\Delta\lt k,[a_i<a_{i+\Delta}]=[b_i\lt b_{i+\Delta}]$。证明考虑把所有 $(i,i+\Delta)$ 的边建出来，方向从大的指向小的，那么上述过程相当于拓扑排序。$i$ 如果是 $0$ 度点 $i$ 必须满足 $r_i=0$ 且任意 $(i-j)\bmod n\lt k$ 的 $j$ 都有 $r_j\neq 0$。证明考虑前半部分相当于不存在 $i+\Delta \rightarrow i$ 的边，而后半部分考虑反证，可以得出不存在 $i-\Delta\rightarrow i$ 的边。因此，合法解存在的情况只有 $0$ 度点之间删边顺序不同的情况，而 $i$ 和 $i+\Delta$ 不可能同时为 $0$ 度点，故得证。

因此如果 $x$ 和 $y$ 之间存在大小关系，那么 $x$ 到 $y$ 之间一定包含了一条由大于号或小于号构成的链。考虑处理出每个点后面 $k-1$ 个点中与其 $a$ 差异最小的点，查询时从 $a_x$ 倍增到 $a_y$，检查跨过的距离是否超过 $x,y$ 之间的距离即可。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#include"plants.h"

using namespace std;

using ll=long long;
const int N=2e5+9;
const int lgN=2e1;
const int inf=1e9+7;

namespace Seg1{
	struct Data{
		int mn,l,r,p,len;
		Data(){}
		Data(int _mn,int _l,int _r,int _p,int _len){
			mn=_mn,l=_l,r=_r,p=_p,len=_len;
		}
		inline friend Data operator +(Data x,Data y){
			if(x.mn!=y.mn) return x.mn<y.mn?x:y;
			Data z(x.mn,x.l,y.r,y.l,y.l-x.r);
			if(x.len>z.len) z.len=x.len,z.p=x.p;
			if(y.len>z.len) z.len=y.len,z.p=y.p;
			return z;
		}
	};
	struct Node{
		int l,r,tag;
		Data dat;
	}tr[N<<2];
	inline void PushUp(int x){tr[x].dat=tr[x<<1].dat+tr[x<<1|1].dat;}
	inline void Push(int x,int k){tr[x].dat.mn+=k,tr[x].tag+=k;}
	inline void PushDown(int x){
		if(!tr[x].tag) return ;
		Push(x<<1,tr[x].tag),Push(x<<1|1,tr[x].tag);
		tr[x].tag=0;
	}
	inline void Build(int x,int l,int r,vector<int> &v){
		tr[x].l=l,tr[x].r=r,tr[x].tag=0;
		if(tr[x].l==tr[x].r) return tr[x].dat=Data(v[l],l,l,-1,-1),void();
		int mid=tr[x].l+tr[x].r>>1;
		Build(x<<1,l,mid,v),Build(x<<1|1,mid+1,r,v);
		PushUp(x);
	}
	inline void Modify(int x,int l,int r,int k){
		if(l<=tr[x].l&&tr[x].r<=r) return Push(x,k);
		PushDown(x);
		int mid=tr[x].l+tr[x].r>>1;
		if(l<=mid) Modify(x<<1,l,r,k);
		if(r>mid) Modify(x<<1|1,l,r,k);
		PushUp(x);
	}
}
struct Seg2{
	struct Node{
		int l,r,dat;
	}tr[N<<2];
	inline void PushUp(int x){tr[x].dat=max(tr[x<<1].dat,tr[x<<1|1].dat);}
	inline void Build(int x,int l,int r,int k){
		tr[x].l=l,tr[x].r=r;
		if(tr[x].l==tr[x].r) return tr[x].dat=k,void();
		int mid=tr[x].l+tr[x].r>>1;
		Build(x<<1,l,mid,k),Build(x<<1|1,mid+1,r,k);
		PushUp(x);
	}
	inline void Set(int x,int pos,int k){
		if(tr[x].l==tr[x].r) return tr[x].dat=k,void();
		int mid=tr[x].l+tr[x].r>>1;
		if(pos<=mid) Set(x<<1,pos,k);
		else Set(x<<1|1,pos,k);
		PushUp(x);
	}
	inline int Query(int x,int l,int r){
		if(l<=tr[x].l&&tr[x].r<=r) return tr[x].dat;
		int mid=tr[x].l+tr[x].r>>1,ans=-inf;
		if(l<=mid) ans=max(ans,Query(x<<1,l,r));
		if(r>mid) ans=max(ans,Query(x<<1|1,l,r));
		return ans;
	}
}Tmx,Tmn;

vector<int> a,ia;
int lp[lgN][N],rp[lgN][N],n,k;
ll len[lgN][N],ren[lgN][N];
void init(int _k,vector<int> r){
	n=r.size(),k=_k;
	a.resize(n),ia.resize(n);

	Seg1::Build(1,0,n-1,r);
	for(int i=n-1;~i;i--){
		Seg1::Data x=Seg1::tr[1].dat;
		x=x+Seg1::Data(x.mn,x.l+n,x.r+n,x.p+n,x.len);
		int p=x.p%n;
		a[p]=i,ia[i]=p;
		Seg1::Modify(1,p,p,inf);
		if(p-k+1>=0) Seg1::Modify(1,p-k+1,p,-1);
		else Seg1::Modify(1,0,p,-1),Seg1::Modify(1,n+p-k+1,n-1,-1);
	}

	Tmx.Build(1,0,n-1,-1);
	for(int i=0;i<n;i++){
		if(ia[i]+k-1<n) lp[0][i]=Tmx.Query(1,ia[i],ia[i]+k-1);
		else lp[0][i]=max(Tmx.Query(1,ia[i],n-1),Tmx.Query(1,0,ia[i]+k-1-n));
		Tmx.Set(1,ia[i],i);
	}
	Tmn.Build(1,0,n-1,-n);
	for(int i=n-1;~i;i--){
		if(ia[i]+k-1<n) rp[0][i]=-Tmn.Query(1,ia[i],ia[i]+k-1);
		else rp[0][i]=-max(Tmn.Query(1,ia[i],n-1),Tmn.Query(1,0,ia[i]+k-1-n));
		Tmn.Set(1,ia[i],-i);
	}

	for(int i=0;i<n;i++){
		if(lp[0][i]>=0) len[0][i]=(ia[lp[0][i]]-ia[i]+n)%n;
		if(rp[0][i]<n) ren[0][i]=(ia[rp[0][i]]-ia[i]+n)%n;
	}
	for(int k=1;k<=__lg(n);k++){
		for(int i=0;i<n;i++){
			if(lp[k-1][i]>=0){
				lp[k][i]=lp[k-1][lp[k-1][i]];
				len[k][i]=len[k-1][i]+len[k-1][lp[k-1][i]];
			}else lp[k][i]=-1;
			if(rp[k-1][i]<n){
				rp[k][i]=rp[k-1][rp[k-1][i]];
				ren[k][i]=ren[k-1][i]+ren[k-1][rp[k-1][i]];
			}else rp[k][i]=n;
		}
	}
}
inline ll LApr(int x,int y){
	ll sum=0;
	for(int k=__lg(n);~k;k--){
		if(lp[k][x]>=y) sum+=len[k][x],x=lp[k][x];
	}
	return sum+k-1;
}
inline ll RApr(int x,int y){
	ll sum=0;
	for(int k=__lg(n);~k;k--){
		if(rp[k][x]<=y) sum+=ren[k][x],x=rp[k][x];
	}
	return sum+k-1;
}
int compare_plants(int x,int y){
	int f=1;
	if(a[x]<a[y]) swap(x,y),f=-1;
	if(LApr(a[x],a[y])>=(y-x+n)%n||RApr(a[y],a[x])>=(x-y+n)%n) return f;
	else return 0;
}
```

### [RMI 2025] Engineers

首先想到枚举 $\min C_i$ 然后双指针 $\max C_i$，设其位置分别为 $i,j$。

那么答案其实就是要删去由 $[1,i)\cup (j,n]$ 构成的虚树的代价。

对于任意一棵树，可以简单地证明将其删空的代价恰为 $\lceil \frac L2 \rceil$ 其中 $L$ 为该无根树的叶子（即一度点）个数。

那么要求就是动态维护 $[1,i)\cup (j,n]$ 的叶子个数。

先随便钦定一个根，除了深度最小的节点以外的叶子可以通过判断其子树内是否由其他点判断是否为叶子，大力树剖维护即可。

而对于深度最小的节点，则可以通过计算剩下的所有点的 LCA 并判断是否严格在该点子树内。

时间复杂度 $O(n\log^2 n)$，实现没啥技术含量，纯一坨。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5+9;
const int lgN=2e1;

vector<int> e[N];
int fa[N],dep[N],siz[N],hson[N];
inline void GetHSon(int x){
	siz[x]=1,hson[x]=-1;
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		fa[y]=x;
		dep[y]=dep[x]+1;
		GetHSon(y);
		siz[x]+=siz[y];
		if(!~hson[x]||siz[y]>siz[hson[x]]) hson[x]=y;
	}
}
int top[N],dfn[N],dcnt;
inline void GetTop(int x,int t){
	top[x]=t;
	dfn[x]=dcnt++;
	if(~hson[x]) GetTop(hson[x],t);
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		if(y==hson[x]) continue ;
		GetTop(y,y);
	}
}

int elr[N<<1],pos[N],sop[N],ecnt;
inline void GetElr(int x){
	elr[ecnt]=x;
	sop[x]=pos[x]=ecnt++;
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		GetElr(y);
		elr[sop[x]=ecnt++]=x;
	}
}
int mn[N<<1][lgN],lg[N<<1];
inline void InitLCA(){
	for(int i=2;i<=ecnt;i++) lg[i]=lg[i>>1]+1;
	for(int i=0;i<ecnt;i++) mn[i][0]=pos[elr[i]];
	for(int k=1;k<=lg[ecnt];k++){
		for(int i=0;i+(1<<k)-1<ecnt;i++){
			mn[i][k]=min(mn[i][k-1],mn[i+(1<<k-1)][k-1]);
		}
	}
}
inline int LCA(int x,int y){
	x=pos[x],y=pos[y];
	if(x>y) swap(x,y);
	int k=lg[y-x+1];
	return elr[min(mn[x][k],mn[y-(1<<k)+1][k])];
}
int lca[N][lgN];
inline void InitR(int n,vector<int> &p){
	for(int i=0;i<n;i++) lca[i][0]=p[i];
	for(int k=1;k<=lg[n];k++){
		for(int i=0;i+(1<<k)-1<n;i++){
			lca[i][k]=LCA(lca[i][k-1],lca[i+(1<<k-1)][k-1]);
		}
	}
}
inline int RLCA(int l,int r){
	int k=lg[r-l+1];
	return LCA(lca[l][k],lca[r-(1<<k)+1][k]);
}

struct Node{
	int l,r,tag;
	array<int,2> dat;
}tr[N<<2];

inline array<int,2> Merge(array<int,2> x,array<int,2> y){
	if(x[0]!=y[0]) return min(x,y);
	else return {x[0],x[1]+y[1]};
}
inline void PushUp(int x){tr[x].dat=Merge(tr[x<<1].dat,tr[x<<1|1].dat);}
inline void Push(int x,int k){tr[x].dat[0]+=k,tr[x].tag+=k;}
inline void PushDown(int x){if(tr[x].tag) Push(x<<1,tr[x].tag),Push(x<<1|1,tr[x].tag),tr[x].tag=0;}

inline void Build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r,tr[x].tag=0;
	if(tr[x].l==tr[x].r) return tr[x].dat={0,1},void();
	int mid=tr[x].l+tr[x].r>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Modify(int x,int l,int r,int k){
	if(l<=tr[x].l&&tr[x].r<=r) return Push(x,k);
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(l<=mid) Modify(x<<1,l,r,k);
	if(r>mid) Modify(x<<1|1,l,r,k);
	PushUp(x);
}
inline void ModToR(int x,int k){
	while(~x){
		Modify(1,dfn[top[x]],dfn[x],k);
		x=fa[top[x]];
	}
}

int solve(int n,int d,vector<int> c,vector<int> ep,vector<int> eq){
	vector<int> p(n),ip(n);
	iota(p.begin(),p.end(),0);
	sort(p.begin(),p.end(),[&](int i,int j){return c[i]<c[j];});
	for(int i=0;i<n;i++) ip[p[i]]=i;
	for(int i=0;i<n-1;i++){
		e[ep[i]].push_back(eq[i]);
		e[eq[i]].push_back(ep[i]);
	}
	fa[0]=-1,GetHSon(0),GetTop(0,0);
	GetElr(0),InitLCA(),InitR(n,p);
	
	int ans=n;
	Build(1,0,n-1);
	for(int i=0;i<n;i++) ModToR(fa[i],1);
	for(int i=0,j=0;i<n;i++){
		while(j<n&&c[p[j]]-c[p[i]]<=d){
			Modify(1,dfn[p[j]],dfn[p[j]],1);
			ModToR(fa[p[j]],-1);
			j++;
		}
		int cnt=0,u=-1,v=-1;
		if(i) u=~u?LCA(u,RLCA(0,i-1)):RLCA(0,i-1);
		if(j<n) u=~u?LCA(u,RLCA(j,n-1)):RLCA(j,n-1);
		if(~u&&(ip[u]<i||ip[u]>=j)){
			if(ip[u]<i){
				if(ip[u]) v=~v?LCA(v,RLCA(0,ip[u]-1)):RLCA(0,ip[u]-1);
				if(ip[u]+1<i) v=~v?LCA(v,RLCA(ip[u]+1,i-1)):RLCA(ip[u]+1,i-1);
				if(j<n) v=~v?LCA(v,RLCA(j,n-1)):RLCA(j,n-1);
			}else{
				if(i) v=~v?LCA(v,RLCA(0,i-1)):RLCA(0,i-1);
				if(j<ip[u]) v=~v?LCA(v,RLCA(j,ip[u]-1)):RLCA(j,ip[u]-1);
				if(ip[u]+1<n) v=~v?LCA(v,RLCA(ip[u]+1,n-1)):RLCA(ip[u]+1,n-1);
			}
			if(~v&&pos[u]<pos[v]&&pos[v]<sop[u]) cnt++;
		}
		cnt+=tr[1].dat[0]==0?tr[1].dat[1]:0;
		ans=min(ans,cnt+1>>1);
		Modify(1,dfn[p[i]],dfn[p[i]],-1);
		ModToR(fa[p[i]],1);
	}

	return ans;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int n,d;
	cin>>n>>d;
	vector<int> c(n),ep(n-1),eq(n-1);
	for(int &x:c) cin>>x;
	for(int i=0;i<n-1;i++) cin>>ep[i]>>eq[i];

	cout<<solve(n,d,c,ep,eq)<<endl;

	return 0;
}
```

### [RMI 2025] Squirrel

首先转化成数 $A_{i,j}$ 的存活周期是 $[j,i]$，每个时刻只能选一个活着的数，问最大总值。

如果一个数 $A_{i,j}$ 没有被选上，且答案 $S$ 的子区间 $S[j:i]$ 中存在一个位置 $p$ 使得 $S_p<A_{i,j}$，那么显然可以把 $S_p$ 替换成 $A_{i,j}$。这告诉我们从大往小贪心选数是对的。

现在的问题是如何安排位置。有一个初步想法是根据 Hall 定理，某个选数方案不合法当且仅当存在一个区间 $[l,r]$ 使得 $\displaystyle \sum_{A_{i,j}\in S}[[j,i]\subseteq [l,r]]\gt r-l+1$。那么相当于维护两个数组 $a,b$，初始 $a_i=b_i=i$，每次新增区间 $[j,i]$ 就令 $a_j\leftarrow a_j-1,b_i\leftarrow b_i-1$，合法条件是 $\displaystyle \min_{0\leq l\leq r\lt n} b_r-a_{l-1}\geq 0$，这是可以用线段树维护的。时间复杂度是 $O(n^2\log n)$，看起来不是很好写，而且常数很大，不一定能过。

考虑一些更加聪明的匹配方法。令 $L_{A_i,j}=j,R_{A_{i,j}}=i$。加入某个 $v$ 时，先姑且尝试把 $v$ 插入在 $L_v$ 的位置。如果 $S_{L_v}$ 是空着的那么直接赢了。如果 $S_{L_v}$ 不是空着的，考虑从 $L_v$ 开始向后的整个非空连续段，现在需要向右扩展一格，可以从连续段中抽出几个位置接力，其中每个位置 $p_i$ 都满足 $R_{S_{p_i}}\geq p_{i+1}$，从而达到向后调整出一个空的目的，并且如果可以替换接力一定替换。同时，在插入之后可以用 $O(n)$ 的代价算出每个位置再一次成功插入所需最小的 $R$，从而 $O(1)$ 快速判断某个插入值是否合法。成功的插入只有 $O(n)$ 次，所以时间复杂度是 $O(n^2)$ 的。

正确性考虑如下证明。首先构造的答案合法性显然。现在考虑证明这样操作不会使得原来合法的答案变得不合法。在上述操作中，注意到如果 $i$ 被推到了 $t$ 处，那么 $[L_i,t)$ 处一定均有值，并且每个值的 $R$ 均不大于 $R_i$。假设有一个 $i$ 无法插入当前的答案集合，由上条性质可得当前 $L_i,R_i$ 所处的连续段 $[l,r]$ 处处都有值，若当前所有值（包括 $i$）均属于答案集合，那么 $|S'|=|[l,r]|+1\gt N(S')=|[l,r]|$。而之前已经证明大往小贪心选数是对的，所以由 Hall 定理可知矛盾，因此正确性得证。

```cpp
#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=2e3+9;

void solve(int n,vector<vector<int>> a,ll &ans,vector<int> &sol){
	int lim=n*(n+1)/2;
	vector<int> l(lim+1,0),r(lim+1,0);
	for(int i=0;i<n;i++){
		for(int j=0;j<=i;j++){
			l[a[i][j]]=j;
			r[a[i][j]]=i;
		}
	}

	ans=0;
	sol.resize(n,0);
	vector<int> req(n);
	iota(req.begin(),req.end(),0);
	for(int i=lim;i>=1;i--){
		if(r[i]>=req[l[i]]){
			ans+=i;
			int val=i,p=l[i];
			while(sol[p]){
				if(r[val]<r[sol[p]]) swap(val,sol[p]);
				p++;
			}
			sol[p]=val;
			for(int j=n-1;~j;j--){
				if(!sol[j]) req[j]=j;
				else{
					req[j]=j+1<n?req[j+1]:n;
					if(r[sol[j]]>=req[j]) req[j]=j;
				}
			}
		}
	}
}

signed main(){
	int n;
	cin>>n;
	vector<vector<int>> a(n);
	for(int i=0;i<n;i++){
		a[i].resize(i+1);
		for(int &x:a[i]) cin>>x;
	}
	
	ll ans=0;
	vector<int> sol;
	solve(n,a,ans,sol);

	cout<<ans<<endl;
	for(int i=0;i<n;i++) cout<<sol[i]<<' ';cout<<endl;

	return 0;
}
```

### [RMI 2025] Cheap-AI

唉我可能确实不会做这种题。

设 $f(L)$ 表示 token 长度为 $L$ 时至多可以选出多少个位置，显然有单调性。

考虑到 $f(L)\leq \lfloor\dfrac nL\rfloor$，因此 $f$ 总共只有 $O(\sqrt n)$ 中不同的点值。

考虑如何计算 $f$ 单点点值。可以根据 $s[i:i+L-1]$ 将 $[L,n]$ 划分成若干等价类，每个等价类从左向右贪心。特别的，等价类在后缀数组上构成若干个无交的连续段，因此不需要额外非常数的代价记录和维护等价类，即可以做到 $O(n)$ 计算 $f$ 单点值。

因此配合分治可以做到 $O(n\sqrt n\log n)$，常数非常小，直接飞过去了。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5+9;

int sa[N],rk[N<<1],lsa[N],lrk[N<<1],cnt[N],h[N],n;

inline void CalcSA(string &s){
	n=s.size(),s=" "+s;

	for(int i=1;i<=n;i++) cnt[rk[i]=s[i]]++;
	for(int i=1;i<128;i++) cnt[i]+=cnt[i-1];
	for(int i=n;i>=1;i--) sa[cnt[rk[i]]--]=i;
	for(int i=0;i<128;i++) cnt[i]=0;

	int m=0;
	for(int i=1;i<=n;i++) lrk[i]=rk[i];
	for(int i=1;i<=n;i++){
		if(lrk[sa[i]]!=lrk[sa[i-1]]) m++;
		rk[sa[i]]=m;
	}

	for(int k=1;k<=n&&m<n;k<<=1){
		int t=0;
		for(int i=n-k+1;i<=n;i++) lsa[++t]=i;
		for(int i=1;i<=n;i++) if(sa[i]>k) lsa[++t]=sa[i]-k;

		for(int i=1;i<=n;i++) cnt[rk[lsa[i]]]++;
		for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
		for(int i=n;i>=1;i--) sa[cnt[rk[lsa[i]]]--]=lsa[i];
		for(int i=0;i<=m;i++) cnt[i]=0;

		m=0;
		for(int i=1;i<=n;i++) lrk[i]=rk[i];
		for(int i=1;i<=n;i++){
			if(lrk[sa[i]]!=lrk[sa[i-1]]||lrk[sa[i]+k]!=lrk[sa[i-1]+k]) m++;
			rk[sa[i]]=m;
		}
	}

	for(int i=1,k=0;i<=n;i++){
		if(k) k--;
		while(s[i+k]==s[sa[rk[i]-1]+k]) k++;
		h[rk[i]]=k;
	}
}

int f[N],g[N],p[N],tnc[N];
inline int F(int x){
	if(x>n) return 0;
	if(x<1) return n+1;
	if(f[x]) return f[x];
	int c=0;
	g[1]=++c;
	for(int i=2;i<=n;i++){
		if(h[i]<x) c++;
		g[i]=c;
	}
	for(int i=1;i<=c;i++) tnc[i]=0,p[i]=-n;
	for(int i=1;i<=n;i++){
		if(p[g[rk[i]]]+x<=i){
			p[g[rk[i]]]=i;
			tnc[g[rk[i]]]++;
		}
	}
	return f[x]=*max_element(tnc+1,tnc+c+1);
}
inline void Conquer(int l,int r){
	if(F(l)==F(r)){
		for(int i=l;i<=r;i++) f[i]=f[l];
		return ;
	}
	int mid=l+r>>1;
	if(mid==l) return ;
	Conquer(l,mid),Conquer(mid+1,r);
}

int solve(int k,string s){
	CalcSA(s);
	Conquer(1,k);
	int ans=n;
	for(int i=1;i<=k;i++) ans=min(ans,n-F(i)*(i-1));
	return ans;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int k;
	string s;
	cin>>k>>s;

	cout<<solve(k,s)<<endl;

	return 0;
}
```

### [RMI 2025] King of Rats

考虑为啥是 $2\times n$，发现不同的联通块不共列。

故放弃直接对连通块计数，转而对连通块左右端点计数，最后除以 $2$ 即可。

考察如下 $2\times 2$ 矩形：

-   包含一个端点的：

    ```
    1 0 | 0 1 | 1 0 | 0 1 | 0 0 | 0 0
    1 0 | 0 1 | 0 0 | 0 0 | 1 0 | 0 1
    ```

-   包含两个端点的：

    ```
    1 0 | 0 1
    0 1 | 1 0
    ```

那么端点之间的计数就独立了，把每种矩形枚举一遍，剩下的 $1$ 安排的方案数直接组合数计算。因为 $k$ 很小，所以可以直接暴力计算阶乘和下降幂，时间复杂度 $O(T(k+\log n))$。

代码对相同的组合数进行了压缩。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
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
inline int Inv(int x){return QPow(x,mod-2);}

inline int B(int n,int m){
	if(m>n||m<0) return 0;
	int fac=1,res=1;
	for(int i=1;i<=m;i++) MulAs(fac,i);
	for(int i=1;i<=m;i++) MulAs(res,n-i+1);
	return Mul(res,Inv(fac));
}

void prec(int subtask_id){}
int solve(int n,int k){
	int ans=0;
	AddAs(ans,B(2*(n-1),k-2));
	AddAs(ans,Mul(2,B(2*(n-1),k-1)));
	AddAs(ans,Mul(3,Mul(n-1,B(2*(n-2),k-2))));
	AddAs(ans,Mul(2,Mul(n-1,B(2*(n-2),k-1))));
	return Mul(ans,Inv(B(2*n,k)));
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int Tid,T;
	cin>>Tid>>T;
	prec(T);
	while(T--){
		int n,k;
		cin>>n>>k;
		cout<<solve(n,k)<<endl;
	}

	return 0;
}
```

### [RMI 2025] Oranges

先从一些特殊情况开始手玩，如果叶子上没有放 kapybara，那么它的父亲一定要放，不然可以直接操作这个叶子。而且一个父亲只能有一个这样的儿子。

然后对于高度为 $2$ 的节点，如果没有 kapybara，那么其所有儿子肯定都有 kapybara，要用的时候随时调用一下即可。

因此可以看出，没有 kapybara 的点一定存在一种和有 kapybara 的点匹配的方式，即每个 kapybara 的管辖范围是一个点或一条边，管辖范围两两不交。这也是好理解的，如果管辖范围有 $3$ 个点，可以先操作到链的一段，然后随即操作另一端，那么就倒闭了。

方便起见强制一个点尽量和自己的儿子匹配，否则再尝试和父亲匹配。那么就可以直接树上背包 DP，时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=6e3+9;
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
inline int Inv(int x){return QPow(x,mod-2);}

vector<int> e[N];
int fa[N],siz[N],f[N][N][2][2],g[N][2][2];
inline void DFS(int x){
	siz[x]=1;
	f[x][1][1][0]=f[x][0][0][0]=1;
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		fa[y]=x;
		DFS(y);
		for(int i=0;i<=siz[x];i++){
			for(int j=0;j<=siz[y];j++){
				for(int p:{0,1}){
					for(int q:{0,1}){
						AddAs(g[i+j][p][1],Mul(f[x][i][p][1],f[y][j][q][1]));
						AddAs(g[i+j][p][0],Mul(f[x][i][p][0],f[y][j][q][1]));
						if(q) AddAs(g[i+j][p][1],Mul(f[x][i][p][1],f[y][j][q][0]));
						if(p^q) AddAs(g[i+j][p][1],Mul(f[x][i][p][0],f[y][j][q][0]));
						else if(p|q) AddAs(g[i+j][p][0],Mul(f[x][i][p][0],f[y][j][q][0]));
					}
				}
			}
		}
		siz[x]+=siz[y];
		for(int i=0;i<=siz[x];i++){
			for(int p:{0,1}){
				for(int q:{0,1}){
					f[x][i][p][q]=g[i][p][q];
					g[i][p][q]=0;
				}
			}
		}
	}
}

vector<int> solve(int n,vector<int> u,vector<int> v){
	for(int i=0;i<n-1;i++){
		e[u[i]].push_back(v[i]);
		e[v[i]].push_back(u[i]);
	}

	DFS(0);
	vector<int> ans(n+1,0);
	for(int i=0;i<=n;i++){
		for(int p:{0,1}) for(int q:{0,1}) if(p|q) AddAs(ans[i],f[0][i][p][q]);
	}

	return ans;
}

signed main(){
	int n;
	cin>>n;
	vector<int> u(n-1,0),v(n-1,0);
	for(int i=0;i<n-1;i++) cin>>u[i]>>v[i];

	vector<int> ans=solve(n,u,v);

	for(int x:ans) cout<<x<<' ';cout<<endl;

	return 0;
}
```
