#ifndef Shape_HPP
#define Shape_HPP
#include<iostream>
#include<memory>
#include"color.hpp"
#include"ray.hpp"
#include<material.hpp>
class Shape
{
  public:
  Shape();
  Shape(std::string const& name,std::shared_ptr<Material> const& material);
   ~Shape();
  virtual float area() const=0;
  virtual float volume() const=0;
  virtual bool intersect (Ray const& ray,float & t) const = 0;
  virtual std::ostream& print(std::ostream& os) const;
  
  private:
  std::string name_;
  std::shared_ptr<Material> material_;

};
std::ostream& operator <<(std::ostream& os, Shape const& s);



#endif