//
//  main.c
//  Milkshakes
//
//  Created by Hong Eunpyeong on 2016. 3. 18..
//  Copyright © 2016년  Hong Eunpyeong. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Flav{
    int f;
    int malt;
} flav;


flav make_flav(int, int);


int get_num(FILE* in){
    char tmp[10];
    int i = 0;
    
    tmp[0] = fgetc(in);
    
    while(tmp[0] == ' ' || tmp[0] == '\n'){         //remove spaces in front of the string
        tmp[0] = fgetc(in);
    }
    
    while(tmp[i] != ' ' && tmp[i] != '\n' && tmp[i] != EOF){        //get character until any space appears
        i++;
        tmp[i] = fgetc(in);
    }
    
    tmp[i] = '\0';
    return atoi(tmp);
}


void get_list(int n_of_cost, int* list_of_cost, flav** list_of_flav, FILE* in, FILE* out){
    int tmp;
    int i, j;
    int k = 0;
    
    
    for(i = 0; i < n_of_cost; i++){
        list_of_cost[i] = get_num(in);
        list_of_flav[i] = (flav*)malloc(list_of_cost[i]*sizeof(flav));
        
        for(j = 0; j < list_of_cost[i]; j++){
            tmp = get_num(in);
            list_of_flav[i][k++] = make_flav(tmp, get_num(in));           //subtract 1 from tmp since flavor begins with 1
            //fprintf(out, "%d %d ", list_of_flav[i][k-1].f, list_of_flav[i][k-1].malt);
        }
        k = 0;
       // fprintf(out, "\n");
    }
    
}


flav make_flav(int t, int m){
    flav f;
    f.f = t;
    f.malt = m;
    return f;
}

void init_list(int* list, int n){
    int i;
    for(i = 0; i < n; i++){
        list[i] = 0;
    }
}


void make_result(int n_of_cost, int n_of_flav, int* list_of_cost, flav** list_of_flav, FILE* out, int test_case){
    int i, j;
    int c = 0;
    flav fv;
    char flag;
    char sat;
    int tmpf = 0;
    int* result = (int*) malloc(n_of_flav*sizeof(int));
    
    init_list(result, n_of_flav);
    
    while(c <= n_of_flav){
        for(i = 0; i < n_of_cost; i++){
            if (list_of_cost[i] == c){
                
                flag = 1;
                for(j = 0; j < c; j++){
                    fv = list_of_flav[i][j];
                    
                    if (fv.malt == 0){
                        if(result[fv.f-1] == 0) {
                            flag = 0;
                            break;
                        }
                    } else{
                        if(result[fv.f-1] == 1) {
                            flag = 0;
                            break;
                        }
                        else tmpf = fv.f;
                    }
                }
                if(flag){
                    result[tmpf-1] = 1;
                }
            }
        }
        c++;
    }

    
    sat = 0;
    fprintf(out, "Case #%d: ", test_case);
    for(i = 0; i < n_of_cost; i++){

        for(j = 0; j < list_of_cost[i]; j++){
            if(list_of_flav[i][j].malt == result[list_of_flav[i][j].f-1]){
                sat = 1;
                break;
            }
        }

        if(sat == 0){
            fprintf(out, "IMPOSSIBLE\n");
            return;
        }
        sat = 0;
    }
    
    for(i = 0; i < n_of_flav; i++){
        fprintf(out, "%d ", result[i]);
    }
    fprintf(out, "\n");
}


int main(int argc, const char * argv[]) {
    FILE* in = fopen("B-large-practice.in.txt", "r");
    FILE* out = fopen("B-practice.out.txt", "w");
    
    if(in == NULL){
        fprintf(stderr, "no such file\n");
        return 1;
    }
    
    char tmp[10];
    int n_of_flav;
    int n_of_cost;
    int n_of_testc;
    int i;
    int *list_of_cost;
    flav **list_of_flav;
    
    
    fgets(tmp, 10, in);
    n_of_testc = atoi(tmp);
    
    for(i = 0; i < n_of_testc; i++){
        fgets(tmp, 10, in);
        n_of_flav = atoi(tmp);
        fgets(tmp, 10, in);
        n_of_cost = atoi(tmp);
        printf("%d %d\n", n_of_flav, n_of_cost);
        
        list_of_flav = (flav**)malloc(n_of_cost*sizeof(flav*));
        list_of_cost = (int*)malloc(n_of_cost*sizeof(int));
        
        get_list(n_of_cost, list_of_cost, list_of_flav, in, out);
        
        make_result(n_of_cost, n_of_flav, list_of_cost, list_of_flav, out, i+1);
    }
    
    fclose(in);
    fclose(out);
    return 0;
}
