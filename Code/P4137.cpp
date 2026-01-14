#include<bits/stdc++.h>
using namespace std;

const int N=2e5+9;
struct node{
    int l,r,dat;
    int lc,rc;
}tr[N*40];
#define dat(x) tr[x].dat
#define l(x) tr[x].l
#define r(x) tr[x].r
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc

int cnt;
void pushup(int x){
    dat(x)=min(dat(lc(x)),dat(rc(x)));
}
void build(int &x,int l,int r){
    x=++cnt;
    l(x)=l;r(x)=r;
    if(l(x)==r(x)) return ;
    int mid=l(x)+r(x)>>1;
    build(lc(x),l,mid);
    build(rc(x),mid+1,r);
}
int modify(int x,int pos,int k){
    int y=++cnt;
    tr[y]=tr[x];
    if(l(x)==r(x)){
        dat(y)=k;
        return y;
    }
    int mid=l(x)+r(x)>>1;
    if(pos<=mid) lc(y)=modify(lc(x),pos,k);
    else rc(y)=modify(rc(x),pos,k);
    pushup(y);
    return y;
}
int query(int x,int k){
    if(l(x)==r(x)) return l(x);
    if(dat(lc(x))<k) return query(lc(x),k);
    else return query(rc(x),k);
}

int root[N],a[N];

int main(){
    int n,m,Max=0;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i],Max=max(Max,a[i]);
    build(root[0],0,Max+1);
    for(int i=1;i<=n;i++) root[i]=modify(root[i-1],a[i],i);
    while(m--){
        int l,r;
        cin>>l>>r;
        cout<<query(root[r],l)<<endl;
    }
}