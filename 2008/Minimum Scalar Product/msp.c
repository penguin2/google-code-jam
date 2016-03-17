//
//  main.c
//  gcj
//
//  Created by Hong Eunpyeong on 2016. 3. 17..
//  Copyright © 2016년  Hong Eunpyeong. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>


int comp (const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}


void get_vec(FILE* in, int* x, int n){
    char tmp[8];
    int i = 0;
    int k = 0;
    
    for(k = 0; k < n; k++){
        tmp[i] = fgetc(in);
        while(tmp[i] != ' ' && tmp[i] != EOF && tmp[i] != '\n'){
            i++;
            tmp[i] = fgetc(in);
        }
        x[k] = atoi(tmp);
        i = 0;
    }
    printf("\n");
}

int main() {
    FILE* in = fopen("A-large-practice.in", "r");
    FILE* out = fopen("A-large-practice.out", "w");
    char tmp[10];
    int test_case, n;
    int i, j;
    int x[800], y[800];
    long long int dot_prod = 0;
    
    fgets(tmp, 10, in);
    test_case = atoi(tmp);
    
    for(i = 0; i < test_case; i++){
        fgets(tmp, 5, in);
        printf("%s %d\n", tmp, i);
        n = atoi(tmp);
        
        get_vec(in, x, n);
        get_vec(in, y, n);
        qsort(x, n, sizeof(int), comp);
        qsort(y, n, sizeof(int), comp);
        
        for(j = 0; j < n; j++){
            
            dot_prod += (long)x[j]*(long)y[n-j-1];
            printf("%d %d %d %lld\n", i, x[j], y[n-j-1], dot_prod);
        }
        fprintf(out, "Case #%d: %lld\n", i+1, dot_prod);
        dot_prod = 0;
    }
    fclose(in);
    fclose(out);
}
