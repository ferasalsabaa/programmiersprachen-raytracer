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
 
  Shape();
  Shape(std::string const& name,std::shared_ptr<Material> const& material);
  Shape(std::string const& name,std::shared_ptr<Material> const& material, glm::mat4 world_transform);
  Shape(Shape const& shape1);
  virtual ~Shape();
  
  virtual float area() const=0;
  virtual float volume() const=0;
  virtual bool intersect (Ray const& ray,float & t) const=0;
  virtual intersection_shape intersect_new (Ray const& ray,float & t) const=0;
  virtual std::ostream& print(std::ostream& os) const;
  virtual glm::vec3 get_normal(glm::vec3 const& schnittpunkt) const=0;
  std::shared_ptr<Material> get_material() const;


  virtual void translate(glm::vec3 const& p);
  virtual void scale(glm::vec3 const& s);
  virtual void rotate_x(float phi);
  virtual void rotate_y(float phi);
  virtual void rotate_z(float phi);


  std::string name() const;
  Material const& material() const;
  glm::mat4 world_transformation() const;
  glm::mat4 world_transformation_inv() const;

  void world_transformation(glm::mat4 const& mat);



  protected:
   std::shared_ptr<Material> material_;
   glm::mat4 world_transformation_
   {1,0,0,0,
    0,1,0,0,
    0,0,1,0,
    0,0,0,1};

   glm::mat4 world_transformation_inv_
   {1,0,0,0,
    0,1,0,0,
    0,0,1,0,
    0,0,0,1};


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