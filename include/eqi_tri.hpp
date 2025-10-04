#pragma once

#include <cmath>
#include <SDL2/SDL.h>

#define PI 3.1415

class EQ_TRI {
public:
    double x1,x2,x3;
    double y1,y2,y3;
    double c_x,c_y;

    double m1x,m1y, m2x,m2y, m3x,m3y;

    float theta1 ,theta2, theta3;

    EQ_TRI( int _x1, int _y1, int _c_x,int _c_y);
    EQ_TRI( double _x1, double _y1, double _x2, double _y2, double _x3, double _y3);
};
