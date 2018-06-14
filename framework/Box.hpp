#ifndef BOX_HPP
#define BOX_HPP
#include <glm/vec3.hpp>
#include "Shape.hpp"
#include <string>


class Box : public Shape {
    
    public:
        Box();
        Box(glm::vec3 const& min_, glm::vec3 const& max);
        Box(glm::vec3 const& min_, glm::vec3 const& max_, std::string const& name, Color const& color);
        glm::vec3 get_min() const;
        glm::vec3 get_max() const;
        double area() const override;
        double volume() const override; 
        std::ostream& print(std::ostream& os) const override;

     private: 
        glm::vec3 min_;
        glm::vec3 max_;

  
};

#endif