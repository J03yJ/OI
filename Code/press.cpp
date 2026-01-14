#include<bits/stdc++.h>

using namespace std;

// ifstream fin("press.in");
// ofstream fout("press.out");
// #define cin fin
// #define cout fout

const int N=5e5+9;

int t[N],b[N];
pair<int,int> p[N];
bool cmp(pair<int,int> a,pair<int,int> b){
    if(a.first!=b.first) return a.first<b.first;
    else return a.second>b.second;
}

int main(){
    int V,n;
    cin>>V>>n;
    for(int i=1;i<=n;i++) cin>>t[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    
    for(int i=1;i<=n;i++) p[i].second=-t[i]+b[i],p[i].first=t[i]+b[i];
    sort(p+1,p+n+1,cmp);

    int ans=0;
    set<int> s;
    for(int i=1;i<=n;i++){
        // cout<<p[i].first<<' '<<p[i].second<<endl;
        auto it=s.lower_bound(p[i].second);
        if(it!=s.end()) s.erase(it);
        s.insert(p[i].second);
        ans=max(ans,(int)s.size());
    }

    cout<<ans<<endl;

    return 0;
}