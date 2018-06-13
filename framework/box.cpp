#define CATCH_CONFIG_RUNNER

#include "box.hpp"

Box::Box() : maximum_{0.0f,0.0f,0.0f} , minimum_{0.0f,0.0f,0.0f}
{}
Box::Box(glm::vec3 const& maximum , glm::vec3 const& minimum) : maximum_{maximum} , minimum_{minimum}
{} 
glm::vec3 Box::get_maximum() const
{
    return maximum_;
}
glm::vec3 Box::get_minimum() const
{
    return minimum_;
}
float Box::area() const
{
  float length = get_maximum().x - get_minimum().x;
  float width = get_maximum().z - get_minimum().z;
  float hight = get_maximum().y - get_minimum().y;
  return 2*(length*width + width*hight + hight*length);
}
float Box::volume() const
{
    float length = get_maximum().x - get_minimum().x;
  float width = get_maximum().z - get_minimum().z;
  float hight = get_maximum().y - get_minimum().y;
  return hight*length*width;
    
}