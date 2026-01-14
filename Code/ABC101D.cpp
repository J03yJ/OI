#include<bits/stdc++.h>

using namespace std;

#define int long long

double F(int x){
    double ans=0,tmp=x;
    while(x) ans+=x%10,x/=10;
    return tmp/ans;
}

signed main(){
    int n,b=1,cur=0;
    cin>>n;
    while(n--){
        while(F(cur+10*b)<F(cur+b)) b*=10;
        cout<<(cur+=b)<<endl;
    }

    return 0;
}