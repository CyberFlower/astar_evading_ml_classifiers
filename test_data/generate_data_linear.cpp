#include <iostream>
#include <stdio.h>
#include <random>
#include <time.h>
#include <vector>
#include <algorithm>

int main(void){
    clock_t start_time=clock();
    std::mt19937 generator(start_time);
    int features[8]={3,3,5,5,10,10,20,20};
    int size[8]={1000,100000,1000,100000,1000,100000,1000,100000};
    for(int test=0;test<8;test++){
        char filename[20];
        sprintf(filename,"%d.in",test+1);
        FILE *fp=fopen(filename,"w");    
        int n=features[test], m=size[test];
        fprintf(fp,"%d %d\n",n,m);   
        // start node features
        std::vector<int> start(n), weight(n);
        for(int j=0;j<features[test];j++) fprintf(fp,"%d ",start[j]=generator()%100+1);
        fprintf(fp,"\n");
        // weights for decision boundary
        for(int j=0;j<features[test];j++) fprintf(fp,"%d ",weight[j]=generator()%10+1);   
        //fprintf(fp,"\n");
        // graph nodes that attacker makes
        for(int j=0;j<std::min(features[test],start[0]);j++){
            fprintf(fp,"%d ",j);
            for(int k=1;k<features[test];k++) fprintf(fp,"%d ",start[k]);
            fprintf(fp,"\n");
        }
        for(int j=0;j<size[test]-start[0];j++){
            for(int k=0;k<features[test];k++) fprintf(fp,"%d ",generator()%100+1);
            fprintf(fp,"\n");
        }     
        for(int j=0;j<size[test];j++){
            for(int k=0;k<features[test];k++) fprintf(fp,"%d ",generator()%100+1);
            fprintf(fp,"\n");
        }             
        fclose(fp);
    }
    return 0;
}