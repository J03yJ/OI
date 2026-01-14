#include<bits/stdc++.h>

using namespace std;

#define int long long

void ExGCD(int a,int b,int &x,int &y){
    if(!b){
        x=1,y=0;
        return ;
    }
    ExGCD(b,a%b,x,y);
    int tmp=x;
    x=y;
    y=tmp-a/b*y;
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        int a,b,c,g,x,y;
        cin>>a>>b>>c;
        g=__gcd(a,b);
        if(c%g){
            cout<<-1<<endl;
            continue ;
        }
        a/=g,b/=g,c/=g;
        ExGCD(a,b,x,y);
        x*=c,y*=c;
        // cout<<x<<' '<<y<<" : "<<endl;
        int xmin=(x%b+b-1)%b+1,ymin=(y%a+a-1)%a+1;
        int xmax=(c-b*ymin)/a,ymax=(c-a*xmin)/b;
        if(xmax>0) cout<<(xmax-xmin)/b+1<<' '<<xmin<<' '<<ymin<<' '<<xmax<<' '<<ymax<<endl;
        else cout<<xmin<<' '<<ymin<<endl;
    }

    return 0;
}