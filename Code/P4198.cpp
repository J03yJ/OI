#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;
const double eps=1e-12;

struct Node{
    int l,r,ans;
    double dat;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat
#define ans(x) tr[x].ans

int F(int x,double k){
    if(l(x)==r(x)) return dat(x)>=k;
    if(k<=dat(x<<1)) return F(x<<1,k)+ans(x);
    else return F(x<<1|1,k);
}
void PushUp(int x){
    dat(x)=max(dat(x<<1),dat(x<<1|1));
    ans(x)=F(x<<1|1,dat(x<<1)+eps);
}
void Build(int x,int l,int r){
    l(x)=l,r(x)=r;
    if(l(x)==r(x)) return ;
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l(x),mid);
    Build(x<<1|1,mid+1,r(x));
    PushUp(x);
}
void Modify(int x,int pos,double k){
    if(l(x)==r(x)) return dat(x)=k,void();
    int mid=l(x)+r(x)>>1;
    if(pos<=mid) Modify(x<<1,pos,k);
    else Modify(x<<1|1,pos,k);
    PushUp(x);
}

int main(){
    int n,m;
    cin>>n>>m;

    Build(1,1,n);
    while(m--){
        int pos,k;
        cin>>pos>>k;
        Modify(1,pos,double(k)/pos);
        cout<<F(1,eps)<<endl;
    }

    return 0;
}