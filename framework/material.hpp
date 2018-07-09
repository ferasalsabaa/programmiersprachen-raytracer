#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include "color.hpp"
#include<iostream>

struct Material
{
    std::string name_;
    Color ka_;
    Color kd_;
    Color ks_;
    float m_;
Material() : ka_{0.0,0.0,0.0} , kd_{0.0,0.0,0.0} , ks_{0.0,0.0,0.0} , m_{0.0}
{}
Material(Color ka,Color kd,Color ks,float m) : ka_{ka} , kd_{kd} , ks_{ks} , m_{m}
{}
friend std::ostream& operator<<(std::ostream& os, Material const& s)
{
    os << "\n name  : " <<s.name_<< "\n ka : " << s.ka_.r<<","<<s.ka_.g<<","<<s.ka_.b<<
   "\n kd : " << s.kd_.r<<","<<s.kd_.g<<","<<s.kd_.b<<
   "\n ka : " << s.ks_.r<<","<<s.ks_.g<<","<<s.ks_.b<<
   "\n Spekularreflexionsexponenten "<<s.m_;
    return os;
}

};


#endif