// C++ program to solve Gold Mine problem 
#include <time.h>
#include <stdio.h>
#include <stdlib.h> 
#define max(a,b) (((a)>(b))?(a):(b))
#include "timer.h"
#include <string.h>

// Returns maximum amount of gold that can be collected 
// when journey started from first column and moves 
// allowed are right, right-up and right-down 

//cols = m, rows = n

long getMaxGold(long* gold, long n, long m) 
{ 
    // Create a table for storing longermediate results 
    // and initialize all cells to 0. The first row of 
    // goldMineTable gives the maximum gold that the miner 
    // can collect when starts that row 
    
    //change to calloc in optimized version !! 
    long* goldTable = (long *)malloc(n * m * sizeof(long));
    
    
    //initialize values to 0 (unnecessary with calloc!)
    for(long row = 0; row < n; row++){
        for (long col = 0; col < m; col++){
            goldTable[row*m + col] = 0;
        }
    }
  
    for (long col=n-1; col>=0; col--) 
    { 
        #pragma omp for
        for (long row=0; row<m; row++) 
        { 
            // Gold collected on going to the cell on the right(->) 
            long right = (col==n-1)? 0: goldTable[row*m + col+1]; 
  
            // Gold collected on going to the cell to right up (/) 
            long right_up = (row==0 || col==n-1)? 0: 
                            goldTable[(row-1)*m + col+1]; 
  
            // Gold collected on going to the cell to right down (\) 
            long right_down = (row==m-1 || col==n-1)? 0: 
                             goldTable[(row+1)*m + col+1]; 
  
            // Max gold collected from taking either of the 
            // above 3 paths 
            goldTable[row *m + col] = gold[row*m + col] + 
                              max(right, max(right_up, right_down)); 
                                                      
        } 
    } 
  
    // The max amount of gold collected will be the max 
    // value in first column of all rows 
    long res = goldTable[0]; 
    for (long i=1; i<m; i++) 
        res = max(res, goldTable[i*m]); 
    return res; 
} 


void printUsage(){
    printf("usage: ./goldMine n m fileInput\n");
    printf("n and m are dimensions of goldmine matrix.\nfileInput is an optional file argument which, if present, will be used to populate the matrix (for testing purposes).\nOtherwise, the matrix will be populated with random numbers.\n");
}
  
long getGoldFromFile(char filename[], long* gold, long n, long m){
    FILE *fp;
    long num;
    long fileResult; 
        
        
    fp = fopen(filename, "r");
        //check if valid:
    if(fp == NULL){
        printf("\nError opening file!\n");
        return -1;
    }
        
    fscanf(fp, "%ld", &num);
    if(feof(fp)){
        printf("\nError parsing file!\n");
        return -1;
    }
    fileResult = num;
    
    for(long row = 0; row < n; row++){
        for (long col = 0; col < m; col++){
            fscanf(fp, "%ld", &num);
            if(feof(fp)){
                printf("\nError parsing file!\n");
                return -1;
            }
            gold[row*m + col] = num;
        }
    }
    return fileResult;
}
    
int writeToFile(long* gold, long result, long n, long m){
    FILE *fp;
    char sN[15];
    char sM[15];
    snprintf(sN, sizeof(sN), "%ld", n);
    snprintf(sM, sizeof(sM), "%ld", m);
      
    char filename[30] = "test";
    strcat(filename, sN);
    strcat(filename, "x");
    strcat(filename, sM);
    strcat(filename, ".txt");
    printf("%s\n", filename);
    fp = fopen(filename, "w");
        //check if valid:
    if(fp == NULL){
        printf("\nError writing to file!\n");
        return -1;
    }
    
    fprintf(fp, "%ld\n", result);
    for(long row = 0; row < n; row++){
        for (long col = 0; col < m; col++){
            fprintf(fp, "%ld ", gold[row*m + col]);
        }
    }
    fprintf(fp, "\n");
    printf("Successfully wrote to file: %s\n", filename);
    fclose(fp);
    return 0;
}
  
  
// Driver Code 
int main(int argc, char* argv[]) 
{ 
    // initialize variables:
    double time1;
    
    long n;
    long m;
    
    
    // variables only used for writing / reading from file:
    int WRITETOFILE = 0; // default 0 = false: set to 1 to write matrix and result to file!
    
    int test = 0; // false
    char filename[100];
    long fileResult; 
    
    //parsing commandline arguments
    if(argc == 3){
        n = atoi(argv[1]);
        m = atoi(argv[2]);
    }
    else if(argc == 4){
        n = atoi(argv[1]);
        m = atoi(argv[2]);
        test = 1;
        strcpy(filename, argv[3]);
        WRITETOFILE = 0;    // don't write to file if reading from one
    }
    else{
        printUsage();
        return -1;
    }
        
    
    //initializing gold matrix:
    long* gold = (long *)malloc(n * m * sizeof(long));
    
    //check for error allocating memory:
    if(gold == NULL){
        printf("\nError allocating memory. n and m may be too large! \nApproximate max values for n*m is 2,025,000,000 (which is 45,340 * 45,340).\n");
        return -1;
    }
    
    srand(time(NULL));
    
    //if test = 0, populate "gold" with random longs in range [0, 9]:
    
    if(test == 0){
        for(long row = 0; row < n; row++){
            for (long col = 0; col < m; col++){
                gold[row*m + col] = rand() % 10;
                //printf("%ld ", gold[row*m + col]);
            }
        }//print("\n");
    }
    
    // otherwise, populate gold from file:
    else{
       fileResult = getGoldFromFile(filename, gold, n, m);
        if(fileResult == -1){
           return -1;
       }
    }
    
    //now, start timer (as all previous work is simply creating goldMine matrix
    initialize_timer ();
    start_timer();
    long res = getMaxGold(gold, n, m);
    printf("result: %ld\n", res); 
    stop_timer();
    time1 = elapsed_time ();
    
    
    //if testing off an 
    if(test != 0){
        if(fileResult == res){
            printf("Correct result!\n");
        }
        else{
            printf("Incorrect result! Result should be: %ld\n", fileResult);
        }
    }
    printf("Time taken: %lf\n" , time1);
    
    //check for WRITETOFILE flag:
  
    if(WRITETOFILE == 1){
        if(writeToFile(gold, res, n, m) == -1){
            return -1;
        }
    }
    return 0; 
} 
