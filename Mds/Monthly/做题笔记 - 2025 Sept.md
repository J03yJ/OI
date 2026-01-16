## 评级规范

### 题目质量

-   ${\sf\color{Red} DownVote\bigtriangledown}$：垃圾题。
-   ${\sf\color{Black}Normal.}$：正常题。
-   ${\sf\color{Green} UpVote\bigtriangleup}$：好题。
-   ${\sf\color{Blue} Great!}$：精妙的 Trick。
-   ${\sf\color{Cyan} Brilliant!!}$：妙完了。
-   ${\sf\color{Gray} Unknown\ast}$：其他。

### 表现

-   ${\sf\color{Red} Blunder??}$：放正赛这么唐完蛋了。
-   ${\sf\color{Peach} Mistake?}$：一些较小的却仍会造成损失的错误。
-   ${\sf\color{Tan} Book\dagger}$：开了题解，但是没犯唐。
-   ${\sf\color{Green} Good.}$：没犯唐独立做出，并理应独立做出。
-   ${\sf\color{Cyan} Excellent\star}$：没犯唐独立做出，并不应独立做出。
-   ${\sf\color{Gray} Unknown\ast}$：其他。

## 题目整理

### [ARC109] E - 1D Reversi Builder

${\sf\color{Blue} Great!}/{\sf\color{Tan} Book\dagger}$

不是哥们我这四年都学了些什么？？？

-   **结论 1**：任意时刻棋子构成的颜色连续段黑白至多各一个。
    -   归纳法可证。
-   **结论 2**：若 $c_1=c_n$，则所有棋子颜色相同。
    -   由结论 1 得出。
-   **结论 3**：若 $c_i\neq c_n$，设 $p$ 为左侧 $c_1$ 连续段的右端点，$q$ 为右侧 $c_n$ 连续段左端点，那么最后的颜色连续段要么是 $\{[1,p],[p+1,n]\}$，要么是 $\{[1,q-1],[q,n]\}$。
    -   当左端点已经到达了 $p$ 左侧的位置，而右端点还没有到 $q$ 右侧的位置时：左端点的颜色在后续过程中将始终和 $c_1$ 相同，而右端点则在此后必定经过 $q-1$，故最终形态应为 $\{[1,q-1],[q,n]\}$。另一种情况同理。
-   **结论 4**：在结论 3 的基础上，设 $W$ 为两端白色连续段的长度，$B$ 为两端黑色连续段长度。若 $s$ 离白色连续段端点较近，则黑石数为 $B$，否则为 $n-W$。
    -   分别对应了结论 3 的两种情况，由于对于每一方来说先到属于自己的连续段肯定不劣，所以都会各自向两边走。

基于以上的结论进行分讨：

- 若 $c_1=c_n$，则贡献为 $n2^{n-2}$。

- 若 $c_1\neq c_n$：

  - 若颜色连续段个数为 $2$，则答案与决策无关，贡献为 $\displaystyle2\sum_{i=1}^{n-1}i=n(n-1)$。

  - 若连续段个数大于 $2$，不是一般性地钦定 $c_1$ 是黑色，考虑枚举 $p,q,s$，贡献为：

    $\displaystyle 2\sum_{p=1}^{n-1}\sum_{q=p+3}^n2^{q-p-3}[(q-1)[s-p\leq q-s]+p[s-p>q-s]]$

以上式子可以 $O(n^3)$ 进行计算，后续优化就不是很好做了。

-   **结论 5**：对于除了 $c_1\neq c_n\wedge s-p=q-s$ 的状态来说，若该状态的最终黑石数量为 $k$，那么它的反状态的最终黑石数量为 $n-k$。
    -   原因显然。

基于结论 5，可以说明粗略估计的贡献总和为 $n2^{n-1}$。

进一步地，我们需要计算出 $s-p=q-s=d$ 这一情况的具体误差，这应该是：$\displaystyle \displaystyle\sum_{d=2}^{\min(s-1,n-s)} (2d-1)\cdot 2^{2d-3}$。

至此，我们在 $O(n\log n)$ 的时间内完成了这题，预处理 $2^k$ 可以做到 $O(n)$。

```cpp
vector<int> pre(n+1,0);
for(int i=2;i<=(n-1)/2;i++) pre[i]=Mul(2*i-1,QPow(2,2*i-3)),AddAs(pre[i],pre[i-1]);
for(int s=1;s<=n;s++){
    int sum=Mul(n,QPow(2,n-1));
    AddAs(sum,pre[min(s-1,n-s)]);
    cout<<Mul(sum,Inv(QPow(2,n)))<<endl;
}
```

### [ARC110] D - Binomial Coefficient is Fun

${\sf\color{Black}Normal.} / {\sf\color{Peach} Mistake?}$

这个题没做出来就是我组合计数没学好。

考虑把每个 $\binom{B_i}{A_i}$ 看成是 $\binom{A_i+D_i}{A_i}$，相当于是让 $A_i$ 个红球和 $D_i$ 个蓝球相互组合，共 $n$ 组。

考虑如何区分这 $n$ 组，使用插板法将球中间加入 $n$ 个隔板，并不和红球做区分，钦定第 $i+{\sum_{j<i}A_i}~(i>1)$ 个是隔板，剩下的是红球。

所以答案是 $\binom{m+n}{\sum A_i+n}$。

```cpp
int sum=accumulate(a.begin(),a.end(),0);
cout<<BruteC(m+n,sum+n)<<endl;
```

### [ARC110] F - Esoswap

${\sf\color{Black}Normal.} / {\sf\color{Peach} Mistake?}$

I HATE AD-HOOOOOOC!!!

**注意到**如果我们一直对位置 $i$ 进行操作，如果某时刻 $P_i\neq 0$，那么在之后的操作中 $P_i'\neq P_i$，所以对 $i$ 操作 $n-1$ 次会使得 $P_i=0$。

发现这个结论之后就比较好做了。考虑推广这个结论，即如何在 $P_0=0$ 的情况下让 $P_1=1$。虽然我们不能直接让 $P_1=1$，但是发现先让 $P_1=0$，再让 $P_0=0$ 时，因为 $P_0$ 要和 $P_1$ swap，所以只能让 $P_0=1$，所以最后有 $P_0=0,P_1=1$。进一步地，可以让 $P_i=i$。

操作次数大概是 $O(n^2)$ 的。

```cpp
cout<<n*n<<endl;
for(int i=n;i;i--) for(int j=n;j--;) cout<<i-1<<endl;
```

### [ARC112] D - Skate

${\sf\color{Black}Normal.} / {\sf\color{Peach} Mistake?}$

题读错了，不是你这滑冰题怎么还能穿墙的。

发现所有点都可以不断 $\tt UR$ 到达 $(1,1)$，所以可以只考虑 $(1,1)$ 是否可以到达所有点。

可以证明这等价于每一行都有地毯或者每一列都有地毯（边界除外）。

所以对两种情况分别贪心地去放地毯即可。

```cpp
inline int Id(int i,int j){return (i-1)*m+j;}
inline void Init(){iota(fa+1,fa+n*m+1,1);}
inline int Find(int x){return fa[x]==x?x:fa[x]=Find(fa[x]);}
inline void Merge(int x,int y){fa[Find(y)]=Find(x);}

signed main(){
    ...
        
	Init();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(!a[i][j]) continue ;
			for(int k=i-1;k;k--){
				if(!a[k][j]) continue ;
				Merge(Id(k,j),Id(i,j));
				break ;
			}
			for(int k=j-1;k;k--){
				if(!a[i][k]) continue ;
				Merge(Id(i,k),Id(i,j));
				break ;
			}
		}
	}

	int rcnt=0;
	for(int i=1;i<=max(n,m);i++){
		if(a[1][i]) vis[Find(Id(1,i))]=1;
		if(a[n][i]) vis[Find(Id(n,i))]=1;
		if(a[i][1]) vis[Find(Id(i,1))]=1;
		if(a[i][m]) vis[Find(Id(i,m))]=1;
	}
	for(int i=2;i<n;i++){
		int flag=0;
		for(int j=1;j<=m;j++) if(a[i][j]) flag|=vis[Find(Id(i,j))];
		if(flag) continue ;
		rcnt++;
		for(int j=1;j<=m;j++) if(a[i][j]) vis[Find(Id(i,j))]=1;
	}
	for(int i=1;i<=n*m;i++) vis[i]=0;
	int ccnt=0;
	for(int i=1;i<=max(n,m);i++){
		if(a[1][i]) vis[Find(Id(1,i))]=1;
		if(a[n][i]) vis[Find(Id(n,i))]=1;
		if(a[i][1]) vis[Find(Id(i,1))]=1;
		if(a[i][m]) vis[Find(Id(i,m))]=1;
	}
	for(int j=2;j<m;j++){
		int flag=0;
		for(int i=1;i<=n;i++) if(a[i][j]) flag|=vis[Find(Id(i,j))];
		if(flag) continue ;
		ccnt++;
		for(int i=1;i<=n;i++) if(a[i][j]) vis[Find(Id(i,j))]=1;
	}

	cout<<min(rcnt,ccnt)<<endl;
    
    ...
}
```

### [ARC112] E - Cigar Box

${\sf\color{Blue} Great!}/{\sf\color{Tan} Book\dagger}$

称对于某个数来说最后一次移动的操作为有效操作，反之则为无效操作。

考虑如下 DP，令 $f_{l,r,k}$ 表示当前执行了最后 $k$ 次操作，共有 $l$ 次为 $\tt L$ 的有效操作，$r$ 次为 $\tt R$ 的有效操作，即确定了 $a_{1\sim l}$ 和 $a_{n-r+1\sim n}$ 的有效操作位置。

有如下转移：

-   $f_{l,r,k+1} \leftarrow 2(l+r)f_{l,r,k}$（一次无效操作）。
-   $f_{l+1,r,k+1}/f_{l,r+1,k+1} \leftarrow f_{l,r,k}$（一次有效操作）。

最后答案就是 $\displaystyle \sum_{l+r\leq n} f_{l,r,m}[a_{1+l\sim n-r}{\rm~is~sorted}]$，时间复杂度 $O(n^3)$。

注意到转移系数只和 $l+r$ 有关，故考虑统计时再指定 ${\tt L}/{\tt R}$ 操作。

令 $g_{L,k}$ 表示执行了 $k$ 次操作，其中有 $L$ 次有效操作。

有如下转移：

-   $g_{L,k+1} \leftarrow 2Lg_{L,k}$（一次无效操作）。
-   $g_{L+1,k+1} \leftarrow g_{L,k}$（一次有效操作）。

答案是 $\displaystyle \sum_{l+r\leq n} g_{l+r,m}\binom{l+r}{l}[a_{1+l\sim n-r}{\rm~is~sorted}]$，时间复杂度 $O(n^2)$。

```cpp
Init(n);
f[0][0]=1;
for(int len=0;len<=n;len++){
    for(int c=len;c<=m;c++){
        AddAs(f[len][c+1],Mul(2,Mul(len,f[len][c])));
        AddAs(f[len+1][c+1],f[len][c]);
    }
}

int ans=0;
for(int lp=1;lp<=n+1;lp++){
    for(int rp=lp-1;rp<=n;rp++){
        if(rp>lp&&a[rp-1]>a[rp]) break ;
        int l=lp-1,r=n-rp;
        AddAs(ans,Mul(C(l+r,l),f[l+r][m]));
    }
}
```

