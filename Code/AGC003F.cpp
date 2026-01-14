#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e3+9;
const int mod=1e9+7;

int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}

int a[N][N],n,m,k;
bool CheckV(){
    for(int i=1;i<=n;i++) if(a[i][1]&&a[i][m]) return 1;
    return 0;
}
bool CheckH(){
    for(int j=1;j<=m;j++) if(a[1][j]&&a[n][j]) return 1;
    return 0;
}
void Trs(){
    for(int i=1;i<=max(n,m);i++){
        for(int j=i;j<=max(n,m);j++){
            swap(a[i][j],a[j][i]);
        }
    }
    swap(n,m);
}
int BCount(){
    int sum=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) sum+=a[i][j];
    }
    return sum;
}
int ACount(){
    int sum=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<m;j++) sum+=a[i][j]&&a[i][j+1];
    }
    return sum;
}
int EACount(){
    int sum=0;
    for(int i=1;i<=n;i++) sum+=a[i][1]&&a[i][m];
    return sum;
}

struct M22{
    int a[2][2];
    M22(){memset(a,0,sizeof a);}
    M22(int w,int x,int y,int z){
        a[0][0]=w;
        a[0][1]=x;
        a[1][0]=y;
        a[1][1]=z;
    }
    M22 operator *(M22 x){
        M22 res;
        for(int i:{0,1}){
            for(int j:{0,1}){
                for(int k:{0,1}){
                    res.a[i][j]=(res.a[i][j]+a[i][k]*x.a[k][j]%mod)%mod;
                }
            }
        }
        return res;
    }
};
M22 QPow(M22 x,int y){
    M22 res=M22(1,0,0,1);
    while(y){
        if(y&1) res=res*x;
        x=x*x;
        y>>=1;
    }
    return res;
}

signed main(){
    cin>>n>>m>>k;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char c;
            cin>>c;
            if(c=='#') a[i][j]=1;
            else a[i][j]=0;
        }
    }

    bool fv=CheckV(),fh=CheckH();
    if(fv&&fh){
        cout<<1<<endl;
        return 0;
    }else if(!fv&&!fh){
        cout<<QPow(BCount(),k-1)<<endl;
        return 0;
    }else if(!fv&&fh) Trs();

    M22 ans=QPow(M22(BCount(),mod-ACount(),0,EACount()),k-1);
    cout<<(ans.a[0][0]+ans.a[0][1])%mod<<endl;

    return 0;
}