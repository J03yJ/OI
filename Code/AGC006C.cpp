#include<bits/stdc++.h>

using namespace std;

const int N=5e2+9;

vector<string> opt;
int nxt[N];

void EraseSpecialChar(string &s){
    while(s.size()&&(s[0]=='{'||s[0]=='}'||s[0]==' ')){
        s.erase(0,1);
    }
    while(s.size()&&(s.back()==' '||s.back()==',')) s.pop_back();
}
bool IsInt(string s){
    for(int i=0;i<s.size();i++) if(s[i]>'9'||s[i]<'0') return 0;
    else return 1;
}

struct Arr{
    int st,ed;
    vector<int> v;
    Arr(){}
    Arr(int s,int t){
        st=s;ed=t;
        v=vector<int>(t-s+1,0);
    }
    int& operator [](int pos){
        return v[pos-st];
    }
};
map<string,Arr> amp;
map<string,bool> avis;
map<string,int> imp;
map<string,bool> ivis;

int CalcVal(string s){
    EraseSpecialChar(s);
    if(!s.size()) return 0;

    vector<int> stk;
    for(int i=0;i<s.size();i++){
        if(s[i]=='[') stk.push_back(i);
        else if(s[i]==']') stk.pop_back();
        if(stk.size()) continue ;
        if(s[i]=='+') return CalcVal(s.substr(0,i))+CalcVal(s.substr(i+1));
        if(s[i]=='-') return CalcVal(s.substr(0,i))-CalcVal(s.substr(i+1));
    }

    if(IsInt(s)) return atoi(s.c_str());
    else if(ivis[s]) return imp[s];
    else{
        int posl=s.find("[");
        int posr=s.find("]");
        string arr=s.substr(0,posl);
        string cur=s.substr(posl+1,posr-posl-1);
        return amp[arr][CalcVal(cur)];
    }
}
int* FindAdd(string s){
    EraseSpecialChar(s);
    if(ivis[s]) return &imp[s];
    else{
        int posl=s.find("[");
        int posr=s.find("]");
        string arr=s.substr(0,posl);
        string cur=s.substr(posl+1,posr-posl-1);
        return &amp[arr][CalcVal(cur)];
    }
}

int main(){
    string tmp;
    while(getline(cin,tmp)){
        if(!tmp.size()||tmp[0]<' ') continue ;
        if(tmp[0]=='#') continue ;
        opt.push_back(tmp);
    }

    vector<int> stk;
    for(int i=0;i<opt.size();i++){
        if(opt[i][0]=='{') stk.push_back(i);
        else if(opt[i][0]=='}') nxt[stk.back()]=i,stk.pop_back();
        nxt[i]=i;
    }
    for(int i=0;i<opt.size();i++){
        EraseSpecialChar(opt[i]);
        // cout<<opt[i]<<endl;
    }

    for(int cur=0;cur<opt.size();){
        if(opt[cur]=="vars"){
            for(int i=cur+1;i<nxt[cur];i++){
                string tmp=opt[i];
                int pos=tmp.find(":");
                string id=tmp.substr(0,pos);
                tmp=tmp.substr(pos+1);
                if(tmp=="int"){
                    ivis[id]=true;
                }else{
                    avis[id]=true;
                    int pos1=tmp.find(",");
                    int pos2=tmp.find("..");
                    string l=tmp.substr(pos1+1,pos2-pos1-1);
                    string r=tmp.substr(pos2+2);
                    r.pop_back();
                    EraseSpecialChar(l);
                    EraseSpecialChar(r);
                    amp[id]=Arr(stoi(l),stoi(r));
                }
            }
            cur=nxt[cur]+1;
        }else if(opt[cur].find(":set")!=string::npos){
            string tmp=opt[cur];
            tmp.erase(0,4);
            int pos=tmp.find(",");
            string add=tmp.substr(0,pos);
            string val=tmp.substr(pos+1);
            *FindAdd(add)=CalcVal(val);
            cur++;
        }else if(opt[cur].find(":yosoro")!=string::npos){
            string tmp=opt[cur];
            tmp.erase(0,7);
            cout<<CalcVal(tmp)<<' ';
            cur++;
        }else cur++;
    }

    cout<<endl;

    return 0;
}