#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <time.h>
/*struct node{
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
};*/
class astar{
private:
    const int prime=101;
    const int mod=1e9+9;
    std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,std::greater<std::pair<int,int>>> pq;
    std::map<int,int> dist, visit;
    std::vector<int> start, weight;
    std::map<int,int> reverse_hash;
    std::set<std::vector<int>> nodes;
    std::map<int,std::set<int>> graph;
    int n,m;
    int lmt;    // constant for decision boundary
    // return negative if current node classified as abnormal
    int l0_dist(std::vector<int> &node){
        int res=0;
        for(int i=0;i<n;i++) res+=weight[i]*node[i];
        res-=lmt;
        return res;
    }     
    // hash function to represent current node
    int hash(std::vector<int> &crt_node){
        long long res=0;
        for(long long feature:crt_node){
            res=(res*prime+feature)%mod;
        }
        reverse_hash[res]=l0_dist(crt_node);
        return (int)res;
    }   
public:
    astar(std::vector<int> &start, std::vector<int> &weight, int n, int m){
        this->start=start;
        this->weight=weight;
        this->n=n;
        this->m=m;
        lmt=0;
        for(int wei:weight) lmt+=wei;
        lmt/=2;
    }
    void push_edge(std::vector<int> &example_node){
        nodes.insert(example_node);
    }
    void generate_graph(){
        for(auto node:nodes){
            int crt_hash=hash(node);
            for(int i=0;i<n;i++){
                node[i]++;
                if(nodes.count(node)){
                    graph[crt_hash].insert(hash(node));
                }
                node[i]--;
            }
            for(int i=0;i<n;i++){
                node[i]--;
                if(nodes.count(node)){
                    graph[crt_hash].insert(hash(node));
                }
                node[i]++;
            }            
        }
    }
    void get_weight(){
        int stt=hash(start);
        dist[stt]=0;
        pq.push({0,stt});
        int cnt=10;
        while(!pq.empty() && cnt>0){
            auto top=pq.top(); pq.pop();
            //int x=top.second%p,y=(top.second/p)%p,z=top.second/(p*p);            
            if(top.first!=dist[top.second]) continue;
            visit[top.second]=top.first;
            if(reverse_hash[top.second]<0){
                cnt--;
                continue;
            }
            for(int xx:graph[top.second]){
                if(dist[xx]>top.first+1){
                    dist[xx]=top.first+1;
                    pq.push({dist[xx],xx});
                }
            }
            /*for(int i=0;i<6;i++){
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
            }*/
        }
        int min_dist=1e9;
        //std::vector<int> result(n,-1);
        for(auto xx:visit){
            if(min_dist>xx.second){
                min_dist=xx.second;
            }
        }
        min_dist=(min_dist==1e9?0:min_dist);
        std::cout<<"[-] minimal distance to become abnormal: "<<min_dist<<std::endl;
        if(min_dist){
            std::cout<<"[-] Another candidates...: "<<std::endl;            
            for(auto xx:visit){
                if(reverse_hash[xx.first]<0){
                    std::cout<<xx.second<<std::endl;
                }
            }            
        }
        //std::cout<<"[-] abnormal features: "<<ex<<" "<<ey<<" "<<ez<<std::endl;
        return;
    }
};
int main(void){
    std::ios_base::sync_with_stdio(false); std::cin.tie(NULL);
    clock_t start_time=clock();
    int n,m; std::cin>>n>>m;
    m*=2;
    std::vector<int> start(n), weight(n);
    //std::cout<<"input "<< n <<" features: ";
    for(int i=0;i<n;i++) std::cin>>start[i];
    //std::cout<<"input "<< n <<" weights to change a features: ";
    for(int i=0;i<n;i++) std::cin>>weight[i];
    astar ast=astar(start,weight,n,m);
    for(int i=0;i<m;i++){
        std::vector<int> tmp(n);
        for(int j=0;j<n;j++) std::cin>>tmp[j];
        ast.push_edge(tmp);
    }
    ast.generate_graph();
    ast.get_weight();
    std::cout<<"[+] Running time: "<<(clock()-start_time)/CLOCKS_PER_SEC<<"s"<<std::endl;
    return 0;
}