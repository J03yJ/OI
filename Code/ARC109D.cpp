#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    int T;
    cin>>T;
    while(T--){
        ll x=0,y=0;
        for(int i=1;i<=3;i++){
            int xx,yy;
            cin>>xx>>yy;
            x+=xx,y+=yy;
        }
        x--,y--;
        x-=x>=0?x/3:(x-2)/3;
        y-=y>=0?y/3:(y-2)/3;
        cout<<max(abs(x),abs(y))+(x==y&&x!=0&&x!=1)<<endl;
    }

    return 0;
}