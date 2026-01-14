#include<bits/stdc++.h>

using namespace std;

const int N=3e1+9;

bitset<N*N> f[N][N];

int main(){
    int n,q;
    cin>>n>>q;
    
    f[0][0][0]=1;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            for(int x=0;x+i<=n;x++){
                for(int y=0;y+j<=n;y++){
                    if((x==1||y==1)&&x&&y) continue ;
                    f[i+x][j+y]|=f[i][j]<<(i*y+j*x);
                }
            }
        }
    }

    while(q--){
        int k;
        cin>>k;
        if(f[n][n][k]) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }

    return 0;
}