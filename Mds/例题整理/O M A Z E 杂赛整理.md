# O M A Z E 杂赛整理

用于记录以 `maze.size` 形态出征的除 UCUP 外的 ICPC 赛制比赛。

## THUCP 2026 初赛

### A. Asian Soul

赛时思路是，考虑重链剖分，将询问剖成 $O(\log n)$ 条重链的前缀。对于一条重链的前缀，ban 掉某个轻子树的询问，可以离线下来从头逐一加入轻子树，然后一边删除一边回答。由于一个点只会在 $O(\log n)$ 条重链上出现，总增删次数就是 $O(n\log n)$ 的，用线段树处理就是 $O(n\log^2 n)$ 的。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=5e5+9;

vector<int> e[N],pos[N];
int a[N],ql[N],qr[N],qu[N],n,m,q;

int fa[N],siz[N],dep[N],hson[N];
inline void GetHSon(int x){
    siz[x]=1;
    for(int y:e[x]){
        if(y==fa[x]) continue ;
        fa[y]=x;
        dep[y]=dep[x]+1;
        GetHSon(y);
        siz[x]+=siz[y];
        if(!hson[x]||siz[hson[x]]<siz[y]) hson[x]=y;
    }
}
int dfn[N],idfn[N],top[N],dcnt;
inline void GetTop(int x,int t){
    top[x]=t;
    dfn[x]=++dcnt;
    idfn[dcnt]=x;
    if(hson[x]) GetTop(hson[x],t);
    for(int y:e[x]){
        if(y==fa[x]) continue ;
        if(y==hson[x]) continue ;
        GetTop(y,y);
    }
}

vector<array<int,2>> qry[N];
inline void InsQ(int x,int id){
    int lst=0;
    while(x){
        qry[x].push_back({lst,id});
        lst=top[x];
        x=fa[top[x]];
    }
}

struct Node{
    int l,r,dat;
}tr[N<<2];

inline void PushUp(int x){tr[x].dat=max(tr[x<<1].dat,tr[x<<1|1].dat);}
inline void Build(int x,int l,int r){
    tr[x].l=l,tr[x].r=r;
    if(tr[x].l==tr[x].r) return tr[x].dat=0,void();
    int mid=tr[x].l+tr[x].r>>1;
    Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
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
    int mid=tr[x].l+tr[x].r>>1;
    if(r<=mid) return Query(x<<1,l,r);
    else if(l>mid) return Query(x<<1|1,l,r);
    else return max(Query(x<<1,l,mid),Query(x<<1|1,mid+1,r));
}

int ans[N];
vector<int> tmp[N];
inline void Calc(){
    auto Ins=[](int x,int k){for(int i:pos[x]) Set(1,i,k);};
    auto Ers=[](int x){for(int i:pos[x]) Set(1,i,0);};
    for(int x=1;x<=n;x++){
        if(x!=top[x]) continue ;
        int low=0;
        for(int y=x;y;y=hson[y]){
            Ins(y,y);
            for(int z:e[y]){
                if(z==fa[y]) continue ;
                if(z==hson[y]) continue ;
                for(int i=dfn[z];i<dfn[z]+siz[z];i++) Ins(idfn[i],y);
            }
            for(auto p:qry[y]) tmp[p[0]].push_back(p[1]);
            for(int i:tmp[0]) ans[i]=max(ans[i],Query(1,ql[i],qr[i]));
            tmp[0].clear();
            for(int z:e[y]){
                if(z==fa[y]) continue ;
                if(z==hson[y]) continue ;
                for(int i=dfn[z];i<dfn[z]+siz[z];i++) Ers(idfn[i]);
                for(int i:tmp[z]) ans[i]=max(ans[i],Query(1,ql[i],qr[i]));
                for(int i=dfn[z];i<dfn[z]+siz[z];i++) Ins(idfn[i],y);
                tmp[z].clear();
            }
        }
        for(int y=x;y;y=hson[y]){
            Ers(y);
            for(int z:e[y]){
                if(z==fa[y]) continue ;
                if(z==hson[y]) continue ;
                for(int i=dfn[z];i<dfn[z]+siz[z];i++) Ers(idfn[i]);
            }
            low=y;
        }
        for(int y=low;y;y=fa[y]){
            for(auto p:qry[y]){
                int i=p[1];
                if(Query(1,ql[i],qr[i])) ans[i]=max(ans[i],y);
            }
            Ins(y,1);
            for(int z:e[y]){
                if(z==fa[y]) continue ;
                if(z==hson[y]) continue ;
                for(int i=dfn[z];i<dfn[z]+siz[z];i++) Ins(idfn[i],1);
            }
            if(y==x) break ;
        }
        for(int y=x;y;y=hson[y]){
            Ers(y);
            for(int z:e[y]){
                if(z==fa[y]) continue ;
                if(z==hson[y]) continue ;
                for(int i=dfn[z];i<dfn[z]+siz[z];i++) Ers(idfn[i]);
            }
        }
    }
}

