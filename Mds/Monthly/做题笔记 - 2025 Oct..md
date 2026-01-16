## 题目整理

### [ABC203] G - GCD Permutation

首先套路地莫反，答案为  $\displaystyle \sum_{a=1}^n \sum_{b=1}^n \mu(a)\mu(b)\frac {f(a,b)(f(a,b)+1)}2$，其中 $f(a,b)=\sharp\{i|{a|i}\wedge b|p_i\}$。

然后出于某些原因，$\displaystyle \sum_{i=1}^n d_id_{p_i}\leq \sum_{i=1}^n d_i^2 \simeq \frac 1{\pi^2} n\log^3n+O(n\log^2n)$，所以直接暴力贡献到 $f(a,b)$ 是 $O(n\log^3 n)$ 的，可以通过。

```cpp
#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=2e5+9;

int p[N],n;
vector<int> tmp[N];

vector<int> d[N];
int ntp[N],pri[N],mu[N],phi[N],pcnt;
inline void Init(int lim){
	ntp[1]=1,mu[1]=1,phi[1]=1;
	for(int i=2;i<=lim;i++){
		if(!ntp[i]) pri[++pcnt]=i,phi[i]=i-1,mu[i]=-1;
		for(int j=1;pri[j]*i<=lim&&j<=pcnt;j++){
			ntp[pri[j]*i]=1;
			if(i%pri[j]){
				phi[pri[j]*i]=phi[pri[j]]*phi[i];
				mu[pri[j]*i]=-mu[i];
			}else{
				phi[pri[j]*i]=pri[j]*phi[i];
				mu[pri[j]*i]=0;
				break ;
			}
		}
	}
	for(int i=1;i<=lim;i++) for(int j=i;j<=lim;j+=i) d[j].push_back(i);
}


signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>p[i];

	Init(n);
	ll ans=0;
	for(int i=1;i<=n;i++){
		for(int j:d[i]){
			for(int k:d[p[i]]) tmp[j].push_back(k);
		}
	}
	for(int i=1;i<=n;i++){
		sort(tmp[i].begin(),tmp[i].end());
		int x=0,r=0;
		for(int j:tmp[i]){
			if(j!=x) x=j,r=0;
			ans+=mu[i]*mu[j]*++r;
		}
	}

	ll sum=0;
	for(int i=1;i<=n;i++) sum+=phi[i];
	ans=2*sum-ans;
	ans=1ll*n*(n+1)/2-ans;

	cout<<ans<<endl;

	return 0;
}
```

### [ARC074] E - RGB Sequence

和哪个电梯题很像来着。

记 $f_{i,j,k}$ 表示当前每个颜色最后一次出现的位置，直接转移即可，时间复杂度 $O(n^3)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=3e2+9;
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

int f[N][N][N],l[N],r[N],c[N],n,m;
vector<int> q[N];

signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>l[i]>>r[i]>>c[i],q[r[i]].push_back(i);

	int ans=0;
	f[0][0][0]=1;
	for(int i=0;i<=n;i++){
		for(int j=0;j<max(i,1);j++){
			for(int k=0;k<max(j,1);k++){
				bool err=0;
				for(int p:q[i]){
					int x=int(i>=l[p])+int(j>=l[p])+int(k>=l[p]);
					err|=x!=c[p];
				}
				if(err){
					f[i][j][k]=0;
					continue ;
				}
				AddAs(f[i+1][i][j],f[i][j][k]);
				AddAs(f[i+1][j][k],f[i][j][k]);
				AddAs(f[i+1][i][k],f[i][j][k]);
				if(i==n) AddAs(ans,f[i][j][k]);
			}
		}
	}

	cout<<ans<<endl;

	return 0;
}
```

### [ARC175] F - Making Palindrome

首先拼接方式肯定是基于某个串的~~脱水缩合~~，例如 $\tt {\color{green}dbc}{\color{blue}\underline{aba}cb}{\color{red}d}$，其中 $\tt {\color{blue}\underline{aba}}$ 是回文中心，那么只需要维护除了回文中心以外的部分继续缩就可以了。

然后不会了。

事实上，每次成功的缩合之后剩下的一定是某个串的前缀或后缀，因此可以刻画这些状态之间的转移关系，从起点状态求到终点状态的最短路即可，时间复杂度 $O(T^2)$，其中 $\displaystyle T=\sum_{i=1}^n |S_i|$。

因为一些意义不明的错误调了很久。

```cpp
#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=5e1+9;
const int M=2e3+9;
const ll inf=1e18;

int c[N],n,tot,st,ed;
string s[N];
vector<array<int,2>> e[M];

inline bool Palin(string s){
	for(int i=0;i<s.size();i++) if(s[i]!=s[s.size()-i-1]) return 0;
	return 1;
}
inline string Merge(string s,string t){
	reverse(t.begin(),t.end());
	while(s.size()&&t.size()&&s.back()==t.back()){
		s.pop_back();
		t.pop_back();
	}
	reverse(t.begin(),t.end());
	return s+t;
}

ll dis[M];
int vis[M];
inline void Dij(){
	for(int i=1;i<=tot;i++) dis[i]=inf;
	priority_queue<array<ll,2>> q;
	q.push({-(dis[st]=0),st});
	while(q.size()){
		int x=q.top()[1];
		q.pop();
		if(vis[x]) continue ;
		vis[x]=1;
		for(auto t:e[x]){
			if(dis[x]+t[1]<dis[t[0]]){
				q.push({-(dis[t[0]]=dis[x]+t[1]),t[0]});
			}
		}
	}
}

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>s[i]>>c[i];

	map<string,int> id;
	st=id[""]=++tot,ed=id["?"]=++tot;
	for(int i=1;i<=n;i++){
		for(int j=0;j<s[i].size();j++){
			string t="?"+s[i].substr(0,j+1);
			if(!id[t]) id[t]=++tot;
		}
		for(int j=0;j<s[i].size();j++){
			string t=s[i].substr(j)+"?";
			if(!id[t]) id[t]=++tot;
		}
	}
	for(int i=1;i<=n;i++){
		if(Palin(s[i])) e[st].push_back({ed,c[i]});
		for(int j=0;j<s[i].size();j++){
			string t="?"+s[i].substr(0,j+1);
			if(Palin(s[i].substr(j+1))) e[st].push_back({id[t],c[i]});
			for(int k=1;k<=n;k++){
				string r=s[k].size()>=t.size()?Merge(t.substr(1),s[k])+"?":Merge(t,s[k]);
				if(r.size()>abs(int(t.size()-1)-int(s[k].size()))+1) continue ;
				if(!id[r]) continue ;
				e[id[t]].push_back({id[r],c[k]});
			}
		}
		for(int j=0;j<s[i].size();j++){
			string t=s[i].substr(j)+"?";
			if(Palin(s[i].substr(0,j))) e[st].push_back({id[t],c[i]});
			for(int k=1;k<=n;k++){
				string r=s[k].size()>=t.size()?"?"+Merge(s[k],t.substr(0,t.size()-1)):Merge(s[k],t);
				if(r.size()>abs(int(t.size()-1)-int(s[k].size()))+1) continue ;
				if(!id[r]) continue ;
				e[id[t]].push_back({id[r],c[k]});
			}
		}
	}

	Dij();

	cout<<(dis[ed]!=inf?dis[ed]:-1)<<endl;

	return 0;
}
```



### [ARC200] D - |A + A|

呃呃怎么只能输出小于 $M$ 的数。

不难发现 $0,1,2,...$ 可以涵盖所有奇数。

不难发现 $0,2,3,...$ 可以涵盖所有 $\geq 6$ 的偶数，如果 $K = M$ 用 $0,1,..,M$ 补就可以了。

感性理解一下，$K=2/4$ 的情况大概只有 $M \bmod K =0$ 了，即等分的情况，答案是 $\{x|x\bmod K=0\}$。

```cpp
#include<bits/stdc++.h>

