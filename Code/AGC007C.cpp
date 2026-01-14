#include<bits/stdc++.h>

using namespace std;

#define double long double
double F(int n,double d,double x){
    if(!n) return 0;
    else return F(n-1,d+(2*d+5*x)/(2*n),x+2*x/n)+d+x*(2*n-1)/2;
}

int main(){
    int n,d,x;
    cin>>n>>d>>x;
    cout<<fixed<<setprecision(9)<<F(n,d,x)<<endl;
    return 0;
}