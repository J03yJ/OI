#include<bits/stdc++.h>
using namespace std;

const int N=2e5+9;

int a[N];
int blk[N],L[N],R[N];

unordered_map<int,int> mp;

struct Q{
    int l,r,id;
    bool operator <(Q x){
        if(blk[l]!=blk[x.l]) return blk[l]<blk[x.l];
        return r<x.r;
    }
}q[N];

int ans[N];
int Lm[N],Rm[N],Ltmp[N],Rtmp[N];

int Naiiv(int l,int r){
    int ans=0;
    for(int i=l;i<=r;i++){
        if(!Lm[a[i]]) Lm[a[i]]=i;
        else ans=max(ans,i-Lm[a[i]]);
    }
    for(int i=l;i<=r;i++) Lm[a[i]]=0;
    return ans;
}

signed main(){
    int n,m;
    cin>>n;
    for(int i=1,cnt=0;i<=n;i++){
        int x;
        cin>>x;
        if(!mp[x]) mp[x]=++cnt;
        a[i]=mp[x];
    }
    cin>>m;
    for(int i=1;i<=m;i++) cin>>q[i].l>>q[i].r,q[i].id=i;

    int B=sqrt(n);
    for(int i=1;i<=B;i++) L[i]=R[i-1]+1,R[i]=R[i-1]+B;R[B]=n;
    for(int i=1,j=1;i<=n;i++){
        if(i>R[j]) j++;
        blk[i]=j;
    }
    sort(q+1,q+m+1);

    for(int i=1,j=1;i<=B;i++){
        int l=R[i]+1,r=R[i];
        for(int res=0,undo=0;j<=m&&blk[q[j].l]==i;j++){
            if(q[j].r<=R[i]) ans[q[j].id]=Naiiv(q[j].l,q[j].r);
            else{
                while(r<q[j].r){
                    r++;
                    if(!Lm[a[r]]) Lm[a[r]]=r;
                    Rm[a[r]]=r;
                    res=max(res,r-Lm[a[r]]);
                }
                undo=res;
                while(l>q[j].l){
                    l--;
                    Ltmp[a[l]]=l;
                    if(!Rtmp[a[l]]) Rtmp[a[l]]=l;
                    res=max(res,max(Rm[a[l]],Rtmp[a[l]])-Ltmp[a[l]]);
                }
                ans[q[j].id]=res;
                res=undo;
                while(l<R[i]+1) Rtmp[a[l]]=Ltmp[a[l]]=0,l++;
            }
        }
        for(int k=L[i];k<=r;k++) Rm[a[k]]=Lm[a[k]]=0; 
    }

    for(int i=1;i<=m;i++) cout<<ans[i]<<endl;
    
    return 0;
}