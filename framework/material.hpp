#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include "color.hpp"
#include<iostream>

struct Material
{


Material() : name_{" "} ,ka_{0.0,0.0,0.0} , kd_{0.0,0.0,0.0} , ks_{0.0,0.0,0.0} , m_{0.0}, opacity_{1}, refraction_index_{0}
{}
Material(Color const& ka,Color const& kd,Color const& ks,float m,int opacity, float refraction_index ) : name_{" "},ka_{ka} , kd_{kd} , ks_{ks} , m_{m}, opacity_{opacity}, refraction_index_{refraction_index}
{}

friend std::ostream& operator<<(std::ostream& os, Material const& s)
{
    os << "\n name  : " <<s.name_<< "\n ka : " << s.ka_.r<<","<<s.ka_.g<<","<<s.ka_.b<<
   "\n kd : " << s.kd_.r<<","<<s.kd_.g<<","<<s.kd_.b<<
   "\n ka : " << s.ks_.r<<","<<s.ks_.g<<","<<s.ks_.b<<
   "\n Spekularreflexionsexponenten ist super"<<s.m_;
    return os;
}

    std::string name_;
    Color ka_;
    Color kd_;
    Color ks_;
    float m_;
    int opacity_;
    float refraction_index_;

};


#endif