//
//  main.c
//  Fly Swatter
//
//  Created by Hong Eunpyeong on 2016. 3. 20..
//  Copyright © 2016년  Hong Eunpyeong. All rights reserved.
//

#include <stdio.h>
#include <math.h>

typedef struct Coordinate{
    double x;
    double y;
}coordinate;

double get_x(double, double);
double get_y(double, double);
double area_arc(double, double);
double get_theta(double, double, double, double, double);

double get_x(double y, double r){
    return sqrt(r*r-y*y);
}
double get_y(double x, double r){
    return sqrt(r*r-x*x);
}
double get_theta(double x1, double y1, double x2, double y2, double r){
    return acos((2*r*r-(x1-x2)*(x1-x2)-(y1-y2)*(y1-y2))/(2*r*r));
}
double area_arc(double th, double r){
    return r*r*(th-sin(th))/2.0;
}


double vert(coordinate d, double f, double R, double t, double r, double g){
    double s;
    double tmp;
    double rt = R-t;    //안쪽 반지름
    char st;    //첫 gap(삼각형일때)
    
    double tx1, tx2, ty1, ty2;  //임시변수
    double th;  //각도
    double savedx = d.x;
    
    s = 0;
    st = 1;
    
    while(d.x*d.x + d.y*d.y < rt*rt){
        if((d.y+g)*(d.y+g)+(d.x+g)*(d.x+g) > rt*rt){
            if((d.x+g)*(d.x+g)+d.y*d.y > rt*rt){
                if(st){
                    tx1 = get_x(d.y, rt);
                    ty1 = rt / sqrt(2);
                    tx2 = get_x(ty1, rt);
                    th = get_theta(tx1, d.y, tx2, ty1, rt);
                    tmp = ((ty1 - d.y)*(tx1 - d.x) / 2.0); // 삼각형 면적
                    tmp += area_arc(th, rt);
                    st = 0;
                }else{
                    if((d.y+g)*(d.y+g)+d.x*d.x > rt*rt){
                        tx1 = get_x(d.y, rt);
                        ty1 = get_y(d.x, rt);
                        th = get_theta(tx1, d.y, d.x, ty1, rt);
                        tmp = (tx1-d.x)*(ty1-d.y)/2 + area_arc(th, rt);
                    }else{
                        double a1, a2;
                        tx1 = get_x(d.y, rt);
                        a1 = (tx1-d.x)*g/2.0;
                        tx2 = get_x(d.y+g, rt);
                        a2 = (tx2-d.x)*g/2.0;
                        tmp = a1+a2;
                        th = get_theta(tx1, d.y, tx2, d.y+g, rt);
                        tmp += area_arc(th, rt);
                    }
                }
            }else{
                if(st){
                    double a1, a2, a3;
                    tx1 = d.x+g;
                    ty2 = rt/sqrt(2.0);
                    tx2 = get_x(ty2, rt);
                    ty1 = get_y(tx1, rt);
                    a1 = (tx2 - d.x)*(ty2-d.y)/2.0;
                    a2 = (ty1-d.y)*(tx1-tx2);
                    a3 = (ty2-ty1)*(tx1-tx2)/2.0;
                    th = get_theta(tx1, ty1, tx2, ty2, rt);
                    tmp = a1+a2+a3+area_arc(th, rt);
                    st = 0;
                }else{
                    double a1, a2, a3;
                    tx1 = d.x+g;
                    ty1 = get_y(tx1, rt);
                    ty2 = d.y+g;
                    tx2 = get_x(ty2, rt);
                    a1 = (tx2-d.x)*g;
                    a2 = (ty1-d.y)*(d.x+g-tx2);
                    a3 = (ty2-ty1)*(tx1-tx2)/2.0;
                    th = get_theta(tx1, ty1, tx2, ty2, rt);
                    tmp = a1+a2+a3+area_arc(th, rt);
                }
            }
        } else{
            if(st){
                tmp = g*g/2.0;
                st = 0;
            }else{
                tmp = g*g;
            }
        }
        
        d.x += g+2*r;
        s += tmp;
    }
    
    d.x = savedx;
    return s;
}



double start(FILE* in){
    double f, R, t, r, g;   //f : 파리 반지름, R : 라켓 바깥 반지름, t : 라켓 두께, r : 줄 두께, g : 줄 간격
    double s;   //누적
    
    fscanf(in, "%lf", &f);
    fscanf(in, "%lf", &R);
    fscanf(in, "%lf", &t);
    fscanf(in, "%lf", &r);
    fscanf(in, "%lf", &g);
    
    
    if(2*f >= g) {      //gap이 좁을 경우 종료
        return 1.0;
    }
    
    t = t + f;  // 유효면적(?)
    r = r + f;
    g = g - 2*f;
    
    
    coordinate d;
    d.x = r;
    d.y = r;
    
    s = 0;
    while(d.y*d.y + d.x*d.x < (R-t)*(R-t)){
        s += vert(d, f, R, t, r, g);
        d.x += g+2*r;
        d.y += g+2*r;
    }
    
    s *= 8;

    return 1.0-s/(acos(-1)*R*R);
    
}

int main() {
    int tc;
    int i;
    FILE* in = fopen("C-large-practice.in", "r");
    FILE* out = fopen("C-practice.out", "w");
    
    if(in == NULL){
        fprintf(stderr, "no such file\n");
        return 1;
    }
    fscanf(in, "%d", &tc);
    
    
    for(i = 0; i < tc; i++){
        fprintf(out, "Case #%d: %f\n", i+1, start(in));
    }
    
    return 0;
}
