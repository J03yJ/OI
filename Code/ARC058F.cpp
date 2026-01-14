#include<bits/stdc++.h>

using namespace std;

const int K=1e4+9;
const int N=2e3+9;
using pii=pair<int,int>;
#define mk make_pair

vector<int> ZAlgo(string s){
    int n=s.size();
    vector<int> z(n);
    z[0]=s.size();
    for(int i=1,l=0,r=0;i<n;i++){
        if(i<=r&&z[i-l]<r-i+1) z[i]=z[i-l];
        else{
            z[i]=max(r-i+1,0);
            while(i+z[i]<n&&s[i+z[i]]==s[z[i]]) z[i]++;
        }
        if(i+z[i]-1>r) l=i,r=i+z[i]-1;
    }
    return z;
}
string Solve(int n,int k,vector<string> &s){
    vector<vector<int>> h(n+1,vector<int>(k+1,0));
    h[n][k]=1;
    for(int i=n-1;i>=1;i--){
        int m=s[i+1].size();
        for(int j=k;j>=0;j--) h[i][j]=h[i+1][j];
        for(int j=k;j>=m;j--) h[i][j-m]|=h[i+1][j];
    }

    vector<vector<bool>> f(n+1,vector<bool>(k+1,0));
    vector<string> t(n+1);
    t[1]=s[1],f[1][0]=f[1][s[1].size()]=1;
    for(int i=2;i<=n;i++){
        int m=s[i].size();
        vector<int> z(ZAlgo(s[i]+t[i-1]));
        vector<pii> stk;
        for(int i=0;i<z.size();i++) z[i]=min(z[i],m);
        auto Comp=[&i,&z,&s,&t,&m](pii p,pii q){
            int res=0,rev=1;
            if(p.first<q.first) swap(p,q),rev=-1;
            int tx=p.first,ty=q.first,sx=p.second,sy=q.second;
            if(ty+m<z.size()&&ty+z[ty+m]<tx&&z[ty+m]<sy) res=t[i-1][ty+z[ty+m]]<s[i][z[ty+m]]?-1:1;
            else if(z[tx-ty]<sx&&tx-ty+z[tx-ty]<sy) res=s[i][z[tx-ty]]<s[i][tx-ty+z[tx-ty]]?-1:1;
            return res*rev;
        };
        for(int j=0;j<=k;j++){
            if(!h[i][j]) continue ;
            pii cur;
            if(j>=m&&f[i-1][j]&&f[i-1][j-m]) cur=Comp({j-m,m},{j,0})==-1?mk(j-m,m):mk(j,0);
            else if(j>=m&&f[i-1][j-m]) cur={j-m,m};
            else if(f[i-1][j]) cur={j,0};
            else continue ;
            while(stk.size()&&Comp(cur,stk.back())==-1){
                f[i][stk.back().first+stk.back().second]=0;
                stk.pop_back();
            }
            if(!stk.size()||!Comp(cur,stk.back())) stk.push_back(cur),f[i][j]=1;
            t[i]=t[i-1].substr(0,stk.back().first)+s[i].substr(0,stk.back().second);
        }
    }

    return t[n];
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    int n,k;
    cin>>n>>k;
    vector<string> s(n+1);
    for(int i=1;i<=n;i++) cin>>s[i];

    cout<<Solve(n,k,s)<<endl;

    return 0;
}