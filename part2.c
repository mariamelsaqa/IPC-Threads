#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int sum = 0;

typedef struct Bounds{
    int lowerBound;
    int UpperBound;
} bounds;

void *calculateSum (void* ptr){
    bounds *bound = (bounds*) ptr;
    pthread_mutex_t mutex;
    int partialSum = 0;
    for (int i=bound->lowerBound; i<=bound->UpperBound; i++) {
        partialSum += i;
    }
    pthread_mutex_lock(&mutex);
    sum += partialSum;
    pthread_mutex_unlock(&mutex);
    return 0;
}

int main(int argc, const char * argv[]) {
    clock_t startTime = clock();
    int threadsNum, T;

    if(argc <= 2){
        printf("enter number of threads and T");
        exit(0);
    }

    threadsNum = atoi(argv[1]);
    T = atoi(argv[2]);
    
    if(threadsNum > T){
        printf("Error! number of threads is greater that T");
        exit(0);
    }

//     printf("%d  %d\n", threadsNum, T);

    int x = T/threadsNum;

    
    bounds* bound = malloc(sizeof(bounds)*threadsNum);

    
    pthread_t* s = (pthread_t*) malloc(threadsNum*sizeof(pthread_t));

    
    for (int i=0; i<threadsNum; i++) {
        bound[i].UpperBound = i*x+x;
        
        
        bound[i].lowerBound = i*x+1;
        if(i==threadsNum-1){
            bound[i].UpperBound+=(T%threadsNum);
        }

//        printf("upper = %d\n", bound[i].UpperBound);
//        printf("lower = %d\n", bound[i].lowerBound);

        
        int iter = pthread_create(&s[i], NULL, calculateSum, (void*)&bound[i]);
        if(iter == 1)
        {
            perror("Threads");
        }
    }
    for (int i=0; i<threadsNum; i++) {
        pthread_join(s[i], NULL);}

    printf("sum = %d\n", sum);
    clock_t endTime = clock();
    double ExecTime = (double) (endTime- startTime) / CLOCKS_PER_SEC;
    printf("Execution Time = %lf seconds\n", ExecTime);
    return 0;
}