### [ARC113] E - Rvom and Rsrev

${\sf\color{Red} DownVote\bigtriangledown}/{\sf\color{Peach} Mistake?}$

$\tt R[e](mov)^{-1}[e]~and~R[e](vers)^{-1}[e]$

分讨题没想明白。

- 对于全 ${\tt a}/{\tt b}$ 串：直接保留

- 对于结尾为 $\tt a$ 的串：考虑将所有 $\tt a$ 字符转移到后面。从后向前考虑，对于前面长度 $\gt 1$ 的 $\tt a$ 段，直接操作段开头的 $\tt a$ 和结尾段开头的 $\tt a$，消掉两个。而对于长度恰好为 $1$ 的段，向前匹配另一个长度恰好为 $1$ 的段删除，找不到再和最后的 $\tt a$ 段开头进行匹配。

- $\tt a$ 个数为偶数的串：因为这个时候 $\tt a$ 已经不能放到最后了，这时删 $\tt a$ 比删 $\tt b$ 优，所以直接两两匹配删光。

- 形如 $\tt aaa...ab...bbb$ 的串：无论如何开头都存在 $\tt a$，所以删成 $\tt ab...bbb$ 最优。

- 对于剩下的串，如果删 $\tt b$，那么最好的情况是保留最后一个 $\tt a$，所以对删 $\tt b$ 进行讨论：

  -   如果不删，那么最后一个 $\tt a$ 的位置不动。
  -   如果删，那么可以通过消耗两个 $\tt b$ 来把 $\tt a$ 调到最后，然后执行上面一坨东西。

  所以如果 $a$ 后面有大于两个 $\tt b$ 就把 $\tt a$ 调到后面去，且尽量调走一个长度大于 $1$ 的段，否则保留。

```cpp
int n=s.size(),a=0,b=0,a1=0,a2=0,la=-1,fb=-1,len=0;
for(int i=0;i<n;i++){
    if(s[i]=='a') a++;
    else b++;
}
for(int i=0;i<n;i++) if(s[i]=='a') la=i;
for(int i=n-1;~i;i--) if(s[i]=='b') fb=i;
for(int i=0;i<n;i++){
    if(s[i]=='a'&&(!i||s[i-1]=='b')&&(i+1>=n||s[i+1]=='b')) a1++;
}
for(int i=0;i<n;i++){
    if(s[i]=='a') a2++;
    if(i&&s[i]=='a'&&s[i-1]=='a') a2--;
}
a2-=a1;

if(a==n||b==n) cout<<s<<endl;
else if(la==n-1){
    for(int i=la;~i;i--){
        if(s[i]=='a') len++;
        else break ;
    }
    if(len>1) a2--;
    else if(len>0) a1--;
    int cnt=a1+(a2<<1);
    cnt+=cnt&1;
    for(int i=0;i<b;i++) cout<<'b';
    for(int i=0;i<a-cnt;i++) cout<<'a';
    cout<<endl;
}else if(~a&1){
    for(int i=0;i<b;i++) cout<<'b';
    cout<<endl;
}else if(la<fb){
    cout<<'a';
    for(int i=0;i<b;i++) cout<<'b';
    cout<<endl;
}else if(n-la-1<=2){
    for(int i=0;i<n;i++){
        if(s[i]=='b') cout<<s[i];
        else if(i==la) cout<<s[i];
    }
    cout<<endl;
}else{
    for(int i=0;i<n;i++){
        if(s[i]=='a') len++;
        else break ;
    }
    if(a2-(len>1)) a2--;
    else a1--;
    int cnt=a1+(a2<<1);
    cnt+=cnt&1;
    for(int i=0;i<b-2;i++) cout<<'b';
    for(int i=0;i<a-cnt;i++) cout<<'a';
    cout<<endl;
}
```



### [ARC114] C - Sequence Scores

${\sf\color{Black}Normal.}/{\sf\color{Red} Blunder??}$

遗失的赋值没做出来。

令 $a_i=a_j=k~(i<j)$，且 $\nexists p\in (i,j),a_p=k$。

则答案为：

$$\displaystyle \sum_{i=1}^n\sum_{k=1}^m m^{n-1}-\sum_{j=i+1}^nm^{i-1}m^{n-j}(m-k)^{j-i-1}$$

$$=\displaystyle nm^n-\sum_{i=1}^n\sum_{k=1}^m\sum_{j=i+1}^nm^{n-(j-i+1)}(m-k)^{j-i-1}$$

$$=\displaystyle nm^n-\sum_{L=2}^n (n-L+1)m^{n-L}\sum_{k=1}^m (m-k)^{L-2}$$

$$=\displaystyle nm^n-\sum_{L=2}^n (n-L+1)m^{n-L}\sum_{k=0}^{m-1} k^{L-2}$$

```cpp
for(int i=0;i<=m;i++) pw[i][0]=1;
for(int i=1;i<=m;i++){
    for(int j=1;j<=n;j++) pw[i][j]=Mul(pw[i][j-1],i);
}

int ans=Mul(n,pw[m][n]);
for(int l=2;l<=n;l++){
    int sum=0;
    for(int j=0;j<m;j++) AddAs(sum,pw[j][l-2]);
    SubAs(ans,Mul(Mul(n-l+1,pw[m][n-l]),sum));
}
```

### [ARC114] D - Moving Pieces on Line

${\sf\color{Green} UpVote\bigtriangleup}/{\sf\color{Green} Good.}$

-   **性质 1**：一个棋子只会向一个方向走。
    -   原因显然。
-   **性质 2**：不存在两个相向的棋子经过同一条线段。
    -   原因显然。

由上面两个性质我们可以设计状态 $f_{i,j}$ 表示当前考虑到第 $i$ 段，有 $j$ 个向右的棋子（$j<0$ 表示借了 $j$ 个向左的棋子），那么有转移：

-   $f_{i,j}+|j|L_i\rightarrow f_{i+1,j+c_{i+1}}$，其中 $L_i$ 是离散化后 $[i,i+1)$ 段的长度，$c_i$ 表示在第 $i$ 个位置有 $c_i$ 个棋子。
-   $f_{i,j}\rightarrow f_{i,j-1}$。$j>0$ 表示终止某一个向右的棋子，$j\leq 0$ 表示贷款一个向左的棋子。

时间复杂度 $O(n(n+k))$。

```cpp
memset(f,0x3f,sizeof f);
f[N+0]=0;
for(int i=1;i<m;i++){
    memset(g,0x3f,sizeof g);
    for(int j=-n;j<=n;j++) g[N+j+cnt[i]]=f[N+j];
    for(int j=n;j>=-n;j--) g[N+j]=min(g[N+j],g[N+j+1]);
    for(int j=-n;j<=n;j++){
        if((j^c[i])&1) g[N+j]=0x3f3f3f3f3f3f3f3f;
        else g[N+j]+=1ll*abs(j)*(val[i+1]-val[i]);
    }
    memcpy(f,g,sizeof f);
}
for(int j=-n;j<=n;j++) g[N+j+cnt[m]]=f[N+j];
for(int j=n;j>=-n;j--) g[N+j]=min(g[N+j],g[N+j+1]);

cout<<(g[N+0]!=0x3f3f3f3f3f3f3f3f?g[N+0]:-1)<<endl;
```



### [ARC117] D - Miracle Tree

${\sf\color{Green} UpVote\bigtriangleup}/{\sf\color{Green} Good.}$

唉但是挨了两罚。

通过手模样例，发现对于一颗树来说，其任意一个欧拉序的 $pos$ 序列均满足题目限制，其中 $\displaystyle pos_i=\min_{elr_j=i} j$。

~~然后发现题目所给变量名是 $E_i$ 所以是对的。~~

不难想到，要让 $\max pos_i$ 尽量小，就要让最后一次回溯的边尽可能多，那么就是直径。

所以从直径端点开始求欧拉序，并将深度小的子树优先遍历即可。

**证明**（${\sf\color{Tan} Book\dagger}$）：

>   令排列 $p_{1\sim n}$ 为 $[1,n]$ 按照 $E_i$ 排序的结果，即：$E_{p_1}<E_{p_2}<...<E_{p_n}$。
>
>   然后限制从 $\forall 1\leq i,j\leq n,~|E_i-E_j|\geq \operatorname{dis}(i,j)$ 转化为 $\forall 1\leq i\lt n,~E_{p_{i+1}}-E_{p_i}\geq \operatorname{dis}(p_i,p_{i+1})$。
>
>   原理是 $\operatorname{dis}(u,p)+\operatorname{dis}(p,v)\leq \operatorname{dis}(u,v)$。
>
>   所以 $\max E_i=E_{p_n}=E_{p_1}+\sum \operatorname{dis}(p_i,p_{i+1})=1+[2(n-1)-\operatorname{dis}(p_1,p_n)]=2n-1-\operatorname{dis}(p_1,p_n)$。
>
>   当然是 $\operatorname{dis}(p_1,p_n)$ 越大越好，所以 $p_1,p_n$ 分别为直径两端点。

```cpp
inline void GetDis(int x,int fa){
	if(!fa) dis[x]=0;
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa) continue;
		dis[y]=dis[x]+1;
		GetDis(y,x);
	}
}
inline void GetHSon(int x){
	mxdep[x]=dep[x];
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa[x]) continue ;
		fa[y]=x;
		dep[y]=dep[x]+1;
		GetHSon(y);
		mxdep[x]=max(mxdep[x],mxdep[y]);
		if(!hson[x]||mxdep[y]>mxdep[hson[x]]) hson[x]=y;
	}
}
inline void GetEuler(int x){
	pos[x]=++ecnt;
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa[x]) continue ;
		if(y==hson[x]) continue ;
		GetEuler(y),ecnt++;
	}
	if(hson[x]) GetEuler(hson[x]),ecnt++;
}

signed main(){
    ...
    
    GetDis(1,0);
	int p=max_element(dis+1,dis+n+1)-dis;
	GetHSon(p);
	GetEuler(p);
    
    for(int i=1;i<=n;i++) cout<<pos[i]<<' ';cout<<endl;
    
    ...
}
```

### [ARC122] D - XOR Game

${\sf\color{Black}Normal.}/{\sf\color{Peach} Mistake?}$

INF 设小吃了 3 罚。

按二进制位从高到低考虑，假设考虑到第 $i$ 位，那么肯定优先让 $0$ 和 $0$ 两两匹配，$1$ 和 $1$ 两两匹配，然后分别递归考虑。

如果最后一定会剩一个 $0$ 和一个 $1$，那么优先选异或和最小的一对。

对所有这样的 $01$ 对取 max 即可。

```cpp
struct Node{
	int son[2];
}tr[N<<5];
#define son(x,k) tr[x].son[k]

int root,cnt;
inline int Allc(){return ++cnt;}
inline void Init(){root=Allc();}
inline void Clear(){while(cnt) memset(&tr[cnt--],0,sizeof Node());}
inline void Insert(int x){
	int u=root;
	for(int k=29;~k;k--){
		if(!son(u,x>>k&1)) son(u,x>>k&1)=Allc();
		u=son(u,x>>k&1);
	}
}
inline int Min(int x){
	int u=root,ans=0;
	for(int k=29;~k;k--){
		if(son(u,x>>k&1)) u=son(u,x>>k&1);
		else u=son(u,~x>>k&1),ans|=1<<k;
	}
	return ans;
}

inline int GetMin(vector<int> &a,vector<int> &b){
	int ans=INT_MAX;
	Init();
	for(int x:b) Insert(x);
	for(int x:a) ans=min(ans,Min(x));
	Clear();
	return ans;
}
inline int TryMax(vector<int> &v,int d){
	if(!v.size()||!~d) return 0;
	vector<int> s[2];
	for(int x:v) s[x>>d&1].push_back(x);
	if(s[0].size()&1) return GetMin(s[0],s[1]);
	else return max(TryMax(s[0],d-1),TryMax(s[1],d-1));
}

signed main(){
    ...
    
	cout<<TryMax(a,29)<<endl;

	...
}
```



