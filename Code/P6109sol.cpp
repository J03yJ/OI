#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
#define MAXN 500005
#define mx(x,y) x=max(x,y)
typedef long long ll;
struct modifyNode{
    int x,l,r,val;
}mdf[MAXN<<1];
struct queryNode{
    int x1,x2,l,r,id;
}ask[MAXN];
int n,m,q;
ll ans[MAXN];
vector<int> mdp[MAXN];

namespace sgt{
    #define mid ((tree[p].l+tree[p].r)>>1)
    #define ls (p<<1)
    #define rs (p<<1|1)
    struct node{
        int l,r;
        bool reset;
        ll maxx,hmax,tag,htag;
    }tree[MAXN<<2];
    void build(int l,int r,int p){
        tree[p].l=l,tree[p].r=r;
        if(l==r) return;
        build(l,mid,ls);
        build(mid+1,r,rs);
    }
    void pushdownTag(int p,ll tag,ll htag){
        mx(tree[p].htag,tree[p].tag+htag);
        tree[p].tag+=tag;
        mx(tree[p].hmax,tree[p].maxx+htag);
        tree[p].maxx+=tag;
    }
    void clearHistory(int p){
        pushdownTag(ls,tree[p].tag,tree[p].htag);
        pushdownTag(rs,tree[p].tag,tree[p].htag);
        tree[p].reset=1;
        tree[p].htag=tree[p].tag=0;
        tree[p].hmax=tree[p].maxx;
    }
    void pushdown(int p){
        if(tree[p].reset){
            clearHistory(ls);
            clearHistory(rs);
            tree[p].reset=0;
        }
        pushdownTag(ls,tree[p].tag,tree[p].htag);
        pushdownTag(rs,tree[p].tag,tree[p].htag);
        tree[p].tag=tree[p].htag=0;
    }
    void update(int p){
        tree[p].maxx=max(tree[ls].maxx,tree[rs].maxx);
        tree[p].hmax=max(tree[ls].hmax,tree[rs].hmax);
    }
    void modify(int l,int r,int k,int p){
        if(l<=tree[p].l&&r>=tree[p].r){
            pushdownTag(p,k,k);
            return;
        }
        pushdown(p);
        if(l<=mid) modify(l,r,k,ls);
        if(r>mid) modify(l,r,k,rs);
        update(p);
    }
    ll query(int l,int r,int p){
        if(l<=tree[p].l&&r>=tree[p].r) return tree[p].hmax;
        pushdown(p);
        ll maxx=0;
        if(l<=mid) mx(maxx,query(l,r,ls));
        if(r>mid) mx(maxx,query(l,r,rs));
        return maxx;
    }
    #undef mid
    #undef ls
    #undef rs
}

void add(int x){
    for(auto v:mdp[x]) sgt::modify(mdf[v].l,mdf[v].r,mdf[v].val,1);
}
void del(int x){
    for(int i=mdp[x].size()-1;i>=0;i--){
        int v=mdp[x][i];
        sgt::modify(mdf[v].l,mdf[v].r,-mdf[v].val,1);
    }
}
bool cmp1(int x,int y){
    return mdf[x].x<mdf[y].x||mdf[x].x==mdf[y].x&&mdf[x].val<mdf[y].val;
}
bool cmp2(int x,int y){
    return ask[x].x2<ask[y].x2;
}
bool cmp3(int x,int y){
    return ask[x].x1>ask[y].x1;
}
void stable(int l,int r,vector<int>& qnum){
    if(qnum.empty()) return;

    int mid=(l+r)>>1;
    
    for(int i=l;i<=mid;i++) add(i);//把mid左侧的扫描线加进去
    
    if(l==r){
        sgt::clearHistory(1);//重置历史最大值当前最大值
        for(auto v:qnum)
        mx(ans[ask[v].id],sgt::query(ask[v].l,ask[v].r,1));
        for(int i=mid;i>=l;i--) del(i);
        return;
    }

    vector<int> qnow,ql,qr;
    for(auto v:qnum){//保存跨区间的询问
        if(ask[v].x2<=mid) ql.push_back(v);
        else if(ask[v].x1>mid) qr.push_back(v);
        else qnow.push_back(v);
    }

    sort(qnow.begin(),qnow.end(),cmp2);
    for(int j=0,i=mid+1;i<=r;i++){
        add(i);//添加右部分的扫描线
        if(i==mid+1) sgt::clearHistory(1);//注意此时才能重置历史最大值
        while(j<qnow.size()&&ask[qnow[j]].x2==i){
            mx(ans[ask[qnow[j]].id],sgt::query(ask[qnow[j]].l,ask[qnow[j]].r,1));//询问操作
            j++;
        }
    }
    for(int i=r;i>mid;i--) del(i);//撤销右区间的扫描线

    stable(mid+1,r,qr);//分治右区间

    sort(qnow.begin(),qnow.end(),cmp3);
    sgt::clearHistory(1);//重置历史最大值
    for(int j=0,i=mid;i>=l;i--){
        while(j<qnow.size()&&ask[qnow[j]].x1==i){
            mx(ans[ask[qnow[j]].id],sgt::query(ask[qnow[j]].l,ask[qnow[j]].r,1));
            j++;
        }
        del(i);//撤销左部分
    }

    stable(l,mid,ql);//分治左区间
}
int main(){
    ios::sync_with_stdio(0);
    cin>>n>>m>>q;
    n++;
    for(int p=0,l1,l2,r1,r2,c,i=1;i<=m;i++){
        cin>>l1>>l2>>r1>>r2>>c;
        mdf[++p]={l1,l2,r2,c};//拆分第一维，分成两条扫描线
        mdp[l1].push_back(p);//存每个位置的扫描线数量
        mdf[++p]={r1+1,l2,r2,-c};//注意是r1+1
        mdp[r1+1].push_back(p);
    }
    for(int i=1;i<=q;i++){
        cin>>ask[i].x1>>ask[i].l>>ask[i].x2>>ask[i].r;
        ask[i].id=i;
    }
    for(int i=1;i<=n;i++) sort(mdp[i].begin(),mdp[i].end(),cmp1);//先减后加，保证历史最大值正确性
    sgt::build(1,n,1);
    vector<int> qnum;
    for(int i=1;i<=q;i++) qnum.push_back(i);
    stable(1,n-1,qnum);//进行分治
    for(int i=1;i<=q;i++) cout<<ans[i]<<endl;//报告答案，大功告成喵！
    return 0;
}