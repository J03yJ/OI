#include<bits/stdc++.h>

using namespace std;

const int N=1e3+9;

pair<int,int> pre[N][N];
int vis[N][N],v[N][N],h[N][N];

int main(){
    int n,m,k;
    cin>>n>>m>>k;
    
    if(k<n){
        cout<<"No"<<endl;
        return 0;
    }

    #define Vld(x,y) ((x)>=1&&(y)>=1&&(x)<=n&&(y)<=m&&!vis[(x)][(y)])
    int x=1,y=1,stp=1;
    vector<pair<int,int>> pth(1,{1,1});
    while(stp+n-x<k){
        vis[x][y]=1;
        if(y==1){
            if(Vld(x,y+1)) pth.push_back({x,y+1}),y++;
            else pth.push_back({x+1,y}),x++;
        }else if(y==m){
            if(Vld(x,y-1)) pth.push_back({x,y-1}),y--;
            else pth.push_back({x+1,y}),x++;
        }else{
            if(Vld(x,y+1)) pth.push_back({x,y+1}),y++;
            else pth.push_back({x,y-1}),y--;
        }
        stp++;
    }
    while(x<n) pth.push_back({++x,y});

    for(int i=1;i<pth.size();i++) pre[pth[i].first][pth[i].second]=pth[i-1];
    for(int i=1;i<=n;i++){
        for(int j=2;j<=m;j++){
            if(make_pair(i,j-1)!=pre[i][j]) h[i][j]=1;
        }
        for(int j=1;j<m;j++){
            if(make_pair(i,j+1)==pre[i][j]) h[i][j+1]=0;
        }
    }
    for(int j=1;j<=m;j++){
        for(int i=2;i<=n;i++){
            if(make_pair(i-1,j)!=pre[i][j]) v[i][j]=1;
        }
        for(int i=1;i<n;i++){
            if(make_pair(i+1,j)==pre[i][j]) v[i+1][j]=0;
        }
    }

    cout<<"Yes"<<endl;
    int s=pth.front().first,t=pth.back().second;
    for(int i=1;i<=m;i++) cout<<'+'<<(i==s?'S':'+');cout<<'+'<<endl;
    for(int i=1;i<n;i++){
        cout<<"+o";
        for(int j=2;j<=m;j++) cout<<(h[i][j]?'|':'.')<<'o';cout<<'+'<<endl;
        for(int j=1;j<=m;j++) cout<<'+'<<(v[i+1][j]?'-':'.');cout<<'+'<<endl;
    }
    cout<<"+o";
    for(int j=2;j<=m;j++) cout<<(h[n][j]?'|':'.')<<'o';cout<<'+'<<endl;
    for(int i=1;i<=m;i++) cout<<'+'<<(i==t?'G':'+');cout<<'+'<<endl;
    
    return 0;
}