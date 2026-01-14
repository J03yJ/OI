#include<bits/stdc++.h>

using namespace std;

int main(){
    int x,y,z;
    cin>>x>>y>>z;
    vector<string> v;
    for(int i=1;i<=x;i++) v.push_back("a");
    for(int i=1;i<=y;i++) v.push_back("b");
    for(int i=1;i<=z;i++) v.push_back("c");
    while(v.size()>1){
        sort(v.begin(),v.end());
        string s=v.front()+v.back();
        v.pop_back();
        v.erase(v.begin());
        v.push_back(s);
    }
    cout<<v.back()<<endl;
    return 0;
}