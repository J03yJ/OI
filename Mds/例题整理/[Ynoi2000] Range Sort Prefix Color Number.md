# [Ynoi2000] Range Sort Prefix Color Number

## 题目描述

给定整数序列 $a_1,\dots,a_n$ ，共 $m$ 次操作；

每次操作给出 $l,r,x$ ，首先进行修改，然后查询 $a_1,\dots,a_x$ 中有多少种不同的值。

若 $l\le r$ ，则进行的修改是将 $a_l,\dots,a_r$ 从小到大排序；否则进行的修改是将 $a_r,\dots,a_l$ 从大到小排序。

**强制在线**。

对于 $20\%$ 的数据，满足 $n,m\le 10^3$。

对于另外 $20\%$ 的数据，满足 $a_i\le 10$。

对于另外 $20\%$ 的数据，满足 $a_i\le 100$。

对于另外 $20\%$ 的数据，满足 $n,m\le 10^5$。

对于 $100\%$ 的数据，满足 $1\le a_i\le n$，$1\le l,r,x\le n$，$1\le n,m\le 10^6$。

$\rm 8s.$

## 题解

发现排序满足颜色段理论，于是考虑直接上 ODT。

发现值域线段树可以合并分裂，于是每个线段维护自己范围内的数，在 ODT 上线段树合并/分裂。（其实这部分可以文艺平衡树）

对于查询，暴力跳连续段肯定时间复杂度爆炸。于是考虑在每个连续段末尾存储该连续段内的答案，放在树状数组上查。散块直接单独查即可。

有些实现细节：实际上由于查询的是前缀，所以可以直接钦定原始数组中第一次出现的数的贡献为 $1$，其他的则为 $0$。可以证明在 stable_sort 的情况下，贡献为 $1$ 的数永远不会越过贡献为 $0$ 的。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

#define ssiz(x) (signed)x.size()
const int N=1e6+9;

struct Node{
    int lc,rc,cnt,siz;
    void Init(){lc=rc=cnt=siz=0;}
}tr[N<<6];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define cnt(x) tr[x].cnt
#define siz(x) tr[x].siz

int trs[N<<6],cnt,ttop;
inline int Allc(){return ttop?trs[ttop--]:++cnt;}
inline void Erase(int x){tr[x].Init(),trs[++ttop]=x;}
inline void PushUp(int x){siz(x)=siz(lc(x))+siz(rc(x)),cnt(x)=cnt(lc(x))+cnt(rc(x));}
void Insert(int &x,int L,int R,int pos,int t){
    if(!x) x=Allc();
    if(L==R){
        siz(x)+=t;
        cnt(x)++;
        return ;
    }
    int mid=(L+R)>>1;
    if(pos<=mid) Insert(lc(x),L,mid,pos,t);
    else Insert(rc(x),mid+1,R,pos,t);
    PushUp(x);
}
void Merge(int &x,int &y,int L,int R){
    if(!x||!y) return x|=y,void();
    if(L==R){
        siz(x)+=siz(y);
        cnt(x)+=cnt(y);
        return Erase(y);
    }
    int mid=(L+R)>>1;
    Merge(lc(x),lc(y),L,mid);
    Merge(rc(x),rc(y),mid+1,R);
    PushUp(x),Erase(y);
}
void Split(int &x,int &y,int L,int R,int k,int op){
    if(!x||k==cnt(x)) return ;
    if(!k) return y=x,x=0,void();
    if(!y) y=Allc();
    if(L==R){
        cnt(y)=cnt(x)-k;
        cnt(x)=k;
        if(!cnt(x)) siz(y)=siz(x);
        return ;
    }
    int mid=(L+R)>>1;
    if(!op){
        Split(lc(x),lc(y),L,mid,min(k,cnt(lc(x))),op);
        Split(rc(x),rc(y),mid+1,R,max(k-cnt(lc(x)),0),op);
    }else{
        Split(rc(x),rc(y),mid+1,R,min(k,cnt(rc(x))),op);
        Split(lc(x),lc(y),L,mid,max(k-cnt(rc(x)),0),op);
    }
    PushUp(x),PushUp(y);
}
int Query(int x,int L,int R,int k,int op){
    if(!k||!x) return 0;
    if(k==cnt(x)) return siz(x);
    if(L==R) return siz(x);
    int mid=(L+R)>>1;
    if(!op){
        if(k<=cnt(lc(x))) return Query(lc(x),L,mid,k,op);
        else return siz(lc(x))+Query(rc(x),mid+1,R,k-cnt(lc(x)),op);
    }else{
        if(k<=cnt(rc(x))) return Query(rc(x),mid+1,R,k,op);
        else return siz(rc(x))+Query(lc(x),L,mid,k-cnt(rc(x)),op);
    }
}

int t[N],vis[N],a[N],n,q;
void Add(int x,int k){while(x<=n){t[x]+=k,x+=x&-x;}}
int Ask(int x){int sum=0;while(x){sum+=t[x],x&=x-1;}return sum;}

struct Seg{
    mutable int l,r,op,root;
    Seg(){}
    Seg(int _l,int _r,int _o,int _rt){l=_l,r=_r,op=_o,root=_rt;}
    bool operator <(Seg s)const{return l<s.l;}
};
set<Seg> s;
inline auto Locate(int pos){return pos&&pos<=n?--s.upper_bound(Seg(pos,0,0,0)):s.end();}
void SplitAt(int pos){
    auto it=Locate(pos);
    if(it==s.end()||it->l==pos) return ;
    Seg lt(it->l,pos-1,it->op,it->root),rt(pos,it->r,it->op,0);
    Add(it->r,-siz(it->root));
    s.erase(it);
    Split(lt.root,rt.root,1,n,lt.r-lt.l+1,lt.op);
    Add(lt.r,siz(lt.root));
    Add(rt.r,siz(rt.root));
    s.insert(lt);
    s.insert(rt);
}
void Sort(int l,int r,int op){
    SplitAt(l),SplitAt(r+1);
    auto lt=Locate(l),rt=Locate(r+1);
    Seg tmp(l,r,op,0);
    for(auto it=lt;it!=rt;it++){
        Add(it->r,-siz(it->root));
        Merge(tmp.root,it->root,1,n);
    }
    s.erase(lt,rt);
    Add(tmp.r,siz(tmp.root));
    s.insert(tmp);
}
int QueryAt(int pos){
    auto it=Locate(pos);
    return Ask(it->l-1)+Query(it->root,1,n,pos-it->l+1,it->op);
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++){
        int root=Allc();
        Insert(root,1,n,a[i],!vis[a[i]]);
        s.insert(Seg(i,i,0,root));
        if(!vis[a[i]]) Add(i,1),vis[a[i]]=1;
    }

    int lst=0;
    while(q--){
        int l,r,x;
        cin>>l>>r>>x;
        l^=lst,r^=lst,x^=lst;
        int op=l>r;
        if(op) swap(l,r);
        Sort(l,r,op);
        cout<<(lst=QueryAt(x))<<endl;
    }

    return 0;
}
```

