#ifndef camera_HPP
#define camera_HPP
#include <glm/vec3.hpp>
#include <iostream>

class Camera {

    public:
    std::string name_;
    float aperture_;
    glm::vec3 origin_;
    glm::vec3 direction_;

    

    Camera() : name_{""}, aperture_{90}, origin_{0.0,10.0,10.0}, direction_{0.0,0.0,-1} {}
    Camera(std::string const& name, float aperture, glm::vec3 origin, glm::vec3 direction) :
     name_{name}, aperture_{aperture}, origin_ {origin}, direction_{direction} {}


    private:
    
};



#endif