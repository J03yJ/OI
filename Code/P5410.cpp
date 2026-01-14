#include<bits/stdc++.h>

using namespace std;

#define Allc(x) x.begin(),x.end()

vector<int> z;
void Z(string s){
    z=vector<int>(s.size(),0);
    for(int i=1,j=0;i<s.size();i++){
        if(j+z[j]>i) z[i]=min(z[i-j],z[j]+j-i);
        while(s[z[i]]==s[i+z[i]]) z[i]++;
        if(i+z[i]>j+z[j]) j=i;
    }
    z[0]=s.size();
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string a,b;
    cin>>a>>b;

    Z(b+a);
    long long ans1=0,ans2=0;
    for(int i=0;i<b.size();i++){
        ans1^=1ll*(min(z[i],int(b.size()-i))+1)*(i+1);
    }
    cout<<ans1<<endl;
    for(int i=0;i<a.size();i++){
        ans2^=1ll*(min(z[i+b.size()],int(b.size()))+1)*(i+1);
    }
    cout<<ans2<<endl;

    return 0;
}