using namespace std;

signed main(){
	int T;
	cin>>T;
	while(T--){
		int m,k;
		cin>>m>>k;
		if(k==m){
			cout<<"Yes"<<endl;
			cout<<m<<endl;
			for(int i=0;i<m;i++) cout<<i<<' ';cout<<endl;
		}else if(k==2||k==4){
			if(m%k) cout<<"No"<<endl;
			else{
				cout<<"Yes"<<endl;
				cout<<k<<endl;
				for(int i=0;i<k;i++) cout<<i*(m/k)<<' ';cout<<endl;
			}
		}else if(k&1){
			cout<<"Yes"<<endl;
			cout<<(k+1)/2<<endl;
			for(int i=0;i<(k+1)/2;i++) cout<<i<<' ';cout<<endl;
		}else{
			cout<<"Yes"<<endl;
			cout<<k/2<<endl;
			cout<<0<<' ';
			for(int i=2;i<=k/2;i++) cout<<i<<' ';cout<<endl;
		}
	}

	return 0;
}
```

### [ARC202] C - Repunits

首先 $\gcd$ 有 $\gcd(R(i),R(j))=R(\gcd(i,j))$ 的重要性质，但是 $\operatorname {lcm}$ 没有，所以考虑对其做 gcd-lcm 容斥，即 min-max 容斥的指数形式：$\displaystyle \operatorname{lcm}(R(S)) = \prod_{T\subseteq S,T\neq \varnothing} \gcd(R(T))^{(-1)^{|T|+1}}=\prod_{x} R(x)^{\sum_{T\subseteq S,T\neq \varnothing}(-1)^{|T|+1}[\gcd(T)=x]}$。

因此，可以通过递推计算 $x$ 的指数并计算差值贡献到答案，时间复杂度 $O(n\cdot d(V)\log V)$。

然而，题解指出，可以对 $\displaystyle f(x)=\sum_{T\subseteq S,T\neq \varnothing}(-1)^{|T|+1}[\gcd(T)=x]$ 容斥：

令 $\displaystyle g(x)=\sum_{T\subseteq S,T\neq \varnothing}(-1)^{|T+1}[x|\gcd(T)]=1+\sum_{i=0}^{c_d}(-1)^{i+1}\binom{c_d}{i}=[c_d>0]$，其中 $c_d=\sharp\{x|x\in S,d|x\}$，则 $\displaystyle f(x)=\sum_{d|x} \mu(d)g(\frac dn)$。

因此，当 $c_d$ 第一次变化时，更新所有 $d$ 的倍数的 $f$ 值，时间复杂度 $O(n\ln n)$。

代码写的是本人的烂 $O(n\cdot d(V)\log V)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=2e5+9;
const int mod=998244353;

inline void AddAs(int &x,int y,int mod){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y,int mod){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y,int mod){x=1ll*x*y%mod;}
inline int Add(int x,int y,int mod){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y,int mod){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y,int mod){return 1ll*x*y%mod;}
inline int QPow(int x,int y,int mod){
	int res=1;
	while(y){
		if(y&1) MulAs(res,x,mod);
		MulAs(x,x,mod);
		y>>=1;
	}
	return res;
}
inline int Inv(int x,int mod){return QPow(x,mod-2,mod);}

vector<int> rd[N],d[N],p[N];
int ntp[N],pri[N],r[N],pcnt;
inline void Init(int lim){
	ntp[1]=1;
	for(int i=2;i<=lim;i++){
		if(!ntp[i]) pri[++pcnt]=i;
		for(int j=1;pri[j]*i<=lim&&j<=pcnt;j++){
			ntp[pri[j]*i]=1;
			if(i%pri[j]==0) break ;
		}
	}
	for(int i=1;i<=lim;i++){
		for(int j=i;j<=lim;j+=i) d[j].push_back(i);
		if(!ntp[i]) for(int j=i;j<=lim;j+=i) p[j].push_back(i);
	}
	for(int i=1;i<=lim;i++) rd[i]=d[i],reverse(rd[i].begin(),rd[i].end());
	for(int i=1;i<=lim;i++) r[i]=Add(Mul(r[i-1],10,mod),1,mod);
}

int f[N],s[N],tmp[N],a[N],n;

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];

	int cur=1;
	Init(2e5);
	for(int i=1;i<=n;i++){
		for(int k:d[a[i]]) tmp[k]=Sub(0,s[k],mod-1);
		for(int x:p[a[i]]){
			for(int k:d[a[i]]){
				if(a[i]%(x*k)==0) SubAs(tmp[k],tmp[x*k],mod-1);
			}
		}
		AddAs(tmp[a[i]],1,mod-1);
		for(int k:d[a[i]]){
			MulAs(cur,QPow(r[k],tmp[k],mod),mod);
			AddAs(f[k],tmp[k],mod-1);
		}
		for(int x:p[a[i]]){
			for(int k:rd[a[i]]){
				if(a[i]%(x*k)==0) AddAs(tmp[k],tmp[x*k],mod-1);
			}
		}
		for(int k:d[a[i]]){
			AddAs(s[k],tmp[k],mod-1);
			tmp[k]=0;
		}
		cout<<cur<<endl;
	}

	return 0;
}
```



### [ARC207] A - Affinity for Artifacts

我居然在没睡醒的情况下想明白了这个题。

首先观察 MP 消耗的代价的形式化表达，即 $\displaystyle \sum_{i=1}^N\max(A_{p_i}-(i-1),0)$。

我们要做的是对满足 $\displaystyle \sum_{i=1}^N\max(A_{p_i}-(i-1),0)\leq X$ 的排列 $p$ 计数。

形式不是很好看，令 $B_i=A_i+1$ 并移项一下：$\displaystyle \sum_{i=1}^N\max(B_{p_i},i)\leq X+\frac{n(n+1)}2$。

至此已经可以 DP 了，把数看成萝卜，位置看成坑，那么每个数只有向前填或者向后填，在知道向后的未填萝卜个数的情况下是可以推算出前面没填的坑的个数的，然后带着每个向后的未填萝卜移动一个单位都会增加一个单位的代价。

令 $f_{i,j,k}$ 表示已经考虑到第 $i$ 个位置了，已经花费了 $j$ 个单位的代价，有 $k$ 个向后的未填萝卜，状态数是 $O(n^4)$ 的，转移可以做到 $O(1)$，时间复杂度 $O(n^4)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

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
#define Inv(x) QPow(x,mod-2)

const int N=1e2+9;

int a[N],cnt[N],su[N],f[N][N*N],g[N][N*N],n,m;

signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i],a[i]++;
	
	int t=n*n;
	m+=n*(n+1)/2;
	
	int sum=0;
	for(int i=1;i<=n;i++) sum+=a[i],cnt[min(a[i],n)]++;
	for(int i=1;i<=n;i++) su[i]=su[i-1]+cnt[i];

	f[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int p=0;p<cnt[i];p++){
			for(int j=0;j<=su[i-1]+p;j++){
				int lft=(i-1)-(su[i-1]+p-j);
				for(int k=0;k<=t;k++){
					AddAs(g[j][k],Mul(lft,f[j][k]));
					AddAs(g[j+1][k],f[j][k]);
				}
			}
			memcpy(f,g,sizeof g);
			memset(g,0,sizeof g);
		}
		for(int j=0;j<=su[i];j++){
			for(int k=0;k<=t;k++){
				if(j) AddAs(g[j-1][k],Mul(j,f[j][k]));
				AddAs(g[j][k],f[j][k]);
			}
		}
		memcpy(f,g,sizeof g);
		memset(g,0,sizeof g);
		for(int j=0;j<=su[i];j++){
			for(int k=j;k<=t;k++){
				AddAs(g[j][k],f[j][k-j]);
			}
		}
		memcpy(f,g,sizeof g);
		memset(g,0,sizeof g);
	}

	int ans=0;
	for(int i=0;i<=t;i++) if(i+sum<=m) AddAs(ans,f[0][i]);

	cout<<ans<<endl;

	return 0;
}
```

### [ARC207] B - Balanced Neighbors 2

？？？

首先 $n\bmod 4=2$ 的情况直接先把 $1,2,...,n/2,n,n-1,...,n/2+1$ 连成一个环，然后每个点和除了与之相对的奇偶性不同的点连边。

然后分奇偶性往环中间加 $0/1/2/3$ 个点即可。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=2e2+9;

int n;
vector<int> e[N];

inline int Get(int u){
	vector<int> dep(n+1,0);
	dep[u]=1;
	queue<int> q;
	q.push(u);
	while(q.size()){
		int x=q.front();
		q.pop();
		for(int y:e[x]){
			if(dep[y]) continue ;
			dep[y]=dep[x]+1;
			if(dep[y]<=3) q.push(y);
		}
	}
	int sum=0;
	for(int i=1;i<=n;i++) if(dep[i]==2||dep[i]==3) sum+=i;
	return sum;
}
inline void Check(){
	vector<int> tmp;
	for(int i=1;i<=n;i++) tmp.push_back(Get(i)),cout<<i<<" : "<<tmp.back()<<endl;
	sort(tmp.begin(),tmp.end());
	if(tmp.front()!=tmp.back()) cout<<"dududu"<<endl;
}

signed main(){
	cin>>n;

	if(n<=5){
		cout<<-1<<endl;
		return 0;
	}

	vector<int> p;
	if(n%4==2){
		for(int i=1;i<=n/2;i++) p.push_back(i);
		for(int i=n;i>n/2;i--) p.push_back(i);
		for(int i=0;i<n;i++){
			for(int j=0;j<n/2;j++){
				int k=(i+1+j*2)%n;
				if(k==(i+n/2)%n) continue ;
				e[p[i]].push_back(p[k]);
				e[p[k]].push_back(p[i]);
			}
		}
	}else if(n%4==0){
		int m=n-2;
		for(int i=1;i<=n/2-1;i++) p.push_back(i);
		for(int i=n;i>n/2+1;i--) p.push_back(i);
		for(int i=0;i<m;i++){
			for(int j=0;j<m/2;j++){
				int k=(i+1+j*2)%m;
				if(k==(i+m/2)%m) continue ;
				e[p[i]].push_back(p[k]);
				e[p[k]].push_back(p[i]);
			}
		}
		for(int i=0;i<m;i+=2){
			e[p[i]].push_back(n/2);
			e[n/2].push_back(p[i]);
		}
		for(int i=1;i<m;i+=2){
			e[p[i]].push_back(n/2+1);
			e[n/2+1].push_back(p[i]);
		}
	}else if(n%4==3){
		int m=n-1;
		for(int i=1;i<=m/2;i++) p.push_back(i);
		for(int i=m;i>m/2;i--) p.push_back(i);
		for(int i=0;i<m;i++){
			for(int j=0;j<m/2;j++){
				int k=(i+1+j*2)%m;
				if(k==(i+m/2)%m) continue ;
				e[p[i]].push_back(p[k]);
				e[p[k]].push_back(p[i]);
			}
		}
		for(int i=0;i<m;i+=2){
			e[p[i]].push_back(n);
			e[n].push_back(p[i]);
		}
	}else if(n%4==1){
		int l=n-1,m=l-2;
		for(int i=1;i<=l/2-1;i++) p.push_back(i);
		for(int i=l;i>l/2+1;i--) p.push_back(i);
		for(int i=0;i<m;i++){
			for(int j=0;j<m/2;j++){
				int k=(i+1+j*2)%m;
				if(k==(i+m/2)%m) continue ;
				e[p[i]].push_back(p[k]);
				e[p[k]].push_back(p[i]);
			}
		}
		for(int i=0;i<m;i+=2){
			e[p[i]].push_back(l/2);
			e[l/2].push_back(p[i]);
		}
		for(int i=1;i<m;i+=2){
			e[p[i]].push_back(l/2+1);
			e[l/2+1].push_back(p[i]);
		}
		e[n].push_back(l/2);
		e[l/2].push_back(n);
		for(int i=1;i<m;i+=2){
			e[p[i]].push_back(n);
			e[n].push_back(p[i]);
		}
	}

	// Check();

	vector<array<int,2>> ans;
	for(int i=1;i<=n;i++){
		sort(e[i].begin(),e[i].end());
		e[i].erase(unique(e[i].begin(),e[i].end()),e[i].end());
		for(int j:e[i]) if(i<=j) ans.push_back({i,j});
	}

	cout<<ans.size()<<endl;
	for(auto t:ans) cout<<t[0]<<' '<<t[1]<<endl;

	return 0;
}
```

### [ARC207] C - Combine to Make Non-decreasing

数据结构要加训.png。

首先对于每个 $r$ 来说，本质不同的 $\displaystyle |_{i=l}^ra_i$ 只有 $O(\log V)$ 个。处理出所有的 $(l_1,l_2,r)$ 三元组，表示：对于所有在 $(l_1,l_2]$ 的 $l$ ，它们的 $\displaystyle |_{i=l}^ra_i$ 都是一样的。这样的三元组只有 $O(n\log V)$ 个。将所有的三元组按照 $\displaystyle |_{i=l}^ra_i$ 排序后直接转移即可，数据结构优化 DP 后是 $O(n\log n\log V)$ 的。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5+9;
const int T=3e1+9;
const int inf=1e9+7;

struct Node{
	int l,r;
	int dat;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat

inline void PushUp(int x){dat(x)=max(dat(x<<1),dat(x<<1|1));}
inline void Build(int x,int l,int r){
	l(x)=l,r(x)=r;
	if(l(x)==r(x)) return dat(x)=l(x)?-inf:0,void();
	int mid=l(x)+r(x)>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void ChMax(int x,int pos,int k){
	if(l(x)==r(x)) return dat(x)=max(dat(x),k),void();
	int mid=l(x)+r(x)>>1;
	if(pos<=mid) ChMax(x<<1,pos,k);
	else ChMax(x<<1|1,pos,k);
	PushUp(x);
}
inline int Query(int x,int l,int r){
	if(l<=l(x)&&r(x)<=r) return dat(x);
	int mid=l(x)+r(x)>>1;
	if(r<=mid) return Query(x<<1,l,r);
	else if(l>mid) return Query(x<<1|1,l,r);
	else return max(Query(x<<1,l,r),Query(x<<1|1,l,r));
}

int a[N],pos[N][T],val[N][T],f[N][T],cur[N],p[N],cnt[N],n;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];

	for(int i=1;i<=n;i++){
		pos[i][0]=i,val[i][0]=a[i];
		for(int j=0;j<=cnt[i-1];j++){
			if((a[i]|val[i-1][j])>(val[i][cnt[i]])){
				cnt[i]++;
				val[i][cnt[i]]=a[i]|val[i-1][j];
				pos[i][cnt[i]]=pos[i-1][j];
			}
		}
	}

