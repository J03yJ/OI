#include<bits/stdc++.h>

using namespace std;

const int N=5e5+9;

long long a[N];

struct node{
    int l,r;
    int mn,mx;
    long long dat;
    __int128 sdat;
    node operator +(node x){
        node ans;
        ans.dat=dat+x.dat;
        ans.sdat=sdat+x.sdat;
        ans.mx=max(mx,x.mx);
        ans.mn=min(mn,x.mn);
        return ans;
    }
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define mn(x) tr[x].mn
#define mx(x) tr[x].mx
#define dat(x) tr[x].dat
#define sdat(x) tr[x].sdat

inline void pushup(int x){
    int l=tr[x].l,r=tr[x].r;
    tr[x]=tr[x*2]+tr[x*2+1];
    tr[x].l=l;tr[x].r=r;
}
void build(int x,int l,int r){
    l(x)=l;r(x)=r;
    if(l(x)==r(x)){
        mn(x)=mx(x)=dat(x)=a[l(x)];
        sdat(x)=a[l(x)]*a[l(x)];
        return ;
    }
    int mid=l(x)+r(x)>>1;
    build(2*x,l,mid);
    build(2*x+1,mid+1,r);
    pushup(x);
}
void modify(int x,int pos,int k){
    if(l(x)==r(x)){
        mn(x)=mx(x)=dat(x)=k;
        sdat(x)=k*k;
        return ;
    }
    int mid=l(x)+r(x)>>1;
    if(pos<=mid) modify(2*x,pos,k);
    else modify(2*x+1,pos,k);
    pushup(x);
}
node query(int x,int l,int r){
    // cout<<x<<' '<<l<<' '<<r<<' '<<l(x)<<' '<<r(x)<<endl;/
    if(l<=l(x)&&r(x)<=r) return tr[x];
    int mid=l(x)+r(x)>>1;
    if(l<=mid&&r>mid) return query(2*x,l,r)+query(2*x+1,l,r);
    else if(l<=mid) return query(2*x,l,r);
    else return query(2*x+1,l,r);
}

long long Sum(long long x){
    return 1ll*x*(x+1)/2;
}
__int128 SSum(__int128 x){
    return x*(x+1)*(2*x+1)/6;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    build(1,1,n);
    while(m--){
        int op,x,y;
        cin>>op>>x>>y;
        if(op==1){
            modify(1,x,y);
            a[x]=y;
        }else{
            node t=query(1,x,y);
            if(t.mx-t.mn!=y-x){
                cout<<"yuanxing"<<endl;
                continue ;
            }
            if(t.dat!=Sum(t.mx)-Sum(t.mn-1)||t.sdat!=SSum(t.mx)-SSum(t.mn-1)){
                cout<<"yuanxing"<<endl;
                continue ;
            }
            cout<<"damushen"<<endl;
        }
    }
    return 0;
}