### [ARC122] E - Increasing LCMs

${\sf\color{Green} UpVote\bigtriangleup}/{\sf\color{Tan} Book\dagger}$

首先有一个显然的思路：

考虑 lcm 严格单调增加相当于对于每个 $i$ 来说，存在某一个质因数 $p$ 满足 $v_p(\operatorname{lcm}(a_1,...,a_{i-1}))\lt v_p(a_i)$，其中 $v_p(n)$ 表示最大的满足 $p^k|n$ 的自然数 $k$。这相当于是让 $a_i$ 是 $v_p(a_j)~(1\leq j\leq i)$ 的严格最大值。

正着做不太好做，考虑倒着钦定，不难发现如果有多个数是剩余集合的候选值，他们的顺序不影响答案合法性。

精细实现一下就有了个 $O(nV^{\frac14}+n^2)$ 的做法。

~~但是我忘了 Pollard-Rho 怎么写了啊。~~

题解指出了另一种思路：

将 $\operatorname{lcm}(a_j|j\in S/\{i\})\lt\operatorname{lcm}(a_j|j\in S)$ 转化成 $\operatorname{lcm}(\operatorname{gcd}(a_i,a_j)|j\in S/\{i\})\lt\operatorname{lcm}(\operatorname{gcd}(a_i,a_j)|j\in S)=a_i$。

于是对于一对 $(i,S)$ 可以 $O(|S|\log V)$ 判断是否合法。

枚举每一位的数可以做到 $O(n^3\log V)$。

```cpp
vector<ll> ans;
for(int t=n;t>=1;t--){
    for(int i=1;i<=n;i++){
        if(vis[i]) continue ;
        ll lcm=1;
        for(int j=1;j<=n;j++) if(j!=i&&!vis[j]) lcm=LCM(lcm,GCD(a[i],a[j]));
        if(lcm!=a[i]){
            vis[i]=1;
            ans.push_back(a[i]);
            break ;
        }
    }
}

if(ans.size()<n) cout<<"No"<<endl;
else{
    cout<<"Yes"<<endl;
    reverse(ans.begin(),ans.end());
    for(ll x:ans) cout<<x<<' ';cout<<endl;
}
```

### [ARC123] D - Inc, Dec - Decomposition

${\sf\color{Green} UpVote\bigtriangleup}/{\sf\color{Tan} Book\dagger}$

令 $f_{i,x}$ 表示当前考虑到第 $i$ 个值，钦定 $B_i=x$ 的最小代价。

有转移 $f_{i,x}\leftarrow f_{i-1,y}+|x|+|A_i-x|$，转移条件是 $y\leq x\wedge A_{i-1}-y\geq A_i-x \Leftrightarrow x\geq y+\max (A_i-A_{i-1},0)$。

注意到代价函数是凸的，并且 $f_{i,x}$ 是从 $f_{i-1}$ 的前缀 min 转移来的，考虑 slope trick 维护，时间复杂度 $O(n\log n)$。

```cpp
auto F=[](ll a,ll x){return abs(x)+abs(x-a);};
ll lpos=-2e13,bs=0,ks=0,dlt=0;
priority_queue<ll> p;
for(int i=1;i<=n;i++){
    dlt-=max(a[i]-a[i-1],0);
    ks-=2;
    bs+=F(a[i],lpos-dlt);
    p.push(dlt),p.push(dlt);
    p.push(a[i]+dlt),p.push(a[i]+dlt);
    while(ks+p.size()>0) p.pop();
}
vector<ll> tmp;
while(p.size()) tmp.push_back(p.top()),p.pop();
reverse(tmp.begin(),tmp.end());
tmp.insert(tmp.begin(),lpos);
for(int i=0;i<2*n;i++) bs+=(ks+i)*(tmp[i+1]-tmp[i]);

cout<<bs<<endl;
```

### [ARC205] B - Triangle Toggle

${\sf\color{Black}Normal.}/{\sf\color{Red} Blunder??}$

为啥这我没写对来着？

对于每个点，贪心地进行操作：如果对于一个三元组 $(a,b,c)$ 存在两条以上的白边，做一次操作肯定不亏。

可以证明这个存在上界 $\sum_u n-1-(n-1-d_u\bmod 2)$，且构造满足上界。

```cpp
ll c=0;
for(int i=1;i<=n;i++) c+=((n-1)-(n-1-d[i]&1));
```

### [ARC205] D - Non-Ancestor Matching

${\sf\color{Black}Normal.}/{\sf\color{Green} Good.}$

考虑贪心，不难发现让 LCA 靠近根的点对优先匹配不劣。

如果对于根节点 $u$，对于所有子树 $v$ 均满足 $2siz_v\leq siz_u-1$，那么子树内除了 $u$ 以外的节点均能匹配。

否则 $v$ 子树内则还有 $siz_v-(siz_u-siz_v-1)$ 个节点仍为匹配，那么保留 $siz_u-siz_v-1$ 个额度，从上到下优先匹配即可。

```cpp
inline int Solve(int x,int lft){
	if(!e[x].size()) return 0;
	sort(e[x].begin(),e[x].end(),[](int i,int j){return siz[i]>siz[j];});
	lft=max(lft-1,0);
	int y=e[x].front();
	if(siz[y]-lft>siz[x]-siz[y]-1){
		int tmp=siz[x]-siz[y]-1;
		return tmp+Solve(y,tmp+lft);
	}else return (siz[x]-lft-1)/2;
}

signed main(){
    ...
    
    for(int i=1;i<=n;i++) siz[i]=1;
    for(int i=n;i>=1;i--) siz[fa[i]]+=siz[i];

    cout<<Solve(1,0)<<endl;
    
    ...
}
```

### [CF2150] D. Attraction Theory

${\sf\color{Green} UpVote\bigtriangleup}/{\sf\color{Tan} Book\dagger}$

令 $f_i$ 表示最后 $i$ 上有 $f_i$ 个棋子，最后要求的答案就是 $\displaystyle \sum_f\sum_{i=1}^na_if_i$。

显然 $c_i\neq 0$ 的 $i$ 构成了一个区间，令这个区间为 $[l,r]$，那么对于所有 $l<i<r$，$f_i$ 都必须是奇数。

钦定左右端点的奇偶性，并根据奇偶性先强制给每个段分配 1/2 个棋子，那么对于剩下的棋子来说，设总数为 $S$，那么每个点期望分配到 $\frac S{r-l+1}$ 个棋子，乘上方案数即可得到所有情况的棋子总数。

通过枚举长度以及预处理二阶前缀和可以做到线性。

```cpp
Init(n);
vector<int> sum(n+1,0),ssum(n+1,0);
for(int i=1;i<=n;i++) sum[i]=Add(sum[i-1],a[i]);
for(int i=1;i<=n;i++) ssum[i]=Add(ssum[i-1],sum[i]);

int ans=Mul(n,sum[n]);
for(int len=2;len<=n;len++){
    for(int lx:{0,1}){
        for(int rx:{0,1}){
            int s=n-len-lx-rx;
            if(s<0) continue ;
            if(s&1) continue ;
            s>>=1;
            AddAs(ans,Mul(Sub(ssum[n],Add(ssum[n-len],ssum[len-1])),Mul(C(s+len-1,len-1),Mul(2*s,Inv(len))+1)));
            AddAs(ans,Mul(sum[n-len+1],Mul(lx,C(s+len-1,len-1))));
            AddAs(ans,Mul(Sub(sum[n],sum[len-1]),Mul(rx,C(s+len-1,len-1))));
        }
    }
}

cout<<ans<<endl;
```



### [CF2150] E1. Hidden Single (Version 1)

${\sf\color{Black}Normal.}/{\sf\color{Peach} Mistake?}$

考虑分治，后面忘了。

```cpp
inline int Query(int x,vector<int> s){
	int k;
	cout<<"? "<<x<<' '<<s.size()<<' ';
	for(int y:s) cout<<y<<' ';cout<<endl;
	cout.flush();
	cin>>k;
	assert(~k);
	return k;
}
inline void Solve(int n,vector<int> lft,vector<int> tfl,vector<int> q){
	if(lft.size()==1){
		cout<<"! "<<lft.back()<<endl;
		cout.flush();
		return ;
	}
	int k=q.size()>>1;
	shuffle(q.begin(),q.end(),rng);
	vector<int> t[2]={vector<int>(q.begin(),q.begin()+k),
	vector<int>(q.begin()+k,q.end())};
	vector<int> p[2],trs[2];
	int sum[2]={t[0].size(),t[1].size()};
	for(int x:lft){
		int f[2]={Query(x,t[0]),0};
		if(!f[0]) f[1]=1;
		else f[1]=Query(x,t[1]);
		if(f[0]&&f[1]) sum[0]--,sum[1]--,trs[0].push_back(x),trs[1].push_back(x);
		else if(f[0]) sum[0]-=2,p[0].push_back(x);
		else if(f[1]) sum[1]-=2,p[1].push_back(x);
	}
	for(int x:tfl){
		if(Query(x,t[0])) sum[0]--,trs[0].push_back(x);
		else sum[1]--,trs[1].push_back(x);
	}
	
	if(sum[0]==-1) Solve(n,p[0],trs[0],t[0]);
	else Solve(n,p[1],trs[1],t[1]);
}
```



### [EC Final 2022] Magic

${\sf\color{Black}Normal.}/{\sf\color{Peach} Mistake?}$

不是最大匹配怎么不是两个集合取 min。

发现对于两个相交的区间 $l_i<l_j<r_i<r_j$，$l_j$ 和 $r_i$ 最多只能选一个。注意到 $l$ 和 $r$ 构成二分图，所以二选一转最小割，使用 dinic，时间复杂度 $O(m\sqrt n)$。

```cpp
s=(n<<1)+1,t=(n<<1)+2;
for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
        if(i==j) continue ;
        if(l[i]<l[j]&&l[j]<r[i]&&r[i]<r[j]){
            w[l[j]][r[i]]=1;
        }
    }
}
for(int i=1;i<=n;i++) w[s][l[i]]=w[r[i]][t]=1;

int sum=0,cnt=0;
while(BFS()) sum+=DFS(s,inf),cnt++;

cout<<(n<<1)-sum<<endl;
```

### [EC Final 2022] Rectangle

${\sf\color{Green} UpVote\bigtriangleup}/{\sf\color{Tan} Book\dagger}$

代码难度要给到 ${\sf\color{Red} DownVote\bigtriangledown}$。

可以分为三竖和两竖一横两种，剩下的翻转坐标系即可。

- 对于三竖的情况：考虑枚举中间那条线，两边的线取值范围就是两边矩形的交。

