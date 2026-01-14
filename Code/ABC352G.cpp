#include<bits/stdc++.h>

using namespace std;

#define int long long
using Poly=vector<int>;
const int N=3e5+9;
const int mod=998244353;
int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
}

int a[N],n;

int main(){

    return 0;
}