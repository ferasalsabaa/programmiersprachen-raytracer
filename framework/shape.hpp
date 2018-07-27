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
  std::shared_ptr<Material> material_;
  Shape();
  Shape(std::string const& name,std::shared_ptr<Material> const& material);
   ~Shape();
  virtual float area() const=0;
  virtual float volume() const=0;
  virtual bool intersect (Ray const& ray,float & t) const = 0;
  virtual std::ostream& print(std::ostream& os) const;
  void set_name(std::string const& na);
  virtual void set_position_X(int) const=0;
  virtual void set_position_Y(int) const=0;
  virtual void set_position_Z(int) const=0;
  
  private:
  std::string name_;
  

};

std::ostream& operator <<(std::ostream& os, Shape const& s);


#endif