- 对于两竖的情况：

  考虑对横线扫描线，那么就是一些加矩形和删矩形的操作。

  令剩下的两条线分别是 $x=L$ 和 $x=R$，首先有限制 $L\leq \min r_i,R\geq \max l_i$。令 $f(L)$ 为左边是 $L$ 的时候 $R$ 上界，那么有 $\displaystyle f(L)=\min_{L<l_i} r_i$，考虑到有撤销操作，把前缀 check min 转化为单点插入求后缀最小值之和，使用楼房重建维护。

边界情况很多。

```cpp
const int INV2=Inv(2);
const int INV6=Inv(6);
inline int C1(int x){return Add(x,0);}
inline int C2(int x){return Mul(Mul(x,x-1),INV2);}
inline int C3(int x){return Mul(Mul(Mul(x,x-1),x-2),INV6);}

int p[N][4],n,xm,ym;
vector<int> xval,yval;
inline int Lx(int i){return xval[i+1]-xval[i];}
inline int Lx(int l,int r){return l<=r?xval[r+1]-xval[l]:0;}
inline int Lx(array<int,2> p){return Lx(p[0],p[1]);}
inline int Ly(int i){return yval[i+1]-yval[i];}
inline int Ly(int l,int r){return l<=r?yval[r+1]-yval[l]:0;}
inline int Ly(array<int,2> p){return Ly(p[0],p[1]);}
inline void Discretize(){
	xval=yval={int(-1e9-1),1,int(1e9+1)};
	for(int i=1;i<=n;i++){
		xval.push_back(p[i][0]);
		yval.push_back(p[i][1]);
		xval.push_back(p[i][2]+1);
		yval.push_back(p[i][3]+1);
	}
	sort(xval.begin(),xval.end());
	sort(yval.begin(),yval.end());
	xval.erase(unique(xval.begin(),xval.end()),xval.end());
	yval.erase(unique(yval.begin(),yval.end()),yval.end());
	for(int i=1;i<=n;i++){
		p[i][0]=lower_bound(xval.begin(),xval.end(),p[i][0])-xval.begin();
		p[i][1]=lower_bound(yval.begin(),yval.end(),p[i][1])-yval.begin();
		p[i][2]=upper_bound(xval.begin(),xval.end(),p[i][2])-xval.begin()-1;
		p[i][3]=upper_bound(yval.begin(),yval.end(),p[i][3])-yval.begin()-1;
	}
	xm=xval.size()-2,ym=yval.size()-2;
}
inline void Flip(){
	swap(xm,ym);
	swap(xval,yval);
	for(int i=1;i<=n;i++) for(int k:{0,2}) swap(p[i][k],p[i][k|1]);
}
inline void ClearVal(){
	xval.clear();
	yval.clear();
}

inline int Work1(){
	int ans=0,lmax=0,rmin=xm+1;
	vector<array<int,2>> f(xm+2,{1,xm}),g(xm+2,{1,xm});
	auto Merge=[](array<int,2> x,array<int,2> y)->array<int,2>{return {max(x[0],y[0]),min(x[1],y[1])};};
	for(int i=1;i<=n;i++){
		f[p[i][2]]=Merge(f[p[i][2]],{p[i][0],p[i][2]});
		g[p[i][0]]=Merge(g[p[i][0]],{p[i][0],p[i][2]});
		lmax=max(lmax,p[i][0]);
		rmin=min(rmin,p[i][2]);
	}
	for(int i=1;i<=xm;i++) f[i]=Merge(f[i],f[i-1]);
	for(int i=xm;i>=1;i--) g[i]=Merge(g[i],g[i+1]);
	for(int i=0;i<=xm+1;i++) f[i]=Merge(f[i],{1,i});
	for(int i=xm+1;i>=0;i--) g[i]=Merge(g[i],{i,xm});
	for(int i=1;i<=xm;i++){
		AddAs(ans,Mul(Mul(C1(Lx(f[i-1])),C1(Lx(g[i+1]))),C1(Lx(i))));
		if(i<=rmin) AddAs(ans,Mul(C1(Lx(g[i+1])),C2(Lx(i))));
		if(i>=lmax) AddAs(ans,Mul(C1(Lx(f[i-1])),C2(Lx(i))));
		if(lmax<=i&&i<=rmin) AddAs(ans,C3(Lx(i)));
	}
	return ans;
}

struct Node{
	int l,r;
	int dat,sum;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat
#define sum(x) tr[x].sum
#define len(x) (Lx(l(x),r(x)))

inline int Calc(int x,int k){
	if(k<=dat(x)) return Mul(len(x),k);
	if(l(x)==r(x)) return sum(x);
	if(k<=dat(x<<1|1)) return Add(Mul(len(x<<1|1),k),Calc(x<<1,k));
	else return Add(Calc(x<<1|1,k),Sub(sum(x),sum(x<<1|1)));
}
inline void PushUp(int x){
	dat(x)=min(dat(x<<1),dat(x<<1|1));
	if(dat(x<<1|1)<=dat(x<<1)) sum(x)=Add(sum(x<<1|1),Mul(len(x<<1),dat(x<<1|1)));
	else sum(x)=Add(sum(x<<1|1),Calc(x<<1,dat(x<<1|1)));
}
inline void Build(int x,int l,int r,int k){
	l(x)=l,r(x)=r,dat(x)=sum(x)=0;
	if(l(x)==r(x)) return dat(x)=k,sum(x)=Mul(len(x),k),void();
	int mid=l(x)+r(x)>>1;
	Build(x<<1,l,mid,k),Build(x<<1|1,mid+1,r,k);
	PushUp(x);
}
inline void Update(int x,int pos,int k){
	if(l(x)==r(x)) return dat(x)=k,sum(x)=Mul(len(x),k),void();
	int mid=l(x)+r(x)>>1;
	if(pos<=mid) Update(x<<1,pos,k);
	else Update(x<<1|1,pos,k);
	PushUp(x);
}
inline int FindL(int x,int k){
	if(l(x)==r(x)) return l(x)+(dat(x)<k);
	if(dat(x<<1|1)<k) return FindL(x<<1|1,k);
	else return FindL(x<<1,k);
}
inline array<int,2> Query(int x,int l,int r,int k){
	if(l<=l(x)&&r(x)<=r) return array<int,2>({min(dat(x),k),Calc(x,k)});
	array<int,2> res({k,0});
	int mid=l(x)+r(x)>>1;
	if(r>mid){
		auto tmp=Query(x<<1|1,l,r,res[0]);
		res[0]=min(res[0],tmp[0]);
		AddAs(res[1],tmp[1]);
	}
	if(l<=mid){
		auto tmp=Query(x<<1,l,r,res[0]);
		res[0]=min(res[0],tmp[0]);
		AddAs(res[1],tmp[1]);
	}
	return res;
}
inline int GetSum(int l,int r){
	return Sub(Query(1,l,xm,inf)[1],r<xm?Query(1,r+1,xm,inf)[1]:0);
}
inline void Puts(int x){
	if(l(x)==r(x)) return ;
	Puts(x<<1),Puts(x<<1|1);
}

struct DelHeap{
	priority_queue<int> p,q;
	inline void Insert(int x){p.push(x);}
	inline void Erase(int x){q.push(x);}
	inline int Top(){
		while(q.size()&&p.top()==q.top()) p.pop(),q.pop();
		return p.top();
	}
	inline int Size(){return p.size()-q.size();}
	inline void Clear(){
		while(p.size()) p.pop();
		while(q.size()) q.pop();
	}
}q[N],lmx,rmn;
inline void Init(){
	lmx.Insert(1);
	rmn.Insert(-xm);
	Build(1,1,xm,1e9+1);
	for(int i=1;i<=xm;i++) q[i].Insert(-1e9-1);
}
inline void ClearHeap(){
	lmx.Clear();
	rmn.Clear();
	for(int i=1;i<=xm;i++) q[i].Clear();
}
inline void Insert(int x0,int x1){
	lmx.Insert(x0),rmn.Insert(-x1);
	if(!--x0) return ;
	int tmp=-q[x0].Top();
	q[x0].Insert(-xval[x1+1]);
	if(-q[x0].Top()!=tmp) Update(1,x0,-q[x0].Top());
}
inline void Erase(int x0,int x1){
	lmx.Erase(x0),rmn.Erase(-x1);
	if(!--x0) return ;
	int tmp=-q[x0].Top();
	q[x0].Erase(-xval[x1+1]);
	if(-q[x0].Top()!=tmp) Update(1,x0,-q[x0].Top());
}
inline int Work2(){
	int ans=0;
	Init();
	vector<int> dlt(xm+1,0);
	for(int i=1;i<=xm;i++){
		dlt[i]=Sub(C2(Lx(i)),Mul(Lx(i),xval[i+1]));
		AddAs(dlt[i],dlt[i-1]);
	}
	vector<vector<array<int,2>>> ins(ym+2),ers(ym+2);
	for(int i=1;i<=n;i++){
		ins[1].push_back({p[i][0],p[i][2]});
		ers[p[i][1]].push_back({p[i][0],p[i][2]});
		ins[p[i][3]+1].push_back({p[i][0],p[i][2]});
	}
	for(int i=1;i<=ym;i++){
		for(auto p:ins[i]) Insert(p[0],p[1]);
		for(auto p:ers[i]) Erase(p[0],p[1]);
		int l=FindL(1,xval[lmx.Top()]),r=-rmn.Top();
		if(l>r) continue ;
		int tmp=GetSum(l,r);
		if(r<lmx.Top()){
			SubAs(tmp,Mul(Lx(l,r),xval[lmx.Top()]));
		}else{
			int p=lmx.Top();
			SubAs(tmp,Mul(Lx(l,p-1),xval[lmx.Top()]));
			AddAs(tmp,Sub(dlt[r],dlt[p-1]));
		}
		AddAs(ans,Mul(C1(Ly(i)),tmp));
	}
	ClearHeap();
	return ans;
}

signed main(){
    ...
    
    cin>>n;
    for(int i=1;i<=n;i++) for(int k:{0,1,2,3}) cin>>p[i][k];

    int ans=0;
    Discretize();
    AddAs(ans,Work1());
    AddAs(ans,Work2());
    Flip();
    AddAs(ans,Work1());
    AddAs(ans,Work2());

    cout<<ans<<endl;
    
	...
}
```

### [ROIR 2024\] Игра с таблицей

${\sf\color{Black}Normal.}/{\sf\color{Green} Good.}$

考虑枚举删除哪些行，并将列划分成均等的两部分，分别维护在删除行的基础上删除列的贡献，排序后双指针判断答案即可，时间复杂度 $O(n2^{\frac 32n})$。

