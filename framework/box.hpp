#ifndef box_HPP
#define box_HPP
#include"shape.hpp"
#include"ray.hpp"
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <catch-1.5/catch.hpp>

#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>




class Box : public Shape 
{
public:
    Box();
    Box(glm::vec3 const& maximum,glm::vec3 const& minimum);
    Box(glm::vec3 const& maximum,glm::vec3 const& minimum,std::string const& name, std::shared_ptr<Material> const& material);
    glm::vec3 get_maximum() const;
    glm::vec3 get_minimum() const;
    float area() const override ;
    float volume()const override;
    std::ostream& print(std::ostream& os) const override;
    bool intersect (Ray const& ray,float & t) const override;
    glm::vec3 get_center() const override;
    float get_radius() const override;
    glm::vec3 get_normal(glm::vec3 const& schnittpunkt) const override; 
    

    glm::vec3 maximum_;
    glm::vec3 minimum_;
    
private:

};

#endif