	Build(1,0,n);
	vector<array<int,4>> tmp;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=cnt[i];j++){
			tmp.push_back({val[i][j],i,pos[i][j+1],pos[i][j]-1});
		}
	}
	sort(tmp.begin(),tmp.end());
	for(auto t:tmp) ChMax(1,t[1],Query(1,t[2],t[3])+1);

	cout<<Query(1,0,n)<<endl;

	return 0;
}
```



### [ARC207] D - Devourers and Cake

这他妈是什么题。

- 若 $N\bmod 2=1$ 且 $M\bmod 2=1$：

  那么如果中心点是 `0` 后手显然胜利。

  如果中心 $3\times3$ 十字形中出现了连续的 `010` 那么后手可以通过操作中间的那个 `1` 来获得胜利。

  在其他情况下，可以转到下面的分类。

- 若 $N\bmod 2=1$ 和 $M\bmod 2=1$ 有且只有一个满足：

  不失一般性地，令 $N\bmod 2=1$。

  如果中心两个点有一个是 `1` 可以向这边消然后转到上面。

  如果中心 $3\times2$ 矩形出现了连续的 `101` 那么可以向这边消转到上面。

  否则后手可以始终维护中间这个比较棘手的状态直到只剩中间的 `00`。

- 若 $N\bmod 2=0$ 且 $M\bmod 2=0$：

  可以枚举第一步操作转到上面的情况。

所以只要拎出中间 $3/4\times3/4$ 的矩形暴力计算即可。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

inline bool DFS(vector<vector<char>> &v,int xl,int xr,int yl,int yr,bool cur){
	if(xl==xr&&yl==yr) return v[xl][yl]-'0'^cur;
	bool flag=1;
	if(xl!=xr){
		flag&=DFS(v,xl+1,xr,yl,yr,cur^1);
		flag&=DFS(v,xl,xr-1,yl,yr,cur^1);
	}
	if(yl!=yr){
		flag&=DFS(v,xl,xr,yl+1,yr,cur^1);
		flag&=DFS(v,xl,xr,yl,yr-1,cur^1);
	}
	return !flag;
}
inline bool Check(vector<vector<char>> &v){
	int n=v.size(),m=v.front().size();
	int x=max(0,(n-1)/2-1),y=max(0,(m-1)/2-1),lx=min(n,4-(n&1)),ly=min(m,4-(m&1));
	vector<vector<char>> t(lx,vector<char>(ly,0));
	for(int i=0;i<lx;i++) for(int j=0;j<ly;j++) t[i][j]=v[i+x][j+y];
	return DFS(t,0,lx-1,0,ly-1,0);
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T;
	cin>>T;
	while(T--){
		int n,m;
		cin>>n>>m;
		vector<vector<char>> a(n,vector<char>(m,0));
		for(auto &v:a) for(char &c:v) cin>>c;
		if(Check(a)) cout<<"First"<<endl;
		else cout<<"Second"<<endl;
	}

	return 0;
}
```

### [ARC208] D - Symmetric Matrix

首先可以把它看成无向图，那么就相当于要构造 $N$ 组点覆盖，拼接方式有 $\displaystyle \frac {N(N-1)}2$ 条边和 $N$ 个点。

然后构造 $N/N-1$ 组最大匹配是典中典，分奇偶讨论：

-   $N$ 是奇数。那么枚举中心未匹配的点，令中心点是 $x$，让 $x-i\bmod N$ 和 $x+i \bmod N$ 互相匹配。显然每对点只会被匹配一次。
-   $N$ 是偶数。先构造出 $N-1$ 组的解，然后每组没匹配的点 $x$ 再和 $N$ 匹配，这样就构造出了 $N-1$ 组点覆盖，最后一组直接加 $N$ 个孤点即可。如果第 $1$ 组包含孤点，直接和第 $N$ 组互换即可。

编号不一样直接重标号就好了。

```cpp
#include<bits/stdc++.h>

using namespace std;

signed main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		vector<int> a(n);
		for(int &x:a) cin>>x,x--;

		bool err=0;
		for(int i=0;i<n;i++) if(a[a[i]]!=i) err|=1;
		int c=0;
		for(int i=0;i<n;i++) if(a[i]==i) c++;
		if(n&1&&c!=1) err|=1;
		if((~n&1)&&(c&1)) err|=1;

		if(err){
			cout<<"No"<<endl;
			continue ;
		}

		vector<vector<array<int,2>>> e(n);
		map<int,int> mp;
		int m=n&1?n:n-1;
		for(int i=0;i<m;i++){
			for(int j=1;j<=m/2;j++){
				int u=(i-j+m)%m,v=(i+j)%m;
				e[i].push_back({u,v});
			}
			if(~n&1) e[i].push_back({i,n-1});
		}
		int cnt=0;
		for(int i=0,lft=-1;i<n;i++){
			if(a[i]<i) continue ;
			if(a[i]==i){
				if(n&1) mp[0]=i;
				else{
					if(~lft){
						mp[e[0][cnt][0]]=lft;
						mp[e[0][cnt][1]]=i;
						lft=-1;
						cnt++;
					}else lft=i;
				}
				continue ;
			}
			mp[e[0][cnt][0]]=i;
			mp[e[0][cnt][1]]=a[i];
			cnt++;
		}

		vector<vector<int>> ans(n,vector<int>(n,-1));
		if(n&1){
			for(int i=0;i<n;i++){
				ans[mp[i]][mp[i]]=i;
				for(auto p:e[i]){
					ans[mp[p[0]]][mp[p[1]]]=i;
					ans[mp[p[1]]][mp[p[0]]]=i;
				}
			}
		}else{
			for(int i=0;i<n-1;i++){
				for(auto p:e[i]){
					if(!i&&a[mp[p[0]]]==mp[p[0]]){
						ans[mp[p[0]]][mp[p[0]]]=i;
						ans[mp[p[1]]][mp[p[1]]]=i;
					}else{
						ans[mp[p[0]]][mp[p[1]]]=i;
						ans[mp[p[1]]][mp[p[0]]]=i;
					}
				}
			}
		}


		cout<<"Yes"<<endl;
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(~ans[i][j]) cout<<ans[i][j]+1<<' ';
				else cout<<n<<' ';
			}
			cout<<endl;
		}
	}

	return 0;
}
```

### [JOI Open 2016] Selling RNA Strands

啊显然就是 ACAM 板子题啊。

没啥就是好久没写 ACAM 想来一发了。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=4e6+9;

struct Node{
	int son[26],fail,ans;
}tr[N];
int cnt,root=0;
inline int Allc(){return ++cnt;}
inline int Insert(string &s){
	int u=root;
	for(int i=0;i<s.size();i++){
		int k=s[i]-'A';
		if(!tr[u].son[k]) tr[u].son[k]=Allc();
		u=tr[u].son[k];
	}
	return u;
}
inline void Build(){
	queue<int> q;
	for(int i=0;i<26;i++){
		if(!tr[root].son[i]) continue ;
		q.push(tr[root].son[i]);
		tr[tr[root].son[i]].fail=root;
	}
	while(q.size()){
		int x=q.front();
		q.pop();
		for(int i=0;i<26;i++){
			if(tr[x].son[i]){
				tr[tr[x].son[i]].fail=tr[tr[x].fail].son[i];
				q.push(tr[x].son[i]);
			}else tr[x].son[i]=tr[tr[x].fail].son[i];
		}
	}
}
inline void Modify(string &s){
	int u=root;
	for(int i=0;i<s.size();i++){
		int k=s[i]-'A';
		u=tr[u].son[k];
		tr[u].ans++;
	}
}
inline void Work(){
	queue<int> q;
	vector<int> d(cnt+1,0);
	for(int i=1;i<=cnt;i++) d[tr[i].fail]++;
	for(int i=1;i<=cnt;i++){
		if(d[i]) continue ;
		q.push(i);
	}
	while(q.size()){
		int x=q.front();
		q.pop();
		tr[tr[x].fail].ans+=tr[x].ans;
		if(!--d[tr[x].fail]) q.push(tr[x].fail);
	}
}

