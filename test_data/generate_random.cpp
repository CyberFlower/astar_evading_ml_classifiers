/*
Full random case generator with one path
13 features, 3 results (3**13=1594323)
start node =(3,3,...,3)
command:
$ g++ -std=c++17 -o gen_rand.exe generate_random.cpp
$ ./gen_rand.exe > generate_random.in
*/
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv){
    clock_t start_time=clock();
    mt19937 generator(start_time);
    int n=13, m=2000000;
    vector<vector<int>> nodes;
    vector<int> start(n,3);
    vector<int> weight(n,0);
    int sum=0;
    for(int i=0;i<n;i++){
        weight[i]=(generator()%100+1);
        sum+=3*weight[i];
    }
    nodes.push_back(start);
    for(int i=1;i<m;i++){
        vector<int> node(n,0);
        for(int j=0;j<n;j++){
            node[j]=(generator()%3)+1;
        }
        nodes.push_back(node);
    }
    cout<<n<<" "<<m<<endl;
    for(int i=0;i<n;i++) cout<<start[i]<<" ";
    cout<<endl;
    for(int i=0;i<n;i++) cout<<weight[i]<<" ";
    cout<<endl;
    cout<<sum/2<<endl;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++) cout<<nodes[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}