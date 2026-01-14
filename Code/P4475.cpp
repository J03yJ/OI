#include<bits/stdc++.h>

using namespace std;

#define ll long long
const int N=5e4+9;

tuple<int,int,int> a[N];

struct cmp{
    bool k;
    cmp(bool K){k=K;}
    bool operator ()(tuple<int,int,int> a,tuple<int,int,int> b){
        if(!k) return get<0>(a)<get<0>(b);
        else return get<1>(a)<get<1>(b);
    }
};

inline void chmin(int &x,int y){if(y<x) x=y;}
inline void chmax(int &x,int y){if(y>x) x=y;}

struct node{
    pair<int,int> mx,mn,dat;
    int lc,rc;
    ll w;
}tr[N];
int cnt,root;
int build(int l,int r,bool cur){
    int mid=l+r>>1;
    #define x mid
    nth_element(a+l,a+mid,a+r+1,cmp(cur));

    tr[x].dat={get<0>(a[mid]),get<1>(a[mid])};

    if(l<mid) tr[x].lc=build(l,mid-1,!cur);
    if(r>mid) tr[x].rc=build(mid+1,r,!cur);

    tr[x].w=get<2>(a[mid])+tr[tr[x].lc].w+tr[tr[x].rc].w;
    tr[x].mn=tr[x].mx=tr[x].dat;
    if(tr[x].lc) chmin(tr[x].mn.first,tr[tr[x].lc].mn.first);
    if(tr[x].rc) chmin(tr[x].mn.first,tr[tr[x].rc].mn.first);
    if(tr[x].lc) chmax(tr[x].mx.first,tr[tr[x].lc].mx.first);
    if(tr[x].rc) chmax(tr[x].mx.first,tr[tr[x].rc].mx.first);
    if(tr[x].lc) chmin(tr[x].mn.second,tr[tr[x].lc].mn.second);
    if(tr[x].rc) chmin(tr[x].mn.second,tr[tr[x].rc].mn.second);
    if(tr[x].lc) chmax(tr[x].mx.second,tr[tr[x].lc].mx.second);
    if(tr[x].rc) chmax(tr[x].mx.second,tr[tr[x].rc].mx.second);

    return x;
    #undef x
}
int lim;
inline bool check(pair<int,int> a,pair<int,int> b){
    return 1ll*get<0>(a)*get<0>(b)+1ll*get<1>(a)*get<1>(b)<lim;
}
ll ans;
void query(int x,pair<int,int> k){
    int tot=(int)check({tr[x].mn.first,tr[x].mn.second},k)+
            (int)check({tr[x].mn.first,tr[x].mx.second},k)+
            (int)check({tr[x].mx.first,tr[x].mn.second},k)+
            (int)check({tr[x].mx.first,tr[x].mx.second},k);
    if(!tot) return ;
    if(tot==4){
        ans+=tr[x].w;
        return ;
    }
    if(tr[x].lc) query(tr[x].lc,k);
    if(tr[x].rc) query(tr[x].rc,k);
    if(check(tr[x].dat,k)) ans+=tr[x].w-(tr[tr[x].lc].w+tr[tr[x].rc].w);
    return ;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>get<0>(a[i])>>get<1>(a[i])>>get<2>(a[i]);

    root=build(1,n,1);
    while(m--){
        ans=0;
        int x,y;
        cin>>x>>y>>lim;
        query(root,{x,y});
        cout<<ans<<endl;
    }

    return 0;
}