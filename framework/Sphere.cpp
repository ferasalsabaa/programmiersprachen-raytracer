#define CATCH_CONFIG_RUNNER

#include "Sphere.hpp"
#include "ray.hpp"
#include<math.h>
#include<glm/glm.hpp>
#include<glm/gtx/intersect.hpp>


Sphere::Sphere() : Shape() , mittel_punkt_{0.0f,0.0f,0.0f} , radius_{0.0f} {
    std::cout<<"sphere constructor 1"<<"\n";
    }

Sphere::Sphere(glm::vec3 const& mittel_punkt,float const& radius) : Shape(), mittel_punkt_{mittel_punkt} , radius_{radius} {
    std::cout<<"sphere constructor 2"<<"\n";
    }

Sphere::Sphere(glm::vec3 const& mittel_punkt,float const& radius,std::string const& name,std::shared_ptr<Material> const& material) : 
    mittel_punkt_{mittel_punkt} , radius_{radius}, Shape(name,material) {}
Sphere::~Sphere()
{
    std::cout<<"sphere destructor"<<"\n";
}
float Sphere::get_radius() const
{
    return radius_;
}
glm::vec3 Sphere::get_mittel_punkt() const
{
    return mittel_punkt_;
}
float Sphere::area() const
{
  return 4 * pow(get_radius(),2) * M_PI;
}
float Sphere::volume() const
{
  return (4.0f/3.0f) * M_PI * (pow(get_radius(),3));
}
std::ostream& Sphere::print(std::ostream& os) const
{   Shape::print(os);
    os<<"\n radius : "<<radius_<<"\n center : " <<"\n x "<<mittel_punkt_.x<<" y "<<mittel_punkt_.y<<" z "<<mittel_punkt_.z<<"\n";
    return os;
}
bool Sphere::intersect(Ray const& ray,float & distance) const
{

glm::vec3 v = glm::normalize(ray.direction); //ohne ende
//auto a = ray.direction = {0.0f,0.0f,1.0f};

return glm::intersectRaySphere(
ray.origin,v,
mittel_punkt_,
radius_ * radius_, // squared radius !!!   
distance);
}