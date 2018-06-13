#include "Sphere.hpp"
#include <glm/vec3.hpp>
#include <math.h>

    Sphere::Sphere() : center_{0.0f}, radius_{0} {}

    Sphere::Sphere(glm::vec3 const& vec3, double const& radius) : center_{vec3}, radius_{radius} {}

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