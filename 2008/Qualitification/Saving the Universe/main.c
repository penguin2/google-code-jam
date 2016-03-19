//
//  main.c
//  Saving the Universe
//
//  Created by Hong Eunpyeong on 2016. 3. 19..
//  Copyright © 2016년  Hong Eunpyeong. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_num(FILE* f){
    char tmp[10];
    fgets(tmp, 10, f);
    return atoi(tmp);
}

void get_far(char** q_list, char** s_list, int q, int s, int* c){
    int i;
    int present = *c;
    int far = present;
    int tmp = present;
    for(i = 0; i < s; i++){
        tmp = present;
        while(tmp < q && strcmp(q_list[tmp], s_list[i]) != 0){
            tmp++;
        }
        if(far < tmp){
            far = tmp;
        }
    }
    *c = far;
}


int main(int argc, const char * argv[]) {
    FILE *in = fopen("A-large-practice.in", "r");
    FILE *out = fopen("A-practice.out", "w");
    int tc;
    int i, j;
    int c;
    int result;
    const int MAX_LEN = 120;
    if(in == NULL){
        fprintf(stderr, "no such file\n");
        return 1;
    }
    tc = get_num(in);
    
    for(i = 0; i < tc; i++){
        int s, q;
        char **s_list;
        char **q_list;
        s = get_num(in);

        s_list = (char**)malloc(s*sizeof(char*));
        
        for(j = 0; j < s; j++){
            s_list[j] = (char*)malloc(MAX_LEN*sizeof(char));
            fgets(s_list[j], MAX_LEN, in);
        }
        
        q = get_num(in);
        q_list = (char**)malloc(q*sizeof(char*));
        for(j = 0; j < q; j++){
            q_list[j] = (char*)malloc(MAX_LEN*sizeof(char));
            fgets(q_list[j], MAX_LEN, in);
        }
        
        c = 0;
        result = 0;
        while(1){
            get_far(q_list, s_list, q, s, &c);
            result++;
            if (c == q){
                result--;
                break;
            }
        }
        
        fprintf(out, "Case #%d: %d\n", i+1, result);
        for(j = 0; j < s; j++){
            free(s_list[j]);
        }
        for(j = 0; j < q; j++){
            free(q_list[j]);
        }
        free(s_list);
        free(q_list);
    }
    
    fclose(in);
    fclose(out);
    return 0;
}
