#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

int a[N],vis[N],n,m;

int main(){
    cin>>n>>m;
    for(int i=1;i<=n+m;i++) cin>>a[i];

    int cnt1=0,cnt2=0,cnt=0;
    for(int i=1;i<=n+m;i++){
        if(vis[i]) continue ;
        cnt++;
        if(a[i]==i) continue ;
        int cur=i,mx=0;
        while(!vis[cur]){
            vis[cur]=1;
            mx=max(mx,cur);
            cur=a[cur];
        }
        if(mx<=n) cnt1++;
        if(i>n) cnt2++;
    }
    cout<<n+m-cnt+2*max(cnt1,cnt2)<<endl;

    return 0;
}