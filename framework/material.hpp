#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include <color.hpp>

struct Material
{
    std::string name_;
    Color ka;
    Color kd;
    Color ks;
    float m;

};

#endif