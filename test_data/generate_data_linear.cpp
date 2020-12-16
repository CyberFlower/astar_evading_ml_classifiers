#include <iostream>
#include <stdio.h>
#include <random>
#include <time.h>
#include <vector>

int main(void){
    clock_t start_time=clock();
    std::mt19937 generator(start_time);
    int features[8]={3,3,5,5,10,10,20,20};
    int size[8]={1000,100000,1000,100000,1000,100000,1000,100000};
    for(int test=0;test<8;test++){
        char filename[20];
        sprintf(filename,"%d.in",test+1);
        std::vector<int> start(features[test]);
        FILE *fp=fopen(filename,"w");    
        // n m 
        fprintf(fp,"%d %d\n",features[test],size[test]);   
        // start node features
        for(int j=0;j<features[test];j++) fprintf(fp,"%d ",generator()%100+1);
        fprintf(fp,"\n");
        // weights for decision boundary
        //for(int j=0;j<features[test];j++) fprintf(fp,"%d ",generator()%10+1);   
        //fprintf(fp,"\n");
        // graph nodes that attacker makes
        for(int j=0;j<size[test];j++){
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