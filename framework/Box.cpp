#include "Box.hpp"
#include <glm/vec3.hpp>
#include <math.h>

Box::Box() : min_{0.0f}, max_{0.0f}, Shape() {} //bei Vektoren, wenn ich nur einen Wert eingebe, werden alle auf diesen gesetzt

Box::Box(glm::vec3 const& min, glm::vec3 const& max) :
     min_{min}, max_{max}, Shape() {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max, std::string const& name, Color const& color) :
     min_{min}, max_{max}, Shape(name, color){}


glm::vec3 Box::get_min() const {
    return min_;
}

glm::vec3 Box::get_max() const {
    return max_;
}

double Box::area() const {
    double width = max_.x - min_.x;
    double height = max_.y - min_.y;
    double depth = max_.z - min_.z;
    return (2*width*height)+(2*height*depth)+(2*width*depth);

}


double Box::volume() const{
    double width = max_.x - min_.x;
    double height = max_.y - min_.y;
    double depth = max_.z - min_.z;

    return width*depth*height;
}