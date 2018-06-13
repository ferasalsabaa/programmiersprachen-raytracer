#ifndef box_HPP
#define box_HPP
#include"shape.hpp"
#include <glm/vec3.hpp>
class Box : public Shape 
{
public:
Box();
Box(glm::vec3 const& maximum,glm::vec3 const& minimum);
Box(glm::vec3 const& maximum,glm::vec3 const& minimum,std::string const& name, Color const& box_color);
glm::vec3 get_maximum() const;
glm::vec3 get_minimum() const;
float area() const override ;
float volume()const override;
private:
glm::vec3 maximum_;
glm::vec3 minimum_;
};

#endif