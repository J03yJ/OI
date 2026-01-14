#include<bits/stdc++.h>

using namespace std;

const int N=5e2+9;
const int M=N*N;

int a[M],n;
vector<pair<int,int>> pos[M];

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int t;
        cin>>t;
        for(int j=1;j<i;j++) pos[1].push_back({t-1,i});
        pos[t].push_back({t,i});
        for(int j=i+1;j<=n;j++) pos[t+1].push_back({n*n,i});
    }

    vector<int> ans;
    priority_queue<pair<int,int>> q;
    for(int i=1;i<=n*n;i++){
        for(pair<int,int> x:pos[i]) q.push({-x.first,x.second});
        if(!q.size()){
            cout<<"No"<<endl;
            return 0;
        }
        pair<int,int> x=q.top();
        q.pop();
        if(-x.first<i){
            cout<<"No"<<endl;
            return 0;
        }
        else ans.push_back(x.second);
    }

    cout<<"Yes"<<endl;
    for(int x:ans) cout<<x<<' ';
    cout<<endl;

    return 0;
}