signed main(){
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);

    cin>>n>>m>>q;
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for(int i=1;i<=m;i++) cin>>a[i],pos[a[i]].push_back(i);
    for(int i=1;i<=q;i++) cin>>ql[i]>>qr[i]>>qu[i];

    GetHSon(1),GetTop(1,1);
    for(int i=1;i<=q;i++) InsQ(qu[i],i);
    Build(1,1,m);
    Calc();

    for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

    return 0;
}
```

正解考虑把询问摊到线段树的 $O(n\log n)$ 的区间上。对于每个线段树节点，把区间内的节点和询问节点共同的虚树建出来，把树遍历一遍就可以得到答案，使用归并和另类虚树建法就是 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=5e5+9;
const int lgN=2e1;

vector<int> e[N];
int a[N],ql[N],qr[N],qu[N],n,m,q;

vector<int> qry[N<<2];
inline void Insert(int x,int L,int R,int l,int r,int id){
	if(l<=L&&R<=r) return qry[x].push_back(id);
	int mid=L+R>>1;
	if(l<=mid) Insert(x<<1,L,mid,l,r,id);
	if(r>mid) Insert(x<<1|1,mid+1,R,l,r,id);
}

int fa[N],elr[N<<1],pos[N],ecnt;
inline void GetElr(int x){
	elr[++ecnt]=x;
	pos[x]=ecnt;
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		fa[y]=x;
		GetElr(y);
		elr[++ecnt]=x;
	}
}
int mn[lgN][N<<1],lg[N<<1];
inline void InitLCA(){
	for(int i=2;i<=ecnt;i++) lg[i]=lg[i>>1]+1;
	for(int i=1;i<=ecnt;i++) mn[0][i]=pos[elr[i]];
	for(int k=1;k<=lg[ecnt];k++){
		for(int i=1;i+(1<<k)-1<=ecnt;i++){
			mn[k][i]=min(mn[k-1][i],mn[k-1][i+(1<<k-1)]);
		}
	}
}
inline int LCA(int x,int y){
	x=pos[x],y=pos[y];
	if(x>y) swap(x,y);
	int k=lg[y-x+1];
	return elr[min(mn[k][x],mn[k][y-(1<<k)+1])];
}

vector<int> ve[N];
inline int GetVir(vector<int> v,vector<int> &node){
	vector<int> stk;
	for(int x:v){
		if(stk.size()){
			int lca=LCA(stk.back(),x);
			if(stk.back()!=lca){
				int lst=0;
				while(stk.size()&&pos[stk.back()]>pos[lca]){
					if(lst) ve[stk.back()].push_back(lst);
					lst=stk.back();
					stk.pop_back();
				}
				if(stk.back()!=lca){
					stk.push_back(lca);
					node.push_back(lca);
				}
				ve[lca].push_back(lst);
			}
		}
		stk.push_back(x);
		node.push_back(x);
	}
	for(int i=0;i+1<stk.size();i++) ve[stk[i]].push_back(stk[i+1]);
	return stk.front();
}

int imp[N],vsiz[N],vson[N],f[N];
inline void GetVSiz(int x){
	vsiz[x]=imp[x];
	for(int y:ve[x]){
		GetVSiz(y);
		vsiz[x]+=vsiz[y];
		vson[x]+=bool(vsiz[y]);
	}
	vson[x]+=imp[x];
}
inline void GetF(int x,int k){
	f[x]=vson[x]?max(x,k):k;
	for(int y:ve[x]) GetF(y,vson[x]-bool(vsiz[y])?max(x,k):k);
}

int ans[N];
inline void Merge(vector<int> &p,vector<int> &q,vector<int> &r){
	int i=0,j=0;
	while(i<p.size()&&j<q.size()){
		if(pos[p[i]]<pos[q[j]]) r.push_back(p[i++]);
		else r.push_back(q[j++]);
	}
	while(i<p.size()) r.push_back(p[i++]);
	while(j<q.size()) r.push_back(q[j++]);
	r.erase(unique(r.begin(),r.end()),r.end());
}
vector<int> v[N<<2];
inline void Solve(int x,int L,int R){
	vector<int> vq,rl,node;
	if(L!=R){
		int mid=L+R>>1;
		Solve(x<<1,L,mid);
		Solve(x<<1|1,mid+1,R);
		Merge(v[x<<1],v[x<<1|1],v[x]);
	}else v[x]={a[L]};
	for(int i=L;i<=R;i++) imp[a[i]]=1;
	for(int i:qry[x]) vq.push_back(qu[i]);
	Merge(v[x],vq,rl);
	int root=GetVir(rl,node);
	GetVSiz(root);
	GetF(root,0);
	for(int i:qry[x]) ans[i]=max(ans[i],f[qu[i]]);
	for(int i:node) imp[i]=vsiz[i]=vson[i]=f[i]=0,ve[i].clear();
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	
	cin>>n>>m>>q;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for(int i=1;i<=m;i++) cin>>a[i];
	for(int i=1;i<=q;i++) cin>>ql[i]>>qr[i]>>qu[i];

	GetElr(1),InitLCA();
	vector<int> p(q);
	iota(p.begin(),p.end(),1);
	sort(p.begin(),p.end(),[](int i,int j){return pos[qu[i]]<pos[qu[j]];});
	for(int i:p) Insert(1,1,m,ql[i],qr[i],i);
	Solve(1,1,m);

	for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

	return 0;
}
```

