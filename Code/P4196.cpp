#include<bits/stdc++.h>

using namespace std;

const double eps=1e-8;
int Sgn(double x){
    if(x>eps) return 1;
    else if(x<eps) return -1;
    else return 0;
}
#define Eq(x,y) (!Sgn((x)-(y)))
#define Neq(x,y) (Sgn((x)-(y)))
#define Gt(x,y) (Sgn((x)-(y))>0)
#define Geq(x,y) (Sgn((x)-(y))>=0)
#define Lt(x,y) (Sgn((x)-(y))<0)
#define Leq(x,y) (Sgn((x)-(y))<=0)

struct Pt{
    double x,y;
    Pt(){}
    Pt(double _x,double _y){
        x=_x,y=_y;
    }    
    Pt operator -(Pt p){return Pt(x-p.x,y-p.y);}
    Pt operator +(Pt p){return Pt(x+p.x,y+p.y);}
    Pt operator *(double k){return Pt(x*k,y*k);}
};
double Cross(Pt p,Pt q){return p.x*q.y-p.y*q.x;}
double Dot(Pt p,Pt q){return p.x*q.x+p.y*q.y;}
double Len(Pt p){return sqrt(p.x*p.x+p.y*p.y);}
double Dist(Pt p,Pt q){return Len(p-q);}

Pt Itsect(Pt a1,Pt a2,Pt b1,Pt b2){
    Pt p=a2-a1,q=b2-b1,r=b1-a1;
    double k=Cross(q,r)/Cross(q,p);
    // cout<<" : "<<k<<' '<<a1.x<<' '<<a1.y<<' '<<a2.x<<' '<<a2.y<<' '<<b1.x<<' '<<b1.y<<' '<<b2.x<<' '<<b2.y<<endl;
    // cout<<"   "<<(a1+p*k).x<<' '<<(a1+p*k).y<<endl;
    return a1+p*k;
}
double Area(vector<Pt> &p){
    if(!p.size()) return 0;
    double ans=0;
    for(int i=1;i<p.size()-1;i++) ans+=Cross(p[i]-p[0],p[i+1]-p[0]);
    return ans/2;
}
void Cut(vector<Pt> &p,Pt a1,Pt a2){
    if(!p.size()) return ;
    vector<Pt> q;
    p.push_back(p.front());
    for(int i=0;i<p.size()-1;i++){
        if(Geq(Cross(a1-p[i],a2-p[i]),0)){
            q.push_back(p[i]);
            if(Lt(Cross(a1-p[i+1],a2-p[i+1]),0)){
                q.push_back(Itsect(p[i],p[i+1],a1,a2));
            }
        }else if(Geq(Cross(a1-p[i+1],a2-p[i+1]),0)){
            q.push_back(Itsect(p[i],p[i+1],a1,a2));
        }
    }
    p=q;
}

int main(){
    int m,n;
    cin>>m>>n;
    vector<Pt> p;
    for(int i=1;i<=n;i++){
        double x,y;
        cin>>x>>y;
        p.push_back(Pt(x,y));
    }

    for(int t=2;t<=m;t++){
        // for(Pt a:p) cout<<a.x<<' '<<a.y<<endl;
        cin>>n;
        vector<Pt> q;
        for(int i=1;i<=n;i++){
            double x,y;
            cin>>x>>y;
            q.push_back(Pt(x,y));
        }
        q.push_back(q.front());
        for(int i=0;i<q.size()-1;i++){
            Cut(p,q[i],q[i+1]);
            // for(Pt a:p) cout<<a.x<<' '<<a.y<<endl;
            // cout<<endl;
        }
    }
    cout<<fixed<<setprecision(3)<<Area(p)<<endl;
    
    return 0;        
}