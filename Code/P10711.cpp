#include<bits/stdc++.h>

using namespace std;

#define fir(x) (x).first
#define sec(x) (x).second
#define endl '\n'
using pii=pair<int,int>;
using ll=long long;
const int N=2e5+9;
const int inf=1e9;
const int V=2e5;

struct Node{
    int l,r,dat;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat

inline void PushUp(int x){dat(x)=min(dat(x<<1),dat(x<<1|1));}
inline void Build(int x,int l,int r){
    l(x)=l,r(x)=r;
    if(l(x)==r(x)) return dat(x)=inf,void();
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
    PushUp(x);
}
inline void Modify(int x,int pos,int k){
    if(l(x)==r(x)) return dat(x)=k,void();
    int mid=l(x)+r(x)>>1;
    if(pos<=mid) Modify(x<<1,pos,k);
    else Modify(x<<1|1,pos,k);
    PushUp(x);
}
inline int Query(int x,int l,int r){
    if(l<=l(x)&&r(x)<=r) return dat(x);
    int mid=l(x)+r(x)>>1;
    if(l<=mid&&r>mid) return min(Query(x<<1,l,mid),Query(x<<1|1,mid+1,r));
    else if(l<=mid) return Query(x<<1,l,r);
    else return Query(x<<1|1,l,r);
}

struct DelHeap{
    priority_queue<int> p,q;
    inline void Insert(int x){p.push(x);}
    inline void Erase(int x){q.push(x);}
    inline int Size(){return p.size()-q.size();}
    inline int Top(){
        if(!Size()) return -inf;
        while(q.size()&&p.top()==q.top()) p.pop(),q.pop();
        return p.top();
    }
}h[N];

int lft[N],typ[N],q;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>q;
    Build(1,1,V);
    for(int i=0,p=1,op;p<=q;p++){
        cin>>op;
        if(op==1){
            ++i;
            cin>>lft[i]>>typ[i];
            int pos=!typ[i]?lft[i]:1;
            h[pos].Insert(-i);
            Modify(1,pos,-h[pos].Top());
        }else if(op==2){
            int j;
            cin>>j;
            int pos=!typ[j]?lft[j]:1;
            h[pos].Erase(-j);
            Modify(1,pos,-h[pos].Top());
            lft[j]=0;
        }else{
            ll b;
            cin>>b;
            vector<pii> ans;
            while(b){
                int j=Query(1,1,min(b,ll(V)));
                if(j==inf) break ;
                int pos=!typ[j]?lft[j]:1;
                h[pos].Erase(-j);
                int k=min(ll(lft[j]),b);
                lft[j]-=k,b-=k;
                if(lft[j]) h[pos].Insert(-j);
                ans.emplace_back(j,k);
                Modify(1,pos,-h[pos].Top());
            }
            cout<<ans.size()<<endl;
            for(pii p:ans) cout<<fir(p)<<' '<<sec(p)<<endl;
        }
    }
    
    return 0;
}