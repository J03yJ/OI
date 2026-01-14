#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e5+9;
const int lgN=20;

int a[N],b[N],pre[N],n,m,ans;
int st[N][lgN],lg[N];
void InitST(){
    for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
    for(int i=1;i<=n;i++) st[i][0]=i;
    for(int k=1;k<=lg[n];k++){
        for(int i=1;i<=n-(1<<k)+1;i++){
            if(a[st[i][k-1]]<a[st[i+(1<<k-1)][k-1]]) st[i][k]=st[i][k-1];
            else st[i][k]=st[i+(1<<k-1)][k-1];
        }
    }
}
int GetMin(int l,int r){
    int k=lg[r-l+1];
    if(a[st[l][k]]<a[st[r-(1<<k)+1][k]]) return st[l][k];
    else return st[r-(1<<k)+1][k];
}
int Binary(int l,int r,int flag,auto F){
    while(l+1<r){
        int mid=l+r>>1;
        if(F(mid)^flag) l=mid;
        else r=mid;
    }
    return flag?r:l;
}
void F(int l,int r){
    if(l>r) return ;
    if(l==r){
        if(a[l]+b[l]<=m) ans++;
        return ;
    }
    int pos=GetMin(l,r);
    F(l,pos-1),F(pos+1,r);
    if(pos-l<=r-pos){
        for(int i=l;i<=pos;i++){
            int t=Binary(pos-1,r+1,0,[i,pos](int x){
                return pre[x]-pre[i-1]+a[pos]<=m;
            });
            ans+=t-pos+1;
            // cout<<l<<' '<<r<<" : "<<i<<' '<<t<<endl;
        }
    }else{
        for(int i=r;i>=pos;i--){
            int t=Binary(l-1,pos+1,1,[i,pos](int x){
                return pre[i]-pre[x-1]+a[pos]<=m;
            });
            ans+=pos-t+1;
            // cout<<l<<' '<<r<<" : "<<i<<' '<<t<<endl;
        }
    }
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];

    for(int i=1;i<=n;i++) pre[i]=pre[i-1]+b[i];
    InitST();
    F(1,n);
    vector<int> v;

    cout<<ans<<endl;

    return 0;
}