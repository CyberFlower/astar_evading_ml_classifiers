#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
const int p=101;
struct node{
    int x,y,z; 
    node(){}
    node(int x, int y, int z){
        this->x=x;
        this->y=y;
        this->z=z;
    }
    bool operator<(const node &other)const{
        if(x==other.x){
            return ((y==other.y)?(z<other.z):(y<other.y));
        }
        return x<other.x;
    }
};
// hash function to represent current node
int hash(int x, int y, int z){
    int res=0;
    res+=x; res+=p*y; res+=p*p*z;
    return res;
}
// return -1 if current node classified as abnormal
// else return l0 distance
int l0_dist(int x, int y, int z){
    int res=x+y+z-150;
    return res;
}
class astar{
private:
    std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,std::greater<std::pair<int,int>>> pq;
    std::map<int,int> dist, visit;
    int start_x, start_y, start_z;
public:
    astar(int start_x, int start_y, int start_z){
        this->start_x=start_x;
        this->start_y=start_y;
        this->start_z=start_z;
    }
    void get_weight(){
        int stt=hash(start_x,start_y,start_z);
        dist[stt]=0;
        pq.push({0,stt});
        while(!pq.empty()){
            auto top=pq.top(); pq.pop();
            int x=top.second%p,y=(top.second/p)%p,z=top.second/(p*p);            
            if(top.first!=dist[top.second]) continue;
            visit[top.second]=top.first;
            if(l0_dist(x,y,z)<0) break;
            for(int i=0;i<6;i++){
                int dx=(i<2?(i%2==0?1:-1):0);
                int dy=((i>=2 && i<4)?(i%2==0?1:-1):0);
                int dz=((i>=4 && i<6)?(i%2==0?1:-1):0);                                
                int nx=x+dx, ny=y+dy, nz=z+dz;
                if(nx<0 || nx>100) continue;
                if(ny<0 || ny>100) continue;
                if(nz<0 || nz>100) continue;
                //if(l0_dist(nx,ny,nz)<0) continue;
                if(!dist.count(hash(nx,ny,nz)) || dist[hash(nx,ny,nz)]>top.first+1){
                    dist[hash(nx,ny,nz)]=top.first+1;
                    pq.push({dist[hash(nx,ny,nz)],hash(nx,ny,nz)});
                }
            }
        }
        int min_dist=1e9;
        int ex=-1,ey=-1,ez=-1;
        for(auto xx:visit){
            int x=xx.first%p, y=(xx.first/p)%p, z=(xx.first/(p*p));
            if(l0_dist(x,y,z)<0 && xx.second<min_dist){
                ex=x, ey=y, ez=z;
                min_dist=xx.second;
            }
        }
        min_dist=(min_dist==1e9?0:min_dist);
        std::cout<<"[-] minimal distance to become abnormal: "<<min_dist<<std::endl;
        std::cout<<"[-] abnormal features: "<<ex<<" "<<ey<<" "<<ez<<std::endl;
        return;
    }
};
int main(void){
    std::cout<<"input three features: ";
    int start_x, start_y, start_z; std::cin>>start_x>>start_y>>start_z;
    astar ast=astar(start_x, start_y, start_z);
    ast.get_weight();
    return 0;
}