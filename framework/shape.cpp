#define CATCH_CONFIG_RUNNER
#include "shape.hpp"
#include<iostream>

Shape::Shape() : name_{""} , material_{} {}

Shape::Shape(std::string const& name,std::shared_ptr<Material> const& material) : name_{name} , material_{material} {}

Shape::Shape(Shape const& shape1): name_{shape1.name_} , material_{shape1.material_} {}

Shape::~Shape() {
}


std::ostream& Shape::print(std::ostream& os) const {
   os << "\n name  : " <<name_<< "\n  ";
   return os;
}

std::ostream& operator<<(std::ostream& os, Shape const& s) {
    s.print(os);
    return os;
}




