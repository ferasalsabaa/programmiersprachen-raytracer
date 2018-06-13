#define CATCH_CONFIG_RUNNER

#include "Sphere.hpp"
#include<math.h>

Sphere::Sphere() : mittel_punkt_{0.0f,0.0f,0.0f} , radius_{0.0f}
{}
Sphere::Sphere(glm::vec3 const& mittel_punkt,float const& radius) : mittel_punkt_{mittel_punkt} , radius_{radius}
{}
Sphere::Sphere(glm::vec3 const& mittel_punkt,float const& radius,std::string const& name,Color const& sphare_color) : mittel_punkt_{mittel_punkt} , radius_{radius},Shape(name,sphare_color)
{}
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
/*std::ostream& Circle::print(std::ostream& os) const
{
    os << "radius : "<<radius_ <<" center :(" << center_.x_ << ", "<< center_.y_ <<")" << "  name: "<<name_ <<" color"<<"( "<<color_circle_.r<<" , "<<color_circle_.g<<" , "<<color_circle_.b<<" )"<<"\n";
    return os;
}
std::ostream& operator<<(std::ostream& os, Circle const& c)
  {
    std::ostream::sentry const ostream_sentry(os);
    return ostream_sentry ? c.print(os) : os;
  }*/
