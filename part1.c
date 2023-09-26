#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int calculateSum (int start, int jump ){
    int sum = 0;
    for (int i=start; i<=(start-1+jump); i++) {
        sum += i;
    }
    return sum;
}

int main(int argc, const char * argv[]) {
    clock_t startTime = clock();
    int filedes[2];
    int NPROC, T;
    if(argc <= 2){
        printf("enter NPROC and T");
        exit(0);
    }

    NPROC = atoi(argv[1]);
    T = atoi(argv[2]);

    if(NPROC > T){
        printf("Error! NPROC is greater that T");
        exit(0);
    }
    // printf("%d  %d\n", NPROC, T);

    int x = T/NPROC;
    
     
    pipe(filedes);
    char writebuffer[80];
    char readsum[80];
    int sum = 0;
    
    for(int i = 0; i < NPROC; i++)
    {
        int lowerBound = i*x+1;
        if(i==NPROC-1){
            x+=(T%NPROC);
        }
        
        if(fork() == 0){ 
            int innerSum = calculateSum(lowerBound,x);
            sprintf(writebuffer,"%d",innerSum);
            int writing = write(filedes[1], &writebuffer, sizeof(writebuffer));
            if(writing < 0)
                perror("write");
            exit(0);
        }
    }
    wait(NULL);
    close(filedes[1]);
    while(read(filedes[0], readsum, sizeof(readsum))>0){
        sum+=atoi(readsum);
    }
        
    printf("Sum = %d\n",sum);
    clock_t endTime = clock();
    double ExecTime = (double) (endTime- startTime) / CLOCKS_PER_SEC;
    printf("Execution Time = %lf seconds\n", ExecTime);
    return 0;
}
