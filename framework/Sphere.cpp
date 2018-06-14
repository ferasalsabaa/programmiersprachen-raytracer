#include "Sphere.hpp"
#include <glm/vec3.hpp>
#include <math.h>
#include "ray.hpp"

    Sphere::Sphere() : center_{0.0f}, radius_{0} {}

    Sphere::Sphere(glm::vec3 const& vec3, double const& radius) : center_{vec3}, radius_{radius} {}

    Sphere::Sphere(glm::vec3 const& vec3, double const& radius, std::string const& name, Color const& color) :
        center_{vec3}, radius_{radius}, Shape(name, color) {}

    glm::vec3 Sphere::get_center() const {
        return center_;
    }

    double Sphere::get_radius() const {
        return radius_;
    }


    double Sphere::area () const {
        return 4*M_PI*pow(radius_,2);
    }
    
    double Sphere::volume() const {
        return (4.0f/3.0f)*M_PI*pow(radius_,3); //Integerdivision (4/3) --> wird abgeschnitten
    }

std::ostream& Sphere::print(std::ostream& os) const {
    Shape::print(os);
    os << "\n Radius: " << radius_ << "\n Zentrum: (" << center_.x << " , " << center_.y << " , " << center_.z << ")\n ";
    return os;
}

bool Sphere::intersect(Ray ray, float distance) const{
    return glm::intersectRaySphere(ray.origin, ray.direction , center_ , radius_ * radius_, distance);
}