```cpp
int h=(m+1)/2;
vector<ll> s1(1<<h,0),s2(1<<m-h,0),s3(1<<n,0);
for(int i=0;i<n;i++){
    for(int j=0;j<h;j++){
        for(int s=0;s<(1<<h);s++) if(s>>j&1) s1[s]+=a[i][j];
    }
    for(int j=h;j<m;j++){
        for(int s=0;s<(1<<m-h);s++) if(s>>j-h&1) s2[s]+=a[i][j];
    }
    for(int j=0;j<m;j++){
        for(int s=0;s<(1<<n);s++) if(s>>i&1) s3[s]+=a[i][j];
    }
}
k=s3[(1<<n)-1]-k;

for(int s=0;s<(1<<n);s++){
    if(s){
        int t=s^s-1;
        for(int i=0;i<n;i++){
            if(~t>>i&1) continue ;
            if(s>>i&1){
                for(int j=0;j<h;j++){
                    for(int u=0;u<(1<<h);u++) if(u>>j&1) s1[u]-=a[i][j];
                }
                for(int j=h;j<m;j++){
                    for(int u=0;u<(1<<m-h);u++) if(u>>j-h&1) s2[u]-=a[i][j];
                }
            }else{
                for(int j=0;j<h;j++){
                    for(int u=0;u<(1<<h);u++) if(u>>j&1) s1[u]+=a[i][j];
                }
                for(int j=h;j<m;j++){
                    for(int u=0;u<(1<<m-h);u++) if(u>>j-h&1) s2[u]+=a[i][j];
                }
            }
        }
    }

    vector<ll> p1(s1),p2(s2);
    sort(p1.begin(),p1.end(),less<ll>());
    sort(p2.begin(),p2.end(),less<ll>());
    for(ll x:p1){
        while(p2.size()&&x+p2.back()>k-s3[s]) p2.pop_back();
        if(p2.size()&&p2.back()+x==k-s3[s]){
            int p=0,q=0;
            for(int t=0;t<(1<<h);t++) if(s1[t]==x) p=t;
            for(int t=0;t<(1<<m-h);t++) if(s2[t]==p2.back()) q=t;
            p|=q<<h;
            cout<<"YES"<<endl;
            cout<<__builtin_popcount(s)+__builtin_popcount(p)<<endl;
            for(int i=0;i<n;i++) if(s>>i&1) cout<<1<<' '<<i+1<<endl;
            for(int i=0;i<m;i++) if(p>>i&1) cout<<2<<' '<<i+1<<endl;
            return 0;
        }
    }
}

cout<<"NO"<<endl;
```



### [ROIR 2024] Обходы бинарного дерева

${\sf\color{Black}Normal.}/{\sf\color{Green} Good.}$

贡献可以分为若干个部分：

-   如果 $i$ 在某个节点的右儿子方向，那么要加上其左儿子的大小。
-   如果 $i$ 在某个节点的左儿子方向，且该节点的点权大于 $0$，那么产生 $1$ 的贡献。
-   如果 $i$ 在某个节点的右儿子方向，且该节点的点权不小于 $0$，那么产生 $1$ 的贡献。

第一部分是简单的，现在考虑如何维护第二第三个贡献。

考虑对序列分块，对每个节点找出最低的块内祖先，整块就是直接预处理权值分别为 $-1/0/1$ 时每个点的块内祖先贡献和，散块 $O(\sqrt n)$ 重构每个点的块内祖先的贡献和即可。查询就是对每个块找最低块内祖先计算贡献，时间复杂度 $O((n+q)\sqrt n)$。

```cpp
int lc[N],rc[N],fa[N],id[N],dfn[N],siz[N],t[N],n,q,icnt,dcnt;
inline void GetId(int x){
	if(!x) return ;
	dfn[x]=++dcnt;
	fa[lc[x]]=fa[rc[x]]=x;
	t[lc[x]]=t[x];
	GetId(lc[x]);
	id[x]=++icnt;
	t[rc[x]]=t[x]+siz[lc[x]];
	GetId(rc[x]);
	siz[x]=siz[lc[x]]+siz[rc[x]]+1;
}

int blk[N],p[N],L[N],R[N],upl[N],upr[N],w[N],c[N],tag[S],lst[N][S],B;
inline void GetLast(int x){
	if(!x) return ;
	for(int i=1;i<=blk[n];i++) lst[x][i]=lst[fa[x]][i];
	lst[x][blk[x]]=x;
	GetLast(lc[x]),GetLast(rc[x]);
}

inline void Build(int x){
	for(int i=L[x];i<=R[x];i++){
		int u=p[i],f=lst[fa[u]][x];
		if(!f){
			w[u]=0;
			continue ;
		}
		w[u]=w[f];
		if(id[u]<id[f]&&c[f]<0) w[u]++;
		if(id[u]>id[f]&&c[f]<=0) w[u]++;
	}
}
inline void PushTag(int x,int k){tag[x]=k;}
inline void PushDown(int x){
	if(tag[x]==-2) return ;
	for(int i=L[x];i<=R[x];i++) c[i]=tag[x];
	tag[x]=-2;
}
inline void BAssign(int l,int r,int k){
	PushDown(blk[l]);
	for(int i=l;i<=r;i++) c[i]=k;
	Build(blk[l]);
}
inline void Assign(int l,int r,int k){
	if(blk[l]==blk[r]) return BAssign(l,r,k);
	BAssign(l,R[blk[l]],k),BAssign(L[blk[r]],r,k);
	for(int i=blk[l]+1;i<blk[r];i++) PushTag(i,k);
}
inline int GetW(int p){
	if(tag[blk[p]]==-2) return w[p];
	else{
		if(tag[blk[p]]==-1) return upl[p]+upr[p];
		else if(tag[blk[p]]==0) return upr[p];
		else return 0;
	}
}
inline int GetC(int p){return tag[blk[p]]==-2?c[p]:tag[blk[p]];}
inline int Query(int x){
	int ans=t[x];
	if(GetC(x)==-1) ans+=1;
	else if(GetC(x)==0) ans+=siz[lc[x]]+1;
	else if(GetC(x)==1) ans+=siz[lc[x]]+siz[rc[x]]+1;
	for(int i=1;i<=blk[n];i++){
		int u=lst[x][i];
		if(!u) continue ;
		ans+=GetW(u);
		if(u==x) continue ;
		if(id[x]<id[u]&&GetC(u)<0) ans++;
		if(id[x]>id[u]&&GetC(u)<=0) ans++;
	}
	return ans;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>lc[i]>>rc[i];
	GetId(1);

	B=sqrt(n);
	for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
	for(int i=1;i<=n;i++) R[blk[i]]=i;
	for(int i=n;i>=1;i--) L[blk[i]]=i;
	for(int i=1;i<=n;i++){
		for(int j=L[i];j<=R[i];j++) p[j]=j;
		sort(p+L[i],p+R[i]+1,[](int i,int j){return dfn[i]<dfn[j];});
	}
	GetLast(1);
	for(int i=1;i<=blk[n];i++){
		for(int j=L[i];j<=R[i];j++){
			int u=p[j],f=lst[fa[u]][i];
			if(!f) continue ;
			upl[u]=upl[f],upr[u]=upr[f];
			if(id[u]<id[f]) upl[u]++;
			else upr[u]++;
		}
		tag[i]=-2;
	}
	for(int i=1;i<=n;i++) c[i]=-1,w[i]=upl[i]+upr[i];

	while(q--){
		int op;
		cin>>op;
		if(op==1){
			int l,r,x;
			cin>>l>>r>>x;
			Assign(l,r,x);
		}else{
			int u;
			cin>>u;
			cout<<Query(u)<<endl;
		}
	}

	return 0;
}
```



### [ICPC 2024 Nanjing R] C. Topology

${\sf\color{Green} UpVote\bigtriangleup}/{\sf\color{Green} Good.}$

令 $q=p^{-1}$，则 $p_i=i\Leftrightarrow q_i=i$。

注意到可以先将 $i$ 的子树删去，最后把节点 $i$ 再塞到第 $i-1$ 个位置后面，答案可以表示成 $q_{fa_i}<i$ 的方案数乘一些组合系数。

具体地，令 $f_u$ 表示以 $u$ 为根的拓扑序数，$g_u$ 表示以 $fa_u$ 为根刨去 $u$ 子树的拓扑序数，$h_{u,i}$ 表示整棵树刨去 $u$ **真子树**且 $q_u=i$ 的方案数。

则有以下递推式：

-   $\displaystyle f_u=(siz_u-1)!\prod_{fa_v=u}\frac 1{siz_v!}f_v$。
-   $\displaystyle g_u=\frac {f_{fa_u}}{f_u\binom{siz_{fa_u}-1}{siz_u}}$。
-   $\displaystyle h_{u,i}=\sum_{j=1}^{i-1} g_uh_{fa_u,j}\binom{n-j-siz_u}{siz_{fa_u}-siz_u-1}$。

则 $\displaystyle ans_i=f_ih_{i,i}\binom{n-i}{siz_i-1}$，递推时间复杂度 $O(n^2)$。

```cpp
vector<int> e[N];
int fa[N],siz[N],f[N],g[N],n;
inline void DFS(int x){
	siz[x]=1,f[x]=g[x]=1;
	for(int y:e[x]){
		fa[y]=x;
		DFS(y);
		siz[x]+=siz[y];
		MulAs(f[x],C(siz[x]-1,siz[y]));
		MulAs(f[x],f[y]);
	}
	for(int y:e[x]) g[y]=Mul(f[x],Inv(Mul(C(siz[x]-1,siz[y]),f[y])));
}
int h[N][N],tmp[N][N];
inline void Calc(int x){
	if(x==1) h[1][1]=1;
	else{
		for(int p=1;p<=n;p++){
			tmp[x][p]=Mul(h[fa[x]][p],Mul(g[x],C(n-siz[x]-p,siz[fa[x]]-siz[x]-1)));
		}
		for(int p=1,sum=0;p<=n-siz[x]+1;p++){
			h[x][p]=sum;
			AddAs(sum,tmp[x][p]);
		}
	}
	for(int y:e[x]) Calc(y);
}

signed main(){
	...
    
	Init(n);
	DFS(1);
	Calc(1);
	for(int i=1;i<=n;i++) cout<<Mul(Mul(h[i][i],f[i]),C(n-i,siz[i]-1))<<' ';cout<<endl;

	...
}
```

### [BalticOI 2025] BOI acronym

${\sf\color{Black}Normal.}/{\sf\color{Tan} Book\dagger}$

AD-HOCCCCCC???

首先可以轻易地确定最左边和最右边的 $\tt B$ 的位置，令其分别为 $L,R$。

从 $L+1$ 到 $R-1$ 逐位考虑是否为 $\tt B$，假设当前位置为 $i$：

-   若 $c_{L,i-1}=c_{L+1,i-1}+1$：那么说明 $\tt B$ 是 $(L,i)$ 的众数。判断 $c_{L,i}$ 是否等于 $c_{L,i-1}+1$ 即可。
-   若 $c_{i+1,R}=c_{i+1,R-1}+1$：那么说明 $\tt B$ 是 $(i,R)$ 的众数。判断 $c_{i,R}$ 是否等于 $c_{i+1,R}+1$ 即可。
-   如果上面两个都不满足，那么说明一遍的众数是 $\tt O$，另一边是 $\tt I$，否则不满足 $\tt B$ 是严格众数，所以需要判断 $i$ 在 $(L,i]$ 和 $[i,R)$ 中是否作为众数出现。

时间复杂度 $O(n)$。

```cpp
int l=0,r=0;
for(int i=1;i<=n;i++) if(a[i][n]==a[1][n]) l=i;
for(int i=n;i>=1;i--) if(a[1][i]==a[1][n]) r=i;

if(a[1][n]==1) cout<<l<<endl;
else if(a[1][n]==2) cout<<l<<' '<<r<<endl;
else{
    cout<<l<<' ';
    for(int i=l+1;i<r;i++){
        if(a[l][i]==a[l+1][i]+1){
            if(a[l][i]==a[l][i-1]+1) cout<<i<<' ';
        }else if(a[i][r]==a[i][r-1]+1){
            if(a[i][r]==a[i+1][r]+1) cout<<i<<' ';
        }else{
            if(a[l+1][i]==a[l+1][i-1]&&a[i][r-1]==a[i+1][r-1]) cout<<i<<' ';
        }
    }
    cout<<r<<endl;
}
```



