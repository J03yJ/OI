#include<bits/stdc++.h>

using namespace std;

int cnt=0;
mt19937 rng(4649);
inline bool Test(){
	cerr<<"Test Case #"<<++cnt<<endl;

	int n=2e5,v=1e6;
	ofstream inf("sol.in");
	inf<<n<<endl;
	for(int i=2;i<=n;i++) inf<<((i>>1)-1<<1|1)<<' ';inf<<endl;
	for(int i=1;i<=n;i++) inf<<rng()%v+1<<' ';inf<<endl;

	return !system("sol < sol.in > sol.out");
}

signed main(){
	while(Test()) ;

	return 0;
}