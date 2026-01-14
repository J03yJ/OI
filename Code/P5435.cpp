#include<bits/stdc++.h>

using namespace std;

const int V=1e6+9;
const int sqV=1e3+9;
const int mod=998244353;

int pri[V],ntp[V],lpf[V],cnt;
int fac[V][3],g[sqV][sqV];
int GCD(int x,int y);
void InitP(int lim){
    for(int i=2;i<=lim;i++){
        if(!ntp[i]) pri[++cnt]=i,lpf[i]=i;
        for(int j=1;j<=cnt&&pri[j]*i<=lim;j++){
            ntp[i*pri[j]]=1;
            lpf[i*pri[j]]=pri[j];
            if(i%pri[j]==0) break ;
        }
    }
    for(int k:{0,1,2}) fac[1][k]=1;
    for(int i=2;i<=lim;i++){
        for(int k:{0,1,2}) fac[i][k]=fac[i/lpf[i]][k];
        fac[i][0]*=lpf[i];
        sort(fac[i],fac[i]+3);
    }
    int m=sqrt(lim);
    for(int i=1;i<=m;i++) g[i][0]=g[0][i]=i;
    for(int i=1;i<=m;i++) g[i][1]=g[1][i]=1;
    for(int i=2;i<=m;i++){
        for(int j=i;j<=m;j++){
            g[i][j]=g[j][i]=g[i][j-i];
        }
    }
}
int GCD(int x,int y){
    int res=1;
    for(int k:{0,1,2}){
        if(ntp[fac[x][k]]){
            int tmp=g[fac[x][k]][y%fac[x][k]];
            res*=tmp;
            y/=tmp;
        }else{
            int tmp=y%fac[x][k]?1:fac[x][k];
            res*=tmp;
            y/=tmp;
        }
    }
    return res;
}

int a[V],b[V],n;

signed main(){
    InitP(1e6);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];

    for(int i=1;i<=n;i++){
        long long ans=0;
        for(long long j=1,w=i;j<=n;j++,w=w*i%mod){
            ans=(ans+w*GCD(a[i],b[j])%mod)%mod;
        }
        cout<<ans<<endl;
    }

    return 0;
}