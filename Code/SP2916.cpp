#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e5+9;
const int inf=1e18;

struct Data{
    int lmx,rmx,mx,sum;
    Data(){}
    Data(int _l,int _r,int _m,int _s){
        lmx=_l,rmx=_r,mx=_m,sum=_s;
    }
    Data operator +(Data x){
        Data res=Data(lmx,x.rmx,max(mx,x.mx),sum+x.sum);
        res.mx=max(res.mx,rmx+x.lmx);
        res.lmx=max(res.lmx,sum+x.lmx);
        res.rmx=max(res.rmx,x.sum+rmx);
        return res;
    }
};
struct Node{
    int l,r;
    Data dat;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat

int a[N],n,q;
void Build(int x,int l,int r){
    l(x)=l,r(x)=r;
    if(l(x)==r(x)){
        dat(x)=Data(a[l(x)],a[l(x)],a[l(x)],a[l(x)]);
        return ;
    }
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l(x),mid);
    Build(x<<1|1,mid+1,r(x));
    dat(x)=dat(x<<1)+dat(x<<1|1);
}
Data Query(int x,int l,int r){
    if(l>r) return Data(-inf,-inf,-inf,0);
    // if(l>r) return Data(0,0,0,0);
    if(l<=l(x)&&r(x)<=r) return dat(x);
    int mid=l(x)+r(x)>>1;
    if(l<=mid&&r>mid) return Query(x<<1,l,r)+Query(x<<1|1,l,r);
    else if(l<=mid) return Query(x<<1,l,r);
    else return Query(x<<1|1,l,r);
}

int Ask(int l,int r,int L,int R){
    if(r<L) return Query(1,l,r).rmx+Query(1,r+1,L-1).sum+Query(1,L,R).lmx;
    else{
        int ans=Query(1,L,r).mx;
        ans=max(ans,Query(1,l,L-1).rmx+Query(1,L,R).lmx);
        ans=max(ans,Query(1,l,r).rmx+Query(1,r+1,R).lmx);
        return ans;
    }
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        Build(1,1,n);
        cin>>q;
        while(q--){
            int l,r,L,R;
            cin>>l>>r>>L>>R;
            cout<<Ask(l,r,L,R)<<endl;
        }
    }

    return 0;
}