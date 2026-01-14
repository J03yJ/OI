#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	mt19937 rng(4649);
	multiset<int> s;
	int m=2e5,q=2e5;
	cout<<m<<' '<<q<<endl;
	for(int i=1,n=0;i<=q;i++){
		int op=rng()%3+1;
		if(op==2) op=1;
		if(op==1){
			cout<<op<<' '<<rng()%m+1<<' '<<rng()%m+1<<endl;
			s.insert(++n);
		}else if(op==2){
			int x=*next(s.begin(),rng()%s.size());
			s.erase(x);
			cout<<op<<' '<<x<<endl;
		}else if(op==3){
			int l0=rng()%m+1;
			int l1=rng()%m+1;
			int r0=rng()%m+1;
			int r1=rng()%m+1;
			if(l0>l1) swap(l0,l1);
			if(r0>r1) swap(r0,r1);
			cout<<op<<' '<<l0<<' '<<l1<<' '<<r0<<' '<<r1<<endl;
		}
	}

	return 0;
}