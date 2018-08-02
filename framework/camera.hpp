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


    Ray shoot_ray(float x, float y, float width_, float height_) const {

        // // //normalize grid range 0,1
        // float ndc_x = (x+0.5)/width_; //0.5 to go through middle of pixel
        // float ndc_y = (y+0.5)/height_;
        // // //calculate image aspect ratio
        // float aspect_ratio = width_/height_;
        // //change grid range to -1,1
        // float px_screen = (2*ndc_x-1)*aspect_ratio;
        // float py_screen = (1-2*ndc_y); //if i add -1 at end, will be the wrong way around

        // float pix_cam_x = px_screen * tan(aperture_/2);
        // float pix_cam_y = py_screen * tan(aperture_/2);


        glm::vec3 rayOrigin{0,0,0};
        glm::vec3 rayDirection = {(x-width_/2), (y-height_/2), -(width_/2)/tan(aperture_/2)}; //check Adrians note!!!
        // glm::vec3 rayDirection = glm::vec3(pix_cam_x, pix_cam_y, -1);
        // rayDirection = glm::normalize(rayDirection - rayOrigin); 
        return Ray{rayOrigin,rayDirection};

    }


     Ray shoot_ray1(float x, float y) const{
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