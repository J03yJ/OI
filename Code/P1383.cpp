#include<bits/stdc++.h>
#include<ext/rope>

using namespace std;

using __gnu_cxx::rope;

const int N=1e5+9;
rope<char> His[N];

int main(){
    int q,cnt=0;
    cin>>q;
    while(q--){
        char op;
        cin>>op;
        if(op=='T'){
            cnt++;
            char c;
            cin>>c;
            His[cnt]=His[cnt-1];
            His[cnt].push_back(c);
        }else if(op=='U'){
            cnt++;
            int k;
            cin>>k;
            His[cnt]=His[cnt-k-1];
        }else if(op=='Q'){
            int pos;
            cin>>pos;
            cout<<His[cnt][pos-1]<<endl;
        }
    }
}