int id[N],n,m;
string s[N],t[N];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		s[i]=s[i]+"Z"+s[i];
	}
	for(int i=1;i<=m;i++){
		string p,q;
		cin>>p>>q;
		t[i]=q+"Z"+p;
		id[i]=Insert(t[i]);
	}

	Build();
	for(int i=1;i<=n;i++) Modify(s[i]);
	Work();

	for(int i=1;i<=m;i++) cout<<tr[id[i]].ans<<endl;

	return 0;
}
```

### [CERC2017] Intrinsic Interval

从 @wtcqwq 那里偷的，嘻嘻。

下文中令“好区间”表示题目中的“区间”。

显然 $[l,r]$ 是好区间的条件可以刻画成 $\displaystyle \max_{i=l}^r \pi_i-\min_{i=l}^r\pi_i-r+l=0$。

**观察到**若 $[l_1,r_1]$ 和 $[l_2,r_2]$ 均为好区间，那么 $[l_1,r_1]\cup[l_2,r_2]$ 也是一个好区间：

> 证明：
>
> 反证法，令 $[l_3,r_3]=[l_1,r_1]\cup[l_2,r_2]$ 不是一个好区间。
>
> 设 $x\in [\min\pi[l_3:r_3],\max\pi[l_3:r_3]]/[l_3,r_3]$，那么由于 $[l_1,r_1]$ 和 $[l_2,r_2]$ 均为好区间，那么 $x\in [l_1,r_1]/[l_3,r_3]$ 且  $x\in [l_2,r_2]/[l_3,r_3]$，而 $([l_1,r_1]/[l_3,r_3])\cup([l_2,r_2]/[l_3,r_3])=\varnothing$，与 $\pi$ 是排列矛盾。
>
> 综上，$[l_3,r_3]$ 是好区间。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=1e5+9;

int p[N],ql[N],qr[N],al[N],ar[N],n,q;
vector<int> qry[N];

struct Node{
	int l,r,dat,tag;
}tr[N<<2];
inline void PushUp(int x){tr[x].dat=min(tr[x<<1].dat,tr[x<<1|1].dat);}
inline void Push(int x,int k){tr[x].dat+=k,tr[x].tag+=k;}
inline void PushDown(int x){
	if(!tr[x].tag) return ;
	Push(x<<1,tr[x].tag);
	Push(x<<1|1,tr[x].tag);
	tr[x].tag=0;
}
inline void Build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r;
	if(tr[x].l==tr[x].r) return ;
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
inline int LFind(int x,int l,int r){
	if(tr[x].dat>0) return r+1;
	if(tr[x].l==tr[x].r) return tr[x].l;
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) return LFind(x<<1,l,r);
	else if(l>mid) return LFind(x<<1|1,l,r);
	else{
		int res=LFind(x<<1,l,r);
		return res>r?LFind(x<<1|1,l,r):res;
	}
}
inline int RFind(int x,int l,int r){
	if(tr[x].dat>0) return l-1;
	if(tr[x].l==tr[x].r) return tr[x].l;
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) return RFind(x<<1,l,r);
	else if(l>mid) return RFind(x<<1|1,l,r);
	else{
		int res=RFind(x<<1|1,l,r);
		return res<l?RFind(x<<1,l,r):res;
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n;
	for(int i=1;i<=n;i++) cin>>p[i];
	cin>>q;
	for(int i=1;i<=q;i++) cin>>ql[i]>>qr[i],qry[qr[i]].push_back(i);

	Build(1,1,n);
	vector<int> mn,mx;
	priority_queue<array<int,2>> h;
	for(int i=1;i<=n;i++){
		if(i>1) Modify(1,1,i-1,-1);
		while(mn.size()&&p[i]<p[mn.back()]){
			int k=p[mn.back()]-p[i],r=mn.back();
			mn.pop_back();
			int l=mn.size()?mn.back()+1:1;
			Modify(1,l,r,k);
		}
		mn.push_back(i);
		while(mx.size()&&p[i]>p[mx.back()]){
			int k=p[i]-p[mx.back()],r=mx.back();
			mx.pop_back();
			int l=mx.size()?mx.back()+1:1;
			Modify(1,l,r,k);
		}
		mx.push_back(i);

		int pos=LFind(1,1,i);
		for(int j:qry[i]) h.push({ql[j],j});
		while(h.size()&&h.top()[0]>=pos){
			int j=h.top()[1],k=RFind(1,1,ql[j]);
			h.pop();
			al[j]=k,ar[j]=i;
		}
	}

	for(int i=1;i<=q;i++) cout<<al[i]<<' '<<ar[i]<<endl;

	return 0;
}
```

### [ROIR 2023] Обыкновенная задача про строки

我怎么没补这题来着。

首先把这个串丢到图上建出自动机，然后就变成在自动机上找欧拉路径数量了。

考虑 BEST 定理，枚举起点终点，在起点和终点之间加一条边，计算出方案数。

但是鉴于这里并不区分边和边，所以还要除掉 $(\sharp e(u,v))!$。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e6+9;
const int C=3;
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

int fac[N],ifac[N];
inline void Init(int lim){
	fac[0]=1;
	for(int i=1;i<=lim;i++) fac[i]=Mul(fac[i-1],i);
	ifac[lim]=Inv(fac[lim]);
	for(int i=lim-1;~i;i--) ifac[i]=Mul(ifac[i+1],i+1);
}

signed main(){
	int Tid,T;
	cin>>Tid>>T;
	while(T--){
		string s;
		cin>>s;

		char tot='a';
		map<char,char> mp;
		for(auto &c:s){
			if(!mp[c]) mp[c]=tot++;
			c=mp[c];
		}
		int T=tot-'a';

		if(T==1){
			cout<<"13"[s.size()==1]<<endl;
			continue ;
		}

		Init(s.size());
		int cnt[C][C],in[C],out[C];
		memset(in,0,sizeof in);
		memset(out,0,sizeof out);
		memset(cnt,0,sizeof cnt);
		for(int i=0;i+1<s.size();i++) cnt[s[i]-'a'][s[i+1]-'a']++;
		for(int i=0;i<T;i++) for(int j=0;j<T;j++) out[i]+=cnt[i][j],in[j]+=cnt[i][j];

		int st=-1,ed=-1;
		for(int i=0;i<T;i++){
			if(in[i]<out[i]) st=i;
			if(in[i]>out[i]) ed=i;
		}

		int ans=0;
		for(int p=0;p<T;p++){
			if(~st&&p!=ed) continue ;
			for(int q=0;q<T;q++){
				if(~ed&&q!=st) continue ;
				if(!~st&&p!=q) continue ;
				int res=1;
				cnt[p][q]++,out[p]++,in[q]++;
				for(int i=0;i<T;i++) MulAs(res,fac[max(out[i]-1,0)]);
				if(T==3) MulAs(res,Sub(Mul(Sub(out[0],cnt[0][0]),Sub(out[1],cnt[1][1])),Mul(cnt[0][1],cnt[1][0])));
				else if(T==2) MulAs(res,Sub(out[0],cnt[0][0]));
				cnt[p][q]--,out[p]--,in[q]--;
				AddAs(ans,res);
			}
		}
		for(int i=0;i<T;i++) for(int j=0;j<T;j++) MulAs(ans,ifac[cnt[i][j]]);

		cout<<ans<<endl;
	}

	return 0;
}
```

### [ICPC 2024 Kunming I] F. Collect the Coins

显然二分答案，考虑维护两个机器人的两个可达区间，更新时如果两个区间都能到达，随便挑一个更新，剩下的变成两个的并即可。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e6+9;

int n;
array<ll,2> a[N];

inline bool Check(int k){
	ll l1=-1e9,r1=1e9,l2=-1e9,r2=1e9,t=-1e9;
	for(int i=1;i<=n;i++){
		l1-=k*(a[i][0]-t),r1+=k*(a[i][0]-t);
		l2-=k*(a[i][0]-t),r2+=k*(a[i][0]-t);
		t=a[i][0];
		bool f1=l1<=a[i][1]&&a[i][1]<=r1;
		bool f2=l2<=a[i][1]&&a[i][1]<=r2;
		if(f1&&f2){
			l1=min(l1,l2),r1=max(r1,r2);
			l2=r2=a[i][1];
		}else if(f1) l1=r1=a[i][1];
		else if(f2) l2=r2=a[i][1];
		else return 0;
	}
	return 1;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i][0]>>a[i][1];
		sort(a+1,a+n+1);

		int l=-1,r=1e9+1;
		while(l+1<r){
			int mid=l+r>>1;
			if(Check(mid)) r=mid;
			else l=mid; 
		}
		
		if(r==1e9+1) cout<<-1<<endl;
		else cout<<r<<endl;
	}

	return 0;
}
```

