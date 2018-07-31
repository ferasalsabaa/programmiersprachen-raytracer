#ifndef camera_HPP
#define camera_HPP
#include <glm/vec3.hpp>
#include <iostream>
#include <glm/gtx/intersect.hpp>
#include <ray.hpp>

class Camera {

    public:
    std::string name_;
    float aperture_;
    glm::vec3 origin_;
    glm::vec3 direction_;
    glm::vec3 up_; 

    

    Camera() : name_{""}, aperture_{90}, origin_{0.0,10.0,10.0}, direction_{0.0,0.0,-1}, up_{0,1,0} {}
    Camera(std::string const& name, float aperture, glm::vec3 origin, glm::vec3 direction, glm::vec3 up) :
     name_{name}, aperture_{aperture}, origin_ {origin}, direction_{direction}, up_{up} {}

     Ray shoot_ray(float x, float y) const{
		glm::vec3 right=glm::cross(direction_,up_); //垂直矢量
		glm::vec3 up=glm::cross(right,direction_); 
		float fovBereich=tan(aperture_*(M_PI*0.5f/180))*2;
		glm::vec3 r=right*( (x-0.5f)*fovBereich );
		glm::vec3 u=up*( (y-0.5f)*fovBereich );
		glm::vec3 tmp=direction_+r+u;
		return Ray{origin_,glm::normalize(tmp)};
	}


    private:
    
};



#endif