### B. 回响形态

考虑把原来的串 $s$ 反转过来，令其为 $t$。那么串 $s_it_{2k-i}\ldots s_js_{2k-j}$ 是回文串等价于 $s[i:j]=s[2k-j,2k-i]$。

因此直接 Manacher 对此类回文串计数即可，时间复杂度 $O(nq)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e6+9;

int f[N<<1],n,q;
char s[N],t[N],o[N<<1];

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>s[i];

	while(q--){
		int k;
		cin>>k;
		for(int i=1;i<=n;i++) t[i]='#';
		for(int i=max(1,k-n);i<=min(n,k-1);i++) t[i]=s[k-i];
		for(int i=1;i<=2*n;i++) o[i]=i&1?s[i+1>>1]:t[i+1>>1];
		
		ll ans=0;
		for(int i=1,l=0,r=-1;i<k;i++){
			int k=i>r?0:min(f[l+r-i-1],r-i);
			while(i-k>=1&&i+k+1<=2*n&&o[i-k]==o[i+k+1]) k++;
			f[i]=k--;
			if(i+k+1>r) l=i-k,r=i+k+1;
			ans+=f[i]+(i&1)>>1;
		}

		cout<<ans<<endl;
	}

	return 0;
}
```

### F. 庭中有奇树

BFS 序在子树中只有树高个区间。

因此考虑先记录所有会用到的查询区间，离散化之后只有至多只有 $O(\sqrt[2^d]V+qd)$ 个节点，$d=2$ 取到 $O(\sqrt[4]V+q)$。

修改考虑记录每个节点管辖区间按位与的结果，修改之后区间内有值会变就暴力递归修改，查询直接逐一对每个区间查询即可。

均摊分析之后是 $O(n\log n\log V)$ 的。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ull=unsigned long long;
using bint=__int128;
const int T=4.5e6+9;
const int N=1e6+9;

ull qx[N],qc[N],n;
int op[N],q,tot;

vector<ull> pos;

struct Node{
	ull len,dat,com;
}tr[T<<2];

inline void PushUp(int x){
	tr[x].dat=tr[x<<1].dat^tr[x<<1|1].dat;
	tr[x].com=tr[x<<1].com&tr[x<<1|1].com;
}
inline void Build(int x,int l,int r){
	if(l==r) return tr[x].len=pos[r+1]-pos[l],void();
	int mid=l+r>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Modify(int x,int L,int R,int l,int r,ull k){
	if((tr[x].com&k)==k) return ;
	if(L==R){
		tr[x].com|=k;
		tr[x].dat=tr[x].len&1?tr[x].com:0;
		return ;
	}
	int mid=L+R>>1;
	if(l<=mid) Modify(x<<1,L,mid,l,r,k);
	if(r>mid) Modify(x<<1|1,mid+1,R,l,r,k);
	PushUp(x);
}
inline ull Query(int x,int L,int R,int l,int r){
	if(l<=L&&R<=r) return tr[x].dat;
	int mid=L+R>>1;
	if(r<=mid) return Query(x<<1,L,mid,l,r);
	else if(l>mid) return Query(x<<1|1,mid+1,R,l,r);
	else return Query(x<<1,L,mid,l,r)^Query(x<<1|1,mid+1,R,l,r);
}

inline bint L(bint l){return l*(l-1)/2+2;}
inline bint R(bint r){return L(r+1)-1;}
inline void Insert(bint l,bint r){
	pos.push_back(l);
	pos.push_back(r+1);
	l=L(l),r=R(r);
	if(l>n) return ;
	r=min(r,bint(n));
	Insert(l,r);
}
inline void Mod(bint l,bint r,ull k){
	int lp=lower_bound(pos.begin(),pos.end(),ull(l))-pos.begin();
	int rp=upper_bound(pos.begin(),pos.end(),ull(r))-pos.begin()-1;
	Modify(1,1,tot,lp,rp,k);
	l=L(l),r=R(r);
	if(l>n) return ;
	r=min(r,bint(n));
	Mod(l,r,k);
}
inline ull Qry(bint l,bint r){
	int lp=lower_bound(pos.begin(),pos.end(),ull(l))-pos.begin();
	int rp=upper_bound(pos.begin(),pos.end(),ull(r))-pos.begin()-1;
	ull res=Query(1,1,tot,lp,rp);
	l=L(l),r=R(r);
	if(l>n) return res;
	r=min(r,bint(n));
	return res^Qry(l,r);
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>q;
	for(int i=1;i<=q;i++){
		cin>>op[i];
		if(op[i]==1) cin>>qx[i]>>qc[i];
		else cin>>qx[i];
		Insert(qx[i],qx[i]);
	}
	
	pos.push_back(0),pos.push_back(n+1);
	sort(pos.begin(),pos.end());
	pos.erase(unique(pos.begin(),pos.end()),pos.end());

	tot=pos.size()-1;
	Build(1,1,tot);

	for(int i=1;i<=q;i++){
		if(op[i]==1) Mod(qx[i],qx[i],qc[i]);
		else cout<<Qry(qx[i],qx[i])<<endl;
	}

	return 0;
}
```

### J. 序列

不知道为什么但是 98 分钟没过题了好急啊瞎几把猜个结论试试不然爆了欸怎么过了。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--){
		ll n,m;
		cin>>n>>m;
		if(~n&1) cout<<"NO"<<endl;
		else{
			ll cnt=0,x=m;
			while(true){
				ll y=1ull<<__lg(x)+1;
				y-=x;
				if(x==y) break ;
				cnt++,x=y;
			}
			int k=__lg(x)+1;
			if(~k&1) cout<<"NO"<<endl;
			else if(cnt*2+1>n) cout<<"NO"<<endl;
			else cout<<"YES"<<endl;
		}
	}

	return 0;
}
```

## NERC 2025

### A. Alphabet City

对每种字母统计个数即可。

### B. Battle of Arrays

不是我都猜对结论了怎么是假题啊。

### D. Doorway

显然每个门要么滑倒最左边要么滑倒最右边，堆维护一下即可。

### G. Greta's Game

### J. Jinx or Jackpot