### [BalticOI 2025] Developer

${\sf\color{Green} UpVote\bigtriangleup}/{\sf\color{Tan} Book\dagger}$

称比两边高的 $b$ 的连续段 $[l,r]$ 为峰，反之为谷。

令 $f_{i,x}$ 表示 $b_i=x$，且 $[?,i]$ 为峰，反之 $g_{i,x}$ 表示 $b_i=x$，且 $[?,i]$ 为谷。

有转移：

-   $\displaystyle f_{i,x}=\min(\min_{j<i} g_{i-1,j},f_{i-1,j})+|x-a_i|$。
-   $\displaystyle g_{i,x}=\min(\min_{j>i} f_{i-1,j},g_{i-1,j})+|x-a_i|$。

朴素计算时间复杂度为 $O(nV)$。

有结论只有 $\displaystyle i\in [1,n],x\in \bigcup_{j=1}^n \{a_j-1,a_j,a_j+1\}$ 是有效的状态。

 进一步的结论是只有 $\displaystyle i\in [1,n],x\in \bigcup_{j=i-4}^{i+4} \{a_j-1,a_j,a_j+1\}$ 是有效的状态。

转移时间复杂度 $O(nK^2)$，其中 $\max K=27$。

**证明**：

>   称 $\exists i\in[l,r],a_i=b_i$ 的区间 $[l,r]$ 为好区间，由此推广可以得到对坏区间，好峰/谷和坏峰/谷的定义。
>
>   有以下结论：
>
>   - **性质 1**：对于最优解的一个峰 $[l,r]$ 中所有 $l\lt i\lt r$ 有 $a_i\gt b_l$。
>
>     >   **证明**：对于 $a_i\lt b_l$ 的显然可以让 $b_i=a_i$，即令 $[i,i]$ 单开一个谷。
>
>   - **性质 2**：对于最优解的一个峰 $[l,r]$ 中任意坏的子区间 $[p,q]$（不包含 $[l,r]$）的长度均不超过 $3$。
>
>     >   **证明**：下文中令 $\displaystyle x=b_l=b_r,y=\min_{i=p}^q a_i$
>     >
>     >   -   若 $l\lt p\leq q\lt r$：则可以将 $b[p:q]$ 改为 $x-1,y,...y,x-1$ 的形式，在 $q-p+1>3$ 时肯定不劣。
>     >   -   若 $l\leq p\leq q\lt r$：则可以将 $b[p:q]$ 改为 $y,...y,x-1$ 的形式，在 $q-p+1>3$ 时肯定不劣。
>     >   -   若 $l\lt p\leq q\leq r$：则可以将 $b[p:q]$ 改为 $x-1,y,...y$ 的形式，在 $q-p+1>3$ 时肯定不劣。
>
>   - **性质 3**：对于最优解的一个峰 $[l,r]$，若整个峰都是坏的，那么 $[l=r][a_l<b_l]([b_l=b_{l-1}+1]+[b_r=b_{r+1}+1])=1$。
>
>     >   **证明**：下文中令 $\displaystyle H=\sum_{i=l}^r [a_i\gt b_i],\displaystyle L=\sum_{i=l}^r [a_i\lt b_i]$。
>     >
>     >   -   若 $H\geq L$，则可以升高所有 $b_i$ 至 $\displaystyle \min_{i\in [l,r]\wedge a_i>b_i} a_i$，这肯定不劣，且 $[l,r]$ 变为好峰。
>     >   -   若 $H<L$，由性质 1 得到 $L\leq 2$，所以 $r-l+1\leq 3$。
>     >       -   若 $\displaystyle \min(b_{l-1},b_{r+1})<\min_{i=l}^r a_i$，那么显然可以把所有 $b_i$ 降低到 $\displaystyle \min_{i=l}^r a_i$，$[l,r]$ 变为好峰。
>     >       -   若 $L=2$，则 $a_l<b_l,a_r<b_r$。
>     >           -   若 $r-l+1=2$，令 $x=b_{l-1},y=b_{r+1}$，那么 $x,y+1$ 和 $x+1,y$ 中间肯定有一个合法，并且缩短了峰的长度至 $1$，转到 $H=0,L=1$ 的情况。
>     >           -   若 $r-l+1=3$，令 $x=b_{l-1},y=b_{r+1}$，那么 $x,?,?$ 和 $?,?,y$ 中间肯定有一个合法，并且缩短了峰的长度至 $2$，转到 $H=L=1$ 的情况。
>     >       -   若 $L=1\gt H=0$：
>     >           -   若 $b_{l-1}=b_{r+1}$，那么直接令 $b_l=b_{l-1}=b_{r+1}$，这个峰直接就没了。
>     >           -   否则令 $b_l=\max(b_{l-1},b_{r+1})+1$ 最优。
>
>   - **性质 4**：对于最优解的一个坏峰 $[i,i]$，如果 $b_i=b_{i+1}+1$，那么 $[i+1,i+1]$ 不能是坏谷。
>
>     >   **证明**：
>     >
>     >   由定义可以得到，$a_i\lt b_i,a_{i+1}\gt b_{i+1}$。
>     >
>     >   由性质 3 可以得到，$b_{i-1}\lt b_{i+1}$。
>     >
>     >   -   若 $a_i\gt b_{i-1}$，那么可以将 $b_i,b_{i+1}$ 全部降低 $b_i-a_i$，这肯定不劣。
>     >   -   若 $a_i\leq b_{i-1}$，那么可以让 $b_i=b_{i+1}=b_{i-1}$，这肯定不劣。
>
>   - **性质 4 推论**：坏峰的两端不能都是坏谷。
>
>   以上 4 个性质以及 1 个推论对于谷仍然适用。
>
>   因此最坏的情况是：峰（长度为 $3$ 的坏后缀）+ 坏谷 + 坏峰 + 谷（长度为 $3$ 的坏前缀）。
>
>   这种情况的坏区间长度为 $8$，所以 $[i-4,i+4]$ 中至少有一个好位置。
>
>   对于坏位置，显然除了好位置 $\pm 0/1$ 的值有用。
>
>   所以只有$\displaystyle i\in [1,n],x\in \bigcup_{j=i-4}^{i+4} \{a_j-1,a_j,a_j+1\}$ 是有效的状态。

```cpp
for(int i=1;i<=n;i++){
    for(int j=max(1-i,-4);j<=min(n-i,4);j++){
        for(int k:{-1,0,1}) val[i].push_back(a[i+j]+k);
    }
    sort(val[i].begin(),val[i].end());
    val[i].erase(unique(val[i].begin(),val[i].end()));
    m[i]=val[i].size();
}

ll ans=0x3f3f3f3f3f3f3f3f;
memset(f,0x3f,sizeof f);
memset(g,0x3f,sizeof g);
for(int j=0;j<m[1];j++) f[1][j]=g[1][j]=0;
for(int i=1;i<=n;i++){
    for(int j=0;j<m[i];j++){
        f[i][j]+=abs(a[i]-val[i][j]);
        g[i][j]+=abs(a[i]-val[i][j]);
    }
    for(int j=0;j<m[i];j++){
        for(int k=0;k<m[i+1];k++){
            if(val[i][j]<val[i+1][k]) g[i+1][k]=min(g[i+1][k],f[i][j]);
            else if(val[i][j]==val[i+1][k]){
                f[i+1][k]=min(f[i+1][k],f[i][j]);
                g[i+1][k]=min(g[i+1][k],g[i][j]);
            }else f[i+1][k]=min(f[i+1][k],g[i][j]);
        }
    }
}
for(int j=0;j<m[n];j++) ans=min(ans,min(f[n][j],g[n][j]));
```

### [BalticOI 2025\] Exponents

${\sf\color{Green} UpVote\bigtriangleup}/{\sf\color{Tan} Book\dagger}$

首先将题目转化成令 $b_i=\max(a_i,a_i)$，每次可以删除一个 $b_i$，并让 $b_{i-1}$ 和 $b_{i+1}$ 对 $b_i+1$ check max，令最后删的那个数 $+1$ 的值最小。不难发现有两个性质：

-   按 $b_i$ 从小到大做肯定不劣。
-   长度为 $k$ 的 $b_i$ 连续段可以合成一个长度为 $\lfloor\frac k{2^t}\rfloor$ 的 $b_i+t$ 连续段。

那么对于区间 $[l,r]$，如果我们把 $[l,r]$ 的广义笛卡尔树建出来，就可以直接在上面 DP 了，暴力做的时间复杂度是 $O(nq)$ 的。

下文中令 $L=\min (\{i|l\leq i,j\leq r,a_i\geq a_j\}),R=\max (\{i|l\leq i,j\leq r,a_i\geq a_j\})$。

考虑把 $[l,r]$ 的笛卡尔树分为三个部分：$[l,L),[L,R],(R,r]$。

对于 $[L,R]$ 的部分，发现这部分的结构可以在 $[1,n]$ 的笛卡尔树上找到对应的连通块计算贡献，前缀和预处理一下即可。

对于 $[l,L)$ 和 $(R,r]$ 的部分，发现这部分的结构可以在 $[l,n]$ 和 $[1,r]$ 的笛卡尔树上找到对应的连通块计算贡献，考虑离线下来，并动态维护前缀或后缀的笛卡尔树。可以暴力向上更新，均摊时间复杂度是 $O(n)$ 的。

最后合并一下答案就行了。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=3e5+9;
const int lgN=20;

int a[N],ql[N],qr[N],bel[N],maxl[N],maxr[N],ans[N],cnt[N],cur[N],n,q;
vector<int> w[N],pos[N],lq[N],rq[N];
inline int Shift(int x,int k){return k<=20?x>>k:0;}

