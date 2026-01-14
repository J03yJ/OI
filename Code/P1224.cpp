#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;
const int D=1e2+9;

int a[N][D],n,d,k;
int tmp2[D],tmp3[D][D];
int Dot(int p,int q){
    int sum=0;
    for(int i=1;i<=d;i++) sum=(sum+a[p][i]*a[q][i])%k;
    return sum;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>d>>k;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=d;j++) cin>>a[i][j],a[i][j]%=k;
        a[i][0]=i;
    }

    mt19937 rng(4649);
    int T=5;
    while(T--){
        shuffle(a+1,a+n+1,rng);
        if(k==2){
            for(int i=1;i<=n;i++){
                int sum=0;
                for(int j=1;j<=d;j++) sum=(sum+tmp2[j]*a[i][j])%k;
                if(sum!=(i-1)%k){
                    for(int j=1;j<i;j++){
                        if(!Dot(i,j)){
                            cout<<min(a[i][0],a[j][0])<<' '<<max(a[i][0],a[j][0])<<endl;
                            return 0;
                        }
                    }
                }
                for(int j=1;j<=d;j++) tmp2[j]=(tmp2[j]+a[i][j])%k;
            }
        }else if(k==3){
            for(int i=1;i<=n;i++){
                int sum=0;
                for(int j=1;j<=d;j++){
                    for(int k=1;k<=d;k++) sum=sum+a[i][j]*a[i][k]*tmp3[j][k];
                }
                sum%=k;
                if(sum!=(i-1)%k){
                    for(int j=1;j<i;j++){
                        if(!Dot(i,j)){
                            cout<<min(a[i][0],a[j][0])<<' '<<max(a[i][0],a[j][0])<<endl;
                            return 0;   
                        }
                    }
                }
                for(int j=1;j<=d;j++){
                    for(int k=1;k<=d;k++) tmp3[j][k]=tmp3[j][k]+a[i][j]*a[i][k];
                }
            }
        }
    }

    cout<<-1<<' '<<-1<<endl;

    return 0;
}