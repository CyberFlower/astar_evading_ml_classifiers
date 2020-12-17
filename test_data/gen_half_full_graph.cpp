/*
This generator generates half-full graph case.
It includes at least one paths(src->dest). 
Src nodes initiallized as (10,10,10,10,10)
a_1*x_1+a_2*x_2+...+a_n*x_n=b
limit of b is initiallized as range*sum(a_i)/2
Duplicate nodes can exist like real world.
command : 
$ g++ -std=c++17 -o half_full.exe gen_half_full_graph.cpp
$ ./half_full.exe 50 > hal_full_graph2.in
*/ 

#include <bits/stdc++.h>
using namespace std;
const int features=5;
const int range=10;
//const int possibility=90;
int main(int argc, char **argv){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    // random seed
    clock_t start_time=clock();
    std::mt19937 generator(start_time);

    int possibility=atoi(argv[1]);
    vector<vector<int>> nodes;
    vector<int> node(features,0);
    vector<int> src(features,10),path(features,10);
    vector<int> weight(features,1);
    int sum=0;
    for(int i=0;i<features;i++){
        weight[i]=(generator()%10+1);
        sum+=weight[i]*range;
    }
    for(node[0]=1;node[0]<=range;node[0]++){
        for(node[1]=1;node[1]<=range;node[1]++){
            for(node[2]=1;node[2]<=range;node[2]++){
                for(node[3]=1;node[3]<=range;node[3]++){
                    for(node[4]=1;node[4]<=range;node[4]++){
                        int flg=generator()%100;
                        if(flg<=possibility) nodes.push_back(node);
                    }                                                        
                }                                    
            }                    
        }        
    }
    nodes.push_back(path);
    int xx=sum;
    sum/=2;
    while(xx>=sum){
        int idx=(generator()%features);
        while(path[idx]==0) idx=(generator()%features);
        path[idx]--; xx-=weight[idx];
        nodes.push_back(path);
    }
    cout<<features<<" "<<nodes.size()<<endl;
    for(int xx:src) cout<<xx<<" ";
    cout<<endl;
    for(int xx:weight) cout<<xx<<" ";
    cout<<endl;
    cout<<sum<<endl;
    for(auto xx:nodes){
        for(int yy:xx) cout<<yy<<" ";
        cout<<endl;
    }
    return 0;
}