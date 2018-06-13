#include "Shape.hpp"

Shape::Shape() : name_{"shape"}, color_{0.0f, 0.0f, 0.0f} {}

Shape::Shape(std::string const& name, Color const& color) : name_{name}, color_{color} {}

std::ostream& Shape::print(std::ostream& os) const {
    os << "Name:" << name_ << "\n Color: (" << color_.r << ", " << color_.g <<  ", " << color_.b << ")\n" ;
    return os;
}

std::ostream& operator <<(std::ostream& os, Shape const& s) {
   s.print(os);
   return os;
}