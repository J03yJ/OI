# [Ynoi2079] Range 2 Pow Sum Pop Count

## 题目描述

给定序列 $a_1,\dots,a_n$，共 $m$ 次查询，每次查询问 $\displaystyle\sum\limits_{i=l}^r 2^{a_i}$ 的二进制表示中 $1$ 的个数。

对于 $100\%$ 的数据，满足 $1\le n\le {10}^5$，$1\le m\le {10}^6$，$1\le a_i\le 10^9$，$1\le l\le r\le n$。

对于 $25\%$ 的数据，满足 $n,m\le 1000$。

对于另外 $25\%$ 的数据，满足 $a_i\le100$。

对于另外 $25\%$ 的数据，满足 $m\le 10^5$

对于另外 $25\%$ 的数据，无特殊限制。

$\rm 2s.$

## 题解

看起来十分不可做，于是暴力莫队，发现有 96pts（喜）。

先分析一下复杂度，乍一看好像是 $O(n^{\frac32}m)$ 的，但是由于答案是 $O(n)$ 的，故时间复杂度应为 $O(nm)$。

发现信息仅为 $0/1$ 考虑 bitset，~~然后发现 bitset 没有进位~~，于是手写 bitset，时间复杂度 $O(\frac{nm}w)$。

跑不满，最慢点 $\rm 1.77s$ 的样子。

## 代码

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>

using namespace std;

using ll=long long;
using ull=unsigned ll;
const int N=1e5+9;
const int M=1e6+9;

int a[N],ql[M],qr[M],blk[N],p[M],ans[M],n,m;
__gnu_pbds::gp_hash_table<int,int> mp;
int val[N],tot;

#define Bit(x) (1ull<<(x))
ull b[N],mask[65];
const int d=6,w=64,msk=63;
void InitMask(){for(int i=1;i<=64;i++) mask[i]=mask[i-1]<<1|1;}
void Insert(int x,int &cnt){
    int i=x>>d,p=x&msk,flag=0;
    if(b[i]>mask[w]-Bit(p)) flag=1;
    cnt-=__builtin_popcountll(b[i]);
    b[i]+=Bit(p);
    cnt+=__builtin_popcountll(b[i]);
    if(flag){
        while(b[++i]==mask[w]) b[i]=0,cnt-=w;
        cnt-=__builtin_popcountll(b[i]);
        b[i]++;
        cnt+=__builtin_popcountll(b[i]);
    }
}
void Erase(int x,int &cnt){
    int i=x>>d,p=x&msk,flag=0;
    if(b[i]<Bit(p)) flag=1;
    cnt-=__builtin_popcountll(b[i]);
    b[i]-=Bit(p);
    cnt+=__builtin_popcountll(b[i]);
    if(flag){
        while(!b[++i]) b[i]=mask[w],cnt+=w;
        cnt-=__builtin_popcountll(b[i]);
        b[i]--;
        cnt+=__builtin_popcountll(b[i]);
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=m;i++) cin>>ql[i]>>qr[i];

    for(int i=1,pos;i<=n;i++){
        pos=a[i];
        while(mp[pos]) mp[pos++]=0;
        mp[pos]=1;
    }
    for(auto p:mp) val[++tot]=p.first;
    sort(val+1,val+tot+1);
    for(int i=1;i<=n;i++) a[i]=lower_bound(val+1,val+tot+1,a[i])-val;

    InitMask();
    int B=ceil(n/sqrt(m));
    for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
    iota(p+1,p+m+1,1);
    sort(p+1,p+m+1,[](int x,int y){
        return blk[ql[x]]^blk[ql[y]]?blk[ql[x]]<blk[ql[y]]:qr[x]<qr[y];
    });
    for(int i=1,l=1,r=0,cnt=0;i<=m;i++){
        while(r<qr[p[i]]) Insert(a[++r],cnt);
        while(l>ql[p[i]]) Insert(a[--l],cnt);
        while(r>qr[p[i]]) Erase(a[r--],cnt);
        while(l<ql[p[i]]) Erase(a[l++],cnt);
        ans[p[i]]=cnt;
    }

    for(int i=1;i<=m;i++) cout<<ans[i]<<endl;

    return 0;
}
```

