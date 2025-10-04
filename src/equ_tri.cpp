#include "../include/eqi_tri.hpp"

#include <cmath>
#include <SDL2/SDL.h>

#define PI 3.1415

EQ_TRI::EQ_TRI( int _x1, int _y1, int _c_x,int _c_y) : c_x(_c_x), c_y(_c_y) , x1(_x1) , y1(_y1){
    float r = sqrt(pow(x1-c_x, 2) + pow(y1-c_y, 2));

    theta1 = std::asinh(y1/x1) * 180/PI;
    theta2 = theta1 + 120;
    theta3 = theta2 + 120;

    x2 = r*cos(theta2 * PI/180); y2 = r*sin(theta2 * PI/180);
    x3 = r*cos(theta3 * PI/180); y3 = r*sin(theta3 * PI/180);

    m1x =  (x1+x2)/2;
    m1y =  (y1+y2)/2;

    m2x =  (x2+x2)/2;
    m2y =  (y2+y3)/2;

    m3x =  (x1+x3)/2;
    m3y =  (y1+y3)/2;
}

EQ_TRI::EQ_TRI( double _x1, double _y1, double _x2, double _y2, double _x3, double _y3) :
    x1(_x1) , y1(_y1), x2(_x2), y2(_y2), x3(_x3), y3(_y3){
    m1x =  (x1+x2)/2;
    m1y =  (y1+y2)/2;

    m2x =  (x2+x2)/2;
    m2y =  (y2+y3)/2;

    m3x =  (x1+x3)/2;
    m3y =  (y1+y3)/2;

    float r = sqrt(pow(x1-c_x, 2) + pow(y1-c_y, 2));

    theta1 = std::asinh(y1/x1) * 180/PI;
    theta2 = theta1 + 120;
    theta3 = theta2 + 120;
}
