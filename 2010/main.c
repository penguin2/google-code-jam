//
//  main.c
//  google_pre_problem
//
//  Created by Hong Eunpyeong on 2016. 3. 16..
//  Copyright © 2016년  Hong Eunpyeong. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void find_pair(int list_i[], int i_num, int c, int pair[]){
    int i, j;
    for(i = 0; i < i_num-1; i++){
        for(j = i+1; j < i_num; j++){
            if(list_i[j] < c){
                if (list_i[i] + list_i[j] == c){
                    if(list_i[i] <= list_i[j]){
                        pair[0] = list_i[i];
                        pair[1] = list_i[j];
                    } else{
                        pair[0] = list_i[j];
                        pair[1] = list_i[i];
                    }
                    return;
                }
            }
        }
    }
}

int main() {
    FILE *in = fopen("A-small-practice.in", "r");
    FILE *out = fopen("A-small-practice.out", "w");
    
    char case_num[20];
    char C[5];
    char I[5];
    char list_I[4000];
    int list_i[100];
    int c, i, j;
    int c_n, i_num;
    int pair[2];
    
    if (in == NULL) {
        fprintf(stderr, "no file\n");
        exit(1);
    }
    
    fgets(case_num, 20, in);
    
    c_n = atoi(case_num);
    
    for(i = 0; i < c_n; i++){
        fgets(C, 5, in);
        c = atoi(C);
        printf("%d\n", c);
        fgets(I, 5, in);
        i_num = atoi(I);
        fgets(list_I, 4000, in);
        char *tmp;
        tmp = strtok(list_I, " ");
        for(j = 0; j < i_num; j++){
            list_i[j] = atoi(tmp);
            tmp = strtok(NULL, " ");
        }
        
        find_pair(list_i, i_num, c, pair);
        fprintf(out, "Case #%d: %d %d\n", i+1, pair[0], pair[1]);
    }
}
