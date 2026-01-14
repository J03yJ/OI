#include<bits/stdc++.h>

using namespace std;

#define int long long

const int N=9;
const int N2=3e1+9;

int a[N][N],s[N][N][N][N],f[N][N][N][N][N2],n,m,t;
vector<int> val;

inline void ChMin(int &x,int y){if(y<x) x=y;}
int Work(int lim){
    memset(f,0x3f,sizeof f);
    for(int il=1;il<=n;il++){
        for(int jl=1;jl<=m;jl++){
            for(int i=1;i<=n-il+1;i++){
                int p=i+il-1;
                for(int j=1;j<=m-jl+1;j++){
                    int q=j+jl-1;
                    if(s[i][j][p][q]>=lim) f[i][j][p][q][0]=s[i][j][p][q];
                    for(int sp=i;sp<p;sp++){
                        for(int x=1;x<=il*jl&&x<=t;x++){
                            for(int y=0;y<x;y++){
                                ChMin(f[i][j][p][q][x],max(f[i][j][sp][q][y],f[sp+1][j][p][q][x-y-1]));
                            }
                        }
                    }
                    for(int sp=j;sp<q;sp++){
                        for(int x=1;x<=il*jl&&x<=t;x++){
                            for(int y=0;y<x;y++){
                                ChMin(f[i][j][p][q][x],max(f[i][j][p][sp][y],f[i][sp+1][p][q][x-y-1]));
                            }
                        }
                    }
                }
            }
        }
    }
    return f[1][1][n][m][t];
}

signed main(){
    cin>>n>>m>>t;
    
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) cin>>a[i][j];
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int p=i;p<=n;p++){
                int sum=0;
                for(int q=j;q<=m;q++){
                    for(int k=i;k<=p;k++) sum+=a[k][q];
                    val.push_back(sum);
                    s[i][j][p][q]=sum;
                }
            }
        }
    }
    sort(val.begin(),val.end());
    val.erase(unique(val.begin(),val.end()),val.end());

    int ans=1e18;
    for(int x:val) ans=min(ans,Work(x)-x); 
    cout<<ans<<endl;

    return 0;
}