#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;
using pii=pair<int,int>;

int x[N],y[N],n;

void Insert(vector<pii> &ans,vector<int> &r,int op){
    op^=1;
    if(ans.size()){
        if(!op) ans.push_back({ans.back().first,y[r.front()]});
        else ans.push_back({x[r.front()],ans.back().second});
    }
    ans.insert(ans.end(),{x[r.front()],y[r.front()]});
    ans.insert(prev(ans.end()),{x[r.front()],y[r.front()]});
    vector<int> tmpr(r.size());
    for(int i=0;i<r.size();i++) tmpr[i]=i&1^op?y[r[i]]:x[r[i]];
    for(int i=1;i<r.size();i++){
        if(i&1^op) ans.push_back({tmpr[i-1],tmpr[i]});
        else ans.push_back({tmpr[i],tmpr[i-1]});
    }
    if(r.size()>1) ans.push_back({x[r.back()],y[r.back()]});
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>x[i]>>y[i];

    set<pii> sx,sy;
    for(int i=1;i<=n;i++) sx.insert({x[i],i}),sy.insert({y[i],i});

    vector<int> p,q,r;
    while(sx.size()){
        int op=r.size()&3,i;
        if(op==0){
            i=sx.begin()->second;
            if(r.size()&&x[r.back()]<x[i]){
                p.push_back(r.back()),r.pop_back();
                continue ;
            }
        }else if(op==3){
            i=sy.begin()->second;
            if(r.size()&&y[r.back()]<y[i]){
                q.push_back(r.back()),r.pop_back();
                continue ;
            }
        }else if(op==2){
            i=sx.rbegin()->second;
            if(r.size()&&x[r.back()]>x[i]){
                p.push_back(r.back()),r.pop_back();
                continue ;
            }
        }else{
            i=sy.rbegin()->second;
            if(r.size()&&y[r.back()]>y[i]){
                q.push_back(r.back()),r.pop_back();
                continue ;
            }
        }
        r.push_back(i);
        sx.erase({x[i],i});
        sy.erase({y[i],i});
    }
    
    // for(int i:p) cout<<x[i]<<":"<<y[i]<<" ";cout<<endl;
    // for(int i:q) cout<<x[i]<<":"<<y[i]<<" ";cout<<endl;
    // for(int i:r) cout<<x[i]<<":"<<y[i]<<" ";cout<<endl;

    vector<pii> ans({{0,0}});
    Insert(ans,r,ans.size()&1);
    sort(p.begin(),p.end(),[](int i,int j){return x[i]<x[j];});
    Insert(ans,p,ans.size()&1);
    sort(q.begin(),q.end(),[](int i,int j){return x[i]<x[j];});
    Insert(ans,q,ans.size()&1);

    cout<<ans.size()<<endl;
    for(pii t:ans) cout<<t.first<<' '<<t.second<<endl;

    return 0;
}