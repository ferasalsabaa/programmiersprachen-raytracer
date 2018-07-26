#ifndef box_HPP
#define box_HPP
#include"shape.hpp"
#include"ray.hpp"
#include <glm/vec3.hpp>
#include<iostream>
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
    
private:
    glm::vec3 maximum_;
    glm::vec3 minimum_;
};

#endif