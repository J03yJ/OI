#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=5e5+9;
const int M=1e3+9;
const int B=1e3;
template<class T1,class T2> inline void ChMin(T1 &x,T2 y){if(y<x) x=y;}

int a[N],pos[N],cnt[N],pre[N],suf[N],n,len,q;
ll f[M][M][2],g[M][M][2];

signed main(){
    cin>>n>>len;
    for(int i=1;i<=n;i++) cin>>a[i],pos[i]=a[i];
    cin>>q;

    sort(pos+1,pos+n+1);
    int tot=unique(pos+1,pos+n+1)-pos-1;
    if(tot>B){
        while(q--) cout<<"No"<<endl;
        return 0;
    }

    for(int i=1;i<=n;i++) cnt[lower_bound(pos+1,pos+tot+1,a[i])-pos]++;
    for(int i=1;i<=tot;i++) pre[i]=pre[i-1]+cnt[i-1];
    for(int i=tot;i>=1;i--) suf[i]=suf[i+1]+cnt[i+1];

    memset(f,0x3f,sizeof f);
    memset(g,0x3f,sizeof g);
    f[1][tot][0]=g[1][tot][1]=0;
    for(int len=tot;len>=1;len--){
        for(int i=1;i<=tot-len+1;i++){
            int j=i+len-1;
            ChMin(f[i][j][0],f[i-1][j][0]+1ll*(pre[i]+suf[j]+1)*(pos[i]-pos[i-1]));
            ChMin(f[i][j][1],f[i][j+1][1]+1ll*(pre[i]+suf[j]+1)*(pos[j+1]-pos[j]));
            ChMin(f[i][j][0],f[i][j][1]+1ll*(pre[i]+suf[j]+1)*(pos[j]-pos[i]));
            ChMin(f[i][j][1],f[i][j][0]+1ll*(pre[i]+suf[j]+1)*(pos[j]-pos[i]));
            ChMin(g[i][j][0],g[i-1][j][0]+1ll*(pre[i]+suf[j]+1)*(pos[i]-pos[i-1]));
            ChMin(g[i][j][1],g[i][j+1][1]+1ll*(pre[i]+suf[j]+1)*(pos[j+1]-pos[j]));
            ChMin(g[i][j][0],g[i][j][1]+1ll*(pre[i]+suf[j]+1)*(pos[j]-pos[i]));
            ChMin(g[i][j][1],g[i][j][0]+1ll*(pre[i]+suf[j]+1)*(pos[j]-pos[i]));
        }
    }

    while(q--){
        int s,t,lim;
        cin>>s>>t>>lim;
        lim-=n;
        
        int p1=upper_bound(pos+1,pos+tot+1,t)-pos-1;
        int p2=lower_bound(pos+1,pos+tot+1,t)-pos;
        ll res=1e18;
        if(1<=p1&&p1<=tot) ChMin(res,abs(s-pos[1])+f[p1][p1][0]+1ll*abs(t-pos[p1])*(n+1));
        if(1<=p2&&p2<=tot) ChMin(res,abs(s-pos[1])+f[p2][p2][0]+1ll*abs(t-pos[p2])*(n+1));
        if(1<=p1&&p1<=tot) ChMin(res,abs(s-pos[tot])+g[p1][p1][0]+1ll*abs(t-pos[p1])*(n+1));
        if(1<=p2&&p2<=tot) ChMin(res,abs(s-pos[tot])+g[p2][p2][0]+1ll*abs(t-pos[p2])*(n+1));
        
        if(res>lim) cout<<"No"<<endl;
        else cout<<"Yes"<<endl;
    }

    return 0;
}