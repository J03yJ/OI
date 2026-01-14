# [Ynoi2017] 由乃的 OJ

## 题目描述

给你一个有 $n$ 个点的树，每个点的包括一个位运算 $opt$ 和一个权值 $x$，位运算有`&`，`|`，`^` 三种，分别用 $1,2,3$ 表示。

每次询问包含三个整数 $x,y,z$，初始选定一个数 $v$。然后 $v$ 依次经过从 $x$ 到 $y$ 的所有节点，每经过一个点 $i$，$v$ 就变成 $v\ opt_i\ x_i$，所以他想问你，最后到 $y$ 时，希望得到的值尽可能大，求最大值。给定的初始值 $v$ 必须是在 $[0,z]$ 之间。

每次修改包含三个整数 $x,y,z$，意思是把 $x$ 点的操作修改为 $y$，数值改为 $z$。

对于 $30\%$ 的数据，$n,m\leq 1$。

对于另外 $20\%$ 的数据，$k\leq 5$。

对于另外 $20\%$ 的数据，位运算只会出现一种。

对于 $100\%$ 的数据，$0\leq n,m \leq 10^5$，$0\leq k\leq 64$。

$\rm 250ms.$

## 题解

发现位与位之间是没有关系的，于是考虑对于每一位独立考虑。

考虑树剖，维护每条链的信息。设变量 $p_{0/1},q_{0/1}$ 表示原本手里的数字是 $0/1$ 正/反着遍历一条链的结果，显然信息是可以合并的，于是直接上线段树。对于每一位跑出来的结果贪心即可，时间复杂度 $O(nk\log ^2n)$。

时间复杂度太劣，无法通过。继续观察发现每一个变量存储的信息仅为 $0/1$ 状压即可把 $k$ 消去，时间复杂度 $O(n\log ^2n)$。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;
using lint=long long;
using ulint=unsigned lint;
#define Bit(k) (__int128(1)<<(k))
#define Mask(k) (Bit(k)-1)

void Read(ulint &x){
    char ch;while(ch=getchar(),ch<'!');x=ch-48;
    while(ch=getchar(),ch>'!') x=(x<<3)+(x<<1)+ch-48;
}
void Write(ulint x){
    if(x>9) Write(x/10);
    putchar(x%10+48);
}

int n,m,lim;
struct Data{
    ulint p[2],q[2];
    Data(){}
    Data(ulint a,ulint b){p[0]=q[0]=a,p[1]=q[1]=b;}
    Data(ulint a,ulint b,ulint c,ulint d){p[0]=a,p[1]=b,q[0]=c,q[1]=d;}
    Data operator +(Data x){
        Data res;
        res.p[0]=p[0]&x.p[1]|~p[0]&x.p[0];
        res.p[1]=p[1]&x.p[1]|~p[1]&x.p[0];
        res.q[0]=x.q[0]&q[1]|~x.q[0]&q[0];
        res.q[1]=x.q[1]&q[1]|~x.q[1]&q[0];
        return res;
    }
    Data operator -(){return Data(q[0],q[1],p[0],p[1]);}
    Data operator -(Data x){return *this+(-x);}
};
struct Node{
    int l,r;
    Data dat;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat
inline void PushUp(int x){dat(x)=dat(x<<1)+dat(x<<1|1);}
void Build(int x,int l,int r){
    l(x)=l,r(x)=r;
    if(l(x)==r(x)) return ;
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l(x),mid),Build(x<<1|1,mid+1,r(x));
    PushUp(x);
}
void Modify(int x,int pos,Data k){
    if(l(x)==r(x)) return dat(x)=k,void();
    int mid=l(x)+r(x)>>1;
    if(pos<=mid) Modify(x<<1,pos,k);
    else Modify(x<<1|1,pos,k);
    PushUp(x);
}
Data Query(int x,int l,int r){
    if(l>r) return Data(0,Mask(lim));
    if(l<=l(x)&&r(x)<=r) return dat(x);
    int mid=l(x)+r(x)>>1;
    if(l<=mid&&r>mid) return Query(x<<1,l,r)+Query(x<<1|1,l,r);
    else if(l<=mid) return Query(x<<1,l,r);
    else return Query(x<<1|1,l,r);
}

int fi[N],ne[N],to[N],adj;
ulint a[N],op[N];
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}
int fa[N],dep[N],siz[N],hson[N];
void DFS1(int x){
    siz[x]=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        fa[y]=x;
        dep[y]=dep[x]+1;
        DFS1(y);
        siz[x]+=siz[y];
        if(siz[y]>siz[hson[x]]) hson[x]=y;
    }
}
int top[N],dfn[N],ed[N],dcnt;
void DFS2(int x,int t){
    top[x]=t;
    dfn[x]=++dcnt;
    if(hson[x]) DFS2(hson[x],t);
    else return ;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        if(y==hson[x]) continue ;
        DFS2(y,y);
    }
}
Data Path(int x,int y){
    Data p(0,Mask(lim)),q(0,Mask(lim));
    while(top[x]!=top[y]){
        if(dep[top[x]]>dep[top[y]]){
            p=p-Query(1,dfn[top[x]],dfn[x]);
            x=fa[top[x]];
        }else{
            q=q-Query(1,dfn[top[y]],dfn[y]);
            y=fa[top[y]];
        }
    }
    if(dep[x]>dep[y]) p=p-Query(1,dfn[y],dfn[x]);
    else q=q-Query(1,dfn[x],dfn[y]);
    return p-q;
}

int main(){
    cin>>n>>m>>lim;
    for(int i=1;i<=n;i++) Read(op[i]),Read(a[i]);
    for(int i=1,u,v;i<n;i++) cin>>u>>v,AdEg(u,v),AdEg(v,u);
    
    DFS1(1),DFS2(1,1),Build(1,1,n);
    for(int i=1;i<=n;i++){
        if(op[i]==1) Modify(1,dfn[i],Data(0,a[i]));
        else if(op[i]==2) Modify(1,dfn[i],Data(a[i],Mask(lim)));
        else Modify(1,dfn[i],Data(a[i],a[i]^Mask(lim)));
    }

    while(m--){
        ulint o,x,y,z;
        Read(o),Read(x),Read(y),Read(z);
        if(o==1){
            ulint ans=0;
            Data tmp=Path(x,y);
            for(int k=lim-1;~k;k--){
                if(z>>k&1){
                    if((tmp.p[0]&Bit(k))<(tmp.p[1]&Bit(k))){
                        ans|=tmp.p[1]&Bit(k);
                    }else{
                        ans|=tmp.p[0]&Bit(k);
                        z=Mask(k);
                    }
                }else ans|=tmp.p[0]&Bit(k);
            }
            Write(ans),putchar('\n');
        }else{
            op[x]=y,a[x]=z;
            if(op[x]==1) Modify(1,dfn[x],Data(0,a[x]));
            else if(op[x]==2) Modify(1,dfn[x],Data(a[x],Mask(lim)));
            else Modify(1,dfn[x],Data(a[x],a[x]^Mask(lim)));
        }
    }

    return 0;
}
```

