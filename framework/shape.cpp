#define CATCH_CONFIG_RUNNER
#include "shape.hpp"
#include<iostream>

Shape::Shape() : name_{""} , material_{}
{std::cout<<"shape constructor ..."<<"\n";}
Shape::Shape(std::string const& name,std::shared_ptr<Material> const& material) : name_{name} , material_{material}
{std::cout<<"shape constructor ..."<<"\n";}
Shape::~Shape()
{std::cout<<"shape destructor ..."<<"\n";}

std::ostream& Shape::print(std::ostream& os) const
{
   os << "\n name  : " <<name_<< "\n material : ";
   return os;
}
std::ostream& operator<<(std::ostream& os, Shape const& s)
{
    s.print(os);
    return os;
}