### [COTS 2024] Tablica

首先发现立方 DP 不是很能优化，因此考虑直接刻画答案形态。

令 $n\geq m$，枚举共有 $c$ 行的和为 $2$，那么剩下行/列和为 $1/2$ 的个数就都知道了。

然后就是直接把和看成匹配额度，容斥掉同一行匹配同一列两次的情况即可，答案为：

$$\displaystyle \sum_{c=0}^{2m-n} \dfrac{1}{2^c}\dbinom{n}{c}\dbinom{m}{c+n-m} \sum_{t=0}^c (-1)^t\dfrac{1}{2^{c+n-m-t}}\dbinom{c}{t}\dbinom{c+n-m}{t}(n+c-2t)!$$

```cpp
#include<bits/stdc++.h>

using namespace std;

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

int fac[N<<1],ifac[N<<1];
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

int n,m;

signed main(){
	cin>>n>>m;
	if(m>n) swap(n,m);
	Init(n<<1);

	int ans=0;
	for(int c=0;c<=2*m-n;c++){
		int tmp=Mul(C(n,c),C(m,n-m+c));
		for(int t=0;t<=c;t++){
			int res=Mul(tmp,Mul(Mul(Mul(C(c,t),C(n-m+c,t)),fac[n+c-2*t]),fac[t]));
			MulAs(res,QPow(Inv(2),n-m+c+c-t));
			if(~t&1) AddAs(ans,res);
			else SubAs(ans,res);
		}
	}

	cout<<ans<<endl;

	return 0;
}
```

### [COTS 2025] Trava

数据结构要加训。

先考虑没有修改咋做。

$$\begin{align}\displaystyle \sum_{i=1}^{N-k+1} \max(a_i,a_{i+1},\ldots,a_{i+k-1})\\=\sum_{i=1}^{N-k+1} \sum_{t=1}^V[t\leq\max(a_i,a_{i+1},\ldots,a_{i+k-1})]\\=(N-k+1)V-\sum_{t=1}^V\sum_{i=1}^{N-k+1}[t\gt\max(a_i,a_{i+1},\ldots,a_{i+k-1})]\end{align}$$

因此对于某一个 $t$，令 $a_i\leq t$ 的 $i$ 构成的连续段长度分别为 $L_1,\ldots,L_m$，那么这部分的贡献就是 $\displaystyle \sum_{i=1}^m \max(L_i-k+1,0)$。

所以考虑 $(i,j)$ 能作为某一个 $L$ 的左右端点的 $t$ 的个数并计算贡献，具体地：$\displaystyle L=\min(a_i,a_j)-\max_{p=i+1}^{j-1} a_p$，而 $L$ 对 $k$ 的贡献是简单的分段函数，区间加等差序列线段树即可。

 令 $p=\max\{j|a_j>a_i\wedge j<i\},q=\min\{a_j>a_i\wedge j>i\}$，发现 $a'_i\leftarrow a_i+1$ 只会扣掉一个 $(p,q)$ 的贡献同时分别加一个 $(p,i)$ 和 $(i,q)$ 的贡献。也就是说每次的修改是 $O(1)$ 的。

总时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=5e5+9;
const int inf=1e9+7;

int a[N],n,q;

