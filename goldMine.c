// C++ program to solve Gold Mine problem 
#include <time.h>
#include <stdio.h>
#include <stdlib.h> 
#define max(a,b) (((a)>(b))?(a):(b))
#include "timer.h"

// Returns maximum amount of gold that can be collected 
// when journey started from first column and moves 
// allowed are right, right-up and right-down 

//cols = m, rows = n

int getMaxGold(int* gold, int n, int m) 
{ 
    // Create a table for storing intermediate results 
    // and initialize all cells to 0. The first row of 
    // goldMineTable gives the maximum gold that the miner 
    // can collect when starts that row 
    
    //change to calloc in optimized version !! 
    int* goldTable = (int *)malloc(n * m * sizeof(int));
    
    
    //initialize values to 0 (unnecessary with calloc!)
    for(int row = 0; row < n; row++){
        for (int col = 0; col < m; col++){
            goldTable[row*m + col] = 0;
        }
    }
  
    for (int col=n-1; col>=0; col--) 
    { 
        for (int row=0; row<m; row++) 
        { 
            // Gold collected on going to the cell on the right(->) 
            int right = (col==n-1)? 0: goldTable[row*m + col+1]; 
  
            // Gold collected on going to the cell to right up (/) 
            int right_up = (row==0 || col==n-1)? 0: 
                            goldTable[(row-1)*m + col+1]; 
  
            // Gold collected on going to the cell to right down (\) 
            int right_down = (row==m-1 || col==n-1)? 0: 
                             goldTable[(row+1)*m + col+1]; 
  
            // Max gold collected from taking either of the 
            // above 3 paths 
            goldTable[row *m + col] = gold[row*m + col] + 
                              max(right, max(right_up, right_down)); 
                                                      
        } 
    } 
  
    // The max amount of gold collected will be the max 
    // value in first column of all rows 
    int res = goldTable[0]; 
    for (int i=1; i<m; i++) 
        res = max(res, goldTable[i*m]); 
    return res; 
} 
  
// Driver Code 
int main(int argc, char* argv[]) 
{ 
    // Time
    double time1;
    
    long n;
    long m;
    
    //parsing commandline arguments
    if(argc < 3){
        printf("usage: ./goldMine n m");
        printf("n and m are dimensions of goldmine matrix. Will be randomly populated with numbers in range [0, 9].");
        return -1;
    }
    else{
        n = atoi(argv[1]);
        m = atoi(argv[2]);
    }
    
    //initializing gold matrix:
    int* gold = (int *)malloc(n * m * sizeof(int));
    
    srand(time(NULL));
    
    //populating "gold" with random ints in range [0, 9]:
    for(int row = 0; row < n; row++){
        for (int col = 0; col < m; col++){
            gold[row*m + col] = rand() % 10;
        }
    }
//     gold[0] = 1;
//     gold[1] = 3;
//     gold[2] = 1;
//     gold[3] = 5;
//     gold[4] = 2;
//     gold[5] = 2;
//     gold[6] = 4;
//     gold[7] = 1;
//     gold[8] = 5;
//     gold[9] = 0;
//     gold[10] = 2;
//     gold[11] = 3;
//     gold[12] = 0;
//     gold[13] = 6;
//     gold[14] = 1;
//     gold[15] = 2;
    
    
    initialize_timer ();
    start_timer();
    printf("%d\n", getMaxGold(gold, n, m)); 
    stop_timer();
    time1 = elapsed_time ();
    
    printf("Time taken xd %lf\n" , time1);
    return 0; 
} 
