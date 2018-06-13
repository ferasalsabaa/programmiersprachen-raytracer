#define CATCH_CONFIG_RUNNER
#include "shape.hpp"
#include<iostream>

Shape::Shape() : name_{""} , shape_color_{0.0,0.0,0.0}
{}
Shape::Shape(std::string const& name,Color const& shape_color) : name_{name} , shape_color_{shape_color}
{}
std::ostream& Shape::print(std::ostream& os) const
{
   os << "name  : " <<name_<< "color : " << shape_color_.r<<"  "<<shape_color_.g<<"  "<<shape_color_.b;
   return os;
}
std::ostream& operator<<(std::ostream& os, Shape const& s)
{
    s.print(os);
    return os;
}