int mxp[N][lgN],lg[N];
inline int Cmp(int i,int j){return a[i]<a[j]?j:i;}
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

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=q;i++){
		cin>>ql[i]>>qr[i];
		if(ql[i]==qr[i]) ans[i]=a[ql[i]];
		qr[i]--;
	}
	for(int i=1;i<=n;i++) a[i]=max(a[i],a[i+1]);

	Init();
	vector<int> stk;
	for(int i=1;i<=n;i++){
		int tmp=0,c=0;
		while(stk.size()&&a[stk.back()]<a[i]){
			tmp=Shift(tmp,a[stk.back()]-c);
			w[stk.back()].push_back(w[stk.back()].back()+tmp);
			tmp=w[stk.back()].back()+pos[stk.back()].size()-1;
			c=a[stk.back()];
			stk.pop_back();
		}
		tmp=Shift(tmp,a[i]-c);
		if(!stk.size()||a[stk.back()]>a[i]){
			pos[i].push_back(0);
			pos[i].push_back(i);
			w[i].push_back(0);
			w[i].push_back(tmp);
			stk.push_back(i);
		}else{
			pos[stk.back()].push_back(i);
			w[stk.back()].push_back(w[stk.back()].back()+tmp);
		}
		bel[i]=stk.back();
		if(i==n){
			int tmp=0,c=0;
			while(stk.size()){
				tmp=Shift(tmp,a[stk.back()]-c);
				w[stk.back()].push_back(w[stk.back()].back()+tmp);
				tmp=w[stk.back()].back()+pos[stk.back()].size()-1;
				c=a[stk.back()];
				stk.pop_back();
			}
		}
	}
	for(int i=1;i<=q;i++){
		if(ql[i]>qr[i]) continue ;
		int p=bel[MaxPos(ql[i],qr[i])];
		int lp=lower_bound(pos[p].begin(),pos[p].end(),ql[i])-pos[p].begin();
		int rp=upper_bound(pos[p].begin(),pos[p].end(),qr[i])-pos[p].begin()-1;
		ans[i]=a[p];
		maxl[i]=pos[p][lp];
		maxr[i]=pos[p][rp];
		cnt[i]+=w[p][rp]-w[p][lp];
		cnt[i]+=rp-lp+1;
		lq[ql[i]].push_back(i);
		rq[qr[i]].push_back(i);
	}
	stk.clear();

	for(int i=1;i<=n;i++){
		int u=0;
		while(stk.size()&&a[stk.back()]<=a[i]) u=stk.back(),stk.pop_back();
		if(u) cur[i]=Shift(cur[u],a[i]-a[u]);
		stk.push_back(i);
		cur[i]++;
		array<int,2> lst({Shift(cur[u],a[i]-a[u]),cur[i]});
		for(int j=stk.size()-2;~j;j--){
			if(lst[0]==lst[1]) break ;
			int k=a[stk[j]]-a[stk[j+1]];
			lst={cur[stk[j]],cur[stk[j]]-Shift(lst[0],k)+Shift(lst[1],k)};
			cur[stk[j]]=lst[1];
		}
		for(int j:rq[i]){
			int k=lower_bound(stk.begin(),stk.end(),maxr[j])-stk.begin()+1;
			if(k>=stk.size()) continue ;
			cnt[j]+=Shift(cur[stk[k]],a[stk[k-1]]-a[stk[k]]);
		}
	}
	for(int i=1;i<=n;i++) cur[i]=0;
	stk.clear();
	
	for(int i=n;i>=1;i--){
		int u=0;
		while(stk.size()&&a[stk.back()]<=a[i]) u=stk.back(),stk.pop_back();
		if(u) cur[i]=Shift(cur[u],a[i]-a[u]);
		stk.push_back(i);
		cur[i]++;
		array<int,2> lst({Shift(cur[u],a[i]-a[u]),cur[i]});
		for(int j=stk.size()-2;~j;j--){
			if(lst[0]==lst[1]) break ;
			int k=a[stk[j]]-a[stk[j+1]];
			lst={cur[stk[j]],cur[stk[j]]-Shift(lst[0],k)+Shift(lst[1],k)};
			cur[stk[j]]=lst[1];
		}
		for(int j:lq[i]){
			int k=lower_bound(stk.begin(),stk.end(),maxl[j],greater<int>())-stk.begin()+1;
			if(k>=stk.size()) continue ;
			cnt[j]+=Shift(cur[stk[k]],a[stk[k-1]]-a[stk[k]]);
		}
	}
	for(int i=1;i<=n;i++) cur[i]=0;
	stk.clear();

	for(int i=1;i<=q;i++) cout<<ans[i]+lg[cnt[i]]+1<<endl;

	return 0;
}
```

### [CCO 2025\] Asteroid Mining

${\sf\color{Black}Normal.}/{\sf\color{Green} Good.}$

棒棒糖题。

首先看到两两整除想到变进制/合并小兵。考虑贪心，若当前考虑到质量为 $p$ 的，下一步考虑质量为 $q$ 的，则先贪 $\lfloor \frac {M\bmod q}p\rfloor$ 个最优的质量为 $p$ 的。剩下的每 $\frac qp$ 个绑成一组丢到质量为 $q$ 的堆里，不足的用 $0$ 补即可。

时间复杂度 $O(n\log n\log V)$。

```cpp
vector<priority_queue<ll>> q(val.size());
for(int i=1;i<=n;i++){
    int pos=lower_bound(val.begin(),val.end(),v[i])-val.begin();
    q[pos].push(w[i]);
}

ll ans=0;
for(int i=0;i+1<val.size();i++){
    while(lim%val[i+1]>=val[i]){
        if(!q[i].size()) break ;
        ans+=q[i].top();
        q[i].pop();
        lim-=val[i];
    }
    while(q[i].size()){
        ll tmp=0;
        for(int j=1;j<=val[i+1]/val[i];j++){
            if(!q[i].size()) break ;
            tmp+=q[i].top();
            q[i].pop();
        }
        q[i+1].push(tmp);
    }
}
for(int i=val.size()-1;~i;i--){
    while(q[i].size()&&lim>=val[i]){
        ans+=q[i].top();
        lim-=val[i];
        q[i].pop();
    }
}
```

### [CCO 2025\] Tree Decorations

${\sf\color{Green} UpVote\bigtriangleup}/{\sf\color{Green} Good.}$

通过仔细阅读题面可以发现，红树的每一个子树都应该在给定树中出现，这引出了红树的合法条件：

- **条件 1**：红树是给定的树的某个子树。

- **条件 2**：令 $S_T$ 为红树中出现和有根树 $T$ 同构的子树的根节点标号，$dep_u$ 表示 $u$ 在**红树**内的深度（1-index），$cnt_T$ 为和**给定树**内有根树 $T$ 同构的树个数。

  那么对于任意的 $T$，应该有：$\displaystyle \sum_{u\in S_T} dep_u \leq cnt_T$。

条件 1 是平凡的，考虑如何维护条件 2，即枚举红树树根 $u$，判断其是否满足 $\displaystyle \sum_{v\in S_T} dep_v-dep_u \leq cnt_T$。

做法是，先树哈希，然后对于每一个 $T$，DSU on tree 维护 $\displaystyle \sum_{v\in S_T} dep_v$ 和 $|S_T|$，计算可以抵达的最小深度。

时间复杂度 $O(n\log^2n)$，可能需要一些比较混沌邪恶的哈希方式。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
using ull=unsigned long long;
const int N=5e5+9;
const ll inf=1e18;

const ull A=7;
const ull B=998244353;
const ull C=114514191981000001;
inline ull XorShift(ull x){return x^(x<<7)^(x>>13);}

ull f[N];
ll sum[N];
map<ull,int> cnt;
vector<int> e[N];
int fa[N],dep[N],siz[N],hson[N],n,m;
inline void GetHash(int x){
	f[x]=B;
	siz[x]=1;
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		fa[y]=x;
		dep[y]=dep[x]+1;
		GetHash(y);
		f[x]+=A*XorShift(f[y]);
		siz[x]+=siz[y];
		sum[x]+=sum[y];
		if(!hson[x]||siz[y]>siz[hson[x]]) hson[x]=y;
	}
	f[x]%=C;
	cnt[f[x]]++;
	sum[x]+=siz[x];
}

ll mndep[N];
set<ull> res;
map<ull,array<ll,2>> c[N];
inline void Solve(int x){
	mndep[x]=-inf;
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		Solve(y);
		mndep[x]=max(mndep[x],mndep[y]);
	}
	swap(c[x],c[hson[x]]);
	auto Insert=[&x](ull key,array<ll,2> val){
		c[x][key][0]+=val[0];
		c[x][key][1]+=val[1];
		val=c[x][key];
		mndep[x]=max(mndep[x],(val[1]-cnt[key]+val[0]-1)/val[0]);
	};
	Insert(f[x],{1,dep[x]});
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		if(y==hson[x]) continue ;
		for(auto p:c[y]) Insert(p.first,p.second);
	}
	if(dep[x]>mndep[x]&&m+sum[x]==n) res.insert(f[x]);
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>m;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	GetHash(1);
	Solve(1);

	cout<<res.size()<<endl;

	return 0;
}
```



### [CCO 2025] Restaurant Recommendation Rescue

${\sf\color{Green} UpVote\bigtriangleup}/{\sf\color{Peach} Mistake?}$

如果 $\sum a_i \neq n-1$ 显然不是一个合法的树状结构。

为了方便起见，让所有 $a_i$ 减去 $1$，那么问题变成是否可以找到一个循环移位 $k$ 使得 $\displaystyle \forall i\in[1,n),\sum_{j=1}^i a_{(j+k)\bmod n+1}\geq 0$。

尝试发掘一下循环移位后的前缀和数组的性质，令 $\displaystyle b_i=\sum_{j=1}^i a_i,c_i=\sum_{j=1}^i a_{(i+k)\bmod n+1}$：

- 若 $i>k$，则 $c_i=b_i-b_k$。
- 若 $i\leq k$，则 $c_i=b_n-(b_k-b_i)=b_i-b_k+b_n$。

所以 $c_i=b_i-b_k+[i\leq k]b_n=b_i-b_k-[i\leq k]$。

综上，我们可以确定合法的 $k$ 有且只有一个，即最左端的 $b_i$ 的最小值位置。

交换 $a_i$ 相当于对 $b_i$ 区间加，使用线段树维护，时间复杂度 $O(n\log n)$。

```cpp
for(int i=1;i<=n;i++) a[i]--;

partial_sum(a+1,a+n+1,pre+1);
if(pre[n]!=-1){
    while(~(q--)) cout<<0<<' '<<0<<endl;
    return 0;
}

Build(1,1,n);
cout<<1<<' '<<dat(1)[1]%n<<endl;
while(q--){
    int i,j;
    cin>>i>>j;
    if(i>j) swap(i,j);
    i++,j++;
    Modify(1,i,j-1,GetPoint(j)-GetPoint(i));
    cout<<1<<' '<<dat(1)[1]%n<<endl;
}
```

### [CEOI 2025\] highest

${\sf\color{Green} UpVote\bigtriangleup}/{\sf\color{Peach} Mistake?}$

下文中令 $a_i=i+v_i,b_i=i+w_i$。

首先如果只有 1-step 操作显然可以倍增，因为选当前可以达到的区间中 $a_i$ 最大作为第一步显然不劣。

考虑推广这个倍增到 1/2-step，发现倒闭了，倒闭的原因在于在 $2^k\rightarrow 2^{k+1}$ 的过程中，可能会出现有一个 2-step 操作横跨两个 $2^k$ 块的情况。

因此，我们直接兼容掉这个情况。具体地，每次倍增的时候同时考虑 $2^k/2^k-1$ 的操作代价最远可以跳到哪里，那么有以下 $4$ 种转移：

-   $2^{k+1}\leftarrow 2^k+2^k$。
-   $2^{k+1}\leftarrow (2^k-1)+2+(2^k-1)$。
-   $(2^{k+1}-1)\leftarrow 2^k+(2^k-1)$。
-   $(2^{k+1}-1)\leftarrow (2^k-1)+2^k$。

在倍增的时候同样维护一个条跳 $c/c-1$ 的操作代价的最远点即可，时间复杂度 $O((n+q)\log n)$。

