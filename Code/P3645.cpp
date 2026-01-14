#include<bits/stdc++.h>
using namespace std;

const int N=3e4+9;

vector<int> D[N];
bitset<N> Vis[N];
queue<tuple<int,int,int>> Q;
bool Asked[N];

void TryJump(int pos,int x,int step){
    if(Vis[pos][x]) return ;
    Vis[pos][x]=1;
    Q.emplace(pos,x,step);
}
void TryAsk(int pos,int step){
    if(Asked[pos]) return ;
    Asked[pos]=1;
    for(int x:D[pos]) TryJump(pos,x,step);
}

int main(){
    int n,m,S,T;
    cin>>n>>m;
    for(int i=0,B,P;i<m;i++){
        cin>>B>>P;
        if(i==0) S=B;
        if(i==1) T=B;
        D[B].push_back(P);
    }

    if(S==T){
        cout<<0<<endl;
        return 0;
    }

    TryAsk(S,0);
    while(Q.size()){
        int pos=get<0>(Q.front()),x=get<1>(Q.front()),step=get<2>(Q.front());
        Q.pop();

        // cout<<pos<<' '<<x<<' '<<step<<endl;

        if(pos-x==T||pos+x==T){
            cout<<step+1<<endl;
            return 0;
        }

        if(pos-x>-1) TryAsk(pos-x,step+1),TryJump(pos-x,x,step+1);
        if(pos+x<n) TryAsk(pos+x,step+1),TryJump(pos+x,x,step+1);
    }

    cout<<-1<<endl;

    return 0;
}