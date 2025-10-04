#pragma once

#include "../include/eqi_tri.hpp"
#include <vector>

class GEN_TRI_FRACTAL {
public:
    EQ_TRI SuperBaseTriangle;
    int NumberOfIterations;
    std::vector<EQ_TRI> OUTPUT_TRIANGLES = {};
    std::vector<EQ_TRI> NextITER_BASE_TRIANGLES = {};

    std::vector<EQ_TRI> gen_sub_triangles(EQ_TRI base);
    void gen_tri_fractal (int n_iter);

    GEN_TRI_FRACTAL(EQ_TRI _base, int _n_iter);
};
