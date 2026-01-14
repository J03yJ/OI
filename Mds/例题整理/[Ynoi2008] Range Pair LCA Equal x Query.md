# [Ynoi2008] Range Pair LCA Equal x Query

## 题目描述

给定一棵 $n$ 个节点的有根树，第 $i$ 个点的编号是 $i$。

有 $m$ 次询问，每次询问给出 $l,r,x$，求有多少点编号的二元组 $(i,j)$ 满足 $l \le i < j \le r$ 且 $i$ 和 $j$ 的最近公共祖先是节点 $x$。

对于 $100\%$ 的数据，$1\le n,m\le 2\times 10^5$，$1 \le l,r,x \le n$。

$\rm 1s.$

## 题解

考虑对度数阈值分治，设阈值为 $\sqrt n$：

- 对于度数小于 $\sqrt n$ 的点，枚举其每个儿子，两两计算贡献，则问题变为 $O(m\sqrt n)$ 次查询的二维数点问题。需要 $O(1)$ 查询，$O(\sqrt n)$ 修改的数据数据结构，想到对值域序列分块，这部分的时间复杂度是 $O(m\sqrt n)$。
- 对于度数大于 $\sqrt n$ 的点，此时枚举每个儿子的时间复杂度是不可接受的，考虑莫队，则时间复杂度变为 $O(\sum siz_u\sqrt{m_u})$。发现即使如此 $\sum siz_u$ 仍然可以达到 $O(n\sqrt n)$ 的级别。注意到每个节点 $u$ 的孩子 $v_1,...v_k$ 中，满足 $siz_{v_i}\gt \sqrt n$ 的 $i$ 不超过 $\sqrt n$ 个，考虑将此类儿子的贡献单独计算，即变为上一种情况，对于剩下的儿子的子树莫队。由于度数大于 $\sqrt n$ 的点 $u$ 必然满足 $siz_u \gt \sqrt n$，故每个点最多被莫队计算一次，所以莫队部分的时间复杂度为 $O(n\sqrt m)$。

总时间复杂度为 $O(m\sqrt n+n\sqrt m)$。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

#define ssiz(x) (signed)x.size()
const int N=4e5+9;
const int sqN=1e3+9;

int fi[N],ne[N<<1],to[N<<1],adj;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

long long ans[N];
int ql[N],qr[N],qx[N],n,m,rt,sonB,sizB;
int fa[N],son[N],siz[N],dfn[N],idfn[N],dcnt;
void DFS1(int x){
    siz[x]=1;
    dfn[x]=++dcnt;
    idfn[dcnt]=x;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        fa[y]=x;
        DFS1(y);
        siz[x]+=siz[y];
        son[x]++;
    }
}

int blk[N],L[N],R[N],bpre[sqN],pre[N],B;
inline void Init(){
    B=sqrt(n);
    for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
    for(int i=1;i<=n;i++) R[blk[i]]=i;
    for(int i=n;i>=1;i--) L[blk[i]]=i;
}
inline void Add(int x,int k){
    for(int i=x;i<=R[blk[x]];i++) pre[i]+=k;
    for(int i=blk[x];i<=blk[n];i++) bpre[i]+=k;
}
inline int Ask(int x){return bpre[blk[x]-1]+pre[x];}
inline int Ask(int l,int r){return Ask(r)-Ask(l-1);}
long long sum[N];
vector<int> q[N];
void DFS2(int x){
    vector<pair<int,int>> qry;
    if(fa[x]){
        if(son[fa[x]]<=sonB) for(int i:q[fa[x]]) qry.push_back({i,-Ask(ql[i],qr[i])});
        else if(siz[x]>sizB) for(int i:q[fa[x]]) qry.push_back({i,-Ask(ql[i],qr[i])});
    }
    for(int i:q[x]){
        if(ql[i]<=x&&x<=qr[i]){
            if(son[x]<=sonB) sum[i]++;
            else ans[i]--;
        }
    }
    if(son[x]>sonB) for(int i:q[x]) sum[i]-=Ask(ql[i],qr[i]);
    Add(x,1);
    for(int i=fi[x];i;i=ne[i]) if(to[i]!=fa[x]) DFS2(to[i]);
    for(auto &p:qry){
        int i=p.first;
        p.second+=Ask(ql[i],qr[i]);
        if(son[fa[x]]<=sonB){
            ans[i]+=1ll*p.second*sum[i];
            sum[i]+=p.second;
        }else ans[i]-=1ll*p.second*p.second;
    }
    if(son[x]>sonB) for(int i:q[x]) sum[i]+=Ask(ql[i],qr[i]),ans[i]+=1ll*sum[i]*sum[i];
    qry.clear();
}

vector<int> p;
int cnt[N],c[N],scnt;
void Push(int x){
    p.clear();
    while(scnt) cnt[scnt--]=0;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        if(siz[y]>sizB) continue ;
        scnt++;
        for(int j=dfn[y];j<dfn[y]+siz[y];j++){
            p.push_back(idfn[j]);
            c[idfn[j]]=scnt;
        }
    }
    sort(p.begin(),p.end());
}
void Modify(long long &res,int pos,int k){
    res-=1ll*cnt[c[pos]]*cnt[c[pos]];
    cnt[c[pos]]+=k;
    res+=1ll*cnt[c[pos]]*cnt[c[pos]];
}
void MoAlgo(int x){
    int sq=sqrt(ssiz(p));
    vector<int> b(ssiz(p),0);
    for(int i=0;i<ssiz(p);i++) b[i]=(i-1)/sq+1;
    vector<array<int,3>> qry;
    for(int i:q[x]){
        int l=lower_bound(p.begin(),p.end(),ql[i])-p.begin();
        int r=upper_bound(p.begin(),p.end(),qr[i])-p.begin()-1;
        if(l>r) continue ;
        qry.push_back({i,l,r});
    }
    sort(qry.begin(),qry.end(),[&b](auto x,auto y){
        if(b[x[1]]^b[y[1]]) return b[x[1]]<b[y[1]];
        else return x[2]<y[2];
    });

    long long res=0;int l=0,r=-1;
    for(auto t:qry){
        while(r<t[2]) Modify(res,p[++r],1);
        while(l>t[1]) Modify(res,p[--l],1);
        while(r>t[2]) Modify(res,p[r--],-1);
        while(l<t[1]) Modify(res,p[l++],-1);
        ans[t[0]]-=res;
    }
}
void DFS3(int x){
    for(int i=fi[x];i;i=ne[i]) if(to[i]!=fa[x]) DFS3(to[i]);
    if(son[x]<=sonB) return ;
    Push(x),MoAlgo(x);
    for(int i:q[x]) ans[i]/=2;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    cin>>n>>m>>rt;
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        AdEg(u,v),AdEg(v,u);
    }
    for(int i=1;i<=m;i++) cin>>ql[i]>>qr[i]>>qx[i],q[qx[i]].push_back(i);

    sizB=sonB=sqrt(n),DFS1(rt);
    Init(),DFS2(rt);
    DFS3(rt);
    
    for(int i=1;i<=m;i++) cout<<ans[i]<<endl;

    return 0;
}
```

