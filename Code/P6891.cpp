#include<bits/stdc++.h>

using namespace std;

const int N=1e6+9;
const int inf=1e9+9;

int a[N],b[N];
pair<int,int> dp[N][2];
pair<int,int> merge(pair<int,int> a,pair<int,int> b){
    return make_pair(min(a.first,b.first),max(a.second,b.second));
}

int main(){
    int n;
    cin>>n;
    n<<=1;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    
    for(int i=1;i<=n;i++) dp[i][0]=dp[i][1]={inf,-inf};
    dp[1][0]={1,1};dp[1][1]={0,0};
    for(int i=2;i<=n;i++){
        if(a[i-1]<=a[i]) dp[i][0]=merge(dp[i][0],dp[i-1][0]);
        if(b[i-1]<=a[i]) dp[i][0]=merge(dp[i][0],dp[i-1][1]);
        if(a[i-1]<=b[i]) dp[i][1]=merge(dp[i][1],dp[i-1][0]);
        if(b[i-1]<=b[i]) dp[i][1]=merge(dp[i][1],dp[i-1][1]);
        dp[i][0].first++;
        dp[i][0].second++;
    }
    // for(int i=1;i<=n;i++) cout<<dp[i][0].first<<' '<<dp[i][0].second<<' '<<dp[i][1].first<<' '<<dp[i][1].second<<endl;

    if(dp[n][0].first<=n/2&&n/2<=dp[n][0].second){
        vector<int> ans(1,0);
        int cnt=n/2;
        for(int i=n;i;i--){
            if(ans.back()==0){
                cnt--;
                if(a[i-1]<=a[i]&&dp[i-1][0].first<=cnt&&cnt<=dp[i-1][0].second) ans.push_back(0);
                else ans.push_back(1);
            }else{
                if(a[i-1]<=b[i]&&dp[i-1][0].first<=cnt&&cnt<=dp[i-1][0].second) ans.push_back(0);
                else ans.push_back(1);
            }
        }
        ans.pop_back();
        reverse(ans.begin(),ans.end());
        for(int x:ans){
            if(!x) cout<<'A';
            else cout<<'B';
        }
        cout<<endl;
    }else if(dp[n][1].first<=n/2&&n/2<=dp[n][1].second){
        vector<int> ans(1,1);
        int cnt=n/2;
        for(int i=n;i;i--){
            // cout<<i<<' '<<ans.back()<<' '<<cnt<<endl;
            if(ans.back()==0){
                cnt--;
                // cout<<dp[i-1][0].first<<' '<<dp[i-1][0].second<<' '<<dp[i-1][1].first<<' '<<dp[i-1][1].second<<endl;
                // cout<<" : "<<cnt<<' '<<a[i-1]<<' '<<a[i]<<endl;
                // cout<<" : "<<(a[i-1]<=a[i])<<(dp[i-1][0].first<=cnt)<<(cnt<=dp[i-1][0].second)<<endl;
                if(a[i-1]<=a[i]&&dp[i-1][0].first<=cnt&&cnt<=dp[i-1][0].second) ans.push_back(0);
                else ans.push_back(1);
            }else{
                if(a[i-1]<=b[i]&&dp[i-1][0].first<=cnt&&cnt<=dp[i-1][0].second) ans.push_back(0);
                else ans.push_back(1);
            }
        }
        ans.pop_back();
        reverse(ans.begin(),ans.end());
        for(int x:ans){
            if(!x) cout<<'A';
            else cout<<'B';
        }
        cout<<endl;
    }else cout<<-1<<endl;

    return 0;
}