#define CATCH_CONFIG_RUNNER
#include "shape.hpp"
#include<iostream>

Shape::Shape() : name_{""} , shape_color_{0.0,0.0,0.0}
{std::cout<<"shape constructor ..."<<"\n";}
Shape::Shape(std::string const& name,Color const& shape_color) : name_{name} , shape_color_{shape_color}
{std::cout<<"shape constructor ..."<<"\n";}
Shape::~Shape()
{std::cout<<"shape destructor ..."<<"\n";}

std::ostream& Shape::print(std::ostream& os) const
{
   os << "\n name  : " <<name_<< "\n color : " << shape_color_.r<<"  "<<shape_color_.g<<"  "<<shape_color_.b;
   return os;
}
std::ostream& operator<<(std::ostream& os, Shape const& s)
{
    s.print(os);
    return os;
}

