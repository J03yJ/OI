#include<bits/stdc++.h>

using namespace std;

int main(){
    int a,b;
    cin>>a>>b;

    if(a<=0&&0<=b) cout<<"Zero"<<endl;
    else{
        if(a>0&&b>0) cout<<"Positive"<<endl;
        else{
            if((a-b)%2) cout<<"Positive"<<endl;
            else cout<<"Negative"<<endl;
        }
    }

    return 0;
}