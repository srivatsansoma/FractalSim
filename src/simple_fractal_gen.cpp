#include "../include/simple_fractal_gen.hpp"

#include "../include/eqi_tri.hpp"
#include <vector>

GEN_TRI_FRACTAL::GEN_TRI_FRACTAL(EQ_TRI _base, int _n_iter) : SuperBaseTriangle(_base) , NumberOfIterations(_n_iter) {}

void GEN_TRI_FRACTAL::gen_tri_fractal (int n_iter){
    NextITER_BASE_TRIANGLES = {SuperBaseTriangle};

    for (int i = 0; i<n_iter; i++){
        std::vector<EQ_TRI> next = {};
        for (EQ_TRI tri :  NextITER_BASE_TRIANGLES){
            std::vector<EQ_TRI> t_next = gen_sub_triangles(tri);
            for (EQ_TRI t_tri : t_next) next.push_back(t_tri);
        }

        NextITER_BASE_TRIANGLES = {};
        for (EQ_TRI t_tri : next) NextITER_BASE_TRIANGLES.push_back(t_tri);
    }
}

std::vector<EQ_TRI> GEN_TRI_FRACTAL::gen_sub_triangles(EQ_TRI base){
    EQ_TRI new_triangle(base.x1, base.y1, base.c_x, base.c_y);
    OUTPUT_TRIANGLES.push_back(new_triangle);

    EQ_TRI base1(base.x1, base.y1, base.m2x, base.m2y, base.m3x,base.m3y);
    EQ_TRI base2(base.x2, base.y2, base.m1x, base.m1y, base.m2x,base.m2y);
    EQ_TRI base3(base.x3, base.y3, base.m2x, base.m2y, base.m1x,base.m1y);

    return {base1, base2, base3};
}
