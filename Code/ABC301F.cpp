#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=3e5+9;
const int p=998244353;

int dp[N][3];
bool vis[26];
inline bool Cap(char c){
    return c>='A'&&c<='Z';
}

int fac[N],inv[N];
int qpow(int x,int y){
    int m=1;
    while(y){
        if(y&1) m=m*x%p;
        x=x*x%p;
        y>>=1;
    }
    return m;
}
void init(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%p;
    inv[n]=qpow(fac[n],p-2);
    for(int i=n-1;~i;i--) inv[i]=inv[i+1]*(i+1)%p;
    // for(int i=1;i<=n;i++) cout<<fac[i]<<" "<<inv[i]<<' '<<inv[i]*fac[i]%p<<endl;
}
int C(int n,int m){
    return fac[n]*inv[m]%p*inv[n-m]%p;
}

signed main(){
    string s;cin>>s;
    int n=s.size();
    s=" "+s;

    init(max(26ll,n));
    dp[0][0]=dp[0][1]=dp[0][2]=1;
    for(int i=1,ccnt=26,qcnt=0,err=0;i<=n;i++){
        if(s[i]=='?'){
            qcnt++;
            if(err) dp[i][0]=0;
            else{
                for(int j=0;j<=min(ccnt,qcnt);j++){
                    dp[i][0]=(dp[i][0]+C(ccnt,j)*C(qcnt,j)%p*fac[j]%p*qpow(26,qcnt-j)%p)%p;
                }
            }
            dp[i][1]=(dp[i-1][1]*26%p+dp[i-1][0]*26%p)%p;
            dp[i][2]=(dp[i-1][1]*26%p+dp[i-1][2]*26%p)%p;
        }else if(Cap(s[i])){
            if(!vis[s[i]-'A']) ccnt--,vis[s[i]-'A']=1;
            else err=1;
            if(err) dp[i][0]=0;
            else{
                for(int j=0;j<=min(ccnt,qcnt);j++){
                    dp[i][0]=(dp[i][0]+C(ccnt,j)*C(qcnt,j)%p*fac[j]%p*qpow(26,qcnt-j)%p)%p;
                }
            }
            dp[i][1]=dp[i-1][1];
            dp[i][2]=dp[i-1][1];
        }else{
            if(err) dp[i][0]=0;
            else{
                for(int j=0;j<=min(ccnt,qcnt);j++){
                    dp[i][0]=(dp[i][0]+C(ccnt,j)*C(qcnt,j)%p*fac[j]%p*qpow(26,qcnt-j)%p)%p;
                }
            }
            dp[i][1]=dp[i-1][0];
            dp[i][2]=dp[i-1][2];
        }
        // cout<<dp[i][0]<<' '<<dp[i][1]<<' '<<dp[i][2]<<' '<<err<<endl;
    }
    cout<<dp[n][2]<<endl;

    return 0;
}