#include<bits/stdc++.h>
using namespace std;

const int N=1e6+9;

int a[N],blk[N];

struct Qs{
    int l,r,id;
    bool operator <(Qs x){
        if(blk[l]!=blk[x.l]) return blk[l]<blk[x.l];
        else return (r>x.r)^(blk[l]%2);
    }
}q[N];

int cnt[N],ans[N];

int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    int m;
    cin>>m;
    for(int i=1;i<=m;i++) cin>>q[i].l>>q[i].r,q[i].id=i;
    
    int B=sqrt(n);
    for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
    sort(q+1,q+m+1);
    
    for(int i=1,l=1,r=0,res=0;i<=m;i++){
        while(r<q[i].r) res+=!cnt[a[++r]]++;
        while(l>q[i].l) res+=!cnt[a[--l]]++;
        while(r>q[i].r) res-=!--cnt[a[r--]];
        while(l<q[i].l) res-=!--cnt[a[l++]];
        ans[q[i].id]=res;
    }

    for(int i=1;i<=m;i++) cout<<ans[i]<<endl;
    
    return 0;
}