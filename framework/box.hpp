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
    Box(glm::vec3 const& minimum, glm::vec3 const& maximum);
    Box(glm::vec3 const& minimum, glm::vec3 const& maximum,std::string const& name, std::shared_ptr<Material> const& material);
    glm::vec3 get_minimum() const;
    glm::vec3 get_maximum() const;
    float area() const override ;
    float volume()const override;
    std::ostream& print(std::ostream& os) const override;
    bool intersect (Ray const& ray,float & t) const override;

    intersection_shape intersect_new (Ray const& ray,float & t) const override;
    bool intersect_box (Ray const& ray, float& t, glm::vec3& normal) const;

    glm::vec3 get_center() const override;
    float get_radius() const override;
    glm::vec3 get_normal(glm::vec3 const& schnittpunkt) const override; 
    glm::vec3 get_normal_box(int x) const;
    
    
private:
    glm::vec3 minimum_;
    glm::vec3 maximum_;

};

#endif