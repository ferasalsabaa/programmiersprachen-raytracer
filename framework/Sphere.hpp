#ifndef Sphare_HPP
#define Sphare_HPP
#include"shape.hpp"
#include"ray.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/vec3.hpp>

class Sphere : public Shape 
{
public:
Sphere();
~Sphere();
Sphere(glm::vec3 const& mittel_punkt,float const& radius);
Sphere(glm::vec3 const& mittel_punkt,float const& radius,std::string const& name,std::shared_ptr<Material> const& material);
float get_radius() const override;
glm::vec3 get_mittelpunkt() const;
glm::vec3 get_normal(glm::vec3 const& schnittpunkt) const override;


float area() const override ;
float volume()const override;
glm::vec3 get_center() const override;
std::ostream& print(std::ostream& os) const override;
bool intersect(Ray const& ray,float & distance) const override;

private:
glm::vec3 mittelpunkt_;
float radius_;

};
//std::ostream& operator<<(std::ostream& os , Shape const& s);


#endif