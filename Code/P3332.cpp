#include<bits/stdc++.h>

using namespace std;

const int N=5e4+9;
using ll=long long;

namespace SgT{
    struct Node{
        int l,r;
        ll dat,tag;
    }tr[N<<2];
    #define l(x) tr[x].l
    #define r(x) tr[x].r
    #define dat(x) tr[x].dat
    #define tag(x) tr[x].tag
    #define len(x) (r(x)-l(x)+1)

    inline void PushUp(int x){dat(x)=dat(x<<1)+dat(x<<1|1);}
    inline void Push(int x,int k){dat(x)+=1ll*k*len(x),tag(x)+=k;}
    inline void PushDown(int x){Push(x<<1,tag(x)),Push(x<<1|1,tag(x)),tag(x)=0;}

    inline void Build(int x,int l,int r){
        l(x)=l,r(x)=r,dat(x)=tag(x)=0;
        if(l(x)==r(x)) return ;
        int mid=l(x)+r(x)>>1;
        Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
        PushUp(x);
    }
    inline void Modify(int x,int l,int r,int k){
        if(l<=l(x)&&r(x)<=r) return Push(x,k);
        int mid=l(x)+r(x)>>1;
        PushDown(x);
        if(l<=mid) Modify(x<<1,l,r,k);
        if(r>mid) Modify(x<<1|1,l,r,k);
        PushUp(x);
    }
    inline ll Query(int x,int l,int r){
        if(l<=l(x)&&r(x)<=r) return dat(x);
        int mid=l(x)+r(x)>>1;
        PushDown(x);
        if(l<=mid&&r>mid) return Query(x<<1,l,r)+Query(x<<1|1,l,r);
        else if(l<=mid) return Query(x<<1,l,r);
        else return Query(x<<1|1,l,r);
    }
}

int op[N],ql[N],qr[N],qc[N],ans[N],n;
inline void Solve(vector<int> &v,int L,int R){
    if(L>R||v.empty()) return ;
    if(L==R){
        for(int x:v) if(op[x]==2) ans[x]=L;
        return ;
    }
    int mid=L+R>>1;
    vector<int> lv,rv;
    for(int x:v){
        if(op[x]==1){
            if(qc[x]>mid) rv.push_back(x),SgT::Modify(1,ql[x],qr[x],1);
            else lv.push_back(x);
        }else if(op[x]==2){
            int tmp=SgT::Query(1,ql[x],qr[x]);
            if(tmp>qc[x]) rv.push_back(x);
            else lv.push_back(x),qc[x]-=tmp;
        }
    }
    for(int x:v) if(op[x]==1&&qc[x]>mid) SgT::Modify(1,ql[x],qr[x],-1);
    Solve(lv,L,mid),Solve(rv,mid+1,R);
}

signed main(){
    return 0;
}