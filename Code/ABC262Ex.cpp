#include<bits/stdc++.h>

using namespace std;

#define int long long
#define Allc(x) (x).begin(),(x).end()
const int N=2e5+9;
const int mod=998244353;

int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}

int ql[N],qr[N],qk[N],val[N],f[N],q,cnt;
vector<int> c[N],pos[N],qry[N];
int Solve(int x){
    int n=pos[x].size();
    for(int i=0;i<n;i++) qry[i].clear();
    for(int i:c[x]){
        int l=lower_bound(Allc(pos[x]),ql[i])-pos[x].begin();
        int r=upper_bound(Allc(pos[x]),qr[i])-pos[x].begin()-1;
        if(l>r) continue ;
        qry[r].push_back(l);
    }
    
    for(int i=0;i<n;i++) f[i]=0;
    f[0]=1;

    int sum=1,tag=1,itag=1,cur=0;
    int w=val[x],invw=QPow(w,mod-2);
    for(int i=1;i<n;i++){
        int mx=-1;
        for(int j:qry[i]) mx=max(mx,j);
        tag=tag*w%mod;
        itag=itag*invw%mod;
        f[i]=sum*itag%mod;
        sum=(sum*w%mod+f[i]*tag%mod)%mod;
        while(cur<mx) sum=(sum+mod-f[cur++]*tag%mod)%mod;
    }
    return sum;
}

int lim[N],fa[N],n,m;
int Find(int x){
    if(fa[x]==x) return x;
    else return fa[x]=Find(fa[x]);
}

signed main(){
    cin>>n>>m>>q;
    for(int i=1;i<=q;i++) cin>>ql[i]>>qr[i]>>qk[i];

    val[++cnt]=m+1;
    for(int i=1;i<=q;i++) val[++cnt]=qk[i];
    sort(val+1,val+cnt+1);
    cnt=unique(val+1,val+cnt+1)-val-1;
    for(int i=1;i<=q;i++) qk[i]=lower_bound(val+1,val+cnt+1,qk[i])-val;
    for(int i=1;i<=q;i++) c[qk[i]].push_back(i);
    
    iota(fa+1,fa+n+2,1);
    for(int i=1;i<=n;i++) lim[i]=cnt;
    for(int i=1;i<=cnt;i++){
        for(int j:c[i]){
            if(Find(ql[j])>qr[j]){
                cout<<0<<endl;
                return 0;
            }
        }
        for(int j:c[i]){
            for(int k=Find(ql[j]);k<=qr[j];k=Find(k+1)){
                lim[k]=i;
                fa[k]=Find(k+1);
            }
        }
    }
    for(int i=1;i<=cnt;i++) pos[i].push_back(0);
    for(int i=1;i<=n;i++) pos[lim[i]].push_back(i);

    int ans=1;
    for(int i=1;i<=cnt;i++){
        if(val[i]!=m+1) ans=ans*Solve(i)%mod;
        else ans=ans*QPow(m+1,pos[i].size()-1)%mod;
    }
    cout<<ans<<endl;

    return 0;
}