```cpp
vector<int> solve(vector<int> &a,vector<int> &b,vector<pair<int,int>> &t){
	int n=a.size(),q=t.size();
	for(int i=0;i<n;i++){
		a[i]=min(i+a[i],n-1);
		b[i]=min(i+b[i],n-1);
	}

	vector<int> lg(n+1,0);
	vector<vector<int>> ap(n,vector<int>(20,0));
	auto CheckA=[&](int i,int j){return a[i]<a[j]?j:i;};
	auto MaxAPos=[&](int l,int r){
		int k=lg[r-l+1];
		return CheckA(ap[l][k],ap[r-(1<<k)+1][k]);
	};
	for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
	for(int i=0;i<n;i++) ap[i][0]=i;
	for(int k=1;k<=lg[n];k++){
		for(int i=0;i<n-(1<<k)+1;i++){
			ap[i][k]=CheckA(ap[i][k-1],ap[i+(1<<k-1)][k-1]);
		}
	}
	
	vector<vector<int>> bp(n,vector<int>(20,0));
	auto CheckB=[&](int i,int j){return b[i]<b[j]?j:i;};
	auto MaxBPos=[&](int l,int r){
		int k=lg[r-l+1];
		return CheckB(bp[l][k],bp[r-(1<<k)+1][k]);
	};
	for(int i=0;i<n;i++) bp[i][0]=i;
	for(int k=1;k<=lg[n];k++){
		for(int i=0;i<n-(1<<k)+1;i++){
			bp[i][k]=CheckB(bp[i][k-1],bp[i+(1<<k-1)][k-1]);
		}
	}

	vector<vector<array<int,2>>> f(n,vector<array<int,2>>(20,{0,0}));
	auto Far=[&](int l,int r,int k,int t){
		int x=MaxAPos(l,r),y=MaxBPos(l,r),z=r;
		return max(max(f[x][k][t],f[y][k][t]),f[z][k][t]);
	};
	auto Query=[&](int l,int r){
		if(l==r) return 0;
		int cur=l,bur=-1,ans=0;
		auto Upd=[&](int k){
			array<int,2> res={-1,-1};
			res[0]=max(res[0],Far(l,cur,k,0));
			if(~bur) res[0]=max(res[0],Far(l,bur,k,1));
			res[1]=max(res[1],Far(l,cur,k,1));
			if(~bur) res[1]=max(res[1],Far(l,b[MaxBPos(l,bur)],k,0));
			return res;
		};
		for(int k=lg[n];~k;k--){
			auto tmp=Upd(k);
			if(tmp[1]<r) ans+=(1<<k),bur=tmp[0],cur=tmp[1];
		}
		return ans+1;
	};
	for(int i=0;i<n;i++) f[i][0]={i,a[i]};
	for(int k=1;k<=lg[n];k++){
		for(int i=0;i<n;i++){
			f[i][k][0]=max(f[i][k][0],Far(i,f[i][k-1][1],k-1,0));
			f[i][k][0]=max(f[i][k][0],Far(i,f[i][k-1][0],k-1,1));
			f[i][k][1]=max(f[i][k][1],Far(i,f[i][k-1][1],k-1,1));
			f[i][k][1]=max(f[i][k][1],Far(i,b[MaxBPos(i,f[i][k-1][0])],k-1,0));
		}
	}

	vector<int> ans(q,0);
	for(int i=0;i<q;i++){
		int l=t[i].first,r=t[i].second;
		ans[i]=Query(l,r);
	}

	return ans;
}
```

### [CEOI 2025] lawnmower

${\sf\color{Black}Normal.}/{\sf\color{Green} Good.}$

令上一次剩下 $d$ 个单位的草，那么对列 $i$ 除草的代价为 $w_i(d)=\left\{\begin{matrix}\lfloor\frac {v_i+d}{c}\rfloor(a_i+b)+a_i & v_i+d\not\equiv 0\pmod c\\\lfloor\frac {v_i+d}{c}\rfloor(a_i+b) & v_i+d\equiv 0\pmod c\end{matrix}\right.$.

设 $f_{i,j}$ 表示已经除完第 $1\sim i$ 列的草，除草机内还剩 $j$ 单位的草，所用的最小代价，那么显然有 $O(n^2)$ DP 转移式：

-   $f_{i+1,(j+v_i)\bmod c}\leftarrow f_{i,j}+w_i(j)$。
-   $f_{i+1,0}\leftarrow f_{i,j}+w_i(j)+b$。

注意到上面 $w_i(j)$ 最多只有三段不同的值，故考虑直接记录偏移量而后用数据结构优化这个式子，时间复杂度 $O(n\log V)$。

```cpp
struct Node{
	int lc,rc;
	ll tag,dat;
}tr[N<<5];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define tag(x) tr[x].tag
#define dat(x) tr[x].dat

int cnt;
inline int Allc(){return dat(++cnt)=inf,cnt;}
inline void PushUp(int x){if(lc(x)) dat(x)=min(dat(lc(x)),dat(rc(x)));}
inline void Push(int &x,ll k){
	if(!x) x=Allc();
	tag(x)+=k,dat(x)+=k;
}
inline void PushDown(int x){
	if(!tag(x)) return ;
	Push(lc(x),tag(x));
	Push(rc(x),tag(x));
	tag(x)=0;
}

inline void ChMin(int &x,int L,int R,int pos,ll k){
	if(!x) x=Allc();
	if(L==R) return dat(x)=min(dat(x),k),void();
	int mid=L+R>>1;
	PushDown(x);
	if(pos<=mid) ChMin(lc(x),L,mid,pos,k);
	if(pos>mid) ChMin(rc(x),mid+1,R,pos,k);
	PushUp(x);
}
inline void Modify(int &x,int L,int R,int l,int r,ll k){
	if(!x) x=Allc();
	if(l<=L&&R<=r) return Push(x,k);
	int mid=L+R>>1;
	PushDown(x);
	if(l<=mid) Modify(lc(x),L,mid,l,r,k);
	if(r>mid) Modify(rc(x),mid+1,R,l,r,k);
	PushUp(x);
}

ll mow(int n,int c,int b,vector<int> &a,vector<int> &v){
	int root=Allc(),dlt=0;
	auto ChM=[&](int p,ll k){ChMin(root,0,c-1,(p-dlt+c)%c,k);};
	auto Upd=[&](int l,int r,ll k){
		if(l>r||r>=c||l<0) return ;
		l=(l-dlt+c)%c;
		r=(r-dlt+c)%c;
		if(l<=r) Modify(root,0,c-1,l,r,k);
		else Modify(root,0,c-1,l,c-1,k),Modify(root,0,c-1,0,r,k);
	};
	ChM(0,0);
	for(int i=0;i<n;i++){
		int t=(c-v[i]%c)%c,k=(v[i]-1)/c;
		Upd(0,t-1,1ll*k*(a[i]+b)+a[i]);
		Upd(t,t,1ll*(k+1)*(a[i]+b));
		Upd(t+1,c-1,1ll*(k+1)*(a[i]+b)+a[i]);
		dlt=(dlt+v[i])%c;
		ChM(0,dat(root)+b);
	}
	Upd(1,c-1,b);
	return dat(root);
}
```

### [NordicOI 2025] Dodgeball Diplomacy

${\sf\color{Black}Normal.}/{\sf\color{Green} Good.}$

显然连通块按大小从大到小相邻的两两配对一定最优，那么问题在于如何维护各连通块以及其大小。

若没有删的是**最大**的边这条性质，那么这就是动态图连通性问题，十分困难。

但是因为删的是最大的边，那么维护出最小生成森林即可，这个的实现是简单的。

LCT 维护即可，时间复杂度 $O(n\log n)$。

```cpp
auto Insert=[](int pos,int k)->void{
    if(~k&1) return ;
    SgT::Flip(1,pos);
    if(pos-1) SgT::Neg(1,1,pos-1);
};
for(int i=1;i<=n;i++) LCT::PushUp(i);
SgT::Build(1,1,n);
Insert(1,n);

priority_queue<array<int,2>> heap;
for(int i=n+1;i<=n+q;i++){
    char op;
    cin>>op;
    if(op=='a'){
        cin>>u[i]>>v[i]>>LCT::tr[i].val[0];
        LCT::tr[i].val[1]=i;
        LCT::PushUp(i);
        heap.push({LCT::tr[i].val});
        if(LCT::FindRoot(u[i])==LCT::FindRoot(v[i])){
            LCT::Split(u[i],v[i]);
            if(LCT::tr[v[i]].dat>LCT::tr[i].val){
                int j=LCT::tr[v[i]].dat[1];
                LCT::Cut(u[j],j),LCT::Cut(j,v[j]);
                LCT::Link(u[i],i),LCT::Link(i,v[i]);
                pp[j]=1;
            }else pp[i]=1;
        }else{
            Insert(LCT::Size(u[i]),-1);
            Insert(LCT::Size(v[i]),-1);
            LCT::Link(u[i],i),LCT::Link(i,v[i]);
            Insert(LCT::Size(u[i]),1);
        }
    }else if(op=='r'){
        int j=heap.top()[1];
        heap.pop();
        if(pp[j]) continue ;
        Insert(LCT::Size(u[j]),-1);
        LCT::Cut(u[j],j),LCT::Cut(j,v[j]);
        Insert(LCT::Size(v[j]),1);
        Insert(LCT::Size(u[j]),1);
        pp[j]=1;
    }else if(op=='d'){
        cout<<SgT::tr[1].sum<<endl;
        cout.flush();
    }
}
```

## 口胡大赛！！！

懒得写的题目，有时间再写吧。

### [ARC138] D - Differ by K bits

令 $D$ 为 $A$ 的差分数组，那么 $\forall i,\operatorname{popcount}(D_i)=K$，并且 $\displaystyle\forall i\neq j,\bigoplus_{k=1}^iD_k \neq \bigoplus_{k=1}^jD_k$

那么我们把所有 $\operatorname{popcount}(x)=K$ 的 $x$ 中的基向量都抽出来做格雷码即可。

### [ARC145] D - Non Arithmetic Progression Set

注意到三进制下把 $2$ ban 掉即可解决限制 1，考虑把所有数拿出来凑一下和 $M$ 同余再平移即可。

### [CF2140] E1/2. Prime Gaming

E1 大概就是直接对抗搜索状压 DP 一下，状态数是 $O(2^n)$ 的。

E2 就是再在上面的东西上乘一些幂。

### [COCI 2008/2009 #4] PERIODNI

建出树后怎么怎么树上背包一下车的放置一下应该就好了。

### [ROIR 2024] Выбор столицы

考虑对于每个树根二分答案，设其为 $t$，那么考虑以下贪心策略：

-   找到当前未被标记的深度最大节点 $u$。
-   标记 $u$ 的 $t$ 级祖先的整个子树。

贪爆 $k$ 条直接放弃即可。每个点换根后的深度可以区间加解决，换根后的 $t$ 级祖先可以抽出路径再分讨，标记子树反正换根后还是 $O(1)$ 个区间，时间复杂度 $O(nk\log^2n)$。

### [ROIR 2024] Разбиение на тройки

不难想到在值域上 DP，令 $f_{i,j,k}$ 表示当前考虑到 $i$，已经用了 $j$ 次 $(i-1,i,i+1)$ 和 $k$ 次 $(i,i+1,i+2)$ 了，这个反正加点限制前缀和优化一下就可以 $O(1)$ 转移了，分析一下状态数发现是 $O(n^2)$ 的于是做完了。

### [Luogu] P4755 Beautiful Pair

考虑分治，只从到分治中心最大值更大的那一边统计，相同钦定左边优先。那么就是一个关于 $a_i$ 和到分治中心的区间最大值二维数点问题，时间复杂度 $O(n\log^2n)$。

题解做法是：每次让最大值作为分治中心，然后让短的那一边去查长的那一边，时间复杂度就是启发式合并的复杂度，即 $O(n\log^2 n)$。
