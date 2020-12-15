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
// return negative if current node classified as abnormal
int l0_dist(std::vector<int> &arr, int x, int y, int z){
    int res=arr[0]*x+arr[1]*y+arr[2]*z-150;
    return res;
}
class astar{
private:
    std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,std::greater<std::pair<int,int>>> pq;
    std::map<int,int> dist, visit;
    std::vector<int> start, weight;
public:
    astar(std::vector<int> &start, std::vector<int> &weight){
        this->start=start;
        this->weight=weight;
    }
    void get_weight(){
        int stt=hash(start[0],start[1],start[2]);
        dist[stt]=0;
        pq.push({0,stt});
        while(!pq.empty()){
            auto top=pq.top(); pq.pop();
            int x=top.second%p,y=(top.second/p)%p,z=top.second/(p*p);            
            if(top.first!=dist[top.second]) continue;
            visit[top.second]=top.first;
            if(l0_dist(weight,x,y,z)<0) break;
            for(int i=0;i<6;i++){
                int dx=(i<2?(i%2==0?1:-1):0);
                int dy=((i>=2 && i<4)?(i%2==0?1:-1):0);
                int dz=((i>=4 && i<6)?(i%2==0?1:-1):0);                                
                int nx=x+dx, ny=y+dy, nz=z+dz;
                if(nx<0 || nx>100) continue;
                if(ny<0 || ny>100) continue;
                if(nz<0 || nz>100) continue;
                //if(l0_dist(nx,ny,nz)<0) continue;
                //int w=(i<2?weight[0]:(i<4?weight[1]:weight[2]));
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
            if(l0_dist(weight,x,y,z)<0 && xx.second<min_dist){
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
    std::vector<int> start(3), weight(3);
    std::cout<<"input three features: ";
    std::cin>>start[0]>>start[1]>>start[2];
    std::cout<<"input three weights to change a features: ";
    std::cin>>weight[0]>>weight[1]>>weight[2];
    astar ast=astar(start,weight);
    ast.get_weight();
    return 0;
}