struct Node{
	int l,r,mx;
	ll sum,d;
	inline int Len(){return r-l+1;}
}tr[N<<2];
inline void PushUp(int x){tr[x].mx=max(tr[x<<1].mx,tr[x<<1|1].mx);}
inline void Push(int x,ll b,ll k){tr[x].sum+=b,tr[x].d+=k;}
inline void PushDown(int x){
	if(!tr[x].sum&&!tr[x].d) return ;
	Push(x<<1,tr[x].sum,tr[x].d);
	Push(x<<1|1,tr[x].sum+tr[x<<1].Len()*tr[x].d,tr[x].d);
	tr[x].sum=tr[x].d=0;
}
inline void Build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r;
	if(tr[x].l==tr[x].r) return ;
	int mid=tr[x].l+tr[x].r>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Set(int x,int pos,int k){
	if(tr[x].l==tr[x].r) return tr[x].mx=k,void();
	int mid=tr[x].l+tr[x].r>>1;
	if(pos<=mid) Set(x<<1,pos,k);
	else Set(x<<1|1,pos,k);
	PushUp(x);
}
inline void Modify(int x,int l,int r,ll b,ll k){
	if(l<=tr[x].l&&tr[x].r<=r) return Push(x,b,k);
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) Modify(x<<1,l,r,b,k);
	else if(l>mid) Modify(x<<1|1,l,r,b,k);
	else{
		Modify(x<<1,l,mid,b,k);
		Modify(x<<1|1,mid+1,r,b+(mid-l+1)*k,k);
	}
	PushUp(x);
}
inline ll Query(int x,int pos){
	if(tr[x].l==tr[x].r) return tr[x].sum;
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(pos<=mid) return Query(x<<1,pos);
	else return Query(x<<1|1,pos);
}
inline int LFind(int x,int l,int r,int k){
	if(tr[x].mx<=k) return r+1;
	if(tr[x].l==tr[x].r) return tr[x].l;
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) return LFind(x<<1,l,r,k);
	else if(l>mid) return LFind(x<<1|1,l,r,k);
	else{
		int res=LFind(x<<1,l,r,k);
		return res>r?LFind(x<<1|1,l,r,k):res;
	}
}
inline int RFind(int x,int l,int r,int k){
	if(tr[x].mx<=k) return l-1;
	if(tr[x].l==tr[x].r) return tr[x].l;
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) return RFind(x<<1,l,r,k);
	else if(l>mid) return RFind(x<<1|1,l,r,k);
	else{
		int res=RFind(x<<1|1,l,r,k);
		return res<l?RFind(x<<1,l,r,k):res;
	}
}
inline void Insert(int l,int k){if(l>0) Modify(1,1,l,1ll*k*l,-k);}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];

	Build(1,1,n);
	Insert(n,inf);
	Insert(n,-(inf-*max_element(a+1,a+n+1)));
	for(int i=1;i<=n;i++) Set(1,i,a[i]);
	vector<int> stk;
	for(int i=1;i<=n;i++){
		int lst=0;
		while(stk.size()&&a[i]>a[stk.back()]){
			Insert(i-stk.back()-1,-(a[stk.back()]-lst));
			lst=a[stk.back()];
			stk.pop_back();
		}
		Insert(i-(stk.size()?stk.back():0)-1,-(a[i]-lst));
		stk.push_back(i);
	}
	int lst=0;
	while(stk.size()){
		Insert(n-stk.back(),-(a[stk.back()]-lst));
		lst=a[stk.back()];
		stk.pop_back();
	}

	while(q--){
		char op;int k;
		cin>>op>>k;
		if(op=='?'){
			cout<<Query(1,k)<<endl;
		}else if(op=='+'){
			int lp=RFind(1,1,k,a[k]),rp=LFind(1,k,n,a[k]);
			Insert(rp-lp-1,1);
			Insert(rp-k-1,-1);
			Insert(k-lp-1,-1);
			Set(1,k,++a[k]);
		}
	}

	return 0;
}
```

### [EGOI 2025] Wind Turbines

操作相当于在 MST 上加 $r-l$ 条 $(i,i+1)$ 的边并删去环上最大边，但是直接刻画不是很好做。通过某种神秘方式注意到这相当于在 Kruskal 重构书上拎出来 $[l,r]$ 的虚树，并删去所有非叶子节点。因此，考虑直接 dsu on tree 每个 LCA 上的支配点对算 2-side 矩形并，并从答案中扣掉即可，时间复杂度 $O(n\log^2 n+m\log m+q\log n)$。

操但是为啥我线段树写错了。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e5+9;

ll ans[N<<1];
int u[N],v[N],w[N],ql[N<<1],qr[N<<1],n,m,q;

int fa[N];
set<int> node[N];
vector<int> qry[N];
vector<array<int,3>> seg[N];
inline int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}

ll tr[N];
inline void Add(int x,ll k){while(x<=n) tr[x]+=k,x+=x&-x;}
inline void Add(int l,int r,ll k){Add(l,k),Add(r+1,-k);}
inline ll Ask(int x){ll sum=0;while(x) sum+=tr[x],x&=x-1;return sum;}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>m>>q;
	for(int i=1;i<=m;i++) cin>>u[i]>>v[i]>>w[i],u[i]++,v[i]++;
	for(int i=1;i<=q;i++) cin>>ql[i]>>qr[i],ql[i]++,qry[++qr[i]].push_back(i);
	for(int i=1;i<=n;i++){
		node[i].insert(i);
		fa[i]=i;
	}

	ll sum=0;
	vector<int> ord(m);
	iota(ord.begin(),ord.end(),1);
	sort(ord.begin(),ord.end(),[](int i,int j){return w[i]<w[j];});
	for(int i:ord){
		if(Find(u[i])==Find(v[i])) continue ;
		u[i]=Find(u[i]),v[i]=Find(v[i]);
		if(node[u[i]].size()<node[v[i]].size()) swap(u[i],v[i]);
		fa[v[i]]=u[i];
		vector<array<int,2>> rg;
		for(int x:node[v[i]]){
			auto it=node[u[i]].lower_bound(x);
			auto jt=it==node[u[i]].begin()?node[u[i]].end():prev(it);
			if(it!=node[u[i]].end()) rg.push_back({x,*it});
			if(jt!=node[u[i]].end()) rg.push_back({*jt,x});
		}
		sum+=w[i];
		sort(rg.begin(),rg.end(),[](auto x,auto y){return x[1]<y[1];});
		int l=0;
		for(auto t:rg){
			if(t[0]<=l) continue ;
			seg[t[1]].push_back({l+1,t[0],w[i]});
			l=t[0];
		}
		node[u[i]].insert(node[v[i]].begin(),node[v[i]].end());
		node[v[i]].clear();
	}

	for(int i=1;i<=n;i++){
		for(auto t:seg[i]) Add(t[0],t[1],t[2]);
		for(int j:qry[i]) ans[j]=sum-Ask(ql[j]);
	}

	for(int i=1;i<=q;i++) cout<<ans[i]<<endl;
	
	return 0;
}
```

### [UOI 2025\] Simple Subsequence

令 $s_i=\displaystyle \sum_{j=l}^i a_i$，那么序列 $a[l:r]$ 是好的需要满足：

- $\displaystyle \min_{i=l-1}^r s_i\geq 0$。
- $\displaystyle \max_{i=l-1}^r s_i \leq s_r$。

通过手绘折线图可以发现，对于一个区间，其一定存在一个极长好的子序列是通过先尽量靠后地删除 $-1$ 使得不存在 $s_i\lt 0$ 的情况，然后再上面的基础上重新计算新的 $s'_i$ 并删除最后 $\displaystyle \max_{i=l-1}^r s'_i-s'_r$ 个 $-1$。

第一部分显然删除的是所有 $\lt 0$ 的前缀最小值位置，个数是 $\displaystyle -\min_{i=l-1}^rs_i$。考虑如何维护改动后的 $\displaystyle \max_{i=l-1}^r s'_i$，由于删除的全都是前缀最小值位置的 $-1$，因此 $i$ 前面删除的 $-1$ 的个数就是 $\displaystyle -\min_{j=l-1}^is_j$，所以 $\displaystyle \max_{i=l-1}^r s'_i=\max_{i=l-1}^r (s_i-\min_{j=l-1}^i s_j)$，线段树上随便合并一下即可，时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=5e5+9;

struct Data{
	int mx,mn,sum,h;
	Data(){}
	Data(int _mx,int _mn,int _sum,int _h){mx=_mx,mn=_mn,sum=_sum,h=_h;}
	inline friend Data operator +(Data l,Data r){
		Data res;
		res.mx=max(l.mx,r.mx+l.sum);
		res.mn=min(l.mn,r.mn+l.sum);
		res.sum=l.sum+r.sum;
		res.h=max(max(l.h,r.h),r.mx+l.sum-l.mn);
		return res;
	}
};

struct Node{
	int l,r;
	Data dat;
}tr[N<<2];
inline void PushUp(int x){tr[x].dat=tr[x<<1].dat+tr[x<<1|1].dat;}
inline void Build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r;
	if(tr[x].l==tr[x].r) return ;
	int mid=tr[x].l+tr[x].r>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Set(int x,int pos,int k){
	if(tr[x].l==tr[x].r) return tr[x].dat=Data(max(k,0),min(k,0),k,max(k,0)),void();
	int mid=tr[x].l+tr[x].r>>1;
	if(pos<=mid) Set(x<<1,pos,k);
	else Set(x<<1|1,pos,k);
	PushUp(x);
}
inline Data Query(int x,int l,int r){
	if(l<=tr[x].l&&tr[x].r<=r) return tr[x].dat;
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) return Query(x<<1,l,r);
	else if(l>mid) return Query(x<<1|1,l,r);
	else return Query(x<<1,l,r)+Query(x<<1|1,l,r);
}

