#ifndef Shape_HPP
#define Shape_HPP
#include<iostream>
#include"color.hpp"
class Shape
{
  public:
  Shape();
  Shape(std::string const& name,Color const& shape_color);
  virtual float area() const=0;
  virtual float volume() const=0;
  virtual std::ostream& print(std::ostream& os) const;
  private:
  std::string name_;
  Color shape_color_;

};
std::ostream& operator <<(std::ostream& os, Shape const& s);



#endif