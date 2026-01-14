#include<bits/stdc++.h>

using namespace std;

int n,m,x=1,y=0,fl;
vector<pair<int,int>> ans;
void F(){
    y++;
    if(x<=n&&y<=m&&x>=1&&y>=1) ans.push_back({x,y});
}
void B(){
    x++,y-=2;
    if(x<=n&&y<=m&&x>=1&&y>=1) ans.push_back({x,y});
}

int main(){
    cin>>n>>m;
    if(n>m) swap(n,m),fl=1;
    while(x!=n){
        F(),F(),F(),B();
        if(x==n) break ;
        F(),F(),B();
        if(x==n) break ;
        F();
    }
    while(y<m) F();
    cout<<ans.size()<<endl;
    if(!fl) for(auto p:ans) cout<<p.first<<' '<<p.second<<endl;
    else for(auto p:ans) cout<<p.second<<' '<<p.first<<endl;

    return 0;
}