#include<bits/stdc++.h>

using namespace std;

#define ssiz(x) (signed)x.size()
#define allc(x) x.begin(),x.end()

int main(){
    int T;
    cin>>T;
    while(T--){
        int n,m;
        cin>>n>>m;
        vector<pair<int,int>> a;
        for(int i=0,x,y;i<n;i++){
            cin>>x>>y;
            if(x<y) continue ;
            x--,y--;
            a.push_back({x,y});
        }
        m--;
        
        long long ans=0,sum=0;
        sort(allc(a),[](auto x,auto y){return x.first>y.first;});
        vector<long long> suc(ssiz(a),0);
        for(int i=ssiz(a)-1;~i;i--){
            if(i==ssiz(a)-1) suc[i]=max(0,a[i].first-a[i].second);
            else suc[i]=suc[i+1]+max(0,a[i].first-a[i].second);
        }
        priority_queue<int> q;
        for(int i=0;i<ssiz(a);i++){
            // cout<<a[i].first<<' '<<a[i].second<<" : "<<sum<<' '<<suc[i]<<' '<<ssiz(q)<<endl;
            if(i>=m) ans=max(ans,suc[i]-sum);
            q.push(a[i].second),sum+=a[i].second;
            if(i>=m) sum-=q.top(),q.pop();
        }

        cout<<ans<<endl;
    }

    return 0;
}