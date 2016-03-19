//
//  main.c
//  Train Timetable
//
//  Created by Hong Eunpyeong on 2016. 3. 19..
//  Copyright © 2016년  Hong Eunpyeong. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Table{
    char name;
    int dep[2];
    int arr[2];
    char flag;
    char start;
}table;

/*
typedef struct Table{
    int n;
    _time* ta;
    _time* tb;
}table;

*/

char exist_prev(table time, table* tab, int n){
    int i;
    printf("%d:%d %d:%d\n", time.dep[0], time.dep[1], time.arr[0], time.arr[1]);
    for(i = 0; i < n; i++){
        if(tab[i].dep[0] < time.dep[0] && tab[i].flag == 0)
            return 1;
        else if(tab[i].dep[0] == time.dep[0] && tab[i].dep[1] < time.dep[1] && tab[i].flag == 0)
            return 1;
    }
    
    return 0;
}


table* next_train(table time, table* tab, int n, int turn_around){
    int i;
    table* tmp;
    tmp = NULL;
    for(i = 0; i < n; i++){
        if((tab[i].dep[0] - time.arr[0])*60 + (tab[i].dep[1] - time.arr[1]) >= turn_around)
            if(tab[i].flag == 0){
                if(tmp == NULL) tmp = &tab[i];
                else if(tmp->dep[0] > tab[i].dep[0] || (tmp->dep[0] == tab[i].dep[0] && tmp->dep[1] > tab[i].dep[1])) tmp = &tab[i];
            }
    }
    return tmp;
}


void link_time(table time, table* tabA, int na, table* tabB, int nb, int turn_around){
    table* tmp;
    if(time.name == 'A'){
        tmp = next_train(time, tabB, nb, turn_around);
        if(tmp == NULL)
            return;
       // printf("%d:%d %d:%d, %d:%d %d:%d\n", time.dep[0], time.dep[1], time.arr[0], time.arr[1], tmp->dep[0], tmp->dep[1], tmp->arr[0], tmp->arr[1]);
        tmp->flag = 1;
        link_time(*tmp, tabA, na, tabB, nb, turn_around);
    } else{
        tmp = next_train(time, tabA, na, turn_around);
        if(tmp == NULL){
            printf("Not Exist? %d:%d %d:%d\n", time.dep[0], time.dep[1], time.arr[0], time.arr[1]);

            return;
        }
        tmp->flag = 1;
        link_time(*tmp, tabA, na, tabB, nb, turn_around);
    }
}


table* search(table* tabA, table* tabB, int na, int nb){
    int i;
    for(i = 0; i < na; i++){
        if(tabA[i].flag == 0){
            printf("A : %d:%d %d:%d\n", tabA[i].dep[0], tabA[i].dep[1], tabA[i].arr[0], tabA[i].arr[1]);
            if(exist_prev(tabA[i], tabB, nb) == 0){
                printf("AAAAA\n");
                return &tabA[i];
            }
        }
    }
    
    for(i = 0; i < nb; i++){
        if(tabB[i].flag == 0){
            printf("B : %d:%d %d:%d\n", tabB[i].dep[0], tabB[i].dep[1], tabB[i].arr[0], tabB[i].arr[1]);
            if(exist_prev(tabB[i], tabA, na) == 0){
                printf("BBBBB\n");
                return &tabB[i];
            }
        }
    }
    return NULL;
}

void get_time(char* strD, char* strA, table*  t, int i, char c){
    char* tmp;
    tmp = strtok(strD, ":");
    t[i].dep[0] = atoi(tmp);
    tmp = strtok(NULL, " \n");
    t[i].dep[1] = atoi(tmp);
    
    tmp = strtok(strA, ":");
    t[i].arr[0] = atoi(tmp);
    tmp = strtok(NULL, " \n");
    t[i].arr[1] = atoi(tmp);
    
    t[i].flag = 0;
    t[i].start = 0;
    t[i].name = c;
}

int main() {
    FILE *in = fopen("B-large-practice.in", "r");
    FILE *out = fopen("B-practice.out", "w");
    int tc;
    int i, j;
    char tmp[20];
    char *t1, *t2;
    int resultA, resultB;
    
    
    if(in == NULL){
        fprintf(stderr, "no such file\n");
        return 1;
    }
    
    fgets(tmp, 10, in);
    tc = atoi(tmp);;
    
    for(i = 0; i < tc; i++){
        table* tabA;
        table* tabB;
        int na, nb;
        fgets(tmp, 10, in);
        int turn_around = atoi(tmp);
        
        //get NA, VB
        fgets(tmp, 10, in);
        t1 = strtok(tmp, " ");
        na = atoi(t1);
        t1 = strtok(NULL, " \n");
        nb = atoi(t1);
        
        
        //get timetable
        tabA = (table*)malloc(na*sizeof(table));
        tabB = (table*)malloc(nb*sizeof(table));
        
        for(j = 0; j < na; j++){
            fgets(tmp, 20, in);
            t1 = strtok(tmp, " ");
            t2 = strtok(NULL, " \n");
            
            get_time(t1, t2, tabA, j, 'A');
        }
        
        for(j = 0; j < nb; j++){
            fgets(tmp, 20, in);
            t1 = strtok(tmp, " ");
            t2 = strtok(NULL, " \n");
            
            get_time(t1, t2, tabB, j, 'B');
        }
        
        
        //
        resultA = 0;
        resultB = 0;
        while(1){
            table* time = search(tabA, tabB, na, nb);
            if(time == NULL) break;
            else{
                time->flag = 1;
                time->start = 1;
                //printf("%d:%d\n", time->dep[0], time->dep[1]);
                if(time->name == 'A') resultA++;
                else resultB++;
                link_time(*time, tabA, na, tabB, nb, turn_around);
            }
        }
        fprintf(out, "Case #%d: %d %d\n", i+1, resultA, resultB);
        free(tabA);
        free(tabB);
    }
    
    fclose(in);
    fclose(out);
    return 0;
}
