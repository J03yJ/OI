#include<bits/stdc++.h>

using namespace std;

const int N=5e4+9;
const int lgV=30;

struct Basis{
    int a[lgV+1];
    Basis(){memset(a,0,sizeof a);}
    Basis(int k){memset(a,0,sizeof a);Insert(k);}
    void Insert(int k){
        for(int i=lgV;~i&&k;i--){
            if(k>>i&1){
                if(!a[i]){
                    a[i]=k;
                    break ;
                }else k^=a[i];
            }
        }
    }
    int Query(int res){
        for(int i=lgV;~i;i--){
            if(res<(res^a[i])) res^=a[i];
        }
        return res;
    }
    int operator [](int pos){return a[pos];}
    Basis operator +(Basis b){
        Basis res=*this;
        for(int i=lgV;~i;i--) res.Insert(b[i]);
        return res;
    }
};
struct Node{
    int l,r;
    Basis dat;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat

void PushUp(int x){
    dat(x)=dat(x<<1)+dat(x<<1|1);
}
void Build(int x,int l,int r){
    l(x)=l,r(x)=r;
    if(l(x)==r(x)) return ;
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l,mid);
    Build(x<<1|1,mid+1,r);
    PushUp(x);
}
void Modify(int x,int pos,int k){
    if(l(x)==r(x)) return dat(x)=Basis(k),void();
    int mid=l(x)+r(x)>>1;
    if(pos<=mid) Modify(x<<1,pos,k);
    else Modify(x<<1|1,pos,k);
    PushUp(x);
}
Basis Query(int x,int l,int r){
    if(l<=l(x)&&r(x)<=r) return dat(x);
    int mid=l(x)+r(x)>>1;
    if(l<=mid&&r>mid) return Query(x<<1,l,r)+Query(x<<1|1,l,r);
    else if(l<=mid) return Query(x<<1,l,r);
    else return Query(x<<1|1,l,r);
}

int a[N],d[N],n,m;

int t[N];
void Add(int x,int k){
    while(x<=n){
        t[x]^=k;
        x+=x&-x;
    }
}
int Ask(int x){
    int ans=0;
    while(x){
        ans^=t[x];
        x&=x-1;
    }
    return ans;
}


int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];

    Build(1,1,n+1);
    for(int i=1;i<=n;i++) Modify(1,i,d[i]=a[i]^a[i-1]),Add(i,d[i]);
    while(m--){
        int op,l,r,v;
        cin>>op>>l>>r>>v;
        if(op==1){
            Modify(1,l,d[l]^=v),Modify(1,r+1,d[r+1]^=v);
            Add(l,v),Add(r+1,v);
        }else{
            auto b=l==r?Basis():Query(1,l+1,r);
            b.Insert(Ask(l));
            cout<<b.Query(v)<<endl;
        }
    }

    return 0;
}