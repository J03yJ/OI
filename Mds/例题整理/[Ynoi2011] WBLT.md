# [Ynoi2011] WBLT

## 题目描述

给你一个长为 $n$ 的序列，有 $m$ 次查询操作。

每次查询操作给定参数 $l,r,b$，需输出最大的 $x$，使得存在一个 $a$，满足 $0\leq a<b$，使得 $a,a+b,a+2b,\ldots,a+(x-1)b$ 都在区间 $[l,r]$ 内至少出现过一次。

如果不存在 $[0,b-1]$ 内的数，则输出 $0$。

对于 $30\%$ 的数据，所有出现过的数在 $[0,1000]$ 之间。

对于另外 $30\%$ 的数据，$b \leq 1000$。

对于 $100\%$ 的数据，所有出现过的数在 $[0,10^5]$ 之间。

$\rm 1.5s.$

## 题解

由于询问看起来就不怎么可做，于是尝试使用桶（bitset ver.）维护。

那么对于询问 $(l,r,b)$，答案就是最大的 $k$，使得 $\displaystyle \bigcap^k_{i=1} cnt[(i-1)b:ib)$ 非空，其中 $cnt$ 是存下 $[l,r]$ 中的值的桶，这部分时间复杂度为 $O(m\cdot\frac Vb\cdot\frac bw)=O(\frac{mV}w)$。

此时可以使用莫队维护 bitset，那么总时间复杂度为 $O(\frac{mV}w+n\sqrt m)$。

然而上面的话显然有问题，bitset 部分的时间复杂度应为 $O(m\cdot\frac Vb\lceil\frac bw\rceil)\neq O(\frac{mV}w)$，这个式子在 $b\lt w$ 时应为 $O(\frac{mV}b)$，它甚至可以取到 $O(mV)$。

所以在 $b<w$ 时还要另寻他法。不妨暴力一点，对于每一种 $b$ 分别单独跑一次莫队，并单独开 $b$ 个 bitset 记录 $a_i\bmod b$ 不同情况下的值，最后的答案就是 $\displaystyle\max_{r=0}^{b-1} \rm mex$ $cnt[l,r]$，这部分时间复杂度为 $O(nw\sum\sqrt m_i)$。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

#define ssiz(x) (signed)x.size()
#define allc(x) x.begin(),x.end()
using lint=long long;
using ull=unsigned lint;
#define Bit(x) (__int128(1)<<(x))
#define Mask(x) (Bit(x)-1)
const int N=2e5+9;

const int V=1e5+1;
const int d=6,w=Bit(d),msk=Mask(d);
const int lim=64;
struct Bitset{
    int len;
    vector<ull> v;
    inline void Reset(){for(ull &x:v) x=0;}
    inline void Set(){for(ull &x:v) x=~0ull;}
    inline void Init(int x,int k){v.resize(2+(len=x>>d)),k?Set():Reset();}
    inline void Flip(){for(ull &x:v) x=~x;}
    inline void Set1(int pos){v[pos>>d]|=1ull<<(pos&msk);}
    inline void Set0(int pos){v[pos>>d]&=~(1ull<<(pos&msk));}
    inline int operator [](int pos){return v[pos>>d]&(1ull<<(pos%msk));}
    inline int All(){for(ull x:v) if(~x) return 0;return 1;}
    inline int Any(){for(ull x:v) if(x) return 1;return 0;}
    inline int Count(){
        int cnt=0;
        for(ull x:v) cnt+=__builtin_popcountll(x);
        return cnt;
    }
    inline int Mex(){
        for(int i=0;;i++) if(~v[i]) return (i<<d)|__builtin_ctzll(~v[i]);
    }
    inline int Low(){
        for(int i=0;;i++) if(v[i]) return (i<<d)|__builtin_ctzll(v[i]);
    }
    inline void operator &=(Bitset &x){for(int i=0;i<=len;i++) v[i]&=x.v[i];}
    inline Bitset operator ~(){Bitset x=*this;x.Flip();return x;}
    Bitset(){}
    Bitset(int x,int k){this->Init(x,k);}
};
ull mask[65];
void InitMask(){for(int i=0;i<=64;i++) mask[i]=Mask(i);}
#define Lsh(x,p) ((p)>63?0:(x)<<(p))
#define Rsh(x,p) ((p)>63?0:(x)>>(p))
inline void Cpy(Bitset &src,Bitset &dst,int x,int len){
    dst.v.clear(),dst.len=len>>d;
    int i,p;
    while(len>=w){
        i=x>>d,p=x&msk;
        dst.v.push_back(Rsh(src.v[i],p)|Lsh(src.v[i+1],w-p));
        len-=w,x+=w;
    }
    if(len){
        i=x>>d,p=x&msk;
        dst.v.push_back(len<=w-p?Rsh(src.v[i],p)&mask[len]:(Rsh(src.v[i],p)|Lsh(src.v[i+1],w-p))&mask[len]);
    }
    dst.v.push_back(0);
}

