#include<bits/stdc++.h>
#include<ext/rope>

using namespace std;
using namespace __gnu_cxx;

#define P(s) for(char x:s) cout<<x;cout<<endl

rope<char> s,rs;
int cur=0;

void Move(int k){cur=k;}
void Prev(){cur--;}
void Next(){cur++;}
char Get(){return s[cur];}

void Insert(string str){
    string rstr="";
    for(int i=str.size()-1;~i;i--) rstr+=str[i];

    rs.insert(s.size()-cur,rstr.c_str());
    s.insert(cur,str.c_str());
}
void Delete(int len){
    rs.erase(s.size()-cur-len,len);
    s.erase(cur,len);
}
rope<char> tmp,rtmp;
void Rotate(int len){
    tmp=s.substr(cur,len);rtmp=rs.substr(s.size()-len-cur,len);
    rs=rs.substr(0,s.size()-len-cur)+tmp+rs.substr(s.size()-cur,cur);
    s=s.substr(0,cur)+rtmp+s.substr(cur+len,s.size()-cur-len);
}

inline char read(){
	char ch=getchar();
	while((ch<32||ch>126)&&ch!='\n') ch=getchar();
	return ch;
}

int main(){
    int Q;
    cin>>Q;
    while(Q--){
        string op;
        cin>>op;
        if(op=="Insert"){
            int n;string str="";
            cin>>n;
            getchar();
            while(n--){
                char ch=read();
                str+=ch;
            }
            Insert(str);
        }else if(op=="Delete"){
            int k;cin>>k;
            Delete(k);
        }else if(op=="Rotate"){
            int k;
            cin>>k;
            Rotate(k);
        }else if(op=="Move"){
            int k;cin>>k;
            Move(k);
        }else if(op=="Prev") Prev();
        else if(op=="Next") Next();
        else if(op=="Get"){
            char c;
            c=Get();
            cout<<c;if(c!='\n') cout<<endl;
        }
    }
}