#include<bits/stdc++.h>

using namespace std;

const int N=1e2+9;

int f[N][N][N][N],s[N][N][N][N],n,k,mod;
inline void AddAs(int &x,int y){x+=y;if(x>=mod) x-=mod;}
inline void SubAs(int &x,int y){x-=y;if(x<0) x+=mod;}
inline int F(int i,int j,int al,int ar,int bl,int br){
    if(al>ar||bl>br||j<0) return 0;
    int sum=s[i][j][ar][br];
    SubAs(sum,s[i][j][ar][bl-1]);
    SubAs(sum,s[i][j][al-1][br]);
    AddAs(sum,s[i][j][al-1][bl-1]);
    return sum;
}

int main(){
    cin>>n>>k>>mod;

    f[1][0][1][1]=s[1][0][1][1]=1;
    for(int i=2;i<=n;i++){
        for(int j=0;j<i;j++){
            for(int a=1;a<=i;a++){
                for(int b=1;b<=i;b++){
                    AddAs(f[i][j][a][b],F(i-1,j-1,1,a-1,1,b-1));
                    AddAs(f[i][j][a][b],F(i-1,j-1,a,i-1,b,i-1));
                    AddAs(f[i][j][a][b],F(i-1,j,1,a-1,b,i-1));
                    AddAs(f[i][j][a][b],F(i-1,j,a,i-1,1,b-1));
                }
            }
            for(int a=1;a<=i;a++){
                for(int b=1;b<=i;b++){
                    s[i][j][a][b]=f[i][j][a][b];
                    AddAs(s[i][j][a][b],s[i][j][a-1][b]);
                    AddAs(s[i][j][a][b],s[i][j][a][b-1]);
                    SubAs(s[i][j][a][b],s[i][j][a-1][b-1]);
                }
            }
        }
    }

    int ans=0;
    for(int a=1;a<=n;a++){
        for(int b=1;b<=n;b++){
            AddAs(ans,f[n][k][a][b]);
        }
    }
    cout<<ans<<endl;

    return 0;
}