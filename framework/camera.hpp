#ifndef camera_HPP
#define camera_HPP
#include <ray.hpp>
#include <glm/vec3.hpp>
#include <iostream>
#include <string>
#include <glm/gtx/intersect.hpp>

//Hallooo Theresa


struct Camera {

  

    Camera();
    Camera(std::string const& name, float aperture, glm::vec3 origin, glm::vec3 direction, glm::vec3 up);
    ~Camera();

    Ray shoot_ray(float x, float y, float width_, float height_);

    Ray shoot_ray1(float x, float y);

    glm::vec3 get_origin() const;

    glm::mat4 transform_camera();
    void translate(glm::vec3 const& p);
    void rotate_x(float phi); //check order!!!
    void rotate_y(float phi); //check order!!!
    void rotate_z(float phi); //check order!!!


 
    std::string name_;
    float aperture_;
    glm::vec3 origin_;
    glm::vec3 direction_;
    glm::vec3 up_;
    glm::mat4 transform_cam_;
    glm::mat4 transform_cam_inv_;
    
};



#endif