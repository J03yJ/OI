#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e5+9;

int a[N],f[N],n,m,t;

signed main(){
    cin>>n>>m>>t;
    for(int i=1;i<=n;i++) cin>>a[i];

    queue<int> q;
    q.push(0);
    for(int i=1,mn=1e18;i<=n;i++){
        while(q.size()&&2*(a[i]-a[q.front()+1])>t){
            mn=min(mn,f[q.front()]-2*a[q.front()+1]);
            q.pop();
        }
        f[i]=mn+2*a[i];
        if(q.size()) f[i]=min(f[i],f[q.front()]+t);
        q.push(i);
    }

    cout<<f[n]+m<<endl;

    return 0;
}