#ifndef triangle_HPP
#define triangle_HPP

#include"ray.hpp"
#include "shape.hpp"
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <math.h>

class Triangle : public Shape
{
    public:
    Triangle();
    Triangle(glm::vec3 const& a,glm::vec3 const& b,glm::vec3 const& c,std::string const& name, std::shared_ptr<Material> const& material);
  
    bool intersect (Ray const& ray,float & t) const override;
    glm::vec3 get_normal(glm::vec3 const& schnittpunkt) const override;
    intersection_shape intersect_new (Ray const& ray,float & t) const;

    ~Triangle();

float area() const override ;
float volume()const override;
glm::vec3 get_center() const override;
std::ostream& print(std::ostream& os) const override;
float get_radius() const override;





    private:
    glm::vec3 a_;
    glm::vec3 b_;
    glm::vec3 c_;


};

#endif