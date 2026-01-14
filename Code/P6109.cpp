#include<bits/stdc++.h>

using namespace std;

const int N=5e5+9;
#define int long long

inline void Chmax(long long &x,long long y){
    if(y>x) x=y;
}

namespace Sgt{
    struct node{
        int l,r;
        long long tag,htag,mx,hmx;
        bool cls;
    }tr[N<<2];
    
    void Build(int x,int l,int r){
        tr[x].l=l;tr[x].r=r;
        if(l==r) return ;
        int mid=l+r>>1;
        Build(x<<1,l,mid);
        Build(x<<1|1,mid+1,r);
    }
    inline void PushUp(int x){
        tr[x].mx=max(tr[x<<1].mx,tr[x<<1|1].mx);
        tr[x].hmx=max(tr[x<<1].hmx,tr[x<<1|1].hmx);
    }
    inline void CalcTag(int x,long long tag,long long htag){
        Chmax(tr[x].htag,tr[x].tag+htag);
        Chmax(tr[x].hmx,tr[x].mx+htag);
        tr[x].tag+=tag;
        tr[x].mx+=tag;
    }
    inline void Push(int x){
        CalcTag(x<<1,tr[x].tag,tr[x].htag);
        CalcTag(x<<1|1,tr[x].tag,tr[x].htag);
        tr[x].tag=tr[x].htag=0;
    }
    inline void Clear(int x){
        Push(x);
        tr[x].cls=1;
        tr[x].hmx=tr[x].mx;
    }
    inline void PushDown(int x){
        if(tr[x].cls){
            Clear(x<<1);Clear(x<<1|1);
            tr[x].cls=0;
        }
        Push(x);
    }
    void Modify(int x,int l,int r,int k){
        if(l<=tr[x].l&&tr[x].r<=r){
            CalcTag(x,k,k);
            return ;
        }
        int mid=tr[x].l+tr[x].r>>1;
        PushDown(x);
        if(l<=mid) Modify(x<<1,l,r,k);
        if(r>mid) Modify(x<<1|1,l,r,k);
        PushUp(x);
    }
    long long Query(int x,int l,int r){
        if(l<=tr[x].l&&tr[x].r<=r) return tr[x].hmx;
        int mid=tr[x].l+tr[x].r>>1;
        long long ans=0;
        PushDown(x);
        if(l<=mid) Chmax(ans,Query(x<<1,l,r));
        if(r>mid) Chmax(ans,Query(x<<1|1,l,r));
        return ans;
    }
}

int n,m,q;
vector<tuple<int,int,int,int>> seg;
vector<int> s[N];
tuple<int,int,int,int> qry[N];
inline bool CmpSeg(int x,int y){
    if(get<0>(seg[x])!=get<0>(seg[y])) return get<0>(seg[x])<get<0>(seg[y]);
    else return get<3>(seg[x])<get<3>(seg[y]);
}

long long ans[N];
inline void Add(int k){
    for(int i=0;i<s[k].size();i++){
        Sgt::Modify(1,get<1>(seg[s[k][i]]),get<2>(seg[s[k][i]]),get<3>(seg[s[k][i]]));
    }
}
inline void Del(int k){
    for(int i=s[k].size()-1;~i;i--){
        Sgt::Modify(1,get<1>(seg[s[k][i]]),get<2>(seg[s[k][i]]),-get<3>(seg[s[k][i]]));
    }
}
inline bool CmpL(int x,int y){
    return get<0>(qry[x])>get<0>(qry[y]);
}
inline bool CmpR(int x,int y){
    return get<1>(qry[x])<get<1>(qry[y]);
}
void Solve(int l,int r,vector<int> &allq){
    if(!allq.size()) return ;

    int mid=l+r>>1;

    for(int i=l;i<=mid;i++) Add(i);

    if(l==r){
        Sgt::Clear(1);
        for(int i:allq){
            Chmax(ans[i],Sgt::Query(1,get<2>(qry[i]),get<3>(qry[i])));
        }
        for(int i=mid;i>=l;i--) Del(i);
        return ;
    }

    vector<int> lq,rq,curq;
    for(int i:allq){
        if(get<1>(qry[i])<=mid) lq.push_back(i);
        else if(get<0>(qry[i])>mid) rq.push_back(i);
        else curq.push_back(i);
    }

    sort(curq.begin(),curq.end(),CmpR);
    for(int i=mid+1,j=0;i<=r;i++){
        Add(i);
        if(i==mid+1) Sgt::Clear(1);
        while(j<curq.size()&&get<1>(qry[curq[j]])==i){
            Chmax(ans[curq[j]],Sgt::Query(1,get<2>(qry[curq[j]]),get<3>(qry[curq[j]])));
            j++;
        }
    }
    for(int i=r;i>mid;i--) Del(i);

    Solve(mid+1,r,rq);

    sort(curq.begin(),curq.end(),CmpL);
    Sgt::Clear(1);
    for(int i=mid,j=0;i>=l;i--){
        while(j<curq.size()&&get<0>(qry[curq[j]])==i){
            Chmax(ans[curq[j]],Sgt::Query(1,get<2>(qry[curq[j]]),get<3>(qry[curq[j]])));
            j++;
        }
        Del(i);
    }

    Solve(l,mid,lq);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    cin>>n>>m>>q;
    seg.push_back(make_tuple(0,0,0,0));
    for(int i=1;i<=m;i++){
        int l1,r1,l2,r2,k;
        cin>>l1>>l2>>r1>>r2>>k;
        s[l1].push_back(seg.size());
        seg.push_back(make_tuple(l1,l2,r2,k));
        s[r1+1].push_back(seg.size());
        seg.push_back(make_tuple(r1+1,l2,r2,-k));
    }
    Sgt::Build(1,1,n+1);
    for(int i=1;i<=n+1;i++) sort(s[i].begin(),s[i].end(),CmpSeg);
    vector<int> allq;
    for(int i=1;i<=q;i++){
        cin>>get<0>(qry[i])>>get<2>(qry[i])>>get<1>(qry[i])>>get<3>(qry[i]);
        allq.push_back(i);
    }
    Solve(1,n,allq);
    for(int i=1;i<=q;i++) cout<<ans[i]<<endl;
    return 0;
}