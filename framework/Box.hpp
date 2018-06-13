#include <glm/vec3.hpp>
#include "Shape.hpp"


class Box : public Shape {
    
    public:
        Box();
        Box(glm::vec3 const& min_, glm::vec3 const& max_);
        glm::vec3 get_min() const;
        glm::vec3 get_max() const;
        double area() const override;
        double volume() const override; 

     private: 
        glm::vec3 min_;
        glm::vec3 max_;

  
};
