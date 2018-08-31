#ifndef Shape_HPP
#define Shape_HPP
#include<iostream>
#include<memory>
#include"color.hpp"
#include"ray.hpp"
#include<material.hpp>
struct intersection_shape;

class Shape
{
  public:
  std::shared_ptr<Material> material_;
  Shape();
  Shape(std::string const& name,std::shared_ptr<Material> const& material);
  Shape(Shape const& shape1);
  virtual ~Shape();
  
  virtual float area() const=0;
  virtual float volume() const=0;
  virtual bool intersect (Ray const& ray,float & t) const=0;
  virtual intersection_shape intersect_new (Ray const& ray,float & t) const=0;
  virtual std::ostream& print(std::ostream& os) const;
  virtual glm::vec3 get_normal(glm::vec3 const& schnittpunkt) const=0;


  private:
  std::string name_;
  

};

std::ostream& operator <<(std::ostream& os, Shape const& s);
struct intersection_shape{
	float distance;
	bool hit;
	glm::vec3 position; 
  glm::vec3 normal;
};

#endif