int a[N],ql[N],qr[N],qb[N],ans[N],n,m;
vector<int> c[65],q;

int blk[N],cnt[N];
void MoAlgo1(){
    if(!ssiz(q)) return ;
    for(int i=0;i<V;i++) cnt[i]=0;
    int B=ceil(n/sqrt(ssiz(q)));
    for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
    sort(allc(q),[](int x,int y)->bool{
        if(blk[ql[x]]^blk[ql[y]]) return blk[ql[x]]<blk[ql[y]];
        else return qr[x]<qr[y];
    });
    
    Bitset vis(V<<1,0),cur,tmp;
    auto Insert=[&vis](int x)->void{if(!cnt[x]++) vis.Set1(x);};
    auto Erase=[&vis](int x)->void{if(!--cnt[x]) vis.Set0(x);};
    int l=1,r=0;
    for(int i:q){
        while(r<qr[i]) Insert(a[++r]);
        while(l>ql[i]) Insert(a[--l]);
        while(r>qr[i]) Erase(a[r--]);
        while(l<ql[i]) Erase(a[l++]);
        Cpy(vis,cur,0,qb[i]);
        while(cur.Any()){
            Cpy(vis,tmp,qb[i]*++ans[i],qb[i]);
            cur&=tmp;
        }
    }
}
int dvd[N],mod[N];
void MoAlgo2(int k){
    if(!ssiz(c[k])) return ;
    int B=ceil(n/sqrt(ssiz(c[k])));
    for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
    sort(allc(c[k]),[](int x,int y)->int{
        if(blk[ql[x]]^blk[ql[y]]) return blk[ql[x]]<blk[ql[y]];
        else return qr[x]<qr[y];
    });
    for(int i=0,r=0,q=0;i<V;i++,r++){
        if(r==k) q++,r=0;
        dvd[i]=q,mod[i]=r;
    }

    for(int i=0;i<V;i++) cnt[i]=0;
    vector<Bitset> vis(k,Bitset((V-1)/k+1+1,0));
    int l=1,r=0;
    auto Insert=[&vis,&k](int x)->void{if(!cnt[x]++) vis[mod[x]].Set1(dvd[x]);};
    auto Erase=[&vis,&k](int x)->void{if(!--cnt[x]) vis[mod[x]].Set0(dvd[x]);};
    for(int i:c[k]){
        while(r<qr[i]) Insert(a[++r]);
        while(l>ql[i]) Insert(a[--l]);
        while(r>qr[i]) Erase(a[r--]);
        while(l<ql[i]) Erase(a[l++]);
        for(auto &b:vis) ans[i]=max(ans[i],b.Mex());
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>ql[i]>>qr[i]>>qb[i];
        if(qb[i]<=w) c[qb[i]].push_back(i);
        else q.push_back(i);
    }

    InitMask();
    MoAlgo1();
    for(int k=1;k<=lim;k++) MoAlgo2(k);

    for(int i=1;i<=m;i++) cout<<ans[i]<<endl;

    return 0;
}
```

