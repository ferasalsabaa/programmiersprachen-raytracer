#ifndef Sphare_HPP
#define Sphare_HPP
#include"shape.hpp"
#include <glm/vec3.hpp>

class Sphere : public Shape 
{
public:
Sphere();
Sphere(glm::vec3 const& mittel_punkt,float const& radius);
float get_radius() const;
glm::vec3 get_mittel_punkt() const;

float area() const override ;
float volume()const override;

private:
glm::vec3 mittel_punkt_;
float radius_;
};


#endif