//
// Created by Jishant Singh on 08/10/20.
//

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum = 0;
void *f(void *p);
int main(int argc, char *argv[]){
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid,&attr,f,argv[1]);
    pthread_join(tid,NULL);
    printf("sum is %d\n",sum);
}

void* f(void* p){
    int n = atoi(p);
    for(int i=0;i<=n;i++){
        sum+=i;
    }
    pthread_exit(0);
}

