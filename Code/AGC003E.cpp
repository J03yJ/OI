#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e5+9;

int a[N],b[N],t[N],n,m,q;

void Solve(int x,int y){
    if(!x) return ;
    int pos=upper_bound(b+1,b+m+1,x)-b-1;
    if(!pos) a[1]+=y,a[x+1]-=y;
    else t[pos]+=(x/b[pos])*y,Solve(x%b[pos],y);
}

signed main(){
    cin>>n>>q;

    if(!q){
        for(int i=1;i<=n;i++) cout<<1<<endl;
        return 0;
    }
    
    b[++m]=n;
    while(q--){
        int x;
        cin>>x;
        while(x<=b[m]) m--;
        b[++m]=x;
    }

    t[m]=1;
    for(int i=m;i>=2;i--) t[i-1]+=(b[i]/b[i-1])*t[i],Solve(b[i]%b[i-1],t[i]);
    a[1]+=t[1];a[b[1]+1]-=t[1];

    for(int i=1;i<=n;i++) a[i]+=a[i-1],cout<<a[i]<<endl;

    return 0;
}