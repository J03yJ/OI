#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=(1<<18)+9;

int a[N];

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int n;
	cin>>n;

	int k=__lg(n);
	for(int i=0;i<=k;i++){
		for(int j=(1<<i);j<(1<<i+1);j++){
			a[j]=(a[j^(1<<i)]^a[(1<<i)-1])|(1<<i);
		}
	}

	if(n==(1<<k+1)-1){
		cout<<"YES"<<endl;
		for(int i=1;i<=n;i++) cout<<a[i]<<' ';cout<<endl;
	}else if(k<3) cout<<"NO"<<endl;
	else if(n<=((1<<k)|(1<<k-1))) cout<<"NO"<<endl;
	else{
		cout<<"YES"<<endl;
		for(int i=1;i<(1<<k)-1;i++) cout<<a[i]<<' ';
		for(int i=1;i<(1<<k-1);i++){
			if((a[i]|(1<<k)|(1<<k-1))<=n) cout<<(a[i]|(1<<k)|(1<<k-1))<<' ';
			cout<<(a[i]|(1<<k))<<' ';
		}
		cout<<(1<<k)<<' ';
		cout<<((1<<k)|(1<<k-1))<<' ';
		cout<<(1<<k-1)<<' ';
		cout<<endl;
	}

	return 0;
}