int a[N],n,q;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];

	Build(1,1,n);
	for(int i=1;i<=n;i++) Set(1,i,a[i]);

	while(q--){
		int op;
		cin>>op;
		if(op==1){
			int x;
			cin>>x;
			Set(1,x,a[x]=-a[x]);
		}else{
			int l,r;
			cin>>l>>r;
			int ans=r-l+1;
			auto tmp=Query(1,l,r);
			ans-=max(0,-tmp.mn);
			ans-=tmp.h-tmp.sum-max(0,-tmp.mn);
			cout<<ans<<endl;
		}
	}

	return 0;
}
```

### [UOI 2025] Reversal ABC

首先如果交换了一对 $\tt\color{red} AB$，那么交换之后就会变成 $\tt??{\color{red}BA}??$，因此对于这个 $\tt A$ 不会再和另外一个 $\tt C$ 组成 $\tt CA$ 进行交换了。因此，如果决定了  字符 $c_i$ 和 $c_j$ 交换，那么后面继续和 $c_i$ 交换的字符必然和 $c_2$ 颜色相同。

因此可以把整个串分为若干个至多存在两种字符的段，每段单独计算贡献。同时注意到 $\tt [BC][BC]$ 显然不如 $\tt [BCBC]$ 优，即不会出现两个同种的相邻字符段，因此每个右端点的最优候选左端点只有 $2$ 个，直接 DP 转移即可，计算贡献是容易的。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e6+9;

int r[N],n;
ll res[N];
char s[N];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>s[i];

		int lst[3]={n+1,n+1,n+1};
		for(int i=n;i>=1;i--){
			int f=s[i]-'A';
			lst[f]=i;
			r[i]=min(lst[(f+1)%3],lst[(f+2)%3])-1;
		}

		ll sum=0;
		int cnt[3]={0,0,0};
		for(int i=1,j=1;i<=n;i++){
			int f=s[i]-'A';
			cnt[f]++,sum+=cnt[(f+2)%3];
			while(j<=i&&cnt[0]&&cnt[1]&&cnt[2]){
				int g=s[j]-'A';
				cnt[g]--,sum-=cnt[(g+1)%3];
				j++;
			}
			res[i]=res[j-1]+sum;
			if(r[j]<i){
				int g=s[j]-'A';
				res[i]=max(res[i],res[r[j]]+sum-1ll*(r[j]-j+1)*cnt[(g+1)%3]);
			}
		}

		cout<<res[n]<<endl;
	}

	return 0;
}
```

### [UOI 2025] Convex Array

由于重排后序列是凸的，因此最小值两边一定单调递增，从小到大排序，显然有 $O(n^4)$ DP：令 $f_{a_1,a_2,b_1,b_2}$ 表示当前数列两边倒数第一/二个分别为 $a_1,a_2,b_1,b_2$，转移显然是 $O(1)$ 的。

然而 $a_1,a_2,b_1,b_2$ 至少有两个分别是 $i$ 和 $i-1$，所以这个是 $O(n^3)$ 的。

考虑继续对 $a_1,a_2,b_1,b_2$ 的形态分类讨论：

- $(i,i-1,x,y)$。
- $(i,i-2,i-1,x)$。
- $(i,x,i-1,i-2)$。

后两种可以直接枚举 $i+1$ 放哪边 $O(1)$ 转移，因此考虑研究第一种。

- $(i,i-1,x,y)\rightarrow (i+1,i,x,y)$：状态没有发生太多变化，因此如果 $2a_i\leq a_{i-1}+a_{i+1}$ 就可以保留所有 $(x,y)$ 对，反之则需要全部删掉。
- $(i,i-1,x,y)\rightarrow (i+1,x,i,i-1)$：这对应的是第二种状态，转移条件是 $2a_x\leq a_y+a_{i+1}$，注意到对于后续的状态是 $x$ 越大限制越松，因此我们只通过满足 $2a_x-a_y\leq a_{i+1}$ 中 $x$ 最大的 $(x,y)$ 对转移。

以上的操作可以通过维护一个三号状态的 $(x,y)$ 集合的惰性修改以及 $x$ 最大的一号二号状态在 $O(n\log n)$ 的时间复杂度内解决。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=3e5+9;

int a[N],n;

inline void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];

	set<array<int,2>> s;
	sort(a+1,a+n+1);
	auto Query=[&](int x){
		auto it=s.lower_bound({x+1,});
		if(it==s.begin()) return -1;
		else return (*--it)[1];
	};
	auto Insert=[&](array<int,2> x){
		if(Query(x[0])>=x[1]) return ;
		s.insert(x);
		while(true){
			auto it=s.upper_bound(x);
			if(it==s.end()) break ;
			if((*it)[1]<=x[1]) s.erase(it);
			else break ;
		}
	};

	int p=-1,q=-1;
	Insert({a[1],1});
	for(int i=3;i<=n;i++){
		int cp=-1,cq=-1;
		cq=Query(a[i]);
		if(a[i]+a[i-2]<2*a[i-1]) s.clear();
		if(~p&&a[i]+a[i-3]>=2*a[i-1]) Insert({a[i-2]*2-a[p],i-2});
		if(~p&&a[i]+a[p]>=2*a[i-2]) cp=max(cp,i-3);
		if(~q&&a[i]+a[q]>=2*a[i-1]) Insert({a[i-2]*2-a[i-3],i-2});
		if(~q&&a[i]+a[i-3]>=2*a[i-2]) cp=max(cp,q);
		p=cp,q=cq;
	}

	if(~p||~q||s.size()) cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
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

## 口胡大赛

记录了懒得写的题。

### [Ynoi2004] rpmtdq

以前做过，然后忘了。

考虑先点分治，对于每层分治的子树把所有点抽出来按编号排序，以距离为权值向两边单调栈找出所有支配点对，对所有点对扫描线即可。

时间复杂度 $O(n\log^2 n+q\log n)$。

### [PA 2018] Skwarki

我怎么做过这个题。

首先把谷转成峰，然后这个东西相当于在笛卡尔树上有两个儿子，左右端点特判一下，枚举最大值位置在哪里，组合数合并一下即可。

### [ROIR 2023] Красивые последовательности

直接 $O(nm\cdot m!)$ DP 即可。

### [ROIR 2023] Камни

注意到答案最多为 $2$，直接怎么怎么维护一下前缀后缀/后缀前缀最大值即可。

### [ROIR 2023] Робот-пылесос

矩形面积并板板题。

### [ROIR 2023]  Разноцветные точки

首先枚举中心点然后极角排序，那么每个 $(i,j)$ 的后继状态 $(i',j')$ 是可以找出来的。

建出基环森林，在环上的 $i$ 就是绿色的。为了找出蓝色的 $i$ 可以按 DFS 序排一遍，相邻的两两找 LCA 即可。

### [ICPC 2024 Kunming I] F. Stop the Castle 2

首先可以转成两个车之间的障碍物只要有一个就可以不增加贡献，然后让行连续段和列连续段两两匹配，算出最多可以少用几个障碍物，跑一遍残量网络构造解即可，时间复杂度 $O(n\sqrt n)$。

### [COI 2025] Bolivija

考虑到对于一堆 $(i,n-i+1)$，区间 $(\min(a_i,a_{n-i+1}),\max(a_i,a_{n-i+1}))$ 是不对称的，因此维护出来所有这样的区间的并，答案就是这个的补集中每一段的子区间个数之和。

### [COCI 2024/2025 #4] Tura Mačkica

不得不承认没想到经典套路。

考虑有向图欧拉回路的条件：

-   图联通。
-   $ind_u=outd_u$。

令 $d_u=outd_u-ind_u$，那么目标就是让所有 $d_u=0$。

考虑树的情况，那么所有边 $u\leftrightarrow v,v\in son_u$ 可以给 $d_v$ 造成 $+1,0,-1$ 之一的贡献，为了使 $d_v=0$ 这条边的定向一定是确定的，因此可以直接从下到上敲定，最后判一次连通性即可。

基环树就是枚举环上一条边的取值。 