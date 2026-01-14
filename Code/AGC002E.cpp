#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;

int a[N],n;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    sort(a+1,a+n+1,[](int x,int y){return x>y;});
    int dlt=0,i=1;
    while(a[i+1]>dlt+1) dlt++,i++;
    
    int x=1,y=a[i]-dlt;
    while(a[i+x]==dlt+1) x++;

    if(x%2&&y%2) cout<<"Second"<<endl;
    else cout<<"First"<<endl;

    return 0;
}