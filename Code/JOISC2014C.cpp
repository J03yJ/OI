#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N=1e5+9;

int a[N];
int L[N],R[N],blk[N];

struct Q{
    int l,r,id;
    bool operator <(Q x){
        if(blk[l]!=blk[x.l]) return blk[l]<blk[x.l];
        else return r<x.r;
    }
}q[N];

int ans[N];
unordered_map<int,int> c;
int Naiiv(int l,int r){
    int ans=0;
    for(int i=l;i<=r;i++){
        c[a[i]]++;
        ans=max(ans,a[i]*c[a[i]]);
    }
    for(int i=l;i<=r;i++) c[a[i]]--;
    return ans;
}

signed main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=m;i++) cin>>q[i].l>>q[i].r,q[i].id=i;
    
    int B=sqrt(n);
    for(int i=1;i<=n;i++) L[i]=R[i-1]+1,R[i]=R[i-1]+B;R[B]=n;
    for(int i=1,j=1;i<=n;i++){
        if(i>R[j]) j++;
        blk[i]=j;
    }
    sort(q+1,q+m+1);

    for(int i=1,j=1;i<=B;i++){
        int r=R[i],l=R[i]+1;
        for(int res=0,undo=0;blk[q[j].l]==i&&j<=m;j++){
            if(q[j].r<=R[i]) ans[q[j].id]=Naiiv(q[j].l,q[j].r);
            else{
                while(r<q[j].r){
                    c[a[++r]]++;
                    res=max(res,c[a[r]]*a[r]);
                }
                undo=res;
                while(l>q[j].l){
                    c[a[--l]]++;
                    res=max(res,c[a[l]]*a[l]);
                }
                ans[q[j].id]=res;
                res=undo;
                while(l<=R[i]) c[a[l++]]--;
            }
        }
        for(int k=R[i]+1;k<=r;k++) c[a[k]]--;
    }

    for(int i=1;i<=m;i++) cout<<ans[i]<<endl;

    return 0;
}