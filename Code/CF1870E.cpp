#include<bits/stdc++.h>

using namespace std;

const int N=5e3+9;
const int V=1<<13;

int a[N];
vector<pair<int,int>> f[N];
bitset<V> dp[N],buc;

int main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        
        for(int i=1;i<=n;i++){
            if(!a[i]){
                f[i].push_back({i,1});
                continue ;
            }
            buc.reset();
            for(int j=i,mex=0;j<=n;j++){
                buc[a[j]]=1;
                while(buc[mex]) mex++;
                if(a[i]>a[j]&&mex>a[i]){
                    f[j].push_back({i,mex});
                    break ;
                }
            }
            buc.reset();
            for(int j=i,mex=0;j>=1;j--){
                buc[a[j]]=1;
                buc[a[j]]=1;
                while(buc[mex]) mex++;
                if(a[i]>a[j]&&mex>a[i]){
                    f[i].push_back({j,mex});
                    break ;
                }
            }
        }

        dp[0][0]=1;
        for(int i=1;i<=n;i++){
            dp[i]=dp[i-1];
            for(pair<int,int> p:f[i]){
                for(int j=0;j<V;j++){
                    dp[i][j]=dp[i][j]|dp[p.first-1][j^p.second];
                }
            }
            f[i].clear();
        }

        for(int i=V-1;~i;i--){
            if(dp[n][i]){
                cout<<i<<endl;
                break ;
            }
        }
    }

    return 0;
}