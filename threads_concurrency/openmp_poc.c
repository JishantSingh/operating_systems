//
// Created by Jishant Singh on 11/10/20.
//

#include <stdio.h>
#include <omp.h>

int main (int argc, char *argv[]){
#pragma omp parallel
    {
        printf("this is parallel